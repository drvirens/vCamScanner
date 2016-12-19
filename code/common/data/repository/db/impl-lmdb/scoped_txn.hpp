//
//  scoped_txn.hpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef scoped_txn_hpp
#define scoped_txn_hpp

#include <exception>
#include "lmdb.h"

using namespace std;

class vsScopedTransactionException : public exception
	{
public:
	virtual const char* what() const throw() { return "vsScopedTransactionException"; }
	};

class vsScopedTransaction
	{
public:
	vsScopedTransaction(MDB_env& aENv);
	~vsScopedTransaction();
	void setStatus(int aStatus) { iStatus = aStatus; }
	MDB_txn* txn() const { return iTxn; }
	
private:
	int open();
	void close();
	
private:
	MDB_env& iEnv;
	MDB_txn* iTxn;
	int iStatus;
	};

#endif /* scoped_txn_hpp */
