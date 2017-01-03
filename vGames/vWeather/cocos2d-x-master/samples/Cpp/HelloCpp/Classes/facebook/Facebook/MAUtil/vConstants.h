//
//  vConstants.h
//  HelloCpp
//
//  Created by Virendra Shakya on 11/2/13.
//
//

#ifndef HelloCpp_vConstants_h
#define HelloCpp_vConstants_h

#include "cocos2d.h"
//#include "talk/base/common.h"

#include "MAUtil/cpp_defs.h"

//using namespace talk_base;
using namespace cocos2d;


//#define MAASSERT ASSERT


/**
 * Displays a message to the user, then shuts down the system.
 * This function does not return.
 * \param result Passed to the operating system, where applicable. Ignored otherwise.
 * \param message The message should be short, not more than 40 characters,
 * to ensure its visibility on all screen sizes.
 * \see MAPanicReport
 */
//noreturn maPanic(in int result, in MAString message);
void maPanic(int result, MAString message);


/**
 * \def PANIC_MESSAGE(msg)
 * Handles a fatal error by calling maPanic().
 * The message includes the name of the function where the error occurred.
 * \see Freeze
 */
//#define PANIC_MESSAGE(msg) panicFunction((msg), __FUNCTION__)
#define PANIC_MESSAGE(msg) CCLOG( msg )

//#define ASSERT_MSG(cond, msg) do{ if(!(cond)) PANIC_MESSAGE(msg); }while(0)
#define ASSERT_MSG(cond, msg)  \
                            do{ \
                              if(!(cond)) \
                                CCLOG (  "ERROR: %s", (msg) ); \
                              } while(0)

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
char* itoa(int value, char* result, int base) ;

#endif
