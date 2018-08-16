#include "conform.h"
#include "log.h"

static struct _s_info {
	Evas_Object *conform;
} s_info = {
		.conform = NULL,
};

Evas_Object *conform_create(Evas_Object *parent)
{
	Evas_Object *conform = NULL;

	if (parent == NULL) {
		__E("parent is NULL");
		return NULL;
	}

	conform = elm_conformant_add(parent);
	if (conform == NULL) {
		__E("Failed to add conformant");
		return NULL;
	}

	elm_win_indicator_mode_set(parent, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(parent, ELM_WIN_INDICATOR_OPAQUE);
	evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(parent, conform);
	evas_object_show(conform);

	s_info.conform = conform;

	return conform;
}

void conform_destroy(void)
{
	if (s_info.conform == NULL) {
		__E("conform is already destroyed");
		return;
	}

	evas_object_del(s_info.conform);
	s_info.conform = NULL;
}

Evas_Object *conform_get(void)
{
	return s_info.conform;
}
