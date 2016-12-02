//
//  db_key_value_store_impl.hpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef db_key_value_store_impl_hpp
#define db_key_value_store_impl_hpp

#include <string>
#include "lmdb.h"
#include "db_key_value_store.hpp"
#include "db_table.hpp"

using namespace std;

class vsKeyValueStore : public vsIKeyValueStore
	{
public:
	vsKeyValueStore(const string& aPath, unsigned long aSize);
	virtual ~vsKeyValueStore();
	
	//vsIKeyValueStore
	virtual void read(function<void(vsIKeyValueReader&)>& aTransaction);
	virtual void readWrite(function<void(vsIKeyValueReaderWriter&)>& aTransaction);
	virtual void sync();
	
private:
	void construct(unsigned long aSize);
	void open(unsigned long aSize);
	void close();
	void createDirectoryIf(const string& aDirPath);
	
private:
	const string& iPath;
	MDB_env* iEnv;
	unique_ptr<vsTable> iTable;
	};

#endif /* db_key_value_store_impl_hpp */
