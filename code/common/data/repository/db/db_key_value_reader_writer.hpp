//
//  db_key_value_reader_writer.hpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef db_key_value_reader_writer_hpp
#define db_key_value_reader_writer_hpp

#include "db_key_value_reader.hpp"
#include "db_key_value_writer.hpp"

class vsIKeyValueReaderWriter : public vsIKeyValueReader, public vsIKeyValueWriter
	{
public:
	vsIKeyValueReaderWriter();
	virtual ~vsIKeyValueReaderWriter();
	
	//reader
	virtual bool readRaw(const vsTData& aKey, vsTData& aValue) = 0;
    virtual bool enumerate(const vsTData& aKeyLowerBound, const vsTData& aKeyUpperBound, vsDirection aDirection,
                            function<void(const vsTData& /*aKey*/, const vsTData& /*aValue*/, bool& /*aStop*/)>& aBlock) = 0;
	
	//write
	virtual void writeRaw(const vsTData& aKey, const vsTData& aValue) = 0;
	virtual bool deleteValueForRawKey(const vsTData& aKey) = 0;
	virtual void deleteAllValues() = 0;
	};

#endif /* db_key_value_reader_writer_hpp */
