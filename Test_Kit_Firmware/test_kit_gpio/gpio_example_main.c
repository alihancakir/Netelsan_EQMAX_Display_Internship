#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "soc/gpio_num.h"

#define BUTTON_1   GPIO_NUM_27 
#define BUTTON_2   GPIO_NUM_26 
#define BUTTON_3   GPIO_NUM_25  


int flag1=0;
int flag2=0;
int flag3=0;
void app_main(void)
{

    gpio_reset_pin(BUTTON_1);
    gpio_set_direction(BUTTON_1, GPIO_MODE_INPUT);
    gpio_pulldown_en(GPIO_NUM_25);   

    gpio_reset_pin(BUTTON_2);
    gpio_set_direction(BUTTON_2, GPIO_MODE_INPUT);
    gpio_pulldown_en(GPIO_NUM_26);
    
    
    gpio_reset_pin(BUTTON_3);
    gpio_set_direction(BUTTON_3, GPIO_MODE_INPUT);
    gpio_pulldown_en(GPIO_NUM_27);


    while (1) {
        int button_1_state = gpio_get_level(BUTTON_1); 
        int button_2_state = gpio_get_level(BUTTON_2); 
        int button_3_state = gpio_get_level(BUTTON_3); 

        if (button_1_state == 1 && flag1==0) { 
			 flag1=1;
	
        } 
        if(flag1==1 && button_1_state==0){
			printf("button 1 pressed\n");
			flag1=0;
		}
//-------------------------------------------------		
        if (button_2_state == 1 && flag2==0) { 
			 flag2=1;
	
        } 
        if(flag2==1 && button_2_state==0){
			printf("button 2 pressed\n");
			flag2=0;
		}		
//-------------------------------------------------
        if (button_3_state == 1 && flag3==0) { 
			 flag3=1;
	
        } 
        if(flag3==1 && button_3_state==0){
			printf("button 3 pressed\n");
			flag3=0;
		}		

		vTaskDelay(pdMS_TO_TICKS(100));
    }
}
