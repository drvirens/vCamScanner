//
//  document_record_creiterion.hpp
//  vsopencvios
//
//  Created by Virendra Shakya on 12/5/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef document_record_creiterion_hpp
#define document_record_creiterion_hpp

#include "record_criterion.hpp"

class vsDocumentRecordCreiterion : public vsRecordCreiterion
    {
public:
    virtual bool fulfillsCriteria(const vsModelBase& retrievedRecord);
    virtual ~vsDocumentRecordCreiterion();
    };

#endif /* document_record_creiterion_hpp */
