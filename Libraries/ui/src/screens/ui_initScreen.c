// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.3
// LVGL version: 8.3.6
// Project name: watch2

#include "../ui.h"

void ui_initScreen_screen_init(void)
{
ui_initScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_initScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_initScreen, lv_color_hex(0x191919), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_initScreen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_sysLoadTapsText = lv_label_create(ui_initScreen);
lv_obj_set_width( ui_sysLoadTapsText, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_sysLoadTapsText, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_sysLoadTapsText, LV_ALIGN_CENTER );
lv_label_set_text(ui_sysLoadTapsText,"system boot...");
lv_obj_set_style_text_color(ui_sysLoadTapsText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_sysLoadTapsText, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_sysLoadTapsText, &lv_font_montserrat_14, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_initScreen, ui_event_initScreen, LV_EVENT_ALL, NULL);

}
