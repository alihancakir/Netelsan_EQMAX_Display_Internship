#ifndef I2C_H_
#define I2C_H_
#include <stdint.h>
#include <stdio.h>
void i2c_init(void);
void write_byte(uint8_t i2c_reg_addr, uint8_t sub_reg_addr, uint8_t value);
void connect_display(void);
#endif 
