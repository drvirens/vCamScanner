//
//  record_criterion.hpp
//  vsopencvios
//
//  Created by Virendra Shakya on 12/5/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef record_criterion_hpp
#define record_criterion_hpp

#include "chat_types.h"

class vsModelBase;

/**
 Criteria for selecting a record in get queries
 */
class vsRecordCreiterion
    {
public:
//    explicit vsRecordCreiterion(vsModelBase& model)
//        : iRecord(model)
//        {
//        }
    virtual ~vsRecordCreiterion(){}
    virtual bool fulfillsCriteria(const vsModelBase& retrievedRecord) = 0;
        
//private:
//    vsModelBase& iRecord;
    };

#endif /* record_criterion_hpp */
