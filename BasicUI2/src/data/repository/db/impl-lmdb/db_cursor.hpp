//
//  db_cursor.hpp
//  vsopencvios
//
//  Created by Virendra Shakya on 12/5/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef db_cursor_hpp
#define db_cursor_hpp

#include "db_table.hpp"
#include "chat_types.h"

typedef enum
    {
    eCursorDirectionForward,
    eCursorDirectionBackward
    } eCursorDirection;

class vsCursor
    {
public:
    vsCursor(const vsTable& aTable, MDB_cursor* aCursor);
    bool positionAt(vs_uint8_t ** aKey, uint32_t* aKeyLen, vs_uint8_t ** aValue, uint32_t* aValueLen, eCursorDirection direction);
    bool next(vs_uint8_t ** aKey, uint32_t* aKeyLen, vs_uint8_t ** aValue, uint32_t* aValueLen);
    bool prev(vs_uint8_t ** aKey, uint32_t* aKeyLen, vs_uint8_t ** aValue, uint32_t* aValueLen);
    virtual ~vsCursor();
private:
    const vsTable& iTbl; //using
    MDB_cursor* iCursor; //using
    };

#endif /* db_cursor_hpp */
