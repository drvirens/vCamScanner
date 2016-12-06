//
//  db_cursor.cpp
//  vsopencvios
//
//  Created by Virendra Shakya on 12/5/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "db_cursor.hpp"
#include "trace.h"

vsCursor::vsCursor(const vsTable& aTable, MDB_cursor* aCursor)
    : iTbl(aTable)
    , iCursor(aCursor)
    { TRACE
    }
vsCursor::~vsCursor()
    { TRACE
    }
bool vsCursor::positionAt(vs_uint8_t ** aKey, uint32_t* aKeyLen, vs_uint8_t ** aValue, uint32_t* aValueLen, eCursorDirection direction) const
    { TRACE
    bool ret = true;
    if (!aKey || 0 == aKeyLen) 
        {
        ret = false;
        return ret;
        }
        
    MDB_val key = {
                  .mv_data = (void*)*aKey,
                  .mv_size = *aKeyLen
                  };
    MDB_val data = {
                   .mv_data = 0,
                   .mv_size = 0
                   };
    MDB_cursor_op op = MDB_SET_RANGE;
    if (eCursorDirectionForward == direction)
        {
        op = MDB_SET_RANGE;
        }
    else 
        {
        op = MDB_SET_KEY;
        }
    int status = mdb_cursor_get(iCursor, &key, &data, op);
    if (MDB_SUCCESS == status)
        {
        *aKey = (vs_uint8_t*)key.mv_data;
        *aKeyLen = key.mv_size;
        if (aValue)
            {
            *aValue = (vs_uint8_t*)data.mv_data;
            }
        if (aValueLen)
            {
            *aValueLen = data.mv_size;
            }
        ret = true;
        }
    else if (MDB_NOTFOUND == status) 
        {
        if (direction == eCursorDirectionBackward)
            {
            ret = prev(aKey, aKeyLen, aValue, aValueLen);
            }
        else 
            {
            ret = false;
            }
        }
    else
        {
        LOG("error = %d", status);
        ret = false;
        }
    
    return ret;
    }
bool vsCursor::next(vs_uint8_t ** aKey, uint32_t* aKeyLen, vs_uint8_t ** aValue, uint32_t* aValueLen) const
    { TRACE
    bool ret = true;
    if (!aKey || 0 == aKeyLen) 
        {
        ret = false;
        return ret;
        }
        
    MDB_val key = {
                  .mv_data = 0,
                  .mv_size = 0
                  };
    MDB_val data = {
                   .mv_data = 0,
                   .mv_size = 0
                   };
    MDB_cursor_op op = MDB_NEXT;
    int status = mdb_cursor_get(iCursor, &key, &data, op);
    if (MDB_SUCCESS == status)
        {
        *aKey = (vs_uint8_t*)key.mv_data;
        *aKeyLen = key.mv_size;
        if (aValue)
            {
            *aValue = (vs_uint8_t*)data.mv_data;
            }
        if (aValueLen)
            {
            *aValueLen = data.mv_size;
            }
        ret = true;
        }
    else
        {
        LOG("error = %d", status);
        ret = false;
        }
    
    return ret;
    }
bool vsCursor::prev(vs_uint8_t ** aKey, uint32_t* aKeyLen, vs_uint8_t ** aValue, uint32_t* aValueLen) const
    { TRACE
    bool ret = true;
    if (!aKey || 0 == aKeyLen) 
        {
        ret = false;
        return ret;
        }
        
    MDB_val key = {
                  .mv_data = 0,
                  .mv_size = 0
                  };
    MDB_val data = {
                   .mv_data = 0,
                   .mv_size = 0
                   };
    MDB_cursor_op op = MDB_PREV;
    int status = mdb_cursor_get(iCursor, &key, &data, op);
    if (MDB_SUCCESS == status)
        {
        *aKey = (vs_uint8_t*)key.mv_data;
        *aKeyLen = key.mv_size;
        if (aValue)
            {
            *aValue = (vs_uint8_t*)data.mv_data;
            }
        if (aValueLen)
            {
            *aValueLen = data.mv_size;
            }
        ret = true;
        }
    else
        {
        LOG("error = %d", status);
        ret = false;
        }
    
    return ret;
    }

