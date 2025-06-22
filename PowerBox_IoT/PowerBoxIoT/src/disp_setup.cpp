#include "disp_setup.h"
#include "disp.h"

// void my_disp_flush (lv_display_t *disp, const lv_area_t *area, uint8_t *pixelmap)
// {
//     uint32_t w = ( area->x2 - area->x1 + 1 );
//     uint32_t h = ( area->y2 - area->y1 + 1 );

// //    if (LV_COLOR_16_SWAP) {
// //        size_t len = lv_area_get_size( area );
// //        lv_draw_sw_rgb565_swap( pixelmap, len );
// //    }

//     display.startWrite();
//     display.setAddrWindow( area->x1, area->y1, w, h );
//    display.pushPixels( (uint16_t*) pixelmap, w * h, true );
//    display.endWrite();
//     lv_disp_flush_ready( disp );
// }

LGFX display; 
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *color_p)
{
    uint32_t w = area->x2 - area->x1 + 1;
    uint32_t h = area->y2 - area->y1 + 1;

    display.startWrite();
    display.setAddrWindow(area->x1, area->y1, w, h);
    display.pushPixels((uint16_t *)color_p, w * h, true);
    display.endWrite();

    lv_disp_flush_ready(disp);  // Inform LVGL that the flushing is done
}



/*Read the touchpad*/
void my_touchpad_read (lv_indev_t * indev_driver, lv_indev_data_t * data)
{
        int32_t touchX, touchY;
    if (!display.getTouch(&touchX, &touchY))
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /* Set the coordinates */
        data->point.x = touchX;
        data->point.y = touchY;

        // Serial.print("Data x ");
        // Serial.println(touchX);

        // Serial.print("Data y ");
        // Serial.println(touchY);
    }
}

