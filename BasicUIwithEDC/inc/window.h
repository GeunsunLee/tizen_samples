#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <Elementary.h>

Evas_Object *window_create(const char *name);
void window_destroy(void);
void window_register_delete_request_cb(Evas_Smart_Cb *cb, void *data);
void window_unregister_delete_request_cb(Evas_Smart_Cb *cb);
Evas_Object *window_get(void);

#endif /* __WINDOW_H__ */
