//
//  vs_db_key_value_reader_writer_impl.cpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "vs_db_key_value_reader_writer_impl.hpp"
#include "db_data.hpp"
#include "trace.h"
#include "db_cursor.hpp"

vsCKeyValueReaderWriter::vsCKeyValueReaderWriter(vsTable& aTable, MDB_txn& aTransaction)
	: iTransaction(&aTransaction)
	{ TRACE
	iTable.reset(&aTable);
	}

vsCKeyValueReaderWriter::~vsCKeyValueReaderWriter()
	{ TRACE
	}

bool vsCKeyValueReaderWriter::readRaw(const vsTData& aKey, vsTData& aValue)
	{ TRACE
	bool ret = false;
	MDB_val mdbKey = {0};
	MDB_val mdbValue = {0};
	
	mdbKey.mv_data = aKey.data();
	mdbKey.mv_size = aKey.length();
	aKey.debugDump();
	int status = mdb_get(iTransaction, dbi(), &mdbKey, &mdbValue);
	if (MDB_SUCCESS != status)
		{
		LOG("\t ERROR: mdb_get [%d]\n", status);
		if (status == MDB_NOTFOUND)
			{
			LOG("\t mdb_get returned MDB_NOTFOUND :( \n");
			}
		if (status == MDB_BAD_TXN)
			{
			LOG("\t mdb_get returned MDB_BAD_TXN :( \n");
			}
		return ret;
		}
		
	ASSERT(MDB_SUCCESS == status);
	aValue.setData(static_cast<vs_uint8_t*>(mdbValue.mv_data));
	aValue.setDataLength(static_cast<vs_uint32_t>(mdbValue.mv_size));
	
	ret = true;
	return ret;
	}
    
bool vsCKeyValueReaderWriter::enumerate(const vsTData& aKeyLowerBound, 
                                        const vsTData& aKeyUpperBound, 
                                        vsDirection aDirection,
    function<void(const vsTData& /*aKey*/, const vsTData& /*aValue*/, bool& /*aStop*/)>& aBlock)
    { TRACE
    bool ret = false;
    function<void(const vsCursor&)> cursorblock = [&](const vsCursor& aCursor)
        {
        LOG("inside lambda cursor bloc");
        MDB_val upperBoundKey = 
            {
            .mv_data = aKeyUpperBound.data(),
            .mv_size = aKeyUpperBound.length()
            };
            
        MDB_val lowerBoundKey =
            {
            .mv_data = aKeyLowerBound.data(),
            .mv_size = aKeyLowerBound.length()
            };
            
        vs_uint8_t* positionedKey         = aKeyLowerBound.data();
        vs_uint32_t positionedKeyLen      = aKeyLowerBound.length();
        
        vs_uint8_t* positionedValue       = 0;
        vs_uint32_t positionedValueLen    = 0;
        
        bool status = aCursor.positionAt(&positionedKey, &positionedKeyLen, &positionedValue, &positionedValueLen, eCursorDirection::eCursorDirectionForward);
        if (status)
            {
            LOG("\npositionAt success\n");
            bool stop = false;
            
            vsTData retValue;
            retValue.setData(positionedValue);
            retValue.setDataLength(positionedValueLen);
            
            aBlock(aKeyLowerBound, retValue,stop);
            
            MDB_val positionedKeyVal =
                {
                .mv_data = (vs_uint8_t*)positionedKey,
                .mv_size = positionedKeyLen
                };
            bool continueSearch = true;
            
            int rc = mdb_cmp(iTransaction, dbi(), &lowerBoundKey, &positionedKeyVal);
            if (0 == rc)
                {
                continueSearch = aCursor.next(&positionedKey, &positionedKeyLen, &positionedValue, &positionedValueLen);
                }
            if (continueSearch)
                {
                LOG("\n continueSearch \n");
                int cmpResult = mdb_cmp(iTransaction, dbi(), &positionedKeyVal, &upperBoundKey);
                if (0 == cmpResult)
                    {
                    LOG("\n mdb_cmp returned EQUAL \n");
                    }
                else if (cmpResult < 0)
                    {
                    LOG("\n mdb_cmp returned less than equal to 0 \n");
                    }
                else 
                    {
                    LOG("\n mdb_cmp returned greater than 0 \n");
                    //no results found
                    }
                }
            }
        };
    readWithCursor(cursorblock);
    return ret;
    }
    
bool vsCKeyValueReaderWriter::readWithCursor(function<void(const vsCursor&)>& aCursorBlock)
    { TRACE
    bool ret = false;
    MDB_cursor* mdbCursor = 0;
    int status = mdb_cursor_open(iTransaction, dbi(), &mdbCursor);
    if (MDB_SUCCESS != status)
        {
        return ret;
        }
    vsCursor* cursor = new vsCursor(*iTable, mdbCursor);
    aCursorBlock(*cursor);
    mdb_cursor_close(mdbCursor);
    ret = true;
    return ret;
    }

void vsCKeyValueReaderWriter::writeRaw(const vsTData& aKey, const vsTData& aValue)
	{ TRACE
	MDB_val mdbKey = {0};
	MDB_val mdbValue = {0};
	
	mdbKey.mv_data = aKey.data();
	mdbKey.mv_size = aKey.length();
	
	mdbValue.mv_data = aValue.data();
	mdbValue.mv_size = aValue.length();
	
	int status = mdb_put(iTransaction, dbi(), &mdbKey, &mdbValue, 0);
	if (MDB_SUCCESS != status)
		{
		LOG("\t ERROR: mdb_put [%d]\n", status);
		}
	}

bool vsCKeyValueReaderWriter::deleteValueForRawKey(const vsTData& aKey)
	{ TRACE
	bool ret;
	return ret;
	}

void vsCKeyValueReaderWriter::deleteAllValues()
	{ TRACE
	}

const MDB_dbi& vsCKeyValueReaderWriter::dbi() const
	{ TRACE
	return iTable->dbi();
	}
