/******************************************************************************
 * @file     main.c
 * @version  V1.00
 * @brief    A project template for M031 MCU.
 *
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "MyGPIOProject_config_1.h"
#include "gpio_config.h"

void UART_Open(UART_T *uart, uint32_t u32baudrate);

int main()
{
    MyGPIOProject_config_1_init();
	
		gpio_config_init();
	
		GPIO_SetMode(PB, BIT14, GPIO_MODE_OUTPUT) ;		//PB14 output defined.
		GPIO_SetMode(PC, BIT4, GPIO_MODE_INPUT);  		//PC4 input defined.
		//GPIO_SetMode(PC, BIT4, GPIO_MODE_INPUT);
		
		PB14=0;  //low side. its mean =1: turn off the i/o

    /* Init UART0 to 115200-8n1 for print message */
    UART_Open(UART0, 115200);

    /* Connect UART to PC, and open a terminal tool to receive following message */
    printf("Hello World\n");
		//PB14=0;
    /* Got no where to go, just loop forever */
    while(1);
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
