#include "soc/gpio_num.h"
#include "driver/gpio.h"
#include <freertos/FreeRTOS.h>
#include <stdbool.h>

#include "hardware.h"

#define menu_button   GPIO_NUM_27		
#define move_button   GPIO_NUM_26		
#define back_button   GPIO_NUM_25

bool menu_button_flag=0;
bool move_button_flag=0;
bool back_button_flag=0;		

void config_gpio(void){				//must be before main block
	
	gpio_reset_pin(menu_button);
	gpio_set_direction(menu_button, GPIO_MODE_INPUT);
	gpio_pulldown_en(GPIO_NUM_27);
	
	gpio_reset_pin(move_button);
	gpio_set_direction(move_button, GPIO_MODE_INPUT);
	gpio_pulldown_en(GPIO_NUM_26);
	
	gpio_reset_pin(back_button);
	gpio_set_direction(back_button, GPIO_MODE_INPUT);
	gpio_pulldown_en(GPIO_NUM_25);
}

bool menu_button_state(){
	bool button_1_state = gpio_get_level(menu_button); 
	
	if (button_1_state == 1 && menu_button_flag==0){ 
		 menu_button_flag=1;
		 vTaskDelay(pdMS_TO_TICKS(20)); 
	}
	
	if(menu_button_flag==1 && button_1_state==0){			//falling edge 
		menu_button_flag=0;
		vTaskDelay(pdMS_TO_TICKS(20));
		printf("menu button pressed\n");
		return 1;
	}
	else{
		return 0;
	}
}

bool move_button_state(){
	bool button_2_state = gpio_get_level(move_button); 
	
	if (button_2_state == 1 && move_button_flag==0){ 
		 move_button_flag=1;
		 vTaskDelay(pdMS_TO_TICKS(20)); 
	}
	
	if(move_button_flag==1 && button_2_state==0){			//falling edge 
		move_button_flag=0;
		vTaskDelay(pdMS_TO_TICKS(20));
		printf("move button pressed\n");
		return 1;
	}
	else{
		return 0;
	}
}

bool back_button_state(){
	bool button_3_state = gpio_get_level(back_button); 
	
	if (button_3_state == 1 && back_button_flag==0){ 
		 back_button_flag=1;
		 vTaskDelay(pdMS_TO_TICKS(20)); 
	}
	
	if(back_button_flag==1 && button_3_state==0){			//falling edge 
		back_button_flag=0;
		vTaskDelay(pdMS_TO_TICKS(20));
		printf("back button pressed\n");
		return 1;
	}
	else{
		return 0;
	}
}
