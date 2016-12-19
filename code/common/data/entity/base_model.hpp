//
//  base_model.hpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/16/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef base_model_hpp
#define base_model_hpp

#include <string>
#include "chat_types.h"
using namespace std;

class TPacker;
class TUnPacker;

class vsModelBase
	{
public:
	vsModelBase();
	virtual ~vsModelBase();
	
    virtual vsModelBase* copy() = 0; //virtual copy constructor
    
	virtual const string& primaryKey() const = 0;
	virtual const vs_int32_t recordSize() const = 0;
	virtual bool pack(TPacker& aPacker) = 0;
	virtual bool unPack(TUnPacker& aPacker) = 0;
	
	};

#endif /* base_model_hpp */
