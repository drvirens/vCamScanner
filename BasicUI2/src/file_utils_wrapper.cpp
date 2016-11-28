//
//  file_utils_wrapper.cpp
//  vsopencvios
//
//  Created by Virendra Shakya on 11/27/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "cvconfig.h"
#include "file_utils_wrapper.h"

#if defined HAVE_TIZEN
#include "BOFileUtil_Tizen.h"
#else
#include "BOFileUtil_iOS.hpp"
#endif

static BOFileUtil* fileUtil_;

void storeCapturedImage(const void* imageData, size_t imageSize) {
	if (!fileUtil_) {
#if defined HAVE_TIZEN
		fileUtil_ = new BOFileUtil_Tizen();
#else
		fileUtil_ = new BOFileUtil_iOS();
#endif
		fileUtil_->init();
	}
	fileUtil_->storeCapturedPhotoAsJpeg(imageData, imageSize, 0);
}



