//
//  file_utils_wrapper.cpp
//  vsopencvios
//
//  Created by Virendra Shakya on 11/27/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include "file_utils_wrapper.hpp"
#include "BOFileUtil_iOS.hpp"

static BOFileUtil* fileUtil_;

void storeCapturedImage(const void* imageData, size_t imageSize) {
	if (!fileUtil_) {
		fileUtil_ = new BOFileUtil_iOS();
		fileUtil_->init();
	}
	fileUtil_->storeCapturedPhotoAsJpeg(imageData, imageSize, 0);
}
