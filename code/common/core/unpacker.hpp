//
//  unpacker.hpp
//  srv-e2e-chat
//
//  Created by Virendra Shakya on 1/9/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef unpacker_hpp
#define unpacker_hpp

#include "chat_types.h"

class TUnPacker
	{
public:
	TUnPacker();
	virtual ~TUnPacker();

	void setBuffer(vs_uint8_t* aBuffer);
	void setBufferLength(vs_int32_t aBufferLen);
	void setMaxLen(vs_int32_t aMaxLen);
	
	const vs_uint8_t* buffer() const;
	vs_int32_t bufferLength() const;

	bool readChars(vs_int8_t* aChars, vs_uint32_t aLength);
	bool readUint16(vs_uint16_t& aInt);
	bool readUint32(vs_uint32_t& aInt);
	bool readUint64(vs_uint64_t& aInt);

private:
	const vs_uint8_t* m_stream;
	vs_int32_t m_max_len;
	vs_int32_t m_position;
	};

#endif /* unpacker_hpp */
