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
#include "db_key_value_reader.hpp"
#include "db_data.hpp"

class vsModelBase;

/**
 Criteria for selecting a record in get queries
 */
class vsRecordCreiterion
    {
public:
    explicit vsRecordCreiterion(const vsTData& aKeyLowerBound,
                                const vsTData& aKeyUpperBound,
                                const vsIKeyValueReader::vsDirection& aDirection)
        : iKeyLowerBound(aKeyLowerBound)
        , iKeyUpperBound(aKeyUpperBound)
        , iDirection(aDirection)
        {
        }
    virtual ~vsRecordCreiterion(){}
    virtual bool fulfillsCriteria(const vsModelBase& retrievedRecord) = 0;
    
    const vsTData& keyLowerBound() const { return iKeyLowerBound; }
    const vsTData& keyUpperBound() const { return iKeyUpperBound; }
    const vsIKeyValueReader::vsDirection& direction() const { return iDirection; }
    
private:
    const vsTData iKeyLowerBound;
    const vsTData iKeyUpperBound;
    const vsIKeyValueReader::vsDirection iDirection;
    };

#endif /* record_criterion_hpp */
