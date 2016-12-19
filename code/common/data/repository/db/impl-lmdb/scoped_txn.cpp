//
//  scoped_txn.cpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "scoped_txn.hpp"
#include "trace.h"

vsScopedTransaction::vsScopedTransaction(MDB_env& aENv)
	: iEnv(aENv)
	, iTxn(0)
	, iStatus(-69)
	{ TRACE
	if (MDB_SUCCESS != (open()))
		{
		throw vsScopedTransactionException();
		}
	}

vsScopedTransaction::~vsScopedTransaction()
	{ TRACE
	close();
	}

int vsScopedTransaction::open()
	{ TRACE 
	int status = MDB_SUCCESS;
	status = mdb_txn_begin(&iEnv, NULL, 0, &iTxn); //XXX: should be MDB_RDONLY for readonly operations like read or enumerate
	if (MDB_SUCCESS != status)
		{
		LOG("mdb_txn_begin failed : [%d]", status);
		}
	ASSERT(0 != iTxn);
	if (!iTxn)
		{
		LOG("nil transaction");
		}
	return status;
	}

void vsScopedTransaction::close()
	{ TRACE
	ASSERT(-69 != iStatus); //Did you forget to call setStatus()
	
	if (MDB_SUCCESS != iStatus)
		{
		mdb_txn_abort(iTxn);
		}
	else
		{
		iStatus = mdb_txn_commit(iTxn);
		if (MDB_SUCCESS != iStatus)
			{
			LOG("mdb_txn_commit failed : [%d]", iStatus);
			}
		}
	}
