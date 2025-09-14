#include <stdio.h>
#include <stdint.h>
#include "disp_driver.h"
#include "driver/i2c.h"
#include "driver/uart.h"
#include "i2c.h"
#include "qr_font.c"
#include <freertos/FreeRTOS.h>
#include <string.h>

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

//OSD screen testing. Select block before testing.
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
//----------------------------------------
		if(block_num==0 && block_state==0){
			printf("block_0 open");
			write_byte(0xB6,0x05,0x00);  // osd block 0 opened
		}
		if(block_num==1 && block_state==0){
			printf("block_1 open");
			write_byte(0xB6,0x05,0x10);  // osd block 1 opened
		}
		if(block_num==2 && block_state==0){
			printf("block_2 open");
			write_byte(0xB6,0x05,0x20);  // osd block 2 opened
		}
		if(block_num==3 && block_state==0){
			printf("block_3 open");
			write_byte(0xB6,0x05,0x30);  // osd block 3 opened
		}
		if(block_num==4 && block_state==0){
			printf("block_4 open");
			write_byte(0xB6,0x05,0x40);  // osd block 4 opened
		}
	}
	else {
		printf("osd fail");
	}
}

//OSD display screen test: block0
void disp_osd_block0_screen_test (void){
	
	printf("block x_size");
	write_byte(0xB6, 0x07,0x01);	//osd block 0 x size
	printf("block y_size");
	write_byte(0xB6, 0x08,0x01);	//osd block 0 y size
	
	
	write_byte(0xB6, 0x0A, 0x30);  // OSD block 0 X stagnent

	//decrasing y pos
	for (uint8_t ypos = 0x00; ypos < 0xFC; ypos += 0x01) {
	        printf("block y_pos");
	        write_byte(0xB6, 0x0B, ypos);  // OSD block 0 Y position
	 }
}

//OSD display general setting (mix,color select,color) 
void disp_osd_config(void){
	
//----------------------------------------------------------	
	//select color from user enable
	printf("color select");
	write_byte(0xB6,0x05,0x61);  // color select from user
	
//----------------------------------------------------------
	//osd mix enable 
	printf("mix enable");
	write_byte(0xB6, 0x06,0x61);	//osd mix enable      
		
	//video and block together
	printf("mix mode -2");
	write_byte(0xB6, 0x06,0x70);	//osd mix mod            

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
	
	/*
	//osd block blink eneable
	printf("blink en");
	write_byte(0xB6,0x05,0x51);  //blink enable
	*/
	
	/*
	//HSYN edge select:	HORIZONTAL 
	printf("hsyn selected");
	write_byte(0xB6,0x35,0x30
	);  //1: falling edge		0: rising edge
	//VSYN edge select:	VERTICAL 
	printf("vsyn selected");
	write_byte(0xB6,0x35,0x50);  //1: falling edge		0: rising edge
	*/
	/*
	//OSD alpha settings
	printf("OSD alpha");
	write_byte(0xB6,0x0C,0x20);  //[2:0]
	
	//OSD bright settings
	printf("OSD bright");
	write_byte(0xB6,0x0C,0x30);  //[7:3]
	*/
	/*
	//bitmap background transparent 
	printf("bitmap trans");
	write_byte(0xB6,0x35,0x41);  //1:no transparent		0: transparent
	*/
	
}

//bottom side OSD bar
void disp_osd_block0_menu(void){
	
	printf("block x_size");
	write_byte(0xB6, 0x07,0x20);	//osd block 0 x size
	printf("block y_size");
	write_byte(0xB6, 0x08,0x04);	//osd block 0 y size
	
	printf("b0 x pos");
	write_byte(0xB6, 0x0A, 0x00);  // OSD block 0 X position
	printf("b0 y pos");
	write_byte(0xB6, 0x0B, 0x08);  // OSD block 0 Y position
/*	
	//TEST SCALER
	write_byte(0xB6, 0x2B, 0xFF);  // vertical
	write_byte(0xB6, 0x2F, 0xFF);  // horizontal
	
	write_byte(0xB6, 0x32, 0x00);  // coef	
*/
		
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


//OSD block blink
void disp_osd_blink(int block_num){
	
	printf("blink frequency");
	write_byte(0xB6,0x06,0x30);  // osd block 1 blink
	
	if(block_num>=0 && block_num <5 ){
		if(block_num==0){
			printf("block_0 blink");
			write_byte(0xB6,0x35,0x20);  // osd block 0 blink
		}
		if(block_num==1){
			printf("block_1 blink");
			write_byte(0xB6,0x35,0x11);  // osd block 1 blink
		}
		if(block_num==2){
			printf("block_2 blink");
			write_byte(0xB6,0x35,0x12);  // osd block 2 blink
		}
		if(block_num==3){
			printf("block_3 blink");
			write_byte(0xB6,0x35,0x13);  // osd block 3 blink
		}
		if(block_num==4){
			printf("block_4 blink");
			write_byte(0xB6,0x35,0x14);  // osd block 4 blink
		}
	}
	else {
		printf("osd fail");
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

void icon_color(uint8_t position,uint8_t font){
	//write_byte(OSD_GROUP_ADDR, 0x05, 61);
	write_byte(OSD_GROUP_ADDR, INDEX_RAM_ADD_H, 0x00);
    write_byte(OSD_GROUP_ADDR,INDEX_RAM_ADD_L,position);
    write_byte(OSD_GROUP_ADDR,ICON_COLOR_ADDR,(font>>8));
	
}

void show_char(uint8_t position,uint16_t font){
	
	//char size scale??
	write_byte(OSD_GROUP_ADDR, 0x76, 0x10);//x
	write_byte(OSD_GROUP_ADDR, 0x77, 0x16);//y
	
	write_byte(OSD_GROUP_ADDR,INDEX_RAM_ADD_H,0x00);
    write_byte(OSD_GROUP_ADDR,INDEX_RAM_ADD_L,position);
    write_byte(OSD_GROUP_ADDR,INDEX_RAM_DATA_H,(font>>8));
    write_byte(OSD_GROUP_ADDR,INDEX_RAM_DATA_L,font);	
}
//string font to sent
//uint16_t info_1[]={N,E,T,E,L,S,A,N,SPACE,A,R,G,E,END};	
//show_string(1,2,info_1);	
//The END flag is for size of text
/*void show_string(uint8_t vertical_position,uint8_t horizontal_position, uint16_t str[]){
	write_byte(OSD_GROUP_ADDR,FONT_RAM_ADD_H,0x00);
	uint8_t position;	
	if(vertical_position>0 && vertical_position<12){
		if(horizontal_position>=0 && horizontal_position<30){
			vertical_position*=32;
			//horizontal_position+=vertical_position*=30;
			position=(vertical_position)+(horizontal_position);			
			for(int i=0; i<30;i++){
				if(str[i]!=END){
					//char size scale				
					write_byte(OSD_GROUP_ADDR, 0x76, 0x10);//x
					write_byte(OSD_GROUP_ADDR, 0x77, 0x16);//y			
				    write_byte(OSD_GROUP_ADDR,FONT_RAM_ADD_L,position);
				    printf("position: %d:",position);
				    write_byte(OSD_GROUP_ADDR,FONT_RAM_DATA_L,str[i]);
				    write_byte(OSD_GROUP_ADDR,FONT_RAM_DATA_H,str[i]>>8);
				 
				  }
				else{
					break;
				 }    
			}			
		}
		else{
			printf("fail due horizontal num.");
		}
	}
	else{
		printf("fail due vertical num.");
	}
}*/
//string font to sent
//uint16_t info_1[]={N,E,T,E,L,S,A,N,SPACE,A,R,G,E,END};	
//show_string(1,2,info_1);	
//The END flag is for size of text
void show_string(uint8_t vertical_position,uint8_t horizontal_position, uint16_t str[]){
	write_byte(OSD_GROUP_ADDR,INDEX_RAM_ADD_H,0x00);
	uint8_t position;	
	printf("vertical: %d\n",vertical_position);
	printf("position: %d\n",horizontal_position);
	if(vertical_position>0 && vertical_position<12){
		if(horizontal_position>=0 && horizontal_position<30){
			vertical_position*=32;
			printf("vertical: %d\n",vertical_position);
			position=(vertical_position)+(horizontal_position);			
			for(int i=0; i<30;i++){
				if(str[i]!=END){
					//char size scale				
					write_byte(OSD_GROUP_ADDR, 0x76, 0x10);//x
					write_byte(OSD_GROUP_ADDR, 0x77, 0x16);//y	
	
				    write_byte(OSD_GROUP_ADDR,INDEX_RAM_ADD_L,position++);
				    printf("position: %d\n",position);
				    write_byte(OSD_GROUP_ADDR,INDEX_RAM_DATA_H,str[i]>>8);
				    write_byte(OSD_GROUP_ADDR,INDEX_RAM_DATA_L,str[i]);				 
				  }
				else{
					break;
				 }    
			}			
		}
		else{
			printf("fail due horizontal num.");
		}
	}
	else{
		printf("fail due vertical num.");
	}
}


void disp_osd_font_ram(void){
	//uint8_t i=0;
	uint8_t position=2*22;
	
	printf("font addr H");
	write_byte(0xB6, 0x0F, 0x00);
	
	printf("font addr L");
	write_byte(0xB6, 0x04, position);
	
//---------------------------------------------------------------------
	printf("font data L");
	write_byte(0xB6, 0x04, position);

	printf("font data H");
	write_byte(0xB6, 0x04, position);

}
/*
void disp_osd_font_config(void){
	
	
}*/

void number_test(void){
	
	uint8_t val = 0x01;
	uint8_t position=1;
	
	printf("ind addr H");
	write_byte(0xB6, 0x0D, 0x00);
	for(int i=0;i<10;i++){
	    printf("ind addr L");
		write_byte(0xB6, 0x00, position);
		printf("ind data H");
		write_byte(0xB6, 0x0E, 0x00);   
		printf("ind data L");
		write_byte(0xB6, 0x01, val);		
		position++;
		val++;
	}
}


//|-------------------------------------------------------------------------------------------
//|											 FONT RAM USER                        		     |
//|-------------------------------------------------------------------------------------------


void costum_send_font(uint8_t position, uint16_t font)
{    
	write_byte(OSD_GROUP_ADDR, FONT_RAM_ADD_H, 0x00);
    write_byte(OSD_GROUP_ADDR, FONT_RAM_ADD_L, position); 
    write_byte(OSD_GROUP_ADDR, FONT_RAM_DATA_H, font>>8); 
    write_byte(OSD_GROUP_ADDR, FONT_RAM_DATA_L, font);
             


}
void load_costum_font_ram(uint8_t position, unsigned char *font) 
{    
	uint8_t i,adr=position*22;
	write_byte(OSD_GROUP_ADDR, FONT_RAM_ADD_H, 0x00);
	for(i=0 ; i<22 ;i++)
	{		
	    write_byte(OSD_GROUP_ADDR, FONT_RAM_ADD_L, adr+i);           
	    write_byte(OSD_GROUP_ADDR, FONT_RAM_DATA_L, *font++); 
	    write_byte(OSD_GROUP_ADDR, FONT_RAM_DATA_H, *font++);   
	}		
}
/*
void load_costum_font_ram(uint8_t position, uint16_t *font) 
{    
	uint8_t i,adr=position*22;
	write_byte(OSD_GROUP_ADDR, FONT_RAM_ADD_H, 0x00);
	for(i=0 ; i<22 ;i++)
	{		
	    write_byte(OSD_GROUP_ADDR, FONT_RAM_ADD_L, adr+i);           
	    write_byte(OSD_GROUP_ADDR, FONT_RAM_DATA_L, *font++); 
	    write_byte(OSD_GROUP_ADDR, FONT_RAM_DATA_H, *font++);   
	}		
}*/

void show_external_font(){
	
	//1.1
uint8_t QR11_BM_1[] =
{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0xF0, 0x00,
 0xF0, 0x00, 0xF0, 0xFF, 0xF1, 0xFF, 0xF1, 0xFF, 0xF1, 0xFF, 0xF1,
  0xFF, 0xF1, 0xFF, 0xF1, 0xFF, 0xF1, 0xFF, 0xF1, 0xFF, 0xF1, 0xFF,
   0xF1, 0xFF, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0xF8, 0x00};
   
   load_costum_font_ram(0,QR11_BM_1);
 
   write_byte(OSD_GROUP_ADDR, FONT_RAM_ADD_H, 0x00);

   write_byte(OSD_GROUP_ADDR, FONT_RAM_ADD_L, 1);    
   
      write_byte(OSD_GROUP_ADDR, FONT_RAM_DATA_H, 0x01);      

   write_byte(OSD_GROUP_ADDR, FONT_RAM_DATA_L, 0xC0);
          

   
   
   
   
}







//RESET SOFT
//write_byte(0xB0, 0x00,0x5A);


