
load_costum_font_ram(2, PANEL);
load_costum_font_ram(3, GOREVLI);
load_costum_font_ram(4, GUVENLIK);
load_costum_font_ram(5, SUBE);


void costum_send_font(unsigned char address, unsigned char font_l, unsigned char font_h) 
{    
    I2C_WriteByteOneReg (I2C0, OSD_REGISTERS, FONT_RAM_ADD_H, 0x00);
    I2C_WriteByteOneReg (I2C0, OSD_REGISTERS, FONT_RAM_ADD_L, address);           
    I2C_WriteByteOneReg (I2C0, OSD_REGISTERS, FONT_RAM_DATA_L, font_l); 
    I2C_WriteByteOneReg (I2C0, OSD_REGISTERS, FONT_RAM_DATA_H, font_h);         
}

void load_costum_font_ram(unsigned char address, unsigned char *font) 
{    
	uint8_t i,adr=address*22;
	
	I2C_WriteByteOneReg (I2C0, OSD_REGISTERS, FONT_RAM_ADD_H, 0x00);
	
	for(i=0 ; i<22 ;i++)
	{		
    I2C_WriteByteOneReg (I2C0, OSD_REGISTERS, FONT_RAM_ADD_L, adr+i);           
    I2C_WriteByteOneReg (I2C0, OSD_REGISTERS, FONT_RAM_DATA_L, *font++); 
    I2C_WriteByteOneReg (I2C0, OSD_REGISTERS, FONT_RAM_DATA_H, *font++);   
	}		
}