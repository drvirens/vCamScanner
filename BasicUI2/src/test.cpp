/*
 * test.cpp
 *
 *  Created on: Nov 18, 2016
 *      Author: virendra.shakya
 */

#include <image_util.h>
#include <storage.h>
#include <app.h>
#include <dlog.h>
#include <stdio.h>
#include <stdlib.h>

#include "test.h"
#include "scannerLite.h"

#ifdef __cplusplus
extern "C" {
#endif

static bool _storage_cb(int storage_id, storage_type_e type, storage_state_e state,
                        const char *path, void *user_data);

int testpleaseScan() {
	//read file image
	static const char *image_util_source_filename = "doc2.jpg";
	static char sample_file_path[522] = {0};
	char *resource_path = app_get_resource_path();
	snprintf(sample_file_path, 522, "%s%s", resource_path, image_util_source_filename);

	//write image path
	static const char *write_image_util_source_filename = "dst.jpg";
//	static char write_sample_file_path[522];
//	char *write__path = app_get_data_path();
//	snprintf(write_sample_file_path, 522, "%s%s", write__path, write_image_util_source_filename);

	// Get the path to the Images directory:

	    // 1. Get internal storage id.
	    int internal_storage_id = -1;

	    int error_code = storage_foreach_device_supported(_storage_cb, &internal_storage_id);
	    if (STORAGE_ERROR_NONE != error_code) {
	        dlog_print(DLOG_ERROR, LOG_TAG,
	                   "storage_foreach_device_supported() failed! Error code = %d", error_code);
	        free(resource_path);
	        return 0;
	    }

	    static char *images_directory = NULL;
	    // 2. Get the path to the Images directory.
	    error_code =
	        storage_get_directory(internal_storage_id, STORAGE_DIRECTORY_IMAGES, &images_directory);
	    if (STORAGE_ERROR_NONE != error_code) {
	        dlog_print(DLOG_ERROR, LOG_TAG, "storage_get_directory() failed with error code: %d",
	                   error_code);
	    }




	    static char image_util_filename_encoded[522] = {0};

	    snprintf(image_util_filename_encoded, 522, "%s/%s", images_directory,
	    		write_image_util_source_filename);

//	    snprintf(image_util_filename_encoded, 522, "%s/%s", resource_path,
//	             image_util_source_filename);
	    free(resource_path);

	const char* thepath = sample_file_path;
	const char* theOutputPath = image_util_filename_encoded;
	pleaseScan(thepath, theOutputPath);
	return 0;
}

static bool _storage_cb(int storage_id, storage_type_e type, storage_state_e state,
                        const char *path, void *user_data)
{
    if (STORAGE_TYPE_INTERNAL == type) {
        int *internal_storage_id = (int *)user_data;
        *internal_storage_id = storage_id;

        // Internal storage found, stop the iteration.
        return false;
    } else {
        // Continue iterating over storages.
        return true;
    }
}

#ifdef __cplusplus
}
#endif
