//
//  unpacker.cpp
//  srv-e2e-chat
//
//  Created by Virendra Shakya on 1/9/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "unpacker.hpp"
#include "trace.h"

TUnPacker::TUnPacker()
	: m_stream(0)
	, m_max_len(0)
	, m_position(0)
	{ TRACE
	}

TUnPacker::~TUnPacker()
	{ TRACE
	}

void TUnPacker::setBuffer(vs_uint8_t* aBuffer)
	{ TRACE
	m_stream = aBuffer;
	}

void TUnPacker::setBufferLength(vs_int32_t aBufferLen)
	{ TRACE
	m_position = aBufferLen;
	}

void TUnPacker::setMaxLen(vs_int32_t aMaxLen)
	{ TRACE
	m_max_len = aMaxLen;
	}

const vs_uint8_t* TUnPacker::buffer() const
	{ TRACE
	return m_stream;
	}

vs_int32_t TUnPacker::bufferLength() const
	{ TRACE
	return m_position;
	}

bool TUnPacker::readChars(vs_int8_t* aChars, vs_uint32_t aLength)
	{ TRACE
	bool r = FALSE;
	if (m_position > m_max_len - aLength)
		{
		return r;
		}
	ASSERT(0 != aChars);
	for (int i=0; i < aLength; i++)
		{
		aChars[i] = m_stream[m_position++];
		}
	r = TRUE;
	return r;
	}

bool TUnPacker::readUint16(vs_uint16_t& aInt)
	{ TRACE
	bool r = FALSE;
	ASSERT(sizeof(aInt) == 2);
	if (m_position > m_max_len - sizeof(aInt))
		{
		return r;
		}
	aInt =  (vs_uint16_t)m_stream[m_position + 0] << 0;
	aInt |= (vs_uint16_t)m_stream[m_position + 1] << 8;
	m_position += sizeof(aInt);
	r = TRUE;
	return r;
	}

bool TUnPacker::readUint32(vs_uint32_t& aInt)
	{ TRACE
	bool r = FALSE;
	ASSERT(sizeof(aInt) == 4);
	if (m_position > m_max_len - sizeof(aInt))
		{
		return r;
		}
	aInt =  (vs_uint32_t)m_stream[m_position + 0] << 0 ;
	aInt |= (vs_uint32_t)m_stream[m_position + 1] << 8 ;
	aInt |= (vs_uint32_t)m_stream[m_position + 2] << 16;
	aInt |= (vs_uint32_t)m_stream[m_position + 3] << 24;
	m_position += sizeof(aInt);
	r = TRUE;
	return r;
	}

bool TUnPacker::readUint64(vs_uint64_t& aInt)
	{ TRACE
	bool r = FALSE;
	ASSERT(sizeof(aInt) == 8);
	if (m_position > m_max_len - sizeof(aInt))
		{
		return r;
		}
	aInt =  (vs_uint64_t)m_stream[m_position + 0] << 0 ;
	aInt |= (vs_uint64_t)m_stream[m_position + 1] << 8 ;
	aInt |= (vs_uint64_t)m_stream[m_position + 2] << 16;
	aInt |= (vs_uint64_t)m_stream[m_position + 3] << 24;
	aInt |= (vs_uint64_t)m_stream[m_position + 4] << 32;
	aInt |= (vs_uint64_t)m_stream[m_position + 5] << 40;
	aInt |= (vs_uint64_t)m_stream[m_position + 6] << 48;
	aInt |= (vs_uint64_t)m_stream[m_position + 7] << 56;

	m_position += sizeof(aInt);
	r = TRUE;
	return r;
	}
