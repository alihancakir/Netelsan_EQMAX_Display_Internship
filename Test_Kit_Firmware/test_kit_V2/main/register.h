#ifndef REGISTER_H_
#define REGISTER_H_


//(I2C_ADDRESS,SUB_ADDRESS,VALUE)

//--------------------------------------------------------------------------------------	
//OSD REGISTER---->0xB6(I2C ADDRESS)
#define OSD_GROUP_ADDR		 		0xB6
	//SUB ADDRESS
	#define INDEX_RAM_ADD_H				0x0D
	#define INDEX_RAM_ADD_L				0x00
	#define INDEX_RAM_DATA_H			0x0E
	#define INDEX_RAM_DATA_L			0x01
	#define FONT_RAM_ADD_H				0x0F
	#define FONT_RAM_ADD_L				0x02
	#define FONT_RAM_DATA_H				0x03
	#define FONT_RAM_DATA_L				0x04
	#define ICON_COLOR_ADDR				0x10
	#define CHAR_X_SIZE					0x76
	#define CHAR_Y_SIZE					0x77

	#define BLOCK_CONFIG_1				0x05
	#define BLOCK_CONFIG_2				0x06			
	#define BLOCK_COLOR					0x2A
	#define OSD_ALPHA_BRIGHT			0x0C
	#define OSD_H_MIRROR				0x35

		//BLOCKX CONFIG
		#define BLOCK0_X_SIZE				0x07		
		#define BLOCK0_Y_SIZE				0x08
		#define BLOCK0_XY_MULT				0x09		
		#define BLOCK0_X_POS				0x0A		
		#define BLOCK0_Y_POS				0x0B		
		
		#define BLOCK1_X_SIZE				0x12		
		#define BLOCK1_Y_SIZE				0x13		
		#define BLOCK1_XY_MULT				0x14		
		#define BLOCK1_X_POS				0x15		
		#define BLOCK1_Y_POS				0x16	
		#define BLOCK1_START_ADDR			0x17	
		
		#define BLOCK2_X_SIZE				0x18		
		#define BLOCK2_Y_SIZE				0x19		
		#define BLOCK2_XY_MULT				0x1A		
		#define BLOCK2_X_POS				0x1B		
		#define BLOCK2_Y_POS				0x1C		
		#define BLOCK2_START_ADDR			0x1D	
		
		#define BLOCK3_X_SIZE				0x1E		
		#define BLOCK3_Y_SIZE				0x1F		
		#define BLOCK3_XY_MULT				0x20	
		#define BLOCK3_X_POS				0x21		
		#define BLOCK3_Y_POS				0x22		
		#define BLOCK3_START_ADDR			0x23	
		
		#define BLOCK4_X_SIZE				0x24		
		#define BLOCK4_Y_SIZE				0x25		
		#define BLOCK4_XY_MULT				0x26		
		#define BLOCK4_X_POS				0x27		
		#define BLOCK4_Y_POS				0x28		
		#define BLOCK4_START_ADDR			0x29	

//--------------------------------------------------------------------------------------	
//VIDEO REGISTER---->0xB4(I2C ADDRESS)
#define VIDEO_GROUP_ADDR		 	0xB4
	//SUB ADDRESS
	#define VIDEO_COLOR					0xD2
	#define VIDEO_CONTRAST				0xD3		
	#define VIDEO_BRIGHTNESS			0xD4
	#define VIDEO_SATURATION			0xD6	

#endif 
