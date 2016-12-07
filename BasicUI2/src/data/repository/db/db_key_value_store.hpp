//
//  db_key_value_store.hpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef db_key_value_store_hpp
#define db_key_value_store_hpp

#include <functional>
using namespace std;

class vsIKeyValueReader;
class vsIKeyValueReaderWriter;

class vsIKeyValueStore
	{
public:
	vsIKeyValueStore();
	virtual ~vsIKeyValueStore();
	
	virtual void read(function<void(vsIKeyValueReader&)>& aTransaction) = 0;
    virtual void enumnerate(function<void(vsIKeyValueReader&)>& aTransaction) = 0;
	virtual void readWrite(function<void(vsIKeyValueReaderWriter&)>& aTransaction) = 0;
	virtual void sync() = 0;
	};

#endif /* db_key_value_store_hpp */
