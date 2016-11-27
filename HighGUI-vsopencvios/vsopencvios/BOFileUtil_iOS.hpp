//
//  BOFileUtil_iOS.hpp
//  vsopencvios
//
//  Created by Virendra Shakya on 11/27/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef BOFileUtil_iOS_hpp
#define BOFileUtil_iOS_hpp

#include "BOFileUtil.h"

class BOFileUtil_iOS : public BOFileUtil {
public:
	virtual void init();
	virtual string getWritablePath() const;
};

#endif /* BOFileUtil_iOS_hpp */
