/* IERG3810_Buzzer.c: C source file for buzzer operations, defined in lab 1 */
#include "stm32f10x.h"
#include "IERG3810_Buzzer.h"

void IERG3810_Buzzer_Init(){
	// enable GPIO-B clock
	RCC -> APB2ENR |= 1 << 3;
	// set-up buzzer (PB8)
	GPIOB -> CRH &= 0xFFFFFFF0;
	GPIOB -> CRH |= 0x00000003;
}

void IERG3810_Buzzer_On(){
	// turn on the buzzer
	GPIOB -> BSRR = 1 << 8;
}

void IERG3810_Buzzer_Off(){
	// turn off the buzzer
	GPIOB -> BRR = 1 << 8;
}
