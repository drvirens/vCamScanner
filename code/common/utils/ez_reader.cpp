//
//  ez_reader.cpp
//  srv-e2e-chat
//
//  Created by Virendra Shakya on 1/17/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "ez_reader.hpp"

#include "packer.hpp"
#include "unpacker.hpp"
#include "primary_key.hpp"
#include "trace.h"

bool extractString(TUnPacker& aUnPacker, string& aStr)
	{
	vs_uint32_t objLen = 0;
	if ( !(aUnPacker.readUint32(objLen)) )
		{
		LOG("\tcould not read the length\n");
		return false;
		}
	ASSERT(objLen >= 0 && objLen < 1000);
	char* strPtr = (char*)(aUnPacker.buffer() + aUnPacker.bufferLength());
	string objName(strPtr, objLen);
	aStr = objName;
	aUnPacker.setBufferLength(aUnPacker.bufferLength() + objLen);
	return true;
	}

bool extractInt64(TUnPacker& aUnPacker, vs_uint64_t& aInt)
	{
	if ( !(aUnPacker.readUint64(aInt)) )
		{
		LOG("\tcould not read the length\n");
		return false;
		}
	return true;
	}
