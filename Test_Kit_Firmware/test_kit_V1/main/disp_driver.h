#ifndef DISP_DRIVER_H_
#define DISP_DRIVER_H_
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

//DISPLAY TEST
void disp_blink();

//DISPLAY SETTINGS
void disp_brightness(int x);
void disp_color(int x);
void disp_contrast(int x);

//VIDEO COLOR
void disp_video_color_test();

//INDEX
void disp_font_lib();

//OSD BLOCK CONTROL
void disp_osd_block_state(int block_num, int block_state);
void disp_osd_block0_screen_test (void);
void disp_osd_config(void);
void disp_osd_block0_bottom_side(void);
void disp_osd_fore_color_select(int x);
void disp_osd_rgb_test_foreground();
void disp_osd_rgb_test_background();

#endif
