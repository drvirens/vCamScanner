//
//  db_key_value_reader.hpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef db_key_value_reader_hpp
#define db_key_value_reader_hpp

#include <functional>

using namespace std;

class vsTData;

class vsIKeyValueReader
	{
public:
    enum vsDirection
        {
        vsDirectionForward,
        vsDirectionReverse
        };
public:
	vsIKeyValueReader();
	virtual ~vsIKeyValueReader();
	
	virtual bool readRaw(const vsTData& aKey, vsTData& aValue) = 0;
    virtual bool enumerate(const vsTData& aKeyLowerBound, const vsTData& aKeyUpperBound, vsDirection aDirection,
                            function<void(const vsTData& /*aKey*/, const vsTData& /*aValue*/, bool& /*aStop*/)>& aBlock) = 0;
	};

#endif /* db_key_value_reader_hpp */
