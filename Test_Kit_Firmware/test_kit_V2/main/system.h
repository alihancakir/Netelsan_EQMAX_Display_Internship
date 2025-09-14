#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

//START
void start_condition(void);

//OSD SETTINGS
void general_menu_block0(bool state);
void show_qr_block0(bool state);
void block2_config(bool state);
void block3_config(bool state);
void block4_config(bool state);
void delete_block(uint8_t size,uint16_t font);

//VIDEO SETTINGS
void color_video(uint8_t value);
void brightness(uint8_t value);
void contrast(uint8_t value);
void saturation(uint8_t value);

//FONT SETTINGS
void show_char(uint8_t position,uint16_t font);
void show_string(uint8_t vertical_position,uint8_t horizontal_position, uint16_t str[]);
void show_custom_font_ram(unsigned char position, uint16_t font);
void load_custom_font_ram(unsigned char position, unsigned char *font);

#endif 
