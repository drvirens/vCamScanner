//
//  db_key_value_writer.hpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef db_key_value_writer_hpp
#define db_key_value_writer_hpp

class vsTData;

class vsIKeyValueWriter
	{
public:
	vsIKeyValueWriter();
	virtual ~vsIKeyValueWriter();
	
	virtual void writeRaw(const vsTData& aKey, const vsTData& aValue) = 0;
	virtual bool deleteValueForRawKey(const vsTData& aKey) = 0;
	virtual void deleteAllValues() = 0;
	};

#endif /* db_key_value_writer_hpp */
