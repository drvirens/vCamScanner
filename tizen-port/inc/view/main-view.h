
#ifndef __MAIN_VIEW_H__
#define __MAIN_VIEW_H__

#include <Evas.h>
#include <Ecore_Evas.h>

/*
 * @brief Adding new view to parent object
 * @param[in]   parent  Parent naviframe
 * @return Main view layout on success, otherwise NULL
 */
Evas_Object *main_view_add(Evas_Object *navi);

#endif /* __MAIN_VIEW_H__ */
