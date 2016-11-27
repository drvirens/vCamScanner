//
//  BOFileUtil.cpp
//  vsopencvios
//
//  Created by Virendra Shakya on 11/26/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "BOFileUtil.hpp"


#define BUFLEN 512

	// Callback function invoked for every captured frame.
void BOFileUtil::storeCapturedPhotoAsJpeg(const void* image_data, size_t image_size, void *user_data)
{
	if ((NULL == image_data) || (0 == image_size)) {
		return;
	}
	char *file_path = (char *)malloc(sizeof(char) * BUFLEN);
	
	if (cameraDirectory_.length() == 0) {
		cameraDirectory_ = getWritablePath();
	}
		// Create a full path to newly created file for storing the taken photo.
	snprintf(file_path, BUFLEN, "%scam%d.jpg", cameraDirectory_.c_str(), (int)time(NULL));
	
		// Open the file for writing.
	FILE *file = fopen(file_path, "w+");
	
		// Write the image to a file.
	fwrite(image_data, 1, image_size, file);
	
		// Close the file.
	fclose(file);
}
