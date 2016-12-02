//
//  db_key_value_reader.hpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef db_key_value_reader_hpp
#define db_key_value_reader_hpp

class vsTData;

class vsIKeyValueReader
	{
public:
	vsIKeyValueReader();
	virtual ~vsIKeyValueReader();
	
	virtual bool readRaw(const vsTData& aKey, vsTData& aValue) = 0;
	};

#endif /* db_key_value_reader_hpp */
