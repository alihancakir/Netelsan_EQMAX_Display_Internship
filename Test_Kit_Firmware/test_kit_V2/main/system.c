#include <freertos/FreeRTOS.h>
#include <stdint.h>
#include "register.h"
#include "stdbool.h"
#include "i2c.h"
#include "font_rom.h"
#include "font_rom.h"


void start_condition(void){
	printf("device started....waiting for connect.\n");
	vTaskDelay(pdMS_TO_TICKS(2000));			//Waiting for wake up display
	i2c_init();												//Initialize i2c
	connect_display();										//Connect to AMT630A
	printf("connected the AMT630A.\n");
}

//OSD SETTINGS
void general_menu_block0(bool state){
	if(state==1){											
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_1,0x01);		//open block0
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_1,0x61);  		//user color select----------------------enable
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_2,0x61);		//OSD mix state--------------------------enable
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_2,0x70);		//OSD mix mode together------------------open
		write_byte(VIDEO_GROUP_ADDR,VIDEO_COLOR,   0x15);  		//Video color select---------------------white----4F: no color back video, 0x14: black
		printf("display configuration done.\n");
		//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		write_byte(OSD_GROUP_ADDR,  BLOCK0_X_SIZE, 0x1F);		//OSD block0  x_size---------------------0x01: 1 block horizontal-----------------------------0x0B: 11 blocks horizontaL---HEXADECIMAL!
		write_byte(OSD_GROUP_ADDR,  BLOCK0_Y_SIZE, 0x0D);		//OSD block0  y_size---------------------0x01: 1 block vertical-------------------------------0x08: 8 blocks vertical------HEXADECIMAL!
		write_byte(OSD_GROUP_ADDR,  BLOCK0_X_POS,  0x19);  		//OSD block0  x_position-----------------show block x_position:first 0x19,second 0x27,third 0x035-----value:(0x19+(PCS*(0x16/2))) 
		write_byte(OSD_GROUP_ADDR,  BLOCK0_Y_POS,  0x06);  		//OSD block0  y_position-----------------show block y_position:first 0x06,second 0x17,third 0x028-----value:(0x06+(PCS*(0x22/2)))                                             
		write_byte(OSD_GROUP_ADDR,  BLOCK_COLOR,   0x10);  		//OSD block color select-----------------white---0x00:transparent
	    write_byte(OSD_GROUP_ADDR,  BLOCK0_XY_MULT,0x00);  		//OSD block0  x_position Multiplier------0x01:OSD block 0 x_size+256px: The second size of display,0x00:disable multiplier
	}
	else{
		
		write_byte(OSD_GROUP_ADDR,BLOCK_CONFIG_1,0x00);			//close block0
	}
}
//significant trick of block1-4: use BLOCKX_START_ADDR when write on the display
void show_qr_block0(bool state){
	if(state==1){											
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_1,0x01);		//open block1
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_1,0x61);  		//user color select----------------------enable
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_2,0x61);		//OSD mix state--------------------------enable
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_2,0x70);		//OSD mix mode together------------------open
		write_byte(VIDEO_GROUP_ADDR,VIDEO_COLOR,   0x14);  		//Video color select---------------------red----4F: no color back video, 0x14: black
		printf("display configuration done.\n");
		//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		write_byte(OSD_GROUP_ADDR,  BLOCK0_X_SIZE, 0x04);		//OSD block1  x_size---------------------0x01: 1 block horizontal-----------------------------0x0B: 11 blocks horizontaL---HEXADECIMAL!
		write_byte(OSD_GROUP_ADDR,  BLOCK0_Y_SIZE, 0x03);		//OSD block1  y_size---------------------0x01: 1 block vertical-------------------------------0x08: 8 blocks vertical------HEXADECIMAL!
		write_byte(OSD_GROUP_ADDR,  BLOCK0_X_POS,  0x92);  		//OSD block1  x_position-----------------show block x_position:first 0x19,second 0x27,third 0x035-----value:(0x19+(PCS*(0x16/2))) 
		write_byte(OSD_GROUP_ADDR,  BLOCK0_Y_POS,  0x17);  		//OSD block1  y_position-----------------show block y_position:first 0x06,second 0x17,third 0x028-----value:(0x06+(PCS*(0x22/2)))                                             
		write_byte(OSD_GROUP_ADDR,  BLOCK_COLOR,   0x60);  		//OSD block color select-----------------white
	    write_byte(OSD_GROUP_ADDR,  BLOCK0_XY_MULT,0x00);  		//OSD block1  x_position Multiplier------0x01:OSD block 1 x_size+256px: The second size of display,0x00:disable multiplier
	}
	else{
		write_byte(OSD_GROUP_ADDR,BLOCK_CONFIG_1,0x00);			//close block1
	}
}
void block2_config(bool state){
	if(state==1){											
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_1,0x21);		//open block2
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_1,0x61);  		//user color select----------------------enable
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_2,0x61);		//OSD mix state--------------------------enable
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_2,0x70);		//OSD mix mode together------------------open
		write_byte(VIDEO_GROUP_ADDR,VIDEO_COLOR,   0x14);  		//Video color select---------------------red----4F: no color back video, 0x14: black
		printf("display configuration done.\n");
		//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		write_byte(OSD_GROUP_ADDR,  BLOCK2_X_SIZE, 0x04);		//OSD block2  x_size---------------------0x01: 1 block horizontal-----------------------------0x0B: 11 blocks horizontaL---HEXADECIMAL!
		write_byte(OSD_GROUP_ADDR,  BLOCK2_Y_SIZE, 0x03);		//OSD block2  y_size---------------------0x01: 1 block vertical-------------------------------0x08: 8 blocks vertical------HEXADECIMAL!
		write_byte(OSD_GROUP_ADDR,  BLOCK2_X_POS,  0x92);  		//OSD block2  x_position-----------------show block x_position:first 0x19,second 0x27,third 0x035-----value:(0x19+(PCS*(0x16/2))) 
		write_byte(OSD_GROUP_ADDR,  BLOCK2_Y_POS,  0x17);  		//OSD block2  y_position-----------------show block y_position:first 0x06,second 0x17,third 0x028-----value:(0x06+(PCS*(0x22/2)))                                             
		write_byte(OSD_GROUP_ADDR,  BLOCK_COLOR,   0x60);  		//OSD block color select-----------------white
	    write_byte(OSD_GROUP_ADDR,  BLOCK2_XY_MULT,0x00);  		//OSD block2  x_position Multiplier------0x01:OSD block 2 x_size+256px: The second size of display,0x00:disable multiplier
	}
	else{
		write_byte(OSD_GROUP_ADDR,BLOCK_CONFIG_1,0x20);			//close block2
	}
}
void block3_config(bool state){
	if(state==1){											
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_1,0x31);		//open block3
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_1,0x61);  		//user color select----------------------enable
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_2,0x61);		//OSD mix state--------------------------enable
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_2,0x70);		//OSD mix mode together------------------open
		write_byte(VIDEO_GROUP_ADDR,VIDEO_COLOR,   0x14);  		//Video color select---------------------red----4F: no color back video, 0x14: black
		printf("display configuration done.\n");
		//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		write_byte(OSD_GROUP_ADDR,  BLOCK3_X_SIZE, 0x04);		//OSD block3  x_size---------------------0x01: 1 block horizontal-----------------------------0x0B: 11 blocks horizontaL---HEXADECIMAL!
		write_byte(OSD_GROUP_ADDR,  BLOCK3_Y_SIZE, 0x03);		//OSD block3  y_size---------------------0x01: 1 block vertical-------------------------------0x08: 8 blocks vertical------HEXADECIMAL!
		write_byte(OSD_GROUP_ADDR,  BLOCK3_X_POS,  0x92);  		//OSD block3  x_position-----------------show block x_position:first 0x19,second 0x27,third 0x035-----value:(0x19+(PCS*(0x16/2))) 
		write_byte(OSD_GROUP_ADDR,  BLOCK3_Y_POS,  0x17);  		//OSD block3  y_position-----------------show block y_position:first 0x06,second 0x17,third 0x028-----value:(0x06+(PCS*(0x22/2)))                                             
		write_byte(OSD_GROUP_ADDR,  BLOCK_COLOR,   0x60);  		//OSD block color select-----------------white
	    write_byte(OSD_GROUP_ADDR,  BLOCK3_XY_MULT,0x00);  		//OSD block3  x_position Multiplier------0x01:OSD block 3 x_size+256px: The second size of display,0x00:disable multiplier
	}
	else{
		write_byte(OSD_GROUP_ADDR,BLOCK_CONFIG_1,0x30);			//close block3
	}
}
void block4_config(bool state){
	if(state==1){											
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_1,0x41);		//open block4
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_1,0x61);  		//user color select----------------------enable
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_2,0x61);		//OSD mix state--------------------------enable
		write_byte(OSD_GROUP_ADDR,  BLOCK_CONFIG_2,0x70);		//OSD mix mode together------------------open
		write_byte(VIDEO_GROUP_ADDR,VIDEO_COLOR,   0x14);  		//Video color select---------------------red----4F: no color back video, 0x14: black
		printf("display configuration done.\n");
		//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		write_byte(OSD_GROUP_ADDR,  BLOCK4_X_SIZE, 0x04);		//OSD block4  x_size---------------------0x01: 1 block horizontal-----------------------------0x0B: 11 blocks horizontaL---HEXADECIMAL!
		write_byte(OSD_GROUP_ADDR,  BLOCK4_Y_SIZE, 0x03);		//OSD block4  y_size---------------------0x01: 1 block vertical-------------------------------0x08: 8 blocks vertical------HEXADECIMAL!
		write_byte(OSD_GROUP_ADDR,  BLOCK4_X_POS,  0x92);  		//OSD block4  x_position-----------------show block x_position:first 0x19,second 0x27,third 0x035-----value:(0x19+(PCS*(0x16/2))) 
		write_byte(OSD_GROUP_ADDR,  BLOCK4_Y_POS,  0x17);  		//OSD block4  y_position-----------------show block y_position:first 0x06,second 0x17,third 0x028-----value:(0x06+(PCS*(0x22/2)))                                             
		write_byte(OSD_GROUP_ADDR,  BLOCK_COLOR,   0x60);  		//OSD block color select-----------------white
	    write_byte(OSD_GROUP_ADDR,  BLOCK4_XY_MULT,0x00);  		//OSD block4  x_position Multiplier------0x01:OSD block 4 x_size+256px: The second size of display,0x00:disable multiplier
	}
	else{
		write_byte(OSD_GROUP_ADDR,BLOCK_CONFIG_1,0x40);			//close block4
	}
}

//VIDEO SETTINGS
void color_video(uint8_t value){
//0x10:red,0x11:green,0x12:blue,0x13:grey,0x14:black,0x15:white,0x4F:no color
	write_byte(VIDEO_GROUP_ADDR, VIDEO_COLOR, value);
}
void brightness(uint8_t value){
	if (value > 0x7F){
		value = 0x7F;
	}
	else{
		write_byte(VIDEO_GROUP_ADDR, VIDEO_BRIGHTNESS, value);
	}
}
void contrast(uint8_t value){
	if (value > 0x7F){
		value = 0x7F;
	}
	else{
		write_byte(VIDEO_GROUP_ADDR, VIDEO_CONTRAST, value);
	}
}
void saturation(uint8_t value){
	if (value > 0x3E){
		value = 0x3E;
	}
	else{
		write_byte(VIDEO_GROUP_ADDR, VIDEO_SATURATION, value);
	}
}

//FONT SETTINGS
void show_char(uint8_t position,uint16_t font){
	
	write_byte(OSD_GROUP_ADDR, CHAR_X_SIZE, 0x10);//x
	write_byte(OSD_GROUP_ADDR, CHAR_Y_SIZE, 0x16);//y
	
	write_byte(OSD_GROUP_ADDR,INDEX_RAM_ADD_H,0x00);
    write_byte(OSD_GROUP_ADDR,INDEX_RAM_ADD_L,position);
    write_byte(OSD_GROUP_ADDR,INDEX_RAM_DATA_H,(font>>8));
    write_byte(OSD_GROUP_ADDR,INDEX_RAM_DATA_L,font);	
}

//string font to sent
//uint16_t info_1[]={N,E,T,E,L,S,A,N,SPACE,A,R,G,E,END};	
//show_string(1,2,info_1);	
void show_string(uint8_t vertical_position,uint8_t horizontal_position, uint16_t str[]){
	write_byte(OSD_GROUP_ADDR,INDEX_RAM_ADD_H,0x00);
	uint8_t position;	
	if(vertical_position>0 && vertical_position<12){
		if(horizontal_position>=0 && horizontal_position<30){
			vertical_position*=31;									//it depends change to OSD block0  x_size
			//printf("vertical: %d\n",vertical_position);
			position=(vertical_position)+(horizontal_position);			
			for(int i=0; i<30;i++){
				if(str[i]!=END){																			//The END flag is for size of text
					//char size scale				
					write_byte(OSD_GROUP_ADDR, 0x76, 0x10);//x
					write_byte(OSD_GROUP_ADDR, 0x77, 0x16);//y				
				    write_byte(OSD_GROUP_ADDR,INDEX_RAM_ADD_L,position++);			
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
void delete_block(uint8_t size,uint16_t font){
	for(int i=0; i<size;i++){
		write_byte(OSD_GROUP_ADDR, CHAR_X_SIZE, 0x10);//x
		write_byte(OSD_GROUP_ADDR, CHAR_Y_SIZE, 0x16);//y
		
		write_byte(OSD_GROUP_ADDR,INDEX_RAM_ADD_H,0x00);
	    write_byte(OSD_GROUP_ADDR,INDEX_RAM_ADD_L,i);
	    write_byte(OSD_GROUP_ADDR,INDEX_RAM_DATA_H,(font>>8));
	    write_byte(OSD_GROUP_ADDR,INDEX_RAM_DATA_L,font);	
		    //vTaskDelay(pdMS_TO_TICKS(200));			 
		}
}

void show_custom_font_ram(unsigned char position, uint16_t font){
	
	write_byte(OSD_GROUP_ADDR, 0x32, 0x0F);  // coef
	
	write_byte(OSD_GROUP_ADDR, 0x2B, 0xFF);  // vertical
	write_byte(OSD_GROUP_ADDR, 0x2C, 0xFF);  // vertical
	write_byte(OSD_GROUP_ADDR, 0x2D, 0xFF);  // vertical
	write_byte(OSD_GROUP_ADDR, 0x2E, 0xFF);  // vertical
	
	write_byte(OSD_GROUP_ADDR, 0x2F, 0xFF);  // horizontal
	write_byte(OSD_GROUP_ADDR, 0x30, 0xFF);  // horizontal
	write_byte(OSD_GROUP_ADDR, 0x31, 0xFF);  // horizontal

	
	write_byte(OSD_GROUP_ADDR, CHAR_X_SIZE,     0x0C);//x
	write_byte(OSD_GROUP_ADDR, CHAR_Y_SIZE,     0x10);//y
	write_byte(OSD_GROUP_ADDR, INDEX_RAM_ADD_H, 0x00);
    write_byte(OSD_GROUP_ADDR, INDEX_RAM_ADD_L, position);
    write_byte(OSD_GROUP_ADDR, INDEX_RAM_DATA_H,(font>>8));
    write_byte(OSD_GROUP_ADDR, INDEX_RAM_DATA_L, font);
}

void load_custom_font_ram(unsigned char position, unsigned char *font) 
{    
	uint8_t i,adr=position*16;
	write_byte(OSD_GROUP_ADDR, FONT_RAM_ADD_H, 0x00);
	for(i=0 ; i<16 ;i++)
	{		
	    write_byte(OSD_GROUP_ADDR, FONT_RAM_ADD_L,   adr+i);           
	    write_byte(OSD_GROUP_ADDR, FONT_RAM_DATA_L, *font++); 
	    write_byte(OSD_GROUP_ADDR, FONT_RAM_DATA_H, *font++);   
	}		
}








