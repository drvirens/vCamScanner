//
//  db_data.cpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/15/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include <string.h>
#include "db_data.hpp"
#include "trace.h"

vsTData::vsTData()
	: iData(0)
	, iLength(0)
	, iShouldDelete(false)
	{ TRACE
	}

vsTData::~vsTData()
	{ TRACE
	if (iShouldDelete)
		{
		delete [] iData;
		}
	iData = 0;
	iLength = 0;
	}

#if defined DEBUG
void vsTData::debugDump() const
	{
	LOG("\n");
	for (vs_uint32_t i = 0; i < iLength; i++)
		{
		vs_uint8_t byte = iData[i];
		LOG("\t%d", byte);
		}
	LOG("\n");
	}
#endif
