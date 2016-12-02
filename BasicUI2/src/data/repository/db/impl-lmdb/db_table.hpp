//
//  db_table.hpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef db_table_hpp
#define db_table_hpp

#include <string>
#include "lmdb.h"

using namespace std;

class vsTable
	{
public:
	vsTable(const string& aTableName, MDB_env& aEnv);
	virtual ~vsTable();
	
	bool create();
	const MDB_dbi& dbi() const { return iDbi; }
	
private:
	const string& iTableName;
	MDB_env& iEnv;
	MDB_dbi iDbi;
	};

#endif /* db_table_hpp */
