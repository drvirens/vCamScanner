//
//  repository_impl.hpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef repository_impl_hpp
#define repository_impl_hpp

#include <memory>
#include <string>
#include "chat_types.h"
#include "repository.hpp"
#include "db_key_value_store_impl.hpp"

using namespace std;
class TPacker;
class TUnPacker;
class vsTData;

class vsRepository : public vsIRepository
	{
public:
	vsRepository(vsIKeyValueStore& aKeyValueStore);
	virtual ~vsRepository();
	virtual void put(vsModelBase& aModel, function<void(const vsModelBase&)> aCompletionBlock);
	virtual void get(vsModelBase& aPrimaryKeyedModel, function<void(const vsModelBase&)> aCompletionBlock);
    virtual void getAll(const vsRecordCreiterion& criteria, function<void(vector<const vsModelBase>&)> aCompletionBlock);
	
private:
	void doPut(vsModelBase& aModel, vsIKeyValueReaderWriter& aReaderWriter);
	void packDBRecord(TPacker& aPacker, vs_int32_t aDbRecordSize, vs_uint8_t* aBuffer);
	void createKey(vsModelBase& aModel, vs_uint64_t& aKeyStream);
	void doGet(vsModelBase& aPrimaryKeyedModel, vsIKeyValueReader& aReader);
	bool recordNotFound(vsTData& aValue) const;
	
private:
	unique_ptr<vsIKeyValueStore> iKeyValueStore;
	};

#endif /* repository_impl_hpp */
