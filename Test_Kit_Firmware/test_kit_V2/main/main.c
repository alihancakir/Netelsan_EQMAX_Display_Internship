#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <freertos/FreeRTOS.h>

#include "esp_system.h"
#include "i2c.h"			//I2C configuration
#include "register.h"		//all register 
#include "font_rom.h"		//font rom in font_rom_h
#include "font_ram.h"		//QR font included in font_ram_h
#include "hardware.h"		//GPIO configuration included in hardware.h
#include "system.h"			//all functions defined in system.h

uint8_t state= 0;			//it's mean 000

bool menu_flag=0; 				
bool qr_flag=0; 
bool settings_flag=0; 
bool video_flag=0;

void app_main(void)
{
	config_gpio();			//set GPIO configuration
	start_condition();		//wait display and initialize communication
	
	while(1)
	{
		printf("satate: %d\n",state);
		if(menu_button_state()==1 && state < 200){
			if(state == 110){
				state=210;
				menu_flag=1;
				qr_flag=1;
				settings_flag=0;
				video_flag=0;
			}
			if(state == 100){
				state=200;
				menu_flag=1;
				settings_flag=1;
				qr_flag=0;
				video_flag=0;
			}			
			if(state == 0){
				state=100;
				qr_flag=1;
				settings_flag=1;
				menu_flag=0;
				video_flag=0;
			}
		}
		if(move_button_state()==1 && state >= 100 && state < 130){	
			state+=10;
			if(state == 110){				
				qr_flag=1;
				menu_flag=0;
				settings_flag=0;
				video_flag=0;
			}		
			if(state == 120){			
				qr_flag=1;
				settings_flag=1;
				menu_flag=0;
				video_flag=0;
				state=100;
			}
		}
		if(back_button_state()==1 && state!=0 )	{	
			if(state == 100 || state == 110 ){
				menu_flag=0;
				qr_flag=0;
				settings_flag=0;			
				state=0;
				video_flag=0;
			}
			
			if(state == 200 || state == 210){
				qr_flag=1;
				settings_flag=1;		
				state=0;
				menu_flag=0;
				//write_byte(0xB0, 0x00,0x5A);
				//vTaskDelay(pdMS_TO_TICKS(2000));
				//esp_restart();
				//delete_block(90);
				
			}			
		}
		if(menu_flag == 0){						//menu showing
		
			if(state == 100){
				show_qr(0);
				general_menu_block0(1);;
				delete_block(90,SPACE);
				show_char(62, SPACE);
				show_char(31, MARK);
				uint16_t text_1[]={U,S,E,R,SPACE,M,A,N,U,A,L,END};	
				uint16_t text_2[]={D,E,V,I,C,E,SPACE,S,E,T,T,I,N,G,S,END};	
				show_string(1,1,text_1);	
				show_string(2,1,text_2);
				printf("opened: menu, closed:device & qr & video\n");	
				menu_flag=1;
				//vTaskDelay(pdMS_TO_TICKS(100));
			}
			if(state == 110){
				show_char(31, SPACE);
				show_char(62, MARK);
			}
		}
		if(state == 200 && qr_flag == 0){						//qr showing
			//delete_block(90);
			general_menu_block0(0);
			//device setting block close
			show_qr(1);
			printf("opened: qr, closed:settings & menu\n");
			qr_flag=1;
		}
		if(state == 210 && settings_flag == 0){						//device settings showing
			general_menu_block0(0);
			//qr menu close
			//show device settings
			printf("opened: settings, closed: menu & qr\n");
			settings_flag=1;
			
		}
		if(state == 0 && video_flag == 0){
			//delete_block(90);
			general_menu_block0(0);
			printf("opened: video, closed:settings & qr & menu\n");
			//device setting block close
			//qr menu close
			color_video(0x4F);
			video_flag=1;
		}
		vTaskDelay(pdMS_TO_TICKS(100));
	}
	
}	


