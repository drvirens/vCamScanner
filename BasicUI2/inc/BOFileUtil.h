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
	virtual void init() = 0;
	void storeCapturedPhotoAsJpeg(const void* image_data, size_t image_size, void *user_data);
	string getLastCapturedJpegFullpath() const;
	
	virtual string getWritablePath() const = 0;
	virtual ~BOFileUtil();
	
protected:
	string cameraDirectory_;
	string lastCapturedJpegFullpath_;
};

#endif /* BOFileUtil_hpp */
