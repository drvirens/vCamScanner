//
//  repository.hpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef repository_hpp
#define repository_hpp

#include <functional>
#include "linked_list.hpp"

using namespace std;

class vsModelBase;
class vsRecordCreiterion;

class vsIRepository
	{
public:
	vsIRepository();
	virtual ~vsIRepository();
	
	virtual void put(vsModelBase& aModel, function<void(const vsModelBase&)> aCompletionBlock) = 0;
	
	//assume that aModels' primary key is correctly set by caller
	virtual void get(vsModelBase& aPrimaryKeyedModel, function<void(const vsModelBase&)> aCompletionBlock) = 0;
        
    virtual void getAll(const vsRecordCreiterion& criteria, function<void(vsLinkedList<const vsModelBase>&)> aCompletionBlock) = 0;
	};

#endif /* repository_hpp */
