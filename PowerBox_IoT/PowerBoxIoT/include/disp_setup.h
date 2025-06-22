#ifndef DISP_SETUP_H
#define DISP_SETUP_H

#include <Arduino.h>
#include <lvgl.h> 
#include "ui.h"// Include LVGL library
#include "disp.h"
#include "global_config.h"


static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 480;

enum { SCREENBUFFER_SIZE_PIXELS = screenWidth * screenHeight / 6};
static lv_color_t buf [SCREENBUFFER_SIZE_PIXELS];
void my_disp_flush (lv_display_t *disp, const lv_area_t *area, uint8_t *pixelmap);
void my_touchpad_read (lv_indev_t * indev_driver, lv_indev_data_t * data);

extern  LGFX display; 
// void static uint32_t my_tick_get_cb (void);
#endif