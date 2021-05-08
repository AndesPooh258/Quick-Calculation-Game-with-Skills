/* IERG3810_TIM.c: C source file for timer operations, defined in lab 5 */
#include "stm32f10x.h"
#include "IERG3810_TIM.h"

void IERG3810_TIM3_Init(u16 arr, u16 psc){
	// TIM3, IRQ#29
	RCC -> APB1ENR |= 1 << 1; // RM0008 page-111, refer to lab-1
	TIM3 -> ARR = arr; // RM0008 page-403
	TIM3 -> PSC = psc; // RM0008 page-402, 403
	TIM3 -> DIER |= 1 << 0; // RM0008 page-393
	TIM3 -> CR1 |= 0x01; // RM0008 page-388
	NVIC -> IP[29] = 0x45; // refer to lab-4
	NVIC -> ISER[0] |= (1 << 29); // refer to lab-4
}

void TIM3_IRQHandler(void){
	if(TIM3 -> SR & 1 << 0){ // RM0008 page-395
		GPIOB -> ODR ^= 1 << 5; // toggle DS0 with read-modify-write
	}
	TIM3 -> SR &= ~(1 << 0); // RM0008 page-395
}

void IERG3810_TIM4_Init(u16 arr, u16 psc){
	// TIM3, IRQ#30
	RCC -> APB1ENR |= 1 << 2; // RM0008 page-111, refer to lab-1
	TIM4 -> ARR = arr; // RM0008 page-403
	TIM4 -> PSC = psc; // RM0008 page-402, 403
	TIM4 -> DIER |= 1 << 0; // RM0008 page-393
	TIM4 -> CR1 |= 0x01; // RM0008 page-388
	NVIC -> IP[30] = 0x45; // refer to lab-4
	NVIC -> ISER[0] |= (1 << 30); // refer to lab-4
}

void TIM4_IRQHandler(void){
	if(TIM4 -> SR & 1 << 0){ // RM0008 page-395
		GPIOE -> ODR ^= 1 << 5; // toggle DS0 with read-modify-write
	}
	TIM4 -> SR &= ~(1 << 0); // RM0008 page-395 
}

void DS0_turnOff(){
	// level one subroutine
	GPIOB -> BSRR = 1 << 5;
}

void DS0_turnOff2(){
	// level two subroutine
	DS0_turnOff(); // call level one subroutine
}

void IERG3810_SYSTICK_Init10ms(void){
	SysTick -> CTRL = 0;
	SysTick -> LOAD = 89999;
	SysTick -> CTRL |= 3;
}

void IERG3810_TIM3_PwmInit(u16 arr, u16 psc){
	RCC -> APB2ENR |= 1 << 3; // RM0008 page-111, refer to lab-1
	GPIOB -> CRL &= 0xFF0FFFFF; // lab-1
	GPIOB -> CRL |= 0x00B00000; // lab-1
	RCC -> APB2ENR |= 1 << 0; // lab-4
	AFIO -> MAPR &= 0xFFFFF3FF; // RM0008 page-179 
	AFIO -> MAPR |= 1 << 11; // RM0008 page-179
	RCC -> APB1ENR |= 1 << 1; // RM0008 page-112
	TIM3 -> ARR = arr; // RM0008 page-403
	TIM3 -> PSC = psc; // RM0008 page-402, 403
	TIM3 -> CCMR1 |= 7 << 12; // RM0008 page-397
	TIM3 -> CCMR1 |= 1 << 11; // RM0008 page-397
	TIM3 -> CCER |= 1 << 4; // RM0008 page-401
	TIM3 -> CR1 = 0x0080; // RM0008 page-388
	TIM3 -> CR1 |= 0x01; // RM0008 page-388
}
