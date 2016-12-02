//
//  ez_reader.hpp
//  srv-e2e-chat
//
//  Created by Virendra Shakya on 1/17/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef ez_reader_hpp
#define ez_reader_hpp

#include <string>
#include "chat_types.h"
using namespace std;
class TUnPacker;
class TPacker;

bool extractString(TUnPacker& aUnPacker, string& aStr);
bool extractInt64(TUnPacker& aUnPacker, vs_uint64_t& aInt);

#endif /* ez_reader_hpp */
