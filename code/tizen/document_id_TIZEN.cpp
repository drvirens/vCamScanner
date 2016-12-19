//
//  document_id.mm
//  vsopencvios
//
//  Created by Virendra Shakya on 12/12/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//


#include <sstream>
#include "document_id.hpp"
#include "trace.h"

//static NSString* const kKeyLastDocId = @"last_doc_id";

static int gTempDocID = 1;
int getLastUsedDocID()
    { TRACE
//    NSUserDefaults* ud = [NSUserDefaults standardUserDefaults];
//    NSNumber* numDocId = (NSNumber*)[ud objectForKey:kKeyLastDocId];
	int numDocId = 0;
    int ret = 0;
    if (numDocId) 
        {
//        ret = [numDocId intValue];
        }
    else 
        {
//        ret = gTempDocID;
        }
    return ret;
    }
    
void setLastDocID(int docid)
    { TRACE
//    NSUserDefaults* ud = [NSUserDefaults standardUserDefaults];
//    NSNumber* numDocId = [NSNumber numberWithInt:docid];
//    [ud setObject:numDocId forKey:kKeyLastDocId];
//    [ud synchronize];
    }
void setNextDocID(int docid)
    { TRACE
//    NSUserDefaults* ud = [NSUserDefaults standardUserDefaults];
//    NSNumber* numDocId = [NSNumber numberWithInt:docid];
//    int i = [numDocId intValue];
//    i++;
//    NSNumber* next = [NSNumber numberWithInt:i];
//    [ud setObject:next forKey:kKeyLastDocId];
//    [ud synchronize];
    }

