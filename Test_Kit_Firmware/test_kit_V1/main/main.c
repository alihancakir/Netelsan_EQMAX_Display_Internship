#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <freertos/FreeRTOS.h>
#include "i2c.h"
#include "disp_driver.h"

void app_main(void)
{
	i2c_init();
	connect_display();

	/*
	1-i2c_init();					:i2c init
	2-connect_display();			:connect to dislay
	3-disp_osd_block_state()		:open block x
	4-disp_osd_config()				:get config(mix,color select) 
	5-size and pos
	6-index settings
	*/
	disp_osd_fore_color_select(4);
	disp_osd_block_state(0, 1);	//osd block 0 opened
	disp_osd_config();
	while(1){
		
		disp_osd_block0_screen_test();
		disp_osd_fore_color_select(1);
		
		
		disp_osd_block0_screen_test();
		disp_osd_fore_color_select(2);
		
		
		disp_osd_block0_screen_test();
		disp_osd_fore_color_select(3);	
	}
	//the target is write the addrss
}
