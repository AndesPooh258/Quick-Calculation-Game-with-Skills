/* IERG3810_TFTLCD.h: header file for TFTLCD operations, defined in lab 3 */
#include "stm32f10x.h"

void IERG3810_TFTLCD_WrReg(u16);
void IERG3810_TFTLCD_WrData(u16);
void IERG3810_TFTLCD_SetParameter(void);
void IERG3810_TFTLCD_Init(void);
void IERG3810_TFTLCD_DrawDot(u16, u16, u16);
void IERG3810_TFTLCD_FillRectangle(u16, u16, u16, u16, u16);
void IERG3810_TFTLCD_SevenSegment(u16, u16, u16, u8);
void IERG3810_TFTLCD_ShowChar(u16, u16, u8, u16, u16);
void IERG3810_TFTLCD_ShowChinChar(u16, u16, u8, u16, u16);
void IERG3810_TFTLCD_ShowChar_NF(u16, u16, u8, u16);
void IERG3810_TFTLCD_ShowChinChar_NF(u16, u16, u8, u16);
void IERG3810_TFTLCD_ShowSpecial_NF(u16, u16, u8, u16);
