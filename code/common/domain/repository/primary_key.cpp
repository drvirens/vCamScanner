//
//  primary_key.cpp
//  test-chat-lmdb
//
//  Created by Virendra Shakya on 1/17/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "primary_key.hpp"
#include "MurmurHash3.h"
#include "packer.hpp"
#include "db_data.hpp"
#include "trace.h"

vsPrimaryKey::vsPrimaryKey(const string& aPrimaryKey)
	: iPrimaryKey(aPrimaryKey)
	, iKeyStreamBuf(0)
	{ TRACE
	}

vsPrimaryKey::~vsPrimaryKey()
	{ TRACE
	delete [] iKeyStreamBuf;
	iKeyStreamBuf = 0;
	}

vs_uint64_t vsPrimaryKey::primaryKey() const
	{ TRACE
	vs_uint64_t ret = 69;
	vs_uint64_t out[2] = {0};
	const vs_uint32_t seed = 0;
	MurmurHash3_x64_128(iPrimaryKey.c_str(), (const int)iPrimaryKey.length(), seed, &out);
	ret = out[1];
	return ret;
	}

void vsPrimaryKey::wrappedPrimaryKey(vsTData& outputObj)
	{ TRACE
	vs_uint32_t len = sizeof(vs_uint64_t);
	
	vs_uint64_t pk = primaryKey();
	iKeyStreamBuf = new vs_uint8_t[len];
	if (!iKeyStreamBuf)
		{
		LOG("OOM \n");
		return;
		}
	TPacker keystreamPacker(iKeyStreamBuf, len, 0);
	keystreamPacker.writeUint64(pk);
	
	outputObj.setData(iKeyStreamBuf);
	outputObj.setDataLength(len);
	}
