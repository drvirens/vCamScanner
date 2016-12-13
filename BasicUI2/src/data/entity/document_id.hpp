//
//  document_id.hpp
//  vsopencvios
//
//  Created by Virendra Shakya on 12/12/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef document_id_hpp
#define document_id_hpp

#include <string>
using namespace std;

extern void setLastDocID(int docid);
extern void setNextDocID(int docid);
extern void retrieveLastDocID(string& docid);

#endif /* document_id_hpp */
