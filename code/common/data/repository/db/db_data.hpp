//
//  db_data.hpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef db_data_hpp
#define db_data_hpp

#include "chat_types.h"

class vsTData
	{
public:
	vsTData();
	~vsTData();
	
	vs_uint8_t* data() const { return iData; }
	vs_uint32_t length() const { return iLength; }
	void setData(vs_uint8_t* aData) { iData = aData; }
	void setDataLength(vs_uint32_t aLen) { iLength = aLen; }
#if 0
	void debugDump() const;
#endif

private:
	vs_uint8_t* iData;
	vs_uint32_t iLength;
	bool iShouldDelete;
	};

#endif /* db_data_hpp */
