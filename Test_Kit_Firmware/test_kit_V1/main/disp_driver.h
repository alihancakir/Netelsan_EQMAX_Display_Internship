#ifndef DISP_DRIVER_H_
#define DISP_DRIVER_H_
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/_types.h>

//FONTS
#define SPACE		 		0x0000
#define N_0		 			0x0001
#define N_1		 			0x0002
#define N_2		 			0x0003
#define N_3		 			0x0004
#define N_4		 			0x0005
#define N_5		 			0x0006
#define N_6		 			0x0007
#define N_7		 			0x0008
#define N_8		 			0x0009
#define N_9		 			0x000A
#define A		 			0x000B
#define B		 			0x000C
#define C		 			0x000D
#define C_2	 				0x0164
#define D		 			0x000E
#define E					0x000F
#define F	 				0x0010
#define G	 				0x0011
#define G_2	 				0x0157
#define H	 				0x0012
#define I	 				0x0013
#define I_2	 				0x014B
#define J	 				0x0014
#define K	 				0x0015
#define L					0x0016
#define M					0x0017
#define N	 				0x0018
#define O	 				0x0019
#define O_2	 				0x0153
#define P		 			0x001A
#define Q	 				0x001B
#define R		 			0x001C
#define S		 			0x001D
#define T		 			0x001E
#define U  	 				0x001F
#define U_2	 				0x0149
#define V  	 				0x0020
#define W  	 				0x0021
#define X  	 				0x0022
#define Y  	 				0x0023
#define Z  	 				0x0024
#define DOT  	 			0x010C
#define D_DOT  	 			0x0134
#define END  	 			0x0135
#define QR11   		0x01C0
#define QR12   		0x01C1
#define QR13   		0x01C2
#define QR14   		0x01C3
#define QR15   		0x01C4
#define QR16  	 	0x01C5
#define QR17   		0x01C6
#define QR18  		0x01C7
#define QR19   		0x01C8
#define QR111   	0x01C9
#define QR112   	0x01CA
#define QR21   		0x01CB
#define QR22   		0x01CC
#define QR23   		0x01CD
#define QR24		0x01CE
#define QR25  		0x01CF
#define QR26   		0x01D0
#define QR27   		0x01D1
#define QR28   		0x01D2
#define QR29   		0x01D3
#define QR211   	0x01D4
#define QR212  		0x01D5


//REGISTER
#define OSD_GROUP_ADDR		0xB6
#define INDEX_RAM_ADD_H		0x0D
#define INDEX_RAM_ADD_L		0x00

#define INDEX_RAM_DATA_H	0x0E
#define INDEX_RAM_DATA_L	0x01
//-----------------------------
#define FONT_RAM_ADD_H		0x0F
#define FONT_RAM_ADD_L		0x02

#define FONT_RAM_DATA_H		0x03
#define FONT_RAM_DATA_L		0x04

#define ICON_COLOR_ADDR		0x10		

//DISPLAY TEST
void disp_blink();

//DISPLAY SETTINGS
void disp_brightness(int x);
void disp_color(int x);
void disp_contrast(int x);

//VIDEO COLOR
void disp_video_color_test();

//INDEX
void show_char(uint8_t position,uint16_t font);
void icon_color(uint8_t position,uint8_t font);
void disp_font_lib();
void number_test(void);
void show_string(uint8_t vertical_position,uint8_t horizontal_position, uint16_t str[]);

//OSD BLOCK CONTROL
void disp_osd_block_state(int block_num, int block_state);
void disp_osd_block0_screen_test (void);
void disp_osd_config(void);
void disp_osd_block0_menu(void);
void disp_osd_fore_color_select(int x);
void disp_osd_rgb_test_foreground();
void disp_osd_rgb_test_background();
void disp_osd_blink(int block_num);

//FONT RAM
void load_costum_font_ram(uint8_t position, unsigned char *font);
/*void load_costum_font_ram(uint8_t position, uint16_t *font);*/
void costum_send_font(uint8_t position, uint16_t font);
void show_external_font();


#endif
