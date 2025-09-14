/*
**Discription:
*I2C write 3 bytes send data codes.
*As you can see the figure, target device has 3 bytes.
*Sending 3 data with buffer in same time.

*Main board: ESP32 DEVKITC (master)
*Target device: AMT630A(slave)

*Here is the understanding the I2C protocol logic related the AMT630A:

---------------------------------------------------------------------------------------------------------------------------------------------------------
|  Start Condition	| 		Slave Address		|			R/W				|  ACK	|		DATA1		|  ACK	|		DATA2		|	Stop Condition	|
---------------------------------------------------------------------------------------------------------------------------------------------------------
|	SDA pull down	| 	it must be 7 bit 		|	it must be 0 due 		|		|	  it fixed 		|		|	  it fixed 		|	SCL pull up		|
|	  delay			| 	(convert to 7 bit 		|	to we using always 		|		|	   8 bits		|		|	   8 bits		|	   delay		|
|	SCL pull down	| 	from 8bit:(0xXX >>1)	|	write to slave			|		|					|		|					|	SDA pull up		|
---------------------------------------------------------------------------------------------------------------------------------------------------------

*/

#include <stdio.h>
#include <stdint.h>
#include "driver/i2c.h"
#include "i2c.h"
#include <freertos/FreeRTOS.h>

#define I2C_MASTER_SCL_IO           22     
#define I2C_MASTER_SDA_IO           21    
#define I2C_MASTER_NUM              I2C_NUM_0                  /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

int count=0;


void write_byte(uint8_t i2c_reg_addr, uint8_t sub_reg_addr, uint8_t value)
{
	
	uint8_t write_buf_2_bytes[2] = {sub_reg_addr, value};	
	//vTaskDelay(pdMS_TO_TICKS(500));
    i2c_master_write_to_device(I2C_MASTER_NUM, i2c_reg_addr >> 1, write_buf_2_bytes,sizeof(write_buf_2_bytes),I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);								  
    
    if(count<2){	// the connected show 2 times without bytes 
   		  count++;
   	}   
   	else {
		
		printf("\t|\t(0x%x,0x%x,0x%x)\t|\tbyte sent\t|\n",i2c_reg_addr,sub_reg_addr,value);
	}
}

void i2c_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);
    i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
    printf("i2c initialized\n");
    printf("\n\tEXP  \t|\t  SENT BYTE  \t\t|\t  INFO  \t|\n");
    printf("----------------|-------------------------------|-----------------------|\n");
}

void connect_display(void)
{	
	//i2c connect address:
	printf("\t-  \t|\t(0xBE,0xC6,0x40)\t|  connected the device |\n");
    write_byte(0xBE,0xC6,0x40);
    printf("\t-  \t|\t(0xB6,0x78,0x02)\t|  connected the device |\n");
    write_byte(0xB6,0x78,0x02);
    vTaskDelay(pdMS_TO_TICKS(2000));
}
void i2c_delete(void){
	i2c_driver_delete(I2C_MASTER_NUM);
}


