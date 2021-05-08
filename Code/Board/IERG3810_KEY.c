/* IERG3810_KEY.c: C source file for key operations, defined in lab 1 */
#include "stm32f10x.h"
#include "IERG3810_KEY.h"

void IERG3810_KEY_Init(){
	// enable GPIO-A and GPIO-E clock
	RCC -> APB2ENR |= 1 << 2;
	RCC -> APB2ENR |= 1 << 6;
	
	// set-up KEY_UP (PA0)
	RCC -> APB2ENR |= 1 << 2;
	GPIOA -> CRL &= 0xFFFFFFF0;
	GPIOA -> CRL |= 1 << 3;
	
	// set-up Key0 (PE4)
	GPIOE -> CRL &= 0xFFF0FFFF;
	GPIOE -> CRL |= 1 << 19;
	
	// set-up Key1 (PE3)
	GPIOE -> CRL &= 0xFFFF0FFF;
	GPIOE -> CRL |= 1 << 15;
	
	// set-up Key2 (PE2)
	GPIOE -> CRL &= 0xFFFFF0FF;
	GPIOE -> CRL |= 1 << 11;
	
	// set default of Key0, Key1, Key2 and KEY_UP
	GPIOE -> BSRR |= 1 << 4;
	GPIOE -> BSRR |= 1 << 3;
	GPIOE -> BSRR |= 1 << 2;
	GPIOA -> BRR |= 1;
}

int IERG3810_KEYUP_Pressed(){ // ^
	return (GPIOA -> IDR & 0x00000001) == 1;
}

int IERG3810_KEY0_Pressed(){ // >
	return (GPIOE -> IDR & 0x00000010) == 0;
}

int IERG3810_KEY1_Pressed(){ // v
	return (GPIOE -> IDR & 0x00000008) == 0;
}

int IERG3810_KEY2_Pressed(){ // <
	return (GPIOE -> IDR & 0x00000004) == 0;
}
