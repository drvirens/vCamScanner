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
        
void retrieveLastDocID(string& docid)
    { TRACE
    int lastusedid = getLastUsedDocID();
    stringstream ss;
    ss << lastusedid;
    docid = ss.str();
    }

