//
//  circular_buffer.hpp
//  srv-e2e-chat
//
//  Created by Virendra Shakya on 1/9/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef circular_buffer_hpp
#define circular_buffer_hpp

#include <memory>
#include <sys/types.h>

using namespace std;

class CCircularBuffer
	{
public:
	CCircularBuffer();
	virtual ~CCircularBuffer();
	
	long read(int aFd);
	unsigned int usedBufferSize() const;
	char peekAByte();
	char peekFirstByte();
	int peekManyBytes(int a_how_many, char** a_stream, int* a_should_free);
	int readManyBytes(int a_how_many, char** a_stream, int* a_should_free);
	void incrementReadOffsetBy(long aIncrementBy);
	void writeBytes(const void* aBytes, unsigned long aLenght);
	
private:
	unsigned int availableBufferSize() const;
	void grow();
	void incrementWriteOffsetBy(long aIncrementBy);
	void prepareIOVectors(struct iovec* a_iovec, int* a_how_many_vectors);
	void construct();
	
private:
	int m_write; // or head - put at head
	int m_read; // or tail - get at tail
	unsigned int m_size;
	shared_ptr<char> m_buffer;
	};

#endif /* circular_buffer_hpp */
