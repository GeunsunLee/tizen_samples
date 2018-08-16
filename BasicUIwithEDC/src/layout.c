#include "layout.h"
#include "log.h"

Evas_Object *layout_create(Evas_Object *parent, const char *edj_path, const char *group_name)
{
	Evas_Object *layout = NULL;
	Eina_Bool ret = EINA_FALSE;

	if (parent == NULL) {
		__E("parent is NULL");
		return NULL;
	}

	if (edj_path == NULL) {
		__E("edj path is NULL");
		return NULL;
	}

	if (group_name == NULL) {
		__E("group name is NULL");
		return NULL;
	}

	layout = elm_layout_add(parent);
	if (layout == NULL) {
		__E("Failed to add layout");
		return NULL;
	}

	ret = elm_layout_file_set(layout, edj_path, group_name);
	if (ret != EINA_TRUE) {
		__E("Failed to set edje file: %s", edj_path);
		evas_object_del(layout);
		return NULL;
	}

	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	return layout;
}

void layout_register_back_cb(Evas_Object *layout, Eext_Event_Cb *cb, void *data)
{
	if (layout == NULL) {
		__E("layout is not exist");
		return;
	}

	eext_object_event_callback_add(layout, EEXT_CALLBACK_BACK, cb, data);
}

void layout_unregister_back_cb(Evas_Object *layout,  Eext_Event_Cb *cb)
{
	if (layout == NULL) {
		__E("layout is not exist");
		return;
	}

	eext_object_event_callback_del(layout, EEXT_CALLBACK_BACK, cb);
}
