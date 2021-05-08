/* IERG3810_LED.c: C source file for LED operations, defined in lab 1 */
#include "stm32f10x.h"
#include "IERG3810_LED.h"

void IERG3810_LED_Init(){
	// Enable GPIO-B and GPIO-E clock
	RCC -> APB2ENR |= 1 << 3;
	RCC -> APB2ENR |= 1 << 6;
	
	// Set-up LED DS0 (PB5)
	GPIOB -> CRL &= 0xFF0FFFFF;
	GPIOB -> CRL |= 0x00300000;
	
	// Set-up LED DS1 (PE5)
	GPIOE -> CRL &= 0xFF0FFFFF;
	GPIOE -> CRL |= 0x00300000;
	
	// Set default of DS0 and DS1
	GPIOB -> BSRR = 1 << 5;
	GPIOE -> BSRR = 1 << 5;
}

void IERG3810_DS0_On(){
	// turn on the red LED
	GPIOB -> BRR = 1 << 5;
}

void IERG3810_DS0_Off(){
	// turn off the red LED
	GPIOB -> BSRR = 1 << 5;
}

void IERG3810_DS1_On(){
	// turn on the green LED
	GPIOE -> BRR = 1 << 5;
}

void IERG3810_DS1_Off(){
	// turn off the green LED
	GPIOE -> BSRR = 1 << 5;
}
