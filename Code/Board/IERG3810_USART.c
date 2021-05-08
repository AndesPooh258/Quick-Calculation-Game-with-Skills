/* IERG3810_USART.c: C source file for USART operations, defined in lab 2 */
#include "stm32f10x.h"

void IERG3810_USART1_init(u32 pclk2, u32 bound){
	// USARTDIV calculation
	float temp;
	u16 mantissa;
	u16 fraction;
	temp = (float) (pclk2*1000000)/(bound*16);
	mantissa = temp;
	fraction = (temp - mantissa) * 16;
	mantissa <<= 4;
	mantissa += fraction;
	
	/*  reference:
		RCC -> APB2RSTR (RM0008 page-103) 
		RCC -> APB2ENR (RM0008 page-142) 
		GPIOx -> CRH (RM0008 page-167)
		USART1 -> BRR (RM0008 page-792)
		USART1 -> CR1 (RM0008 page-793) */
	
	RCC -> APB2ENR |= 1 << 2; // enable GPIO-A clock (IOPAEN=1)
	RCC -> APB2ENR |= 1 << 14; // enable USART2 clock (USART1EN=1)
	GPIOA -> CRH &= 0xFFFFF00F; // set PA9, PA10 Alternate Function
	GPIOA -> CRH |= 0x000008B0; // set PA9, PA10 Alternate Function
	RCC -> APB2RSTR |= 1 << 14; // reset USART1 (USART1RST=1)
	RCC -> APB2RSTR &=~ (1 << 14); // no effect (USART1RST=0)
	USART1 -> BRR = mantissa; // set Baud rate register = USARTDIV
	USART1 -> CR1 |= 0x2008; // enable USART1 (UE=1) and Transmitter (TE=1)
}

void IERG3810_USART2_init(u32 pclk1, u32 bound){
	// USARTDIV calculation
	float temp;
	u16 mantissa;
	u16 fraction;
	temp = (float) (pclk1*1000000)/(bound*16);
	mantissa = temp;
	fraction = (temp - mantissa) * 16;
	mantissa <<= 4;
	mantissa += fraction;
	
	/*  reference:
		RCC -> APB1RSTR (RM0008 page-106) 
		RCC -> APB2ENR (RM0008 page-142) 
		RCC -> APB1ENR (RM0008 page-144) 
		GPIOx -> CRL (RM0008 page-166)
		USART2 -> BRR (RM0008 page-792)
		USART2 -> CR1 (RM0008 page-793) */
	
	RCC -> APB2ENR |= 1 << 2; // enable GPIO-A clock (IOPAEN=1)
	RCC -> APB1ENR |= 1 << 17; // enable USART2 clock (USART2EN=1)
	GPIOA -> CRL &= 0xFFFF00FF; // set PA2, PA3 Alternate Function
	GPIOA -> CRL |= 0x00008B00; // set PA2, PA3 Alternate Function
	RCC -> APB1RSTR |= 1 << 17; // reset USART2 (USART2RST=1)
	RCC -> APB1RSTR &= ~(1 << 17); // no effect (USART2RST=0)
	USART2 -> BRR = mantissa; // set Baud rate register = USARTDIV
	USART2 -> CR1 |= 0x2008; // enable USART2 (UE=1) and Transmitter (TE=1)
}

void USART_print(u8 USARTport, char *st){
	/*  reference: 
		USART -> SR (RM0008 page-790)
		USART -> DR (RM0008 page-792) */
	
	u8 i=0;
	while(st[i] != 0x00){
		if ((USARTport == 1) && (USART1 -> SR & 0x00000080)){
			USART1 -> DR = st[i];
			i++;
		} else if ((USARTport == 2) && (USART2 -> SR & 0x00000080)){
			USART2 -> DR = st[i];
			i++;
		}
		if(i == 255) break;
	}
}
