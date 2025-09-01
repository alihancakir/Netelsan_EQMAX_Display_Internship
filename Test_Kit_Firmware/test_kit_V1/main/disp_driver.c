#include <stdio.h>
#include <stdint.h>
#include "driver/i2c.h"
#include "driver/uart.h"
#include "i2c.h"
#include <freertos/FreeRTOS.h>

//|-------------------------------------------------------------------------------------------
//|										 DISPLAY TEST                                        |
//|-------------------------------------------------------------------------------------------

//disp_blink(0): stop blink		disp_blink(1): start blink
void disp_blink(){
	for(int i=0;i<4;i++){
		printf("contrast 0h");
		write_byte(0xB4,0xD3,0x10);  // set contrast min 0h
		printf("contrast 80h");
		write_byte(0xB4,0xD3,0x80);  // set contrast max 80h
	}		
}

//|-------------------------------------------------------------------------------------------
//|										 DISPLAY SETTINGS                                    |
//|-------------------------------------------------------------------------------------------

//brightness setting 	0-80h
void disp_brightness(int x){
	if (x > 0x7F)x = 0x7F;
	if (x < 0) x = 0; 		
	printf("brightness: %x",(uint8_t)x);
	write_byte(0xB4,0xD4,(uint8_t)x);
}

//color setting 		0-80h
void disp_color(int x){
	if (x > 0x7F)x = 0x7F;
	if (x < 0) x = 0; 		
	printf("color: %x",(uint8_t)x);
	write_byte(0xB4,0xD4,(uint8_t)x);
}

//contrast setting 		0-80h
void disp_contrast(int x){
	if (x > 0x7F)x = 0x7F;
	if (x < 0) x = 0; 		
	printf("contrast: %x",(uint8_t)x);
	write_byte(0xB4,0xD4,(uint8_t)x);
}

//|-------------------------------------------------------------------------------------------
//|											 	OSD BLOCK                        		     |
//|-------------------------------------------------------------------------------------------

//OSD screen testing. Select block befor testing.
void disp_osd_rgb_test_foreground(){
	for(int i=0;i<1;i++){	
		
		printf("color red");
		write_byte(0xB6,0x2A,0x10);  // color: red
		printf("color green");
		write_byte(0xB6,0x2A,0x20);  // color: green
		printf("color blue");
		write_byte(0xB6,0x2A,0x30);  // color: blue
		printf("color trans");
		write_byte(0xB6,0x2A,0x00);  // color: trans
	}	
}
void disp_osd_rgb_test_background(){
	for(int i=0;i<1;i++){	
		printf("color yellow");
		write_byte(0xB6,0x2A,0x40);  // color: yellow
		printf("color grey");
		write_byte(0xB6,0x2A,0x50);  // color: grey
		printf("color white");
		write_byte(0xB6,0x2A,0x60);  // color: white
		printf("color black");
		write_byte(0xB6,0x2A,0x70);  // color: black
		printf("color trans");
		write_byte(0xB6,0x2A,0x00);  // color: trans
	}	
}

//OSD block select
void disp_osd_block_state(int block_num, int block_state){
	if(block_num>=0 && block_num <5 ){
		if(block_num==0 && block_state==1){
			printf("block_0 open");
			write_byte(0xB6,0x05,0x01);  // osd block 0 opened
		}
		if(block_num==1 && block_state==1){
			printf("block_1 open");
			write_byte(0xB6,0x05,0x11);  // osd block 1 opened
		}
		if(block_num==2 && block_state==1){
			printf("block_2 open");
			write_byte(0xB6,0x05,0x21);  // osd block 2 opened
		}
		if(block_num==3 && block_state==1){
			printf("block_3 open");
			write_byte(0xB6,0x05,0x31);  // osd block 3 opened
		}
		if(block_num==4 && block_state==1){
			printf("block_4 open");
			write_byte(0xB6,0x05,0x41);  // osd block 4 opened
		}
	}
	else {
		printf("osd fail");
	}
}

//OSD display screen test: block0
void disp_osd_block0_screen_test (void){
	
	printf("block x_size");
	write_byte(0xB6, 0x07,0x30);	//osd block 0 x size
	printf("block y_size");
	write_byte(0xB6, 0x08,0x02);	//osd block 0 y size
	
	
	write_byte(0xB6, 0x0A, 0x00);  // OSD block 0 X stagnent

	//decrasing y pos
	for (uint8_t ypos = 0x00; ypos < 0xFc; ypos += 0x04) {
	        printf("block y_pos");
	        write_byte(0xB6, 0x0B, ypos);  // OSD block 0 Y position
	 }
}

//OSD display general setting (mix,color select,color) 
void disp_osd_config(void){
	
	//osd mix enable 
	printf("mix enable");
	write_byte(0xB6, 0x06,0x61);	//osd mix enable      
//----------------------------------------------------------	
	//video and block not together
/*	printf("mix mode -1");
	write_byte(0xB6, 0x06,0x70);	//osd mix enable            
*/	
	//video and block together
	printf("mix mode -2");
	write_byte(0xB6, 0x06,0x71);	//osd mix enable            
//----------------------------------------------------------	
	//select color from user enable
	printf("color select");
	write_byte(0xB6,0x05,0x61);  // color select from user
/*	
	//select color from user disable
	printf("color select");
	write_byte(0xB6,0x05,0x60);  // color select from user
*/
//----------------------------------------------------------
	//select osd block color 
	/*	[3-0] OSD foreground color 
		[7-4] OSD background color 
 
		00h- Transparent 
		10h- RED 
		20h- GREEN 
		30h- BLUE 
		40h- YELLOW 
		50h- GREY 
		60h- WHITE 
		70h- BLACK 
	*/

}

//bottom side OSD bar
void disp_osd_block0_bottom_side(void){
	
	printf("block x_size");
	write_byte(0xB6, 0x07,0x30);	//osd block 0 x size
	printf("block y_size");
	write_byte(0xB6, 0x08,0x04);	//osd block 0 y size
	
	printf("b0 x pos");
	write_byte(0xB6, 0x0A, 0x00);  // OSD block 0 X position
	printf("b0 y pos");
	write_byte(0xB6, 0x0B, 0xCC);  // OSD block 0 Y position	
}

//OSD display color select
void disp_osd_fore_color_select(int x){	
	
		if(1==x){
			printf("color red");
			write_byte(0xB6,0x2A,0x10);  // color: red
			}
		if(2==x){
			printf("color green");
			write_byte(0xB6,0x2A,0x20);  // color: green
			}
		if(3==x){
			printf("color blue");
			write_byte(0xB6,0x2A,0x30);  // color: blue
			}
		if(4==x){
			printf("color trans");
		write_byte(0xB6,0x2A,0x00);  // color: trans
			}
		
}

//|-------------------------------------------------------------------------------------------
//|											 VIDEO COLOR                        		     |
//|-------------------------------------------------------------------------------------------

//its controlling screen. No video signal on the screen
void disp_video_color_test(){
	for(int i=0;i<1;i++){
		printf("color red");
		write_byte(0xB4,0xD2,0x10);  // color: red
		printf("color green");
		write_byte(0xB4,0xD2,0x11);  // color: green
		printf("color blue");
		write_byte(0xB4,0xD2,0x12);  // color: blue
		printf("color grey");
		write_byte(0xB4,0xD2,0x13);  // color: grey
		printf("color black");
		write_byte(0xB4,0xD2,0x14);  // color: black
		printf("color white");
		write_byte(0xB4,0xD2,0x15);  // color: white
		printf("back video");
		write_byte(0xB4,0xD2,0x4F);  // color: no
	}	
}

//|-------------------------------------------------------------------------------------------
//|											 		INDEX                        		     |
//|-------------------------------------------------------------------------------------------

void disp_font_lib(){
	printf("ADDR high");
	write_byte(0xB6, 0x0D, 0x01);   // 0x01 (high byte)
	printf("ADDR low");
	write_byte(0xB6, 0x00, 0x20);   // 0xC0 (low byte)

	printf("wrote high");
	write_byte(0xB6, 0x0F,0x00);	//osd block 0 x size
	printf("wrote low");
	write_byte(0xB6, 0x02,0x11);	//osd block 0 x size
}














