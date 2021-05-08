/* IERG3810_Clock.c: C source file for initializing clock tree, defined in lab 2 */
#include "stm32f10x.h"
#include "IERG3810_Clock.h"

void IERG3810_clock_tree_init(void){
	u8 PLL=7;
	unsigned char temp=0;
	/*  reference:
		FLASH -> ACR (RM0008 page-60) 
		RCC -> CR (RM0008 page-129) 
		RCC -> CFGR (RM0008 page-131) */
	
	RCC -> CFGR &= 0xF8FF0000; // reset the Clock Configuration Register
	RCC -> CR &= 0xFEF6FFFF; // reset the Clock Control Register
	
	RCC -> CR |= 0x00010000; // enable HSE oscillator (HSEON=1)
	while(!(RCC -> CR >> 17)); // check whether HSE oscillator is ready (HSERDY)
		
	RCC -> CFGR = 0x00000C00; // set APB1 to be HCLK divided by 2 (PPRE1=100), APB2 to be HCLK not divided (PPRE2=001)
	
	// setting the PLL clock
	RCC -> CFGR |= PLL << 18; // PLL input clock x 9 (PLLMUL=111)
	RCC -> CFGR |= 1 << 16; // clock from PREDIV1 selected as PLL input clock (PLLSRC=1)
	FLASH -> ACR |= 0x32; // set FLASH with 2 wait states
	
	RCC -> CR |= 0x01000000; // enable PLL (PLLON=1)
	while(!(RCC -> CR >> 25)); // check whether PLL is ready (PLLEDY)
	RCC -> CFGR |= 0x00000002; // selected PLL as system clock (SW=10)
	
	// check whether PLL is used as system clock (SWS)
	while(temp != 0x02){
		temp = RCC -> CFGR >> 2;
		temp &= 0x03;
	}
}
