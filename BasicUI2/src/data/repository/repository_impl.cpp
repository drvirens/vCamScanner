//
//  repository_impl.cpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "repository_impl.hpp"
#include "base_model.hpp"
#include "packer.hpp"
#include "unpacker.hpp"
#include "db_data.hpp"
#include "db_key_value_reader_writer.hpp"
#include "MurmurHash3.h"
#include "trace.h"
#include "primary_key.hpp"
#include "record_criterion.hpp"

// -----------------------------------------------------------------------------
enum vsERepositoryRecordType
	{
	vsERepositoryRecordTypeUndefined,
	vsERepositoryRecordTypeUser
	};
// -----------------------------------------------------------------------------
class vsValueRecord
	{
public:
	//for packing
	vsValueRecord(vs_uint32_t aModelSize,
								vsERepositoryRecordType aModelType,
								vs_uint8_t* aActualRecordDump);
	//for unpacking
	vsValueRecord();
	
	~vsValueRecord();
	bool pack(TPacker& aPacker);
	bool unPack(TUnPacker& aUnpacker);
	
	vs_uint32_t recordSize() const;
	//needed for unpacking model
	vs_uint8_t* actualRecordDump() const { return iActualRecordDump; }
	vs_uint32_t modelSize() const { return iModelSize; }
	
private: //layout of the DBRecord
	vs_uint32_t iRecordSize;
	vs_uint8_t iModelType; //vsERepositoryRecordType
	vs_uint32_t iModelSize; //in terms of bytes
	vs_uint8_t* iActualRecordDump;
	
private: //house keeping
	bool iShouldDelete;
	};
// -----------------------------------------------------------------------------
vsValueRecord::vsValueRecord(vs_uint32_t aModelSize,
								vsERepositoryRecordType aModelType,
								vs_uint8_t* aActualRecordDump)
	: iModelSize(aModelSize)
	, iModelType(aModelType)
	, iActualRecordDump(aActualRecordDump)
    , iShouldDelete(false)
	{ TRACE
	iRecordSize = sizeof(vs_uint32_t)		+ //how big is this record?
								sizeof(vs_uint8_t)		+ //what kind of record is stored here?
								sizeof(vs_uint32_t)		+ //how big is the raw data?
								iModelSize;							//how big is the model itself?
	}
vsValueRecord::vsValueRecord()
	: iModelSize(0)
	, iModelType(vsERepositoryRecordTypeUndefined)
	, iActualRecordDump(0)
	, iShouldDelete(false)
	{
	}
vsValueRecord::~vsValueRecord()
	{ TRACE
	if (iShouldDelete)
		{
		delete [] iActualRecordDump;
		iActualRecordDump = 0;
		}
	}

vs_uint32_t vsValueRecord::recordSize() const
	{ TRACE
	return iRecordSize;
	}
bool vsValueRecord::pack(TPacker& aPacker)
	{ TRACE
	bool ret = false;
	while (true)
		{
		if ( !(aPacker.writeUint32(iRecordSize)) ) {break;}
		if ( !(aPacker.writeChars((const vs_int8_t*)&iModelType, sizeof(vs_uint8_t))) ) {break;}
		if ( !(aPacker.writeUint32(iModelSize)) ) {break;}
		if ( !(aPacker.writeChars((const vs_int8_t*)iActualRecordDump, iModelSize)) ) {break;}
		ret = true;
		break;
		} //while end
	return ret;
	}
bool vsValueRecord::unPack(TUnPacker& aUnpacker)
	{ TRACE
	bool ret = false;
	while (true)
		{
		if (!( aUnpacker.readUint32(iRecordSize) )) { break; }
		aUnpacker.setMaxLen(iRecordSize); //now that we know how large is the record, adjust it here
		if (!( aUnpacker.readChars((vs_int8_t*)&iModelType, sizeof(vs_uint8_t)) )) { break; }
		if (!( aUnpacker.readUint32(iModelSize) )) { break; }
		iActualRecordDump = new vs_uint8_t[iModelSize];
		if (!iActualRecordDump)
			{
			LOG("OOM - vsValueRecord::unPack");
			break;
			}
		iShouldDelete = true;
		if (!( aUnpacker.readChars((vs_int8_t*)iActualRecordDump, iModelSize) )) { break; }
		ret = true;
		break;
		} //while end
	return ret;
	}

// -----------------------------------------------------------------------------
static void doParse(vsTData dbKey, vsTData dbValue, vsModelBase& aPrimaryKeyedModel);
static void doParse(vsTData dbKey, vsTData dbValue, vsModelBase& aPrimaryKeyedModel)
    {
    	//how big is the record? first 4 bytes will us that
	TUnPacker recordUnPacker;
	vs_int32_t bufLen = sizeof(vs_uint32_t);

	recordUnPacker.setBuffer((vs_uint8_t*)dbValue.data());
	recordUnPacker.setBufferLength((vs_int32_t)0);
	recordUnPacker.setMaxLen(bufLen);
	
	vsValueRecord decoder;
	bool ret = decoder.unPack(recordUnPacker);
	ASSERT(ret);
	if (!ret)
		{
		LOG("\t vsRepository::doGet: something went wrong while unpacking dbrecord \n");
		return;
		}
		
	//decoder has raw bytes for our actual model - unpack it now
	vs_uint8_t* actualRecordDump = decoder.actualRecordDump();
	vs_uint32_t modelSize = decoder.modelSize();
	
	ASSERT(0 != actualRecordDump);
	ASSERT(modelSize > 0);
	
	TUnPacker modelDecoder;
	modelDecoder.setBuffer((vs_uint8_t*)actualRecordDump);
	modelDecoder.setBufferLength((vs_int32_t)0);
	modelDecoder.setMaxLen(modelSize);
	
	aPrimaryKeyedModel.unPack(modelDecoder);
    }
    
// -----------------------------------------------------------------------------
vsRepository::vsRepository(vsIKeyValueStore& aKeyValueStore)
	{ TRACE
	iKeyValueStore.reset(&aKeyValueStore);
	}
vsRepository::~vsRepository()
	{ TRACE
	}
// -----------------------------------------------------------------------------
#pragma mark - put
// -----------------------------------------------------------------------------
void vsRepository::put(vsModelBase& aModel, function<void(const vsModelBase&)> aCompletionBlock)
	{ TRACE
	ASSERT(0 != iKeyValueStore);
	std::function<void(vsIKeyValueReaderWriter&)> readWriteBlock = [&](vsIKeyValueReaderWriter& aReaderWriter)
		{
		doPut(aModel, aReaderWriter);
		aCompletionBlock(aModel);
		};
		
	iKeyValueStore->readWrite(readWriteBlock);
	}

void vsRepository::doPut(vsModelBase& aModel, vsIKeyValueReaderWriter& aReaderWriter)
	{ TRACE
		//
		// create value
		//

	//pack the model itself first
	vs_uint32_t recordSize = aModel.recordSize();
	ASSERT(recordSize > 0);
	if (recordSize <= 0)
		{
		LOG("\t recordSize is zero which is wrong \n");
		return;
		}
	vs_uint8_t* stream = new vs_uint8_t[recordSize]; // <------------------------
	if (!stream)
		{
		LOG("\t OOM - \n");
		return;
		}
	
	TPacker packer(stream, recordSize, 0);
	bool ret = aModel.pack(packer);
	ASSERT(ret);
	if (!ret)
		{
		LOG("\t something went wrong while unpacking \n");
		return;
		}
	
	//
	vsERepositoryRecordType modelType = vsERepositoryRecordTypeUser;
	vs_uint8_t* actualRecordDump = stream;
	vsValueRecord record(recordSize, modelType, actualRecordDump);
	
	vs_uint32_t valStreamLen = record.recordSize();
	ASSERT(valStreamLen > 0);
	if (valStreamLen <= 0)
		{
		LOG("\t valStreamLen is zero which is wrong \n");
		return;
		}
	vs_uint8_t* valStream = new vs_uint8_t[valStreamLen];// <--------------------
	if (!valStream)
		{
		LOG("\t OOM - could not allocate memory \n");
		return;
		}
	TPacker valPacker(valStream, valStreamLen, 0);
	ret = record.pack(valPacker);
	ASSERT(ret);
	if (!ret)
		{
		LOG("\t something went wrong \n");
		return;
		}
		
	
	vsTData dbValue;
	dbValue.setData(valStream);
	dbValue.setDataLength(valStreamLen);
	
		//
		// create key
		//
	vsTData dbKey;
	vsPrimaryKey pk(aModel.primaryKey());
	pk.wrappedPrimaryKey(dbKey);
	dbKey.debugDump();
	
		//
		//store dbKey and dbValue
		//
	aReaderWriter.writeRaw(dbKey, dbValue);
	
	delete [] stream;
	delete [] valStream;
	}

// -----------------------------------------------------------------------------
#pragma mark - get
// -----------------------------------------------------------------------------
void vsRepository::get(vsModelBase& aPrimaryKeyedModel, function<void(const vsModelBase&)> aCompletionBlock)
	{ TRACE
	ASSERT(0 != iKeyValueStore);
	std::function<void(vsIKeyValueReader&)> readBlock = [&](vsIKeyValueReader& aReader)
		{
		doGet(aPrimaryKeyedModel, aReader);
		aCompletionBlock(aPrimaryKeyedModel);
		};
	iKeyValueStore->read(readBlock);
	}

void vsRepository::getAll(const vsRecordCreiterion& criteria, function<void(vsLinkedList<const vsModelBase>&)> aCompletionBlock)
    { TRACE
    ASSERT(0 != iKeyValueStore);
    
    vsTData theKeyLowerBound = criteria.keyLowerBound();
    vsTData theKeyUpperBound = criteria.keyUpperBound(); 
    vsIKeyValueReader::vsDirection theDirection = criteria.direction();
                           
    std::function<void(vsIKeyValueReader&)> readBlock = [&](vsIKeyValueReader& aReader)
        {
        LOG("\nenumerate callback\n");
        vsLinkedList<const vsModelBase>* collection = new vsLinkedList<const vsModelBase>();
        doEnumerate(*collection, criteria, aReader);
        aCompletionBlock(*collection);
        };
    iKeyValueStore->enumnerate(theKeyLowerBound, theKeyUpperBound, theDirection, readBlock);
    }
#include "document.hpp"
void vsRepository::doEnumerate(vsLinkedList<const vsModelBase>& collection, const vsRecordCreiterion& criteria, vsIKeyValueReader& aReader) 
    { TRACE
    
    vsTData theKeyLowerBound = criteria.keyLowerBound();
    vsTData theKeyUpperBound = criteria.keyUpperBound(); 
    vsIKeyValueReader::vsDirection theDirection = criteria.direction();
    vsModelBase& model = criteria.model();
    
    function<void (const vsTData &, const vsTData &, bool &)> block = [&](const vsTData& aKey, const vsTData& aValue, bool& aStop) {
        LOG("\n what to do here? \n");
        doParse(aKey, aValue, model);
        
        //copy
        //vsDocument doc; // = model.copy(); //virtual copy constructor
        vsModelBase* doc = model.copy();
        collection.add(doc);
    };
    
    aReader.enumerate(theKeyLowerBound, theKeyUpperBound, theDirection, block);
    }
    
void vsRepository::doGet(vsModelBase& aPrimaryKeyedModel, vsIKeyValueReader& aReader)
	{ TRACE
    
    //create key
	vsTData dbKey;
	vsPrimaryKey pk(aPrimaryKeyedModel.primaryKey());
	pk.wrappedPrimaryKey(dbKey);
	dbKey.debugDump();

    //value to accept in this
	vsTData dbValue;
    
    //read raw
	aReader.readRaw(dbKey, dbValue);
	if (!recordNotFound(dbValue))
		{
		LOG("\t record not found \n");
		return;
		}
	
    //parse
    doParse(dbKey, dbValue, aPrimaryKeyedModel);
    
//	//how big is the record? first 4 bytes will us that
//	TUnPacker recordUnPacker;
//	vs_int32_t bufLen = sizeof(vs_uint32_t);
//
//	recordUnPacker.setBuffer((vs_uint8_t*)dbValue.data());
//	recordUnPacker.setBufferLength((vs_int32_t)0);
//	recordUnPacker.setMaxLen(bufLen);
//	
//	vsValueRecord decoder;
//	bool ret = decoder.unPack(recordUnPacker);
//	ASSERT(ret);
//	if (!ret)
//		{
//		LOG("\t vsRepository::doGet: something went wrong while unpacking dbrecord \n");
//		return;
//		}
//		
//	//decoder has raw bytes for our actual model - unpack it now
//	vs_uint8_t* actualRecordDump = decoder.actualRecordDump();
//	vs_uint32_t modelSize = decoder.modelSize();
//	
//	ASSERT(0 != actualRecordDump);
//	ASSERT(modelSize > 0);
//	
//	TUnPacker modelDecoder;
//	modelDecoder.setBuffer((vs_uint8_t*)actualRecordDump);
//	modelDecoder.setBufferLength((vs_int32_t)0);
//	modelDecoder.setMaxLen(modelSize);
//	
//	aPrimaryKeyedModel.unPack(modelDecoder);
	}

bool vsRepository::recordNotFound(vsTData& aValue) const
	{
	return (( (NULL != aValue.data()) && (aValue.length() > 0) ));
	}
