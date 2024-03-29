//
//  vs_db_key_value_reader_writer_impl.hpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef vs_db_key_value_reader_writer_impl_hpp
#define vs_db_key_value_reader_writer_impl_hpp

#include <memory>
#include "lmdb.h"
#include "db_key_value_reader_writer.hpp"
#include "db_table.hpp"
#include "db_cursor.hpp"

using namespace std;

class vsCKeyValueReaderWriter : public vsIKeyValueReaderWriter
	{
public:
	vsCKeyValueReaderWriter(vsTable& aTable, MDB_txn& aTransaction);
	virtual ~vsCKeyValueReaderWriter();
	
		//reader
	virtual bool readRaw(const vsTData& aKey, vsTData& aValue);
    virtual bool enumerate(const vsTData& aKeyLowerBound, 
                           const vsTData& aKeyUpperBound, 
                           vsDirection aDirection,
                           function<void(const vsTData& /*aKey*/, const vsTData& /*aValue*/, bool& /*aStop*/)>& aBlock);
	
		//write
	virtual void writeRaw(const vsTData& aKey, const vsTData& aValue);
	virtual bool deleteValueForRawKey(const vsTData& aKey);
	virtual void deleteAllValues();
	
private:
	const MDB_dbi& dbi() const;
    bool readWithCursor(function<void(const vsCursor&)>& aCursorBlock);
	
private:
	unique_ptr<vsTable> iTable;
	MDB_txn* iTransaction;
	};

#endif /* vs_db_key_value_reader_writer_impl_hpp */
