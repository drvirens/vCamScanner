//
//  BOFileUtil.hpp
//  vsopencvios
//
//  Created by Virendra Shakya on 11/26/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef BOFileUtil_hpp
#define BOFileUtil_hpp

#include <stdio.h>
#include <string>

using namespace std;

class BOFileUtil {
	
public:
	static void storeCapturedPhotoAsJpeg(const void* image_data, size_t image_size, void *user_data);
	
	virtual string getWritablePath() const = 0;
	
};

#endif /* BOFileUtil_hpp */
