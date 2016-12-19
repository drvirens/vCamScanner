//
//  packer.cpp
//  srv-e2e-chat
//
//  Created by Virendra Shakya on 1/7/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "packer.hpp"
#include "trace.h"

TPacker::TPacker(vs_uint8_t* aStream, vs_int32_t aMaxLen, vs_int32_t aPos)
	: m_stream(aStream)
	, m_max_len(aMaxLen)
	, m_position(aPos)
	{ TRACE
	}

TPacker::~TPacker()
	{ TRACE
	}

vs_uint8_t* TPacker::buffer() const
	{ TRACE
	return m_stream;
	}

vs_int32_t TPacker::bufferLength() const
	{ TRACE
	return m_position;
	}

bool TPacker::writeChars(const vs_int8_t* aChars, vs_uint32_t aLength)
	{ TRACE
	bool r = FALSE;
	if (m_position > m_max_len - aLength)
		{
		return r;
		}
	for (int i=0; i<aLength; i++)
		{
		m_stream[m_position++] = aChars[i];
		}
	r = TRUE;
	return r;
	}

bool TPacker::writeUint16(vs_uint16_t aInt)
	{ TRACE
	bool r = FALSE;
	ASSERT(sizeof(aInt) == 2);
	if (m_position > m_max_len - sizeof(aInt))
		{
		return r;
		}
	m_stream[m_position + 0] = (aInt     ) & 0xFF;
	m_stream[m_position + 1] = (aInt >> 8) & 0xFF;
	m_position += sizeof(aInt);
	r = TRUE;
	return r;
	}

bool TPacker::writeUint32(vs_uint32_t aInt)
	{ TRACE
	bool r = FALSE;
	ASSERT(sizeof(aInt) == 4);
	if (m_position > m_max_len - sizeof(aInt))
		{
		return r;
		}
	m_stream[m_position + 0] = (aInt >> 0)  & 0xFF;
	m_stream[m_position + 1] = (aInt >> 8)  & 0xFF;
	m_stream[m_position + 2] = (aInt >> 16) & 0xFF;
	m_stream[m_position + 3] = (aInt >> 24) & 0xFF;
	m_position += sizeof(aInt);
	
	r = TRUE;
	return r;
	}

bool TPacker::writeUint64(vs_uint64_t aInt)
	{ TRACE
	bool r = FALSE;
	ASSERT(sizeof(aInt) == 8);
	if (m_position > m_max_len - sizeof(aInt))
		{
		return r;
		}
	m_stream[m_position + 0] = (aInt >> 0)  & 0xFF;
	m_stream[m_position + 1] = (aInt >> 8)  & 0xFF;
	m_stream[m_position + 2] = (aInt >> 16) & 0xFF;
	m_stream[m_position + 3] = (aInt >> 24) & 0xFF;
	m_stream[m_position + 4] = (aInt >> 32) & 0xFF;
	m_stream[m_position + 5] = (aInt >> 40) & 0xFF;
	m_stream[m_position + 6] = (aInt >> 48) & 0xFF;
	m_stream[m_position + 7] = (aInt >> 56) & 0xFF;
	m_position += sizeof(aInt);
	
	r = TRUE;
	return r;
	}
