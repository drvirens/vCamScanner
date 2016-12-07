//
//  time_utils.cpp
//  vsopencvios
//
//  Created by Virendra Shakya on 12/7/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "time_utils.hpp"


void currentTime(string& aCurrTime)
    {
    static const int kBufSize = 100;
    time_t rawtime;
    struct tm* timeinfo = 0;
    char buffer[kBufSize] = {0};

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime(buffer,kBufSize,"%j%d%W%B%Y%H%I%M", timeinfo);
    
    char ptrbuffer[kBufSize] = {0};
    sprintf(ptrbuffer, "%s_%p", buffer, &aCurrTime);
    
    aCurrTime = ptrbuffer;
    }
