#include <Elementary.h>

#include "window.h"
#include "log.h"

static struct _s_info {
	Evas_Object *win;
} s_info = {
		.win = NULL,
};

Evas_Object *window_create(const char *name)
{
	Evas_Object *win = NULL;

	if (name == NULL) {
		__E("window name is NULL");
		__E("set the default name for window");
		name = "DEFAULT_WINDOW";
	}

	win = elm_win_util_standard_add(name, name);
	if (win == NULL) {
		__E("Failed to add window: %s", name);
		return NULL;
	}

	elm_win_conformant_set(win, EINA_TRUE);
	elm_win_autodel_set(win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(win, (const int *)(&rots), 4);
	}

	s_info.win = win;

	return win;
}

void window_destroy(void)
{
	if (s_info.win != NULL) {
		__E("Window is already destroyed");
		return;
	}

	evas_object_del(s_info.win);
	s_info.win = NULL;
}

void window_register_delete_request_cb(Evas_Smart_Cb *cb, void *data)
{
	if (s_info.win == NULL) {
		__E("Window is not exist");
		return;
	}

	evas_object_smart_callback_add(s_info.win, "delete,request", cb, data);
}

void window_unregister_delete_request_cb(Evas_Smart_Cb *cb)
{
	if (s_info.win == NULL) {
		__E("Window is not exist");
		return;
	}

	evas_object_smart_callback_del(s_info.win, "delete,request", cb);
}

Evas_Object *window_get(void)
{
	return s_info.win;
}
