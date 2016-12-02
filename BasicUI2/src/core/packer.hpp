//
//  packer.hpp
//  srv-e2e-chat
//
//  Created by Virendra Shakya on 1/7/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef packer_hpp
#define packer_hpp

#include "chat_types.h"

class TPacker
	{
public:
	TPacker(vs_uint8_t* aStream, vs_int32_t aMaxLen, vs_int32_t aPos);
	virtual ~TPacker();
	
	vs_uint8_t* buffer() const;
	vs_int32_t bufferLength() const;
	
	bool writeChars(const vs_int8_t* aChars, vs_uint32_t aLength);
	bool writeUint16(vs_uint16_t aInt);
	bool writeUint32(vs_uint32_t aInt);
	bool writeUint64(vs_uint64_t aInt);
	
private:
	vs_uint8_t* m_stream;
	vs_int32_t m_max_len;
	vs_int32_t m_position;
	};

#endif /* packer_hpp */
