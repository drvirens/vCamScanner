
#include "vcamscannertizen.h"
#include "user_callbacks.h"

Evas_Object *GLOBAL_DEBUG_BOX;

void _add_entry_text(const char *text)
{
    Evas_Coord c_y;

    elm_entry_entry_append(GLOBAL_DEBUG_BOX, text);
    elm_entry_entry_append(GLOBAL_DEBUG_BOX, "<br>");
    elm_entry_cursor_end_set(GLOBAL_DEBUG_BOX);
    elm_entry_cursor_geometry_get(GLOBAL_DEBUG_BOX, NULL, &c_y, NULL, NULL);
    elm_scroller_region_show(GLOBAL_DEBUG_BOX, 0, c_y, 0, 0);
}

static Eina_Bool _pop_cb(void *data, Elm_Object_Item *item)
{
    elm_win_lower(((appdata_s *)data)->win);
    return EINA_FALSE;
}

Evas_Object *_new_button(void *data, Evas_Object *display, char *name, void *cb)
{
    // Create a button
    Evas_Object *bt = elm_button_add(display);
    elm_object_text_set(bt, name);
    evas_object_smart_callback_add(bt, "clicked", (Evas_Smart_Cb) cb, data);
    evas_object_size_hint_weight_set(bt, EVAS_HINT_EXPAND, 0.0);
    evas_object_size_hint_align_set(bt, EVAS_HINT_FILL, EVAS_HINT_FILL);
    elm_box_pack_end(display, bt);
    evas_object_show(bt);
    return bt;
}

static void _btn_clear_cb(void *data, Evas_Object *btn, void *ev)
{
    elm_entry_entry_set(GLOBAL_DEBUG_BOX, "");
}

Evas_Object *_create_new_cd_display(appdata_s *ad, char *name, void *cb, Evas_Object *conform)
{
    Evas_Object *box = elm_box_add(conform);
    elm_object_content_set(conform, box);

    elm_box_horizontal_set(box, EINA_FALSE);
    evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    evas_object_show(box);

    // Create a box for adding content
    Evas_Object *bbox = elm_box_add(box);
    Evas_Coord padding_between_buttons = 3;
    elm_box_padding_set(bbox, 0, padding_between_buttons);
    elm_box_horizontal_set(bbox, EINA_FALSE);
    evas_object_size_hint_align_set(bbox, EVAS_HINT_FILL, EVAS_HINT_FILL);
    evas_object_size_hint_weight_set(bbox, EVAS_HINT_EXPAND, 0.0);
    elm_box_pack_end(box, bbox);
    evas_object_show(bbox);


    return box;
}

static void create_base_gui(appdata_s *ad)
{
    // Required to display the camera preview correctly (without any rotation).
    elm_config_accel_preference_set("opengl");

    // Setting the window
    ad->win = elm_win_util_standard_add(PACKAGE, PACKAGE);
    elm_win_conformant_set(ad->win, EINA_TRUE);
    elm_win_autodel_set(ad->win, EINA_TRUE);
    elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
    elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_OPAQUE);

    /* Create conformant */
    Evas_Object *conform = elm_conformant_add(ad->win);
    evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    elm_win_resize_object_add(ad->win, conform);
//    evas_object_show(conform);


    // Fill the list with items
    Evas_Object* mainBox = create_buttons_in_main_window(ad, conform);

    //viren+
    elm_object_content_set(conform, mainBox);
    evas_object_show(conform);

    startCamera(ad);
    //viren-

    // Show the window after base gui is set up
    evas_object_show(ad->win);
}

static bool app_create(void *data)
{
    /*
     * Hook to take necessary actions before main event loop starts
     * Initialize UI resources and application's data
     * If this function returns true, the main loop of application starts
     * If this function returns false, the application is terminated
     */
    create_base_gui((appdata_s *)data);

    return true;
}

static void app_terminate(void *data)
{
    camera_pop_cb();
}

int main(int argc, char *argv[])
{
    appdata_s ad;
    memset(&ad, 0x00, sizeof(appdata_s));

    ui_app_lifecycle_callback_s event_callback;
    memset(&event_callback, 0x00, sizeof(ui_app_lifecycle_callback_s));

    event_callback.create = app_create;
    event_callback.terminate = app_terminate;

    int error_code = ui_app_main(argc, argv, &event_callback, &ad);
    if (error_code != APP_ERROR_NONE)
        DLOG_PRINT_ERROR("ui_app_main()", error_code);

    return error_code;
}

