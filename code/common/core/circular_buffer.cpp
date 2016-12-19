//
//  circular_buffer.cpp
//  srv-e2e-chat
//
//  Created by Virendra Shakya on 1/9/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include <sys/uio.h>
#include "circular_buffer.hpp"
#include "trace.h"

static const unsigned int kInitBufferSize					= 32*1024; //32kb
//static const unsigned int kBufferSizeMultiplier		= 2;

CCircularBuffer::CCircularBuffer()
	{ TRACE
	construct();
	}

void CCircularBuffer::construct()
	{ TRACE
	m_write					= 0;
	m_read					= 0;
	m_size					= kInitBufferSize;
	m_buffer.reset(new char[m_size]);
	memset(m_buffer.get(), '0', m_size);
	}

CCircularBuffer::~CCircularBuffer()
	{ TRACE
	}

long CCircularBuffer::read(int aFd)
	{ TRACE
	long read_bytes;
	unsigned int avail = availableBufferSize();
	if (avail < m_size/2) //if available is less than 50% space left, then grow
		{
		grow();
		}
	struct iovec vectors[2] = {0};
	int how_many_vectors=0;
	prepareIOVectors(&vectors[0], &how_many_vectors);
	read_bytes = readv(aFd, &vectors[0], how_many_vectors);
	if (read_bytes>0)
		{
		incrementWriteOffsetBy(read_bytes);
		}
	
	return read_bytes;
	}

unsigned int CCircularBuffer::usedBufferSize() const
	{ TRACE
	unsigned int used;
	if (m_write < m_read)
		{
		used = m_size - m_read + m_write;
		}
	else
		{
		used = m_write - m_read;
		}
	return used;
	}

char CCircularBuffer::peekAByte()
	{ TRACE
	if (unlikely(1 > usedBufferSize()))
		{
		return -1;
		}
	char r;
	r = *(char*)(m_buffer.get() + m_read);
	return r;
	}
char CCircularBuffer::peekFirstByte()
	{ TRACE
	if (unlikely(1 > usedBufferSize()))
		{
		return -1;
		}
	char r;
	r = *(char*)(m_buffer.get() + m_read);
	return r;
	}

int CCircularBuffer::peekManyBytes(int a_how_many, char** a_stream, int* a_should_free)
	{ TRACE
	if (unlikely(a_how_many > usedBufferSize()))
		{
		return -1;
		}
	if (unlikely(m_write < m_read))
		{
		//can we use contiguous chunk?
		int end_size = m_size - m_read;
		if (end_size >= a_how_many)
			{
			*a_stream = m_buffer.get() + m_read;
			*a_should_free = FALSE;
			}
		else
			{
			*a_stream = (char*)malloc(a_how_many); //XXX
			memcpy(*a_stream, m_buffer.get() + m_read, end_size);
			memcpy(*a_stream + end_size, m_buffer.get(), a_how_many - end_size);
			*a_should_free = TRUE;
			}
		}
	else //contiguous
		{
		*a_stream = m_buffer.get() + m_read;
		*a_should_free = FALSE;
		}
	return 0;
	}

int CCircularBuffer::readManyBytes(int a_how_many, char** a_stream, int* a_should_free)
	{ TRACE
	int r = peekManyBytes(a_how_many, a_stream, a_should_free);
	if (-1 != r)
		{
		incrementReadOffsetBy(a_how_many);
		}
		
	return r;
	}

unsigned int CCircularBuffer::availableBufferSize() const
	{ TRACE
	unsigned int avail;
	if (m_write	< m_read)
		{
		avail = m_read - m_write - 1;
		}
	else
		{
		avail = m_size - m_write + m_read - 1;
		}
	return avail;
	}

void CCircularBuffer::grow()
	{ TRACE
	LOG("TODO ---> CCircularBuffer::grow() is NOT implemented yet :( ");
	}

void CCircularBuffer::incrementWriteOffsetBy(long aIncrementBy)
	{ TRACE
	m_write = (m_write + aIncrementBy) % (m_size);
	}

void CCircularBuffer::incrementReadOffsetBy(long aIncrementBy)
	{ TRACE
	m_read = (m_read + aIncrementBy) % (m_size);
	// XXX
	//reset the cursors if they catchup with each other
//	if (m_read == m_write)
//		{
//		m_read = 0;
//		m_write = 0;
//		}
	}

void CCircularBuffer::prepareIOVectors(struct iovec* a_iovec, int* a_how_many_vectors)
	{ TRACE
	ASSERT(0 != a_iovec);
	*a_how_many_vectors = 1;
	if (m_write < m_read)
		{
		a_iovec[0].iov_base = m_buffer.get() + m_write;
		a_iovec[0].iov_len = m_read - m_write - 1;
		}
	else
		{
		a_iovec[0].iov_base = m_buffer.get() + m_write;
		a_iovec[0].iov_len = m_size - m_write - 1;
		if (m_read > 0)
			{
			a_iovec[0].iov_len += 1;
			a_iovec[1].iov_base = m_buffer.get();
			a_iovec[1].iov_len = m_read -1;
			*a_how_many_vectors = 2;
			}
		}
	}

void CCircularBuffer::writeBytes(const void* aBytes, unsigned long aLenght)
	{ TRACE
	unsigned int avail = availableBufferSize();
	while (avail < aLenght)
		{
		grow();
		avail = availableBufferSize();
		} //end while
		
	if (m_write < m_read)
		{
		memcpy(m_buffer.get() + m_write, aBytes, aLenght);
		m_write += aLenght;
		return;
		}
		
	unsigned int endSize = m_size - m_write;
	if (endSize >= aLenght)
		{
		memcpy(m_buffer.get() + m_write, aBytes, aLenght);
		m_write += aLenght;
		return;
		}
		
	//copy the first endSize bytes
	memcpy(m_buffer.get() + m_write, aBytes, endSize);
	//copy remaining data
	memcpy(m_buffer.get(), ((char*)aBytes) + endSize, (aLenght - endSize));
	m_write = (aLenght - endSize);
	
	return;
	}

