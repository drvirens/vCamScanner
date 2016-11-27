//
//  BOCameraUtil.cpp
//  vsopencvios
//
//  Created by Virendra Shakya on 11/26/16.
//  Copyright © 2016 Virendra Shakya. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "BOCameraUtil.hpp"


#define BUFLEN 512

static char *camera_directory = NULL;

	// Callback function invoked for every captured frame.
void didCapturePhoto(const void* image_data, size_t image_size, void *user_data)
{
	if (NULL == image_data) {
		return;
	}
	char *file_path = (char *)malloc(sizeof(char) * BUFLEN);
	
		// Create a full path to newly created file for storing the taken photo.
	snprintf(file_path, BUFLEN, "%s/cam%d.jpg", camera_directory, (int)time(NULL));
	
		// Open the file for writing.
	FILE *file = fopen(file_path, "w+");
	
		// Write the image to a file.
	fwrite(image_data, 1, image_size, file);
	
		// Close the file.
	fclose(file);
}
