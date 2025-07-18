// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 9.1.0
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"


#include <Arduino.h>
#include "global.h"

///////////////////// VARIABLES ////////////////////
void logoFade_Animation(lv_obj_t * TargetObject, int delay);
void logoEventFade_Animation(lv_obj_t * TargetObject, int delay);
void slideup_Animation(lv_obj_t * TargetObject, int delay);
void scale_Animation(lv_obj_t * TargetObject, int delay);
void slidedown_Animation(lv_obj_t * TargetObject, int delay);
void gridstroke1_Animation(lv_obj_t * TargetObject, int delay);
void gridstroke2_Animation(lv_obj_t * TargetObject, int delay);
void solarstroke1_Animation(lv_obj_t * TargetObject, int delay);
void solarstroke2_Animation(lv_obj_t * TargetObject, int delay);
void inverterstroke1_Animation(lv_obj_t * TargetObject, int delay);
void inverterstroke2_Animation(lv_obj_t * TargetObject, int delay);
void btn_Animation(lv_obj_t * TargetObject, int delay);


// SCREEN: ui_SplashScreen1
void ui_SplashScreen1_screen_init(void);
void ui_event_SplashScreen1(lv_event_t * e);
lv_obj_t * ui_SplashScreen1;
lv_obj_t * ui_Block;
lv_obj_t * ui_logoBlock;
lv_obj_t * ui_logo1;
lv_obj_t * ui_splashaction;
lv_obj_t * ui_Spinner1;
lv_obj_t * ui_LoadState;
// CUSTOM VARIABLES


// SCREEN: ui_SplashScreen2
void ui_SplashScreen2_screen_init(void);
void ui_event_SplashScreen2(lv_event_t * e);
lv_obj_t * ui_SplashScreen2;
lv_obj_t * ui_Block1;
lv_obj_t * ui_logoBlock2;
lv_obj_t * ui_Image2;
lv_obj_t * ui_splashaction2;
lv_obj_t * ui_LoadLebel;
// CUSTOM VARIABLES


// SCREEN: ui_MAIN
void ui_MAIN_screen_init(void);
void ui_event_MAIN(lv_event_t * e);
lv_obj_t * ui_MAIN;
lv_obj_t * ui_MainBlock;
lv_obj_t * ui_bottomBar;
lv_obj_t * ui_header;
lv_obj_t * ui_Time;
lv_obj_t * ui_bluetoothicon;
lv_obj_t * ui_wifiIcon;
lv_obj_t * ui_lockIcon;
lv_obj_t * ui_upsIcon;
lv_obj_t * ui_liteIcon;
lv_obj_t * ui_networkIcon;
lv_obj_t * ui_HOME;
lv_obj_t * ui_HomeContibnner;
lv_obj_t * ui_sun;
lv_obj_t * ui_solarPanel;
lv_obj_t * ui_grid;
lv_obj_t * ui_pbx;
lv_obj_t * ui_load;
lv_obj_t * ui_batteryPack;
lv_obj_t * ui_batteryGuage;
lv_obj_t * ui_batteryContainner;
lv_obj_t * ui_chargingFlag;
lv_obj_t * ui_batteryHead;
lv_obj_t * ui_gridActive;
lv_obj_t * ui_gridstroke2;
lv_obj_t * ui_gridstroke1;
lv_obj_t * ui_gridstroke3;
lv_obj_t * ui_solarActive;
lv_obj_t * ui_solarstroke1;
lv_obj_t * ui_solarstroke2;
lv_obj_t * ui_solarstroke3;
lv_obj_t * ui_inverterActive;
lv_obj_t * ui_inverterstroke2;
lv_obj_t * ui_inverterstroke1;
lv_obj_t * ui_SwitchContainer;
void ui_event_pwrBtn(lv_event_t * e);
lv_obj_t * ui_pwrBtn;
lv_obj_t * ui_tabindicator;
lv_obj_t * ui_BattLabel;
lv_obj_t * ui_BattPercent;
lv_obj_t * ui_percent;
lv_obj_t * ui_SolarVoltLabel;
lv_obj_t * ui_SolarVolt;
lv_obj_t * ui_volt2;
lv_obj_t * ui_gridlabel;
lv_obj_t * ui_gridVolt;
lv_obj_t * ui_volt;
lv_obj_t * ui_SolarCurLabel;
lv_obj_t * ui_SolarCurrent;
lv_obj_t * ui_curr;
lv_obj_t * ui_LoadVoltLabel;
lv_obj_t * ui_LoadVolt;
lv_obj_t * ui_volt3;
lv_obj_t * ui_LoadPwerLabel;
lv_obj_t * ui_loadPwr;
lv_obj_t * ui_curr2;
lv_obj_t * ui_topBar;
lv_obj_t * ui_Balcontainner;
lv_obj_t * ui_Container3;
lv_obj_t * ui_Image5;
lv_obj_t * ui_Label4;
lv_obj_t * ui_Container4;
lv_obj_t * ui_BalUnit;
lv_obj_t * ui_Label6;
void ui_event_MONITOR(lv_event_t * e);
lv_obj_t * ui_MONITOR;
lv_obj_t * ui_Image8;
lv_obj_t * ui_Image9;
lv_obj_t * ui_monitorContainner;
lv_obj_t * ui_total_Usage_container;
lv_obj_t * ui_totalUsage;
lv_obj_t * ui_Label8;
lv_obj_t * ui_Label3;
lv_obj_t * ui_Image6;
lv_obj_t * ui_usageGraph;
lv_obj_t * ui_usageGraph_Xaxis;
lv_obj_t * ui_usageGraph_Yaxis1;
lv_obj_t * ui_usageGraph_Yaxis2;
lv_obj_t * ui_Label7;
lv_obj_t * ui_Panel2;
lv_obj_t * ui_Label9;
lv_obj_t * ui_Label10;
lv_obj_t * ui_Label11;
lv_obj_t * ui_battVolt;
lv_obj_t * ui_cell1;
 lv_obj_t * ui_cell2;
 lv_obj_t * ui_cell3;
lv_obj_t * ui_solarVolt;
lv_obj_t * ui_Vsys;
lv_obj_t * ui_isys;
lv_obj_t * ui_vsys2;
lv_obj_t * ui_chargeCurrent1;
lv_obj_t * ui_Bal_Unit_Containner;
lv_obj_t * ui_totalUsage1;
lv_obj_t * ui_Label12;
lv_obj_t * ui_Label13;
lv_obj_t * ui_Image7;
lv_obj_t * ui_Bal_Unit_Containner1;
lv_obj_t * ui_totalUnit;
lv_obj_t * ui_Label5;
lv_obj_t * ui_Label14;
lv_obj_t * ui_Image10;
lv_obj_t * ui_SETTING;
lv_obj_t * ui_Setting_Containner;
void ui_event_About(lv_event_t * e);
lv_obj_t * ui_About;
lv_obj_t * ui_text2;
lv_obj_t * ui_wifiContainner;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Image1;
void ui_event_wifiSwitch(lv_event_t * e);
lv_obj_t * ui_wifiSwitch;
lv_obj_t * ui_upscontianer;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Image3;
void ui_event_upsSwitch(lv_event_t * e);
lv_obj_t * ui_upsSwitch;
lv_obj_t * ui_BackLight;
lv_obj_t * ui_Image4;
lv_obj_t * ui_bleContainner1;
lv_obj_t * ui_Label15;
lv_obj_t * ui_Image13;
void ui_event_bluetoothSwitch1(lv_event_t * e);
lv_obj_t * ui_bluetoothSwitch1;
// CUSTOM VARIABLES


// SCREEN: ui_Success_Screen
void ui_Success_Screen_screen_init(void);
void ui_event_Success_Screen(lv_event_t * e);
lv_obj_t * ui_Success_Screen;
lv_obj_t * ui_MainBlock2;
lv_obj_t * ui_Image12;
lv_obj_t * ui_firstSuccessLabel;
lv_obj_t * ui_secondSuccessLabel;
// CUSTOM VARIABLES


// SCREEN: ui_Error_Screen
void ui_Error_Screen_screen_init(void);
void ui_event_Error_Screen(lv_event_t * e);
lv_obj_t * ui_Error_Screen;
lv_obj_t * ui_MainBlock1;
lv_obj_t * ui_Image11;
lv_obj_t * ui_firstErrorLabel;
lv_obj_t * ui_secondErrorLabel;
// CUSTOM VARIABLES


// SCREEN: ui_Wifi_Setup
void ui_Wifi_Setup_screen_init(void);
lv_obj_t * ui_Wifi_Setup;
lv_obj_t * ui_MainBlock3;
void ui_event_WifiList(lv_event_t * e);
lv_obj_t * ui_WifiList;
void ui_event_wifiScan(lv_event_t * e);
lv_obj_t * ui_wifiScan;
lv_obj_t * ui_text3;
void ui_event_keyboard(lv_event_t * e);
lv_obj_t * ui_keyboard;
lv_obj_t * ui_wifiLoading;
void ui_event_PassWordText(lv_event_t * e);
lv_obj_t * ui_PassWordText;
void ui_event_backHomeButton(lv_event_t * e);
lv_obj_t * ui_backHomeButton;
// CUSTOM VARIABLES

// EVENTS
lv_obj_t * ui____initial_actions0;

// IMAGES AND IMAGE SETS
const lv_image_dsc_t * ui_imgset_bluetooth[1] = {&ui_img_icons_bluetooth24_png};
const lv_image_dsc_t * ui_imgset_wifi[1] = {&ui_img_icons_wifi24_png};
const lv_image_dsc_t * ui_imgset_net[4] = {&ui_img_icons_net0_png, &ui_img_icons_net1_png, &ui_img_icons_net2_png, &ui_img_icons_net3_png};
const lv_image_dsc_t * ui_imgset_[1] = {&ui_img_12471400_png};
const lv_image_dsc_t * ui_imgset_20240808_[2] = {&ui_img_20240808_153214_png, &ui_img_20240808_165355_png};
const lv_image_dsc_t * ui_imgset_water_[1] = {&ui_img_water_3_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void logoFade_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_malloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->imgset = (lv_img_dsc_t **)ui_imgset_;
    PropertyAnimation_0_user_data->imgset_size = sizeof(ui_imgset_) / (sizeof(lv_image_dsc_t *));
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_in);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);

}
void logoEventFade_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_malloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->imgset = (lv_img_dsc_t **)ui_imgset_;
    PropertyAnimation_0_user_data->imgset_size = sizeof(ui_imgset_) / (sizeof(lv_image_dsc_t *));
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 2000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_in);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_opacity);
    lv_anim_start(&PropertyAnimation_0);

}
void slideup_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_malloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->imgset = (lv_img_dsc_t **)ui_imgset_;
    PropertyAnimation_0_user_data->imgset_size = sizeof(ui_imgset_) / (sizeof(lv_image_dsc_t *));
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 500);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 30, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_start(&PropertyAnimation_0);

}
void scale_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_malloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->imgset = (lv_img_dsc_t **)ui_imgset_;
    PropertyAnimation_0_user_data->imgset_size = sizeof(ui_imgset_) / (sizeof(lv_image_dsc_t *));
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 500);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_zoom);
    lv_anim_set_values(&PropertyAnimation_0, 0, 50);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_in_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_image_zoom);
    lv_anim_start(&PropertyAnimation_0);

}
void slidedown_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_malloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->imgset = (lv_img_dsc_t **)ui_imgset_;
    PropertyAnimation_0_user_data->imgset_size = sizeof(ui_imgset_) / (sizeof(lv_image_dsc_t *));
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 500);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, -20, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_start(&PropertyAnimation_0);

}
void gridstroke1_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_malloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->imgset = (lv_img_dsc_t **)ui_imgset_;
    PropertyAnimation_0_user_data->imgset_size = sizeof(ui_imgset_) / (sizeof(lv_image_dsc_t *));
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 100, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 10);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, true);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_start(&PropertyAnimation_0);

}
void gridstroke2_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_malloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->imgset = (lv_img_dsc_t **)ui_imgset_;
    PropertyAnimation_0_user_data->imgset_size = sizeof(ui_imgset_) / (sizeof(lv_image_dsc_t *));
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, 0, 100);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 10);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, true);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_x);
    lv_anim_start(&PropertyAnimation_0);

}
void solarstroke1_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_malloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->imgset = (lv_img_dsc_t **)ui_imgset_;
    PropertyAnimation_0_user_data->imgset_size = sizeof(ui_imgset_) / (sizeof(lv_image_dsc_t *));
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, -100, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_start(&PropertyAnimation_0);

}
void solarstroke2_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_malloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->imgset = (lv_img_dsc_t **)ui_imgset_;
    PropertyAnimation_0_user_data->imgset_size = sizeof(ui_imgset_) / (sizeof(lv_image_dsc_t *));
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, 0, 100);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 10);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_x);
    lv_anim_start(&PropertyAnimation_0);

}
void inverterstroke1_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_malloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->imgset = (lv_img_dsc_t **)ui_imgset_;
    PropertyAnimation_0_user_data->imgset_size = sizeof(ui_imgset_) / (sizeof(lv_image_dsc_t *));
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 100, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 10);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 1000);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_start(&PropertyAnimation_0);

}
void inverterstroke2_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_malloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->imgset = (lv_img_dsc_t **)ui_imgset_;
    PropertyAnimation_0_user_data->imgset_size = sizeof(ui_imgset_) / (sizeof(lv_image_dsc_t *));
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, 0, 100);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 10);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_x);
    lv_anim_start(&PropertyAnimation_0);

}
void btn_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_malloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->imgset = (lv_img_dsc_t **)ui_imgset_;
    PropertyAnimation_0_user_data->imgset_size = sizeof(ui_imgset_) / (sizeof(lv_image_dsc_t *));
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 50);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 5, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, true);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_start(&PropertyAnimation_0);

}

///////////////////// FUNCTIONS ////////////////////
void ui_event_SplashScreen1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_SCREEN_LOAD_START) {
        logoFade_Animation(ui_logo1, 0);
        logoEventFade_Animation(ui_splashaction, 0);
    }
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        _ui_screen_change(&ui_SplashScreen2, LV_SCR_LOAD_ANIM_FADE_ON, 500, 2000, &ui_SplashScreen2_screen_init);
    }
}

void ui_event_SplashScreen2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_SCREEN_LOAD_START) {
        logoFade_Animation(ui_LoadLebel, 0);
        logoFade_Animation(ui_Image2, 0);
    }
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        _ui_screen_change(&ui_MAIN, LV_SCR_LOAD_ANIM_NONE, 500, 3000, &ui_MAIN_screen_init);
    }
}

void ui_event_MAIN(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_SCREEN_LOADED) {
        gridstroke1_Animation(ui_gridstroke1, 0);
        gridstroke2_Animation(ui_gridstroke2, 0);
        solarstroke1_Animation(ui_solarstroke1, 0);
        solarstroke2_Animation(ui_solarstroke2, 0);
        inverterstroke2_Animation(ui_inverterstroke1, 0);
        inverterstroke2_Animation(ui_inverterstroke2, 0);
        solarstroke2_Animation(ui_solarstroke3, 0);
        gridstroke2_Animation(ui_gridstroke3, 0);
    }
}

void ui_event_pwrBtn(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);

    if(event_code == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(target, LV_STATE_CHECKED)) {
        power_ON(e);
    }
    if(event_code == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(target, LV_STATE_CHECKED)) {
        power_OFF(e);
       
    }
}

void ui_event_MONITOR(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_active()) == LV_DIR_TOP) {
        lv_indev_wait_release(lv_indev_active());
        _ui_flag_modify(ui_header, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

void ui_event_About(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_Wifi_Setup, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_Wifi_Setup_screen_init);
    }
}

void ui_event_wifiSwitch(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);

    if(event_code == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(target, LV_STATE_CHECKED)) {
        wifiON(e);
        // _ui_flag_modify(ui_wifiIcon, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        // wifiFlag = true;
    }
    if(event_code == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(target, LV_STATE_CHECKED)) {
        // _ui_flag_modify(ui_wifiIcon, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        wifiOFFF(e);
        // wifiFlag = false;
    }
}

void ui_event_upsSwitch(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);

    if(event_code == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(target, LV_STATE_CHECKED)) {
        // _ui_flag_modify(ui_upsIcon, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        // bleON(e);
        upsON(e);
    }
    if(event_code == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(target, LV_STATE_CHECKED)) {
        // _ui_flag_modify(ui_bluetoothicon, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        // bleOFF(e);
        upsOFF(e);  
    }
}

void ui_event_bluetoothSwitch1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);

    if(event_code == LV_EVENT_VALUE_CHANGED &&  lv_obj_has_state(target, LV_STATE_CHECKED)) {
        // _ui_flag_modify(ui_bluetoothicon, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        bleON(e);
    }
    if(event_code == LV_EVENT_VALUE_CHANGED &&  !lv_obj_has_state(target, LV_STATE_CHECKED)) {
        // _ui_flag_modify(ui_bluetoothicon, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        bleOFF(e);
    }
}

void ui_event_Success_Screen(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_SCREEN_LOADED) {
        _ui_screen_change(&ui_MAIN, LV_SCR_LOAD_ANIM_FADE_IN, 500, 2000, &ui_MAIN_screen_init);

    }
}

void ui_event_Error_Screen(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_SCREEN_LOADED) {
        _ui_screen_change(&ui_MAIN, LV_SCR_LOAD_ANIM_FADE_IN, 500, 2000, &ui_MAIN_screen_init);

    }
}

void ui_event_WifiList(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_READY) {
        wifiSELECT(e);
        _ui_flag_modify(ui_PassWordText, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}

void ui_event_wifiScan(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        // wifiSCAN(e);
        wifiScan = true;
    }
}

// void ui_event_keyboard(lv_event_t * e)
// {
//     lv_event_code_t event_code = lv_event_get_code(e);

//     if(event_code == LV_EVENT_READY) {
//         wifiPasswordDetails(e);
//         _ui_flag_modify(ui_PassWordText, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
//     }
// }

void ui_event_PassWordText(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_FOCUSED) {
        _ui_flag_modify(ui_keyboard, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}

void ui_event_backHomeButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_MAIN, LV_SCR_LOAD_ANIM_NONE, 500, 0, &ui_MAIN_screen_init);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

    lv_disp_t * dispp = lv_display_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_SplashScreen1_screen_init();
    ui_SplashScreen2_screen_init();
    ui_MAIN_screen_init();
    ui_Success_Screen_screen_init();
    ui_Error_Screen_screen_init();
    ui_Wifi_Setup_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_SplashScreen1);
}
