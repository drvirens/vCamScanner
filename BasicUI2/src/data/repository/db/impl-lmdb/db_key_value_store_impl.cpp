//
//  db_key_value_store_impl.cpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//
#include <iostream>
#include <fstream>
#include "db_key_value_store_impl.hpp"
#include "trace.h"
#include "scoped_txn.hpp"
#include "vs_db_key_value_reader_writer_impl.hpp"

static const string kTableName = "vsUser";

vsKeyValueStore::vsKeyValueStore(const string& aPath, unsigned long aSize)
	: iPath(aPath)
	, iEnv(0)
	{ TRACE
	construct(aSize);
	}

void vsKeyValueStore::construct(unsigned long aSize)
	{ TRACE
	ASSERT(iPath.length() > 0);
	ASSERT(aSize > 0);
	if ( !(iPath.length() > 0 && aSize > 0) )
		{
		LOG("\t invalid args \n");
		return;
		}
	open(aSize);
	}

void vsKeyValueStore::open(unsigned long aSize)
	{ TRACE
	int status = mdb_env_create(&iEnv);
	if (MDB_SUCCESS != status)
		{
		LOG("\t could not create mdb_env_create \n");
		return;
		}
	createDirectoryIf(iPath);
	while (true)
		{
		status = mdb_env_set_mapsize(iEnv, aSize);
		if (MDB_SUCCESS != status) { LOG("mdb_env_set_mapsize failed: %d", status); break;}
		
		status = mdb_env_set_maxdbs(iEnv, 64);
		if (MDB_SUCCESS != status) { LOG("mdb_env_set_maxdbs failed: %d", status); break;}

        //status = mdb_env_open(iEnv, iPath.c_str(), MDB_NOSYNC, 0664);
        status = mdb_env_open(iEnv, iPath.c_str(), MDB_NOLOCK, 0664); //for iOS use MDB_NOLOCK. MDB_NOSYNC crashes for Documents/ dir
		if (MDB_SUCCESS != status) { LOG("mdb_env_open failed: %d", status); break;}
		
		int removeReaders = 0;
		status = mdb_reader_check(iEnv, &removeReaders);
		if (removeReaders)
			{
			LOG("\t removed [%d] stale readers\n", removeReaders);
			}
		iTable.reset(new vsTable(kTableName, *iEnv));
		bool creeated = iTable->create();
		ASSERT(creeated);
		if (!creeated)
			{
			LOG("\t ERROR: could not create table %s \n", kTableName.c_str());
			}
		break;
		}
	}

void vsKeyValueStore::createDirectoryIf(const string& aDirPath)
	{ TRACE
	// XXX
	}

void vsKeyValueStore::close()
	{ TRACE
	if (!iEnv)
		{
		return;
		}
	
	mdb_close(iEnv, iTable->dbi());
	mdb_env_close(iEnv);
	iEnv = 0;
	}

vsKeyValueStore::~vsKeyValueStore()
	{ TRACE
	close();
	}

void vsKeyValueStore::sync()
	{ TRACE
	int status = mdb_env_sync(iEnv, 1);
	if (MDB_SUCCESS != status)
		{
		LOG("\t error while syncing\n");
		}
	}

void vsKeyValueStore::read(function<void(vsIKeyValueReader&)>& aTransaction)
	{ TRACE
	ASSERT(iTable);
	if (!iTable) { return; }
	
	vsScopedTransaction scopedTxn(*iEnv);
	MDB_txn* txn = scopedTxn.txn();
	ASSERT(0 != iTable.get());
	vsIKeyValueReaderWriter* obj = new vsCKeyValueReaderWriter( *(iTable.get()), *txn );
	if (obj)
		{
		scopedTxn.setStatus(MDB_SUCCESS); //make sure to set status for scopedTxn here
		aTransaction(*obj);
		}
    delete obj;
    obj = 0;
	}

void vsKeyValueStore::readWrite(function<void(vsIKeyValueReaderWriter&)>& aTransaction)
	{ TRACE
	ASSERT(iTable);
	if (!iTable) { return; }
	
	vsScopedTransaction scopedTxn(*iEnv);
	MDB_txn* txn = scopedTxn.txn();
	ASSERT(0 != iTable.get());
	vsIKeyValueReaderWriter* obj = new vsCKeyValueReaderWriter( *(iTable.get()), *txn );
	if (obj)
		{
		scopedTxn.setStatus(MDB_SUCCESS); //make sure to set status for scopedTxn here
		aTransaction(*obj);
		}
	}
