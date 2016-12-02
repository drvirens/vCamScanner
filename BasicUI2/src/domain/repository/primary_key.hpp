//
//  primary_key.hpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/17/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef primary_key_hpp
#define primary_key_hpp

#include <string>
#include "chat_types.h"
//#include "db_data.hpp"

using namespace std;

class vsTData;

class vsPrimaryKey
	{
public:
	vsPrimaryKey(const string& aPrimaryKey);
	~vsPrimaryKey();
	
	vs_uint64_t primaryKey() const;
	void wrappedPrimaryKey(vsTData& outputObj);
	
private:
	const string& iPrimaryKey;
	vs_uint8_t* iKeyStreamBuf;
	};

#endif /* primary_key_hpp */
