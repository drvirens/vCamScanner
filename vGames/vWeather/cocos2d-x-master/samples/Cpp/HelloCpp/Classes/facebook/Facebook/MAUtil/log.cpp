//
//  log.cpp
//  HelloCpp
//
//  Created by Virendra Shakya on 11/4/13.
//
//

#include <stdio.h> //for vspintf
#include "log.h"
#include "cocos2d.h"

//using namespace talk_base;
using namespace cocos2d;

void LogV(const char* fmt, va_list args) {
//	int res;
//	InitLog();
//	CriticalSectionHandler csh(&gLogCS);
//	
//	char tempString[1024];
//	res = vsprintf(tempString, fmt, args);
//	logWithNSLog(tempString, res);
//	
//	FILE* file = fopen(sFilename, "a");
//	res = vfprintf(file, fmt, args);
//	fclose(file);
//	if(res < 0)
//		MoSyncErrorExit(ERR_INTERNAL);

	char tempString[1024];
	vsprintf(tempString, fmt, args);
  CCLOG ( "tempString = %s", tempString );
}
