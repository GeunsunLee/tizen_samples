#include "basicuiwithedc.h"
#include "window.h"
#include "conform.h"
#include "layout.h"
#include "log.h"

static void __win_delete_request_cb(void *data, Evas_Object *obj, void *event_info)
{
	ui_app_exit();
}

static void __layout_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	/* Let window go to hide state. */

	Evas_Object *win = (Evas_Object *) data;
	if (win == NULL) {
		__E("win is NULL");
		return;
	}

	elm_win_lower(win);
}

static void app_get_resource(const char *edj_file_in, char *edj_path_out, int edj_path_max)
{
	char *res_path = app_get_resource_path();
	if (res_path) {
		snprintf(edj_path_out, edj_path_max, "%s%s", res_path, edj_file_in);
		free(res_path);
	}
}

static void create_base_gui(void)
{
	Evas_Object *win = NULL;
	Evas_Object *conform = NULL;
	Evas_Object *layout = NULL;
	char edj_path[PATH_MAX] = {0, };

	/* Window */
	win = window_create(PACKAGE);
	if (win == NULL) {
		__E("Failed to create window");
		return;
	}

	window_register_delete_request_cb(__win_delete_request_cb, NULL);

	/* Conformant */
	conform = conform_create(win);
	if (conform == NULL) {
		__E("Failed to create conform");
		window_unregister_delete_request_cb(__win_delete_request_cb);
		window_destroy();
		return;
	}

	/* Base Layout */
	app_get_resource(EDJ_FILE, edj_path, (int)PATH_MAX);

	layout = layout_create(win, edj_path, GRP_MAIN);
	if (layout == NULL) {
		__E("Failed to create layout");
		conform_destroy();
		window_unregister_delete_request_cb(__win_delete_request_cb);
		window_destroy();
		return;
	}

	layout_register_back_cb(layout, __layout_back_cb, win);
	elm_object_content_set(conform, layout);

	/* Show window after base gui is set up */
	evas_object_show(win);
}

static bool app_create(void *data)
{
	create_base_gui();

	return true;
}

static void app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

static void app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
}

static void app_resume(void *data)
{
	/* Take necessary actions when application becomes visible. */
}

static void app_terminate(void *data)
{
	/* Release all resources. */
}

static void ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/

	int ret;
	char *language;

	ret = app_event_get_language(event_info, &language);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "app_event_get_language() failed. Err = %d.", ret);
		return;
	}

	if (language != NULL) {
		elm_language_set(language);
		free(language);
	}
}

static void ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

static void ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}

int main(int argc, char *argv[])
{
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, NULL);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, NULL);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, NULL);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, NULL);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, NULL);

	ret = ui_app_main(argc, argv, &event_callback, NULL);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_main() is failed. err = %d", ret);
	}

	return ret;
}
