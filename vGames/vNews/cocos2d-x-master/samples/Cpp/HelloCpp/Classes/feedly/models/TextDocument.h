//
//  TextDocument.h
//  HelloCpp
//
//  Created by Virendra Shakya on 11/29/13.
//
//

#ifndef __HelloCpp__TextDocument__
#define __HelloCpp__TextDocument__

#include <string>
using namespace std;


class TextDocument {
  public:
    std::string toPlainText() const;
    void setHtml(const std::string &content);
};

#endif /* defined(__HelloCpp__TextDocument__) */
