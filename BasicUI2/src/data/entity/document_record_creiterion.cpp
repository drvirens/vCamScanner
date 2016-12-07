//
//  document_record_creiterion.cpp
//  vsopencvios
//
//  Created by Virendra Shakya on 12/5/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "document_record_creiterion.hpp"
#include "trace.h"

bool vsDocumentRecordCreiterion::fulfillsCriteria(const vsModelBase& retrievedRecord)
    { TRACE
    return true;
    }
    
vsModelBase& vsDocumentRecordCreiterion::model() const
    { TRACE
    return const_cast<vsDocument&>(iModel);
    }

vsDocumentRecordCreiterion::~vsDocumentRecordCreiterion()
    { TRACE
        
    }
    
    
