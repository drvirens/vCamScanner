//
//  file_utils_wrapper.hpp
//  vsopencvios
//
//  Created by Virendra Shakya on 11/27/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#ifndef file_utils_wrapper_hpp
#define file_utils_wrapper_hpp

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
	
void storeCapturedImage(const void* imageData, size_t imageSize);
const char* storedJpegImageFullPath(void);

#ifdef __cplusplus
}
#endif

#endif /* file_utils_wrapper_hpp */
