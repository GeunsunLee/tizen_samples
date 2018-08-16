#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include <Elementary.h>
#include <efl_extension.h>

Evas_Object *layout_create(Evas_Object *parent, const char *edj_path, const char *group_name);
void layout_register_back_cb(Evas_Object *layout, Eext_Event_Cb *cb, void *data);
void layout_unregister_back_cb(Evas_Object *layout,  Eext_Event_Cb *cb);
Evas_Object *layout_get(void);

#endif /* __LAYOUT_H__ */
