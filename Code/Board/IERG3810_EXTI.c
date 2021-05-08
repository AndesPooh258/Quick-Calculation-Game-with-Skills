/* IERG3810_EXTI.c: C source file for external interrupt, defined in lab 4 */
#include "stm32f10x.h"
#include "IERG3810_USART.h"
#include "IERG3810_EXTI.h"
#include "Board.h"
#include "global.h"
#include "calculate.h"
#include "display.h"

// global variables
u32 timeout = 10000; // for PS2 Keyboard timeout
u32 ps2key = 0; // store PS2 keyboard data
u32 ps2count = 0; // count PS2 keyboard received bit
u8 ps2dataReady = 0; // 1 = PS2 keyboard received data correctly
u32 readkey = 0;

void IERG3810_NVIC_SetPriorityGroup(u8 prigroup){
	// set PRIGROUP AIRCR[10:8]
	u32 temp, temp1;
	temp1 = prigroup & 0x00000007; // only concern 3 bits
	temp1 <<= 8;
	temp = SCB -> AIRCR; // ARM DDI0337E page 8-22
	temp &= 0x0000F8FF; // ARM DDI0337E page 8-22
	temp |= 0x05F0000; // ARM DDI0337E page 8-22
	SCB -> AIRCR = temp;
}

void IERG3810_key2_ExtiInit(void){
	// KEY2 at PE2, EXTI-2, IRQ#8
	RCC -> APB2ENR |= 1 << 6; // refer to lab-1
	GPIOE -> CRL &= 0xFFFFF0FF; // refer to lab-1
	GPIOE -> CRL |= 0x00000800; // refer to lab-1
	GPIOE -> ODR |= 1 << 2; // refer to lab-1
	
	RCC -> APB2ENR |= 0x01; // (RM0008, page-119)
	AFIO -> EXTICR[0] &= 0xFFFFF0FF; // (RM0008, page-185)
	AFIO -> EXTICR[0] |= 0x00000400; // (RM0008, page-185)
	EXTI -> IMR |= 1 << 2; // (RM0008, page-202)
	EXTI -> FTSR |= 1 << 2; // (RM0008, page-203)
	// EXTI -> RTSR |= 1 << 2; // (RM0008, page-203)
	
	NVIC -> IP[8] = 0x65; // set priority of this interrupt
	NVIC -> ISER[0] |= 1 << 8; // (D10337E, page 8-3)
}

void EXTI2_IRQHandler(void){
	EXTI -> PR = 1 << 2; // clear this exception pending bit
}

void IERG3810_keyUP_ExtiInit(void){
	// KEYUP at PA0, EXTI-0, IRQ#6
	RCC -> APB2ENR |= 1 << 2;
	GPIOA -> CRL &= 0XFFFFFFF0;
	GPIOA -> CRL |= 0X00000008;
	GPIOA -> ODR |= 0;
	
	RCC -> APB2ENR|=0x01;
	AFIO -> EXTICR[0] &= 0xFFFFFFF0;
	AFIO -> EXTICR[0] |= 0x00000000;
	EXTI -> IMR |= 1;
	EXTI -> FTSR |= 1;
	
	NVIC -> IP[6] = 0x75; // set priority to level 0x75
	
	NVIC -> ISER[0] |= 1 << 6;
}

void EXTI0_IRQHandler(void){
	// when the game is running and player still have skill
	if(state == 1 && skill > 0){
		USART_print(2, " Game Stopped.");
		printStop();
		USART_print(2, " Game Resumed.");
		skill--;
		printUpperPanel();
	}
	EXTI -> PR = 1; // clear this exception pending bit
}

void IERG3810_PS2key_ExtiInit(void){
	// PS2 Keyboard CLK at PC11, EXTI-11, IRQ#40
	RCC -> APB2ENR |= 1 << 4; // enable PC11 as input
	GPIOC -> CRH &= 0XFFFFF0FF;
	GPIOC -> CRH |= 0X00000800;
	GPIOC -> ODR |= 1 << 2;
	
	RCC -> APB2ENR |= 0x01; // setting interrupt line
	AFIO -> EXTICR[2] &= 0xFFFF0FFF;
	AFIO -> EXTICR[2] |= 0x00002000;
	EXTI -> IMR |= 1 << 11;
	EXTI -> FTSR |= 1 << 11;
	
	NVIC -> IP[40] = 0x75; // set priority of this interrupt
	NVIC -> ISER[1] |= 1 << 8;
}

void EXTI15_10_IRQHandler(void){
	if (!ps2dataReady){
		if (ps2count > 0 && ps2count < 9)
			ps2key |= ((GPIOC -> IDR & 1 << 10) >> 10) << (ps2count - 1);
		ps2count++;
	}

	Delay(10); // a short delay can eliminate the error
	EXTI -> PR = 1 << 11; // clear this exception pending bit
}
