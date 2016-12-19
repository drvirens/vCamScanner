//
//  db_table.cpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "db_table.hpp"
#include "scoped_txn.hpp"
#include "trace.h"

vsTable::vsTable(const string& aTableName, MDB_env& aEnv)
	: iTableName(aTableName)
	, iEnv(aEnv)
	{ TRACE
	}

vsTable::~vsTable()
	{ TRACE
	}

bool vsTable::create()
	{ TRACE
	bool created = false;
	ASSERT(iTableName.length() > 0);
	vsScopedTransaction txn(iEnv);
	txn.setStatus(mdb_dbi_open(txn.txn(), iTableName.c_str(), MDB_CREATE, &iDbi));
	created = true;
	return created;
	}

