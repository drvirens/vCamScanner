/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "user_callbacks.h"

#include <stdio.h>
#include <unistd.h>
#include <camera.h>
#include <storage.h>

#include "test.h"
#include "BOFileUtil_Tizen.h"

#define BUFLEN 512

typedef struct _camdata {
    camera_h g_camera;          // Camera handle
    Evas_Object *cam_display;
    Evas_Object *cam_display_box;
    Evas_Object *display;
    Evas_Object *preview_bt;
    Evas_Object *zoom_bt;
    Evas_Object *brightness_bt;
    Evas_Object *photo_bt;
    bool cam_prev;
} camdata;
static camdata cam_data;

static char *camera_directory = NULL;
BOFileUtil* fileUtil_ = 0;

static const char *_camera_state_to_string(camera_state_e state)
{
    switch (state) {
    case CAMERA_STATE_NONE:
        return "CAMERA_STATE_NONE";

    case CAMERA_STATE_CREATED:
        return "CAMERA_STATE_CREATED";

    case CAMERA_STATE_PREVIEW:
        return "CAMERA_STATE_PREVIEW";

    case CAMERA_STATE_CAPTURING:
        return "CAMERA_STATE_CAPTURING";

    case CAMERA_STATE_CAPTURED:
        return "CAMERA_STATE_CAPTURED";

    default:
        return "Unknown";
    }
}

static bool _storage_cb(int storage_id, storage_type_e type, storage_state_e state,
                        const char *path, void *user_data)
{
    if (STORAGE_TYPE_INTERNAL == type) {
        int *internal_storage_id = (int *)user_data;

        if (NULL != internal_storage_id)
            *internal_storage_id = storage_id;

        // Internal storage found, stop the iteration.
        return false;
    } else {
        // Continue iterating over storages.
        return true;
    }
}

// Callback function invoked for every preview resolution that is supported by the device.
static bool _preview_resolution_cb(int width, int height, void *user_data)
{
    if (NULL != user_data) {
        int *resolution = (int *)user_data;
        resolution[0] = width;
        resolution[1] = height;
    }

    return true;
}

// Callback function invoked when image capturing is finished.
static void _camera_completed_cb(void *user_data)
{
    // Start the camera preview again.
    int error_code = camera_start_preview(cam_data.g_camera);
    if (CAMERA_ERROR_NONE != error_code) {
        DLOG_PRINT_ERROR("camera_start_preview()", error_code);
        PRINT_MSG("Could not restart the camera preview.");
    }
}

static void _image_saved(void *data)
{
	char *file_path = (char*)data;
	if (file_path) {
		PRINT_MSG("read the saved file here and do opencv processing on it");
		testpleaseScan(file_path);
	}

    PRINT_MSG("Image stored in the %s", (char *)data);
    free(data);
}

// Callback function invoked for every captured frame.
static void _camera_capturing_cb(camera_image_data_s *image, camera_image_data_s *postview,
                                 camera_image_data_s *thumbnail, void *user_data)
{
    if (NULL != image && NULL != image->data) {
        dlog_print(DLOG_DEBUG, LOG_TAG, "Writing image to file.");

        if (!fileUtil_) {
			fileUtil_ = new BOFileUtil_Tizen();
			fileUtil_->init();
		}

        const void* imageData = image->data;
        size_t imageSize = image->size;
		fileUtil_->storeCapturedPhotoAsJpeg(imageData, imageSize, 0);

        /*
        char *file_path = (char *)malloc(sizeof(char) * BUFLEN);

        // Create a full path to newly created file for storing the taken photo.
        snprintf(file_path, BUFLEN, "%s/cam%d.jpg", camera_directory, (int)time(NULL));

        // Open the file for writing.
        FILE *file = fopen(file_path, "w+");

        // Write the image to a file.
        fwrite(image->data, 1, image->size, file);

        // Close the file.
        fclose(file);
        */

       // ecore_job_add(_image_saved, (void *)file_path);
    } else {
        dlog_print(DLOG_ERROR, LOG_TAG,
                   "An error occurred during taking the photo. The image is NULL.");
    }
}

// Callback function invoked when the camera focusing state changes.
static void _camera_focus_cb(camera_focus_state_e state, void *user_data)
{
    if (CAMERA_FOCUS_STATE_FOCUSED == state) {
        // Take a photo.
        int error_code =
            camera_start_capture(cam_data.g_camera, _camera_capturing_cb, _camera_completed_cb,
                                 NULL);
        if (CAMERA_ERROR_NONE != error_code) {
            DLOG_PRINT_ERROR("camera_start_capture()", error_code);
            PRINT_MSG("Could not start taking a photo.");
        }
    }
}

// Callback invoked when the "Take a photo" button is clicked.
static void __camera_cb_photo(appdata_s *ad, Evas_Object *obj, void *event_info)
{
    // Focus the camera on the current view.
    int error_code = camera_start_focusing(cam_data.g_camera, false);
    if (CAMERA_ERROR_NONE != error_code) {
        if (CAMERA_ERROR_NOT_SUPPORTED != error_code) {
            DLOG_PRINT_ERROR("camera_start_focusing()", error_code);
            PRINT_MSG("Focusing is not supported on this device. The picture will be taken without focusing.");
        } else {
            dlog_print(DLOG_INFO, LOG_TAG,
                       "Focusing is not supported on this device. The picture will be taken without focusing.");
        }

        // Take a photo (If the focusing is not supported, then just take a photo, without focusing).
        error_code =
            camera_start_capture(cam_data.g_camera, _camera_capturing_cb, _camera_completed_cb,
                                 NULL);
        if (CAMERA_ERROR_NONE != error_code) {
            DLOG_PRINT_ERROR("camera_start_capture()", error_code);
            PRINT_MSG("Could not start capturing the photo.");
        }
    }
}

// Callback function invoked when "Brightness" button is clicked.
static void __camera_cb_bright(appdata_s *ad, Evas_Object *obj, void *event_info)
{
    // Get the minimal and maximal supported value for the camera brightness attribute.
    int min, max;

    int error_code = camera_attr_get_brightness_range(cam_data.g_camera, &min, &max);
    if (CAMERA_ERROR_NONE != error_code) {
        DLOG_PRINT_ERROR("camera_attr_get_brightness_range()", error_code);
        PRINT_MSG("Could not get brightness range.");
    }

    // Get the current value of the camera brightness attribute.
    int brightness_level;

    error_code = camera_attr_get_brightness(cam_data.g_camera, &brightness_level);
    if (CAMERA_ERROR_NONE != error_code) {
        DLOG_PRINT_ERROR("camera_attr_get_brightness()", error_code);
        PRINT_MSG("Could not get current brightness value.");
    }

    // Set new value of the camera brightness attribute
    brightness_level = brightness_level == max ? min : ++brightness_level;
    error_code = camera_attr_set_brightness(cam_data.g_camera, brightness_level);
    if (CAMERA_ERROR_NONE != error_code) {
        if (CAMERA_ERROR_NOT_SUPPORTED != error_code) {
            DLOG_PRINT_ERROR("camera_attr_set_brightness()", error_code);
            PRINT_MSG("Could not set new brightness value.");
        } else
            dlog_print(DLOG_INFO, LOG_TAG, "Camera brightness is not supported on this device.");
    } else
        PRINT_MSG("Brightness value set to %d", brightness_level);
}

// Callback function invoked when "Zoom" button is clicked.
static void __camera_cb_zoom(appdata_s *ad, Evas_Object *obj, void *event_info)
{
    // Get the minimal and maximal supported value for the camera zoom attribute.
    int min, max;

    int error_code = camera_attr_get_zoom_range(cam_data.g_camera, &min, &max);
    if (CAMERA_ERROR_NONE != error_code) {
        DLOG_PRINT_ERROR("camera_attr_get_zoom_range()", error_code);
        PRINT_MSG("Could not get zoom range.");
    }

    // Get the current value of the camera zoom attribute.
    int zoom;

    error_code = camera_attr_get_zoom(cam_data.g_camera, &zoom);
    if (CAMERA_ERROR_NONE != error_code) {
        DLOG_PRINT_ERROR("camera_attr_get_zoom()", error_code);
        PRINT_MSG("Could not get current zoom value.");
    }

    // Set new value of the camera zoom attribute
    zoom = zoom == max ? min : ++zoom;
    error_code = camera_attr_set_zoom(cam_data.g_camera, zoom);
    if (CAMERA_ERROR_NONE != error_code) {
        if (CAMERA_ERROR_NOT_SUPPORTED != error_code) {
            DLOG_PRINT_ERROR("camera_attr_set_zoom()", error_code);
            PRINT_MSG("Could not set new zoom value.");
        } else {
            dlog_print(DLOG_INFO, LOG_TAG, "Camera zoom is not supported on this device.");
            PRINT_MSG("Camera zoom is not supported on this device.");
        }
    } else
        PRINT_MSG("Zoom value set to %d", zoom);
}

// Callback invoked when the "Start preview" button is clicked.
static void __camera_cb_preview(appdata_s *ad, Evas_Object *obj, void *event_info)
{
    int error_code = CAMERA_ERROR_NONE;

    if (!cam_data.cam_prev) {
        // Show the camera preview UI element.
        evas_object_size_hint_weight_set(cam_data.display, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
        evas_object_size_hint_weight_set(cam_data.cam_display_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
        evas_object_show(cam_data.cam_display_box);

        // Start the camera preview.
        error_code = camera_start_preview(cam_data.g_camera);
        if (CAMERA_ERROR_NONE != error_code) {
            DLOG_PRINT_ERROR("camera_start_preview()", error_code);
            PRINT_MSG("Could not start the camera preview.");
            return;
        }

        PRINT_MSG("Camera preview started.");
        cam_data.cam_prev = true;

        elm_object_text_set(cam_data.preview_bt, "Stop preview");

        // Enable other camera buttons.
        elm_object_disabled_set(cam_data.zoom_bt, EINA_FALSE);
        elm_object_disabled_set(cam_data.brightness_bt, EINA_FALSE);
        elm_object_disabled_set(cam_data.photo_bt, EINA_FALSE);
    } else {
        // Hide the camera preview UI element.
        evas_object_size_hint_weight_set(cam_data.display, EVAS_HINT_EXPAND, 0.0);
        evas_object_size_hint_weight_set(cam_data.cam_display_box, EVAS_HINT_EXPAND, 0.0);
        evas_object_hide(cam_data.cam_display_box);

        // Stop the camera preview.
        error_code = camera_stop_preview(cam_data.g_camera);
        if (CAMERA_ERROR_NONE != error_code) {
            DLOG_PRINT_ERROR("camera_stop_preview()", error_code);
            PRINT_MSG("Could not stop the camera preview.");
            return;
        }

        PRINT_MSG("Camera preview stopped.");
        cam_data.cam_prev = false;

        elm_object_text_set(cam_data.preview_bt, "Start preview");

        // Disable other camera buttons.
        elm_object_disabled_set(cam_data.zoom_bt, EINA_TRUE);
        elm_object_disabled_set(cam_data.brightness_bt, EINA_TRUE);
        elm_object_disabled_set(cam_data.photo_bt, EINA_TRUE);
    }
}

// Callback invoked when the "Camera" screen is being closed.
void camera_pop_cb()
{
    // Stop camera focusing.
    camera_cancel_focusing(cam_data.g_camera);

    // Stop camera preview.
    camera_stop_preview(cam_data.g_camera);
    cam_data.cam_prev = false;

    // Unregister camera preview callback.
    camera_unset_preview_cb(cam_data.g_camera);

    // Unregister camera focus change callback.
    camera_unset_focus_changed_cb(cam_data.g_camera);

    // Destroy camera handle.
    camera_destroy(cam_data.g_camera);
    cam_data.g_camera = NULL;

    // Free the Camera directory path.
    free(camera_directory);
}

// Callback function invoked when the size of the box changes.
void _post_render_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
    Evas_Object **cam_data_image = (Evas_Object **)data;

    // Get the size of the parent box.
    int x = 0, y = 0, w = 0, h = 0;
    evas_object_geometry_get(obj, &x, &y, &w, &h);

    // Set the size of the image object.
    evas_object_resize(*cam_data_image, w, h);
    evas_object_move(*cam_data_image, 0, y);
}

// Camera menu creation.
Evas_Object* create_buttons_in_main_window(appdata_s *ad, Evas_Object *conform)
{
    // Create the window with camera preview and buttons for manipulating the camera and taking the photo.
    //cam_data.display = _create_new_cd_display(ad, "Camera", NULL);
	cam_data.display = _create_new_cd_display(ad, "", NULL, conform);

    //viren+
    //original
    // Create a box for the camera preview.
//    cam_data.cam_display_box = elm_box_add(cam_data.display);
//    elm_box_horizontal_set(cam_data.cam_display_box, EINA_FALSE);
//    evas_object_size_hint_align_set(cam_data.cam_display_box, EVAS_HINT_FILL, EVAS_HINT_FILL);
//    evas_object_size_hint_weight_set(cam_data.cam_display_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
//    elm_box_pack_end(cam_data.display, cam_data.cam_display_box);
//    evas_object_show(cam_data.cam_display_box);

    //modified
    cam_data.cam_display_box = elm_box_add(cam_data.display);
	elm_box_horizontal_set(cam_data.cam_display_box, EINA_FALSE);
	evas_object_size_hint_align_set(cam_data.cam_display_box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(cam_data.cam_display_box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_box_pack_end(cam_data.display, cam_data.cam_display_box);
	evas_object_show(cam_data.cam_display_box);
        //viren-

    Evas *evas = evas_object_evas_get(cam_data.cam_display_box);
    cam_data.cam_display = evas_object_image_add(evas);
    evas_object_event_callback_add(cam_data.cam_display_box, EVAS_CALLBACK_RESIZE, _post_render_cb,
                                   &(cam_data.cam_display));

#if 0 //viren+

    // Create buttons for the Camera.
    cam_data.preview_bt = _new_button(ad, cam_data.display, "Start preview", __camera_cb_preview);
    cam_data.zoom_bt = _new_button(ad, cam_data.display, "Zoom", __camera_cb_zoom);
    cam_data.brightness_bt = _new_button(ad, cam_data.display, "Brightness", __camera_cb_bright);
    cam_data.photo_bt = _new_button(ad, cam_data.display, "Take a photo", __camera_cb_photo);

    // Disable buttons different than "Start preview" when the preview is not running.
    elm_object_disabled_set(cam_data.zoom_bt, EINA_TRUE);
    elm_object_disabled_set(cam_data.brightness_bt, EINA_TRUE);
    elm_object_disabled_set(cam_data.photo_bt, EINA_TRUE);
#endif //viren-

	cam_data.photo_bt = _new_button(ad, cam_data.display, "Take a photo", __camera_cb_photo);

    return cam_data.display;
}

int startCamera(appdata_s *ad) {

    // Create the camera handle for the main camera of the device.
    int error_code = camera_create(CAMERA_DEVICE_CAMERA0, &(cam_data.g_camera));
    if (CAMERA_ERROR_NONE != error_code) {
        DLOG_PRINT_ERROR("camera_create()", error_code);
        PRINT_MSG("Could not create a handle to the camera.");
        return 0;
    }

    // Check the camera state after creating the handle.
    camera_state_e state;
    error_code = camera_get_state(cam_data.g_camera, &state);
    if (CAMERA_ERROR_NONE != error_code || CAMERA_STATE_CREATED != state) {
        dlog_print(DLOG_ERROR, LOG_TAG, "camera_get_state() failed! Error code = %d, state = %s",
                   error_code, _camera_state_to_string(state));
        return 0;
    }

    // Enable EXIF data storing during taking picture. This is required to edit the orientation of the image.
    error_code = camera_attr_enable_tag(cam_data.g_camera, true);
    if (CAMERA_ERROR_NONE != error_code) {
        DLOG_PRINT_ERROR("camera_attr_enable_tag()", error_code);
        PRINT_MSG("Could not enable the camera tag.");
    }

    // Set the camera image orientation. Required (on Kiran device) to save the image in regular orientation (without any rotation).
    error_code =
        camera_attr_set_tag_orientation(cam_data.g_camera, CAMERA_ATTR_TAG_ORIENTATION_RIGHT_TOP);
    if (CAMERA_ERROR_NONE != error_code) {
        DLOG_PRINT_ERROR("camera_attr_set_tag_orientation()", error_code);
        PRINT_MSG("Could not set the camera image orientation.");
    }

    // Set the picture quality attribute of the camera to maximum.
    error_code = camera_attr_set_image_quality(cam_data.g_camera, 100);
    if (CAMERA_ERROR_NONE != error_code) {
        DLOG_PRINT_ERROR("camera_attr_set_image_quality()", error_code);
        PRINT_MSG("Could not set the picture quality.");
    }

    // Set the display for the camera preview.
    error_code =
        camera_set_display(cam_data.g_camera, CAMERA_DISPLAY_TYPE_EVAS,
                           GET_DISPLAY(cam_data.cam_display));
    if (CAMERA_ERROR_NONE != error_code) {
        DLOG_PRINT_ERROR("camera_set_display()", error_code);
        PRINT_MSG("Could not set the camera display.");
        return 0;
    }

    // Set the resolution of the camera preview:
    int resolution[2];

    // 1. Find the best resolution that is supported by the device.
    error_code =
        camera_foreach_supported_preview_resolution(cam_data.g_camera, _preview_resolution_cb,
                resolution);
    if (CAMERA_ERROR_NONE != error_code) {
        DLOG_PRINT_ERROR("camera_foreach_supported_preview_resolution()", error_code);
        PRINT_MSG("Could not find the best resolution for the camera preview.");
        return 0;
    }

    // 2. Set found supported resolution for the camera preview.
    error_code = camera_set_preview_resolution(cam_data.g_camera, resolution[0], resolution[1]);
    if (CAMERA_ERROR_NONE != error_code) {
        DLOG_PRINT_ERROR("camera_set_preview_resolution()", error_code);
        PRINT_MSG("Could not set the camera preview resolution.");
    } else
        PRINT_MSG("Camera resolution set to: %d %d", resolution[0], resolution[1]);

    // Set the capture format for the camera.
    error_code = camera_set_capture_format(cam_data.g_camera, CAMERA_PIXEL_FORMAT_JPEG);
    if (CAMERA_ERROR_NONE != error_code) {
        DLOG_PRINT_ERROR("camera_set_capture_format()", error_code);
        PRINT_MSG("Could not set the capturing format.");
    }

    // Set the focusing callback function.
    error_code = camera_set_focus_changed_cb(cam_data.g_camera, _camera_focus_cb, NULL);
    if (CAMERA_ERROR_NONE != error_code) {
        DLOG_PRINT_ERROR("camera_set_focus_changed_cb()", error_code);
        PRINT_MSG("Could not set a callback for the focus changes.");
    }

    // Get the path to the Camera directory:

    // 1. Get internal storage id.
    int internal_storage_id = -1;

    error_code = storage_foreach_device_supported(_storage_cb, &internal_storage_id);
    if (STORAGE_ERROR_NONE != error_code) {
        DLOG_PRINT_ERROR("storage_foreach_device_supported()", error_code);
        PRINT_MSG("Could not get internal storage id.");
        return 0;
    }

    // 2. Get the path to the Camera directory.
    error_code =
        storage_get_directory(internal_storage_id, STORAGE_DIRECTORY_CAMERA, &camera_directory);
    if (STORAGE_ERROR_NONE != error_code) {
        DLOG_PRINT_ERROR("storage_get_directory()", error_code);
        PRINT_MSG("Could not get the path to the Camera directory.");
    }

    //viren+
    __camera_cb_preview(0, 0, 0);
    //viren-

    return 1;
}


