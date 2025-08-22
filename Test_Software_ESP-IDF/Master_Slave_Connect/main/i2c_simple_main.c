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

*Author: Alihan Cakir(intern)
*Company: Netelsan
*Purpose: Wake up the TFT Display Driver of EQMAX Unit.

*/

#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"

static const char *TAG = "i2c-simple-example";

#define I2C_MASTER_SCL_IO           22     
#define I2C_MASTER_SDA_IO           21    
#define I2C_MASTER_NUM              I2C_NUM_0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          100000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000


static esp_err_t write_byte(uint8_t reg_addr, uint8_t data1, uint8_t data2)
{
    int ret_2_bytes;
    uint8_t write_buf_2_bytes[2] = {data1, data2};						  
    ret_2_bytes = i2c_master_write_to_device(I2C_MASTER_NUM, reg_addr >> 1,
    								 write_buf_2_bytes,
    								 sizeof(write_buf_2_bytes),
    								  I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    								  
    printf("2 bytes sending: %d \n",ret_2_bytes);

    return ret_2_bytes;
}

/**
 * @brief i2c master initialization
 */
static esp_err_t i2c_master_init(void)
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

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

void app_main(void)
{
    
    ESP_ERROR_CHECK(i2c_master_init());
    vTaskDelay(pdMS_TO_TICKS(100));

    ESP_LOGI(TAG, "I2C initialized successfully");
    

    /* Demonstrate writing by reseting the MPU9250 */
    ESP_ERROR_CHECK(write_byte(0xBE,0xC6,0x40));
    ESP_ERROR_CHECK(write_byte(0xB6,0x78,0x02));
    ESP_ERROR_CHECK(write_byte(0xB4,0xD4,0x80));  // set brightness 100
    
    ESP_ERROR_CHECK(write_byte(0xB4,0xD6,0x80));
    ESP_ERROR_CHECK(write_byte(0xB4,0xD3,0x80));
    
    
    //ESP_ERROR_CHECK(i2c_driver_delete(I2C_MASTER_NUM));
    ESP_LOGI(TAG, "I2C de-initialized successfully");
}
