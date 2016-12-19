//
//  trace.h
//  simple_chat_server
//
//  Created by Virendra Shakya on 12/26/15.
//  Copyright © 2015 Virendra Shakya. All rights reserved.
//

#ifndef trace_h
#define trace_h

#include <stdio.h>
#include <assert.h>

#define DEBUG 1

#define TRACE printf("  %s\n", __PRETTY_FUNCTION__);
#if defined DEBUG
	#define LOG printf
#else
	#define LOG 
#endif

#define ASSERT assert

#define TRUE 1
#define FALSE 0

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)



#endif /* trace_h */
