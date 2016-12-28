
#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <Evas.h>
#include <Ecore_Evas.h>

typedef struct _window window;

/*
 * @brief Create application main window
 * @return Window on success, otherwise NULL
 */
window *window_create();

/*
 * @brief Lower application window to hide application without exiting
 * @param[in]   win     Application window
 */
void window_destroy(window *win);

/*
 * @brief Destroy application main window
 * @param[in]   win     Application window
 */
void window_lower(window *win);

/*
 * @brief Set content to be displayed in window
 * @param[in]   win     Application window
 * @param[in]   content Window content
 */
void window_content_set(window *win, Evas_Object *layout);

/*
 * @brief Get window layout to use as a parent for window content
 * @param[in]   win     Application window
 * @return Window layout
 */
Evas_Object *window_layout_get(const window *win);

#endif /* __WINDOW_H__ */
