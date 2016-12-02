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
