/* IERG3810_TFTLCD.c: C source file for TFTLCD operations, defined in lab 3 */
#include "stm32f10x.h"
#include "FONT.H"
#include "CFONT.H"
#include "SFONT.H"

typedef struct{
	u16 LCD_REG;
	u16 LCD_RAM;
} LCD_TypeDef;

#define LCD_BASE ((u32)(0x6C000000 | 0x000007FE))
#define LCD 		 ((LCD_TypeDef *) LCD_BASE)

void IERG3810_TFTLCD_WrReg(u16 regval){
	LCD->LCD_REG=regval;
}

void IERG3810_TFTLCD_WrData(u16 data){
	LCD->LCD_RAM=data;
}

void IERG3810_TFTLCD_SetParameter(void){
	IERG3810_TFTLCD_WrReg(0x01); // software Reset
	IERG3810_TFTLCD_WrReg(0x11); // turn on sleep mode (Exit_sleep_mode)
	
	IERG3810_TFTLCD_WrReg(0x3A); // set_pixel_format
	IERG3810_TFTLCD_WrData(0x55); // 65535 colors
	
	IERG3810_TFTLCD_WrReg(0x29); // display ON
	
	IERG3810_TFTLCD_WrReg(0x36); // Memory Access Control (Section 8.2.29, page-127)
	IERG3810_TFTLCD_WrData(0xCA);
}

void IERG3810_TFTLCD_Init(void){ // set FSMC
	/*	reference:
		RCC -> APB2ENR (RM0008 page-108)
		RCC -> APB2ENR (RM0008 page-142)
		GPIOx -> CRL (RM0008 page-166)
		GPIOx -> CRH (RM0008 page-167) 
		FSMC_BTR (RM0008 page-521) */
	
	RCC -> AHBENR |= 1 << 8; // enable FSMC clock (FSMCEN=1)
	RCC -> APB2ENR |= 1 << 3; // enable GPIO-B clock (IOPBEN=1)
	RCC -> APB2ENR |= 1 << 5; // enable GPIO-D clock (IOPDEN=1)
	RCC -> APB2ENR |= 1 << 6; // enable GPIO-E clock (IOPEEN=1)
	RCC -> APB2ENR |= 1 << 8; // enable GPIO-G clock (IOPGEN=1)
	GPIOB -> CRL &= 0xFFFFFFF0; // set-up PB0
	GPIOB -> CRL |= 0x00000003;
	
	// PORT D
	GPIOD -> CRH &= 0x00FFF000; // set-up Data Bus, Read (PD4) and Write (PD5)
	GPIOD -> CRH |= 0xBB000BBB;
	GPIOD -> CRL &= 0xFF00FF00;
	GPIOD -> CRL |= 0x00BB00BB;
	
	// PORT E
	GPIOE -> CRH &= 0x00000000; // set-up Data Bus
	GPIOE -> CRH |= 0xBBBBBBBB;
	GPIOE -> CRL &= 0x0FFFFFFF;
	GPIOE -> CRL |= 0xB0000000;
	
	// PORT G
	GPIOG -> CRH &= 0xFFF0FFFF; // set-up Chip select (PG12) and Register select (PG0)
	GPIOG -> CRH |= 0x000B0000;
	GPIOG -> CRL &= 0xFFFFFFF0; // PG0 -> RS
	GPIOG -> CRL |= 0x0000000B;
	
	// LCD uses FSMC Bank 4 memory bank
	// use Mode A
	FSMC_Bank1 -> BTCR[6] = 0x00000000; // reset FSMC_BCR4
	FSMC_Bank1 -> BTCR[7] = 0x00000000; // reset FSMC_BTR4
	FSMC_Bank1E -> BWTR[6] = 0x00000000; // reset FSMC_BWTR4
	FSMC_Bank1 -> BTCR[6] |= 1 << 12; // FSMC_BCR4 -> WREN
	FSMC_Bank1 -> BTCR[6] |= 1 << 14; // FSMC_BCR4 -> EXTMOD
	FSMC_Bank1 -> BTCR[6] |= 1 << 4; // FSMC_BCR4 -> MWID
	FSMC_Bank1 -> BTCR[7] |= 0 << 28; // FSMC_BTR4 -> ACCMOD
	FSMC_Bank1 -> BTCR[7] |= 1 << 0; // FSMC_BTR4 -> ADDSET
	FSMC_Bank1 -> BTCR[7] |= 0xF << 8; // FSMC_BTR4 -> DATAST
	FSMC_Bank1E -> BWTR[6] |= 0 << 28; // FSMC_BWTR4 -> ACCMOD
	FSMC_Bank1E -> BWTR[6] |= 0 << 0; // FSMC_BWTR4 -> ADDSET
	FSMC_Bank1E -> BWTR[6] |= 3 << 8; // FSMC_BWTR4 -> DATAST
	FSMC_Bank1 -> BTCR[6] |= 1 << 0; // FSMC_BCR4 -> FACCEN
	IERG3810_TFTLCD_SetParameter(); // special setting for LCD module
	GPIOB -> BSRR = 1; // LCD_LIGHT_ON;
}

void IERG3810_TFTLCD_DrawDot(u16 x, u16 y, u16 color){
	IERG3810_TFTLCD_WrReg(0x2A); // set x position
	IERG3810_TFTLCD_WrData(x >> 8);
	IERG3810_TFTLCD_WrData(x & 0xFF);
	IERG3810_TFTLCD_WrData(0x01);
	IERG3810_TFTLCD_WrData(0x3F);
	
	IERG3810_TFTLCD_WrReg(0x2B); // set y position
	IERG3810_TFTLCD_WrData(y >> 8);
	IERG3810_TFTLCD_WrData(y & 0xFF);
	IERG3810_TFTLCD_WrData(0x01);
	IERG3810_TFTLCD_WrData(0xDF);
	
	IERG3810_TFTLCD_WrReg(0x2C); // set point with color
	IERG3810_TFTLCD_WrData(color);
}

void IERG3810_TFTLCD_FillRectangle(u16 color, u16 start_x, 
					u16 length_x, u16 start_y, u16 length_y){
	u32 index=0;
	IERG3810_TFTLCD_WrReg(0x2A);
	IERG3810_TFTLCD_WrData(start_x >> 8);
	IERG3810_TFTLCD_WrData(start_x & 0xFF);
	IERG3810_TFTLCD_WrData((start_x + length_x - 1) >> 8);
	IERG3810_TFTLCD_WrData((start_x + length_x - 1) & 0xFF);
	
	IERG3810_TFTLCD_WrReg(0x2B);
	IERG3810_TFTLCD_WrData(start_y >> 8);
	IERG3810_TFTLCD_WrData(start_y & 0xFF);
	IERG3810_TFTLCD_WrData((start_y + length_y - 1) >> 8);
	IERG3810_TFTLCD_WrData((start_y + length_y - 1) & 0xFF);
	
	IERG3810_TFTLCD_WrReg(0x2C); // LCD_WriteRAM_Prepare();
	for(index = 0; index < length_x * length_y; index++){
		IERG3810_TFTLCD_WrData(color);
	}
}
	
void IERG3810_TFTLCD_SevenSegment(u16 color, u16 start_x, u16 start_y, u8 digit){
	// out of range
	if (digit > 9) return;
	
	// Pin A
	switch(digit){
		case 1:
		case 4:
			break;
		default:
			IERG3810_TFTLCD_FillRectangle(color, start_x + 10, 60, start_y + 150, 10);
	}
	
	// Pin B
	switch(digit){
		case 5:
		case 6:
			break;
		default:
			IERG3810_TFTLCD_FillRectangle(color, start_x + 70, 10, start_y + 85, 65);
	}
	
	// Pin C
	if (digit != 2){
			IERG3810_TFTLCD_FillRectangle(color, start_x + 70, 10, start_y + 10, 65);
	}
	
	// Pin D
	switch(digit){
		case 1:
		case 4:
		case 7:
			break;
		default:
			IERG3810_TFTLCD_FillRectangle(color, start_x + 10, 60, start_y, 10);
	}
	
	// Pin E
	switch(digit){
		case 0:
		case 2:
		case 6:
		case 8:
			IERG3810_TFTLCD_FillRectangle(color, start_x, 10, start_y + 10, 65);
	}
	
	// Pin F
	switch(digit){
		case 1:
		case 2:
		case 3:
		case 7:
			break;
		default:
			IERG3810_TFTLCD_FillRectangle(color, start_x, 10, start_y + 85, 65);
	}
	
	// Pin G
	switch(digit){
		case 0:
		case 1:
		case 7:
			break;
		default:
			IERG3810_TFTLCD_FillRectangle(color, start_x + 10, 60, start_y + 75, 10);
	}
}

void IERG3810_TFTLCD_ShowChar(u16 x, u16 y, u8 ascii, u16 color, u16 bgcolor){
	u8 i, j;
	u8 index;
	u8 height=16, length=8;
	
	if(ascii < 32 || ascii > 127) return;
	ascii -= 32;
	
	IERG3810_TFTLCD_WrReg(0x2A);
	IERG3810_TFTLCD_WrData(x >> 8);
	IERG3810_TFTLCD_WrData(x & 0xFF);
	IERG3810_TFTLCD_WrData((x + length - 1) >> 8);
	IERG3810_TFTLCD_WrData((x + length - 1) & 0xFF);
	
	IERG3810_TFTLCD_WrReg(0x2B);
	IERG3810_TFTLCD_WrData(y >> 8);
	IERG3810_TFTLCD_WrData(y & 0xFF);
	IERG3810_TFTLCD_WrData((y + height - 1) >> 8);
	IERG3810_TFTLCD_WrData((y + height - 1) & 0xFF);
	
	IERG3810_TFTLCD_WrReg(0x2C); // LCD_WriteRAM_Prepare();
	
	for(j = 0; j < height / 8; j++){
		for(i = 0; i < height / 2; i++){
			for(index = 0; index < length; index++){
				if((asc2_1608[ascii][index*2+1-j] >> i) & 0x01) IERG3810_TFTLCD_WrData(color);
				else IERG3810_TFTLCD_WrData(bgcolor);
			}
		}
	}
}

void IERG3810_TFTLCD_ShowChinChar(u16 x, u16 y, u8 id, u16 color, u16 bgcolor){
	u8 i, j;
	u8 index;
	u8 height=16, length=16;
	
	if(id > 5) return;
	
	IERG3810_TFTLCD_WrReg(0x2A);
	IERG3810_TFTLCD_WrData(x >> 8);
	IERG3810_TFTLCD_WrData(x & 0xFF);
	IERG3810_TFTLCD_WrData((x + length - 1) >> 8);
	IERG3810_TFTLCD_WrData((x + length - 1) & 0xFF);
	
	IERG3810_TFTLCD_WrReg(0x2B);
	IERG3810_TFTLCD_WrData(y >> 8);
	IERG3810_TFTLCD_WrData(y & 0xFF);
	IERG3810_TFTLCD_WrData((y + height - 1) >> 8);
	IERG3810_TFTLCD_WrData((y + height - 1) & 0xFF);
	
	IERG3810_TFTLCD_WrReg(0x2C); // LCD_WriteRAM_Prepare();
	
	for(j = 0; j < height / 8; j++){
		for(i = 0; i < height / 2; i++){
			for(index = 0; index < length; index++){
				if((chi_1616[id][index*2+1-j] >> i) & 0x01) IERG3810_TFTLCD_WrData(color);
				else IERG3810_TFTLCD_WrData(bgcolor);
			}
		}
	}
}

void IERG3810_TFTLCD_ShowChar_NF(u16 x, u16 y, u8 ascii, u16 color){
	u8 i, j;
	u8 index;
	u8 height=16, length=8;
	
	if(ascii < 32 || ascii > 127) return;
	ascii -= 32;
	
	for(j = 0; j < height / 8; j++){
		for(i = 0; i < height / 2; i++){
			for(index = 0; index < length; index++){
				if((asc2_1608[ascii][index*2+1-j] >> i) & 0x01)
					IERG3810_TFTLCD_DrawDot(x+index, y+8*j+i, color);
			}
		}
	}
}

void IERG3810_TFTLCD_ShowChinChar_NF(u16 x, u16 y, u8 id, u16 color){
	u8 i, j;
	u8 index;
	u8 height=16, length=16;
	
	if(id > 5) return;
	
	for(j = 0; j < height / 8; j++){
		for(i = 0; i < height / 2; i++){
			for(index = 0; index < length; index++){
				if((chi_1616[id][index*2+1-j] >> i) & 0x01)
					IERG3810_TFTLCD_DrawDot(x+index, y+8*j+i, color);
			}
		}
	}
}

void IERG3810_TFTLCD_ShowSpecial_NF(u16 x, u16 y, u8 id, u16 color){
	u8 i, j;
	u8 index;
	u8 height=16, length=16;
	
	if(id > 5) return;
	
	for(j = 0; j < height / 8; j++){
		for(i = 0; i < height / 2; i++){
			for(index = 0; index < length; index++){
				if((special_1616[id][index*2+1-j] >> i) & 0x01)
					IERG3810_TFTLCD_DrawDot(x+index, y+8*j+i, color);
			}
		}
	}
}
