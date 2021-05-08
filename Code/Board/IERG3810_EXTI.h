/* IERG3810_EXTI.h: header file for external interrupt, defined in lab 4 */
#include "stm32f10x.h"

extern u32 timeout;
extern u32 ps2key;
extern u32 ps2count;
extern u8 ps2dataReady;

void IERG3810_NVIC_SetPriorityGroup(u8);
void IERG3810_key2_ExtiInit(void);
void EXTI2_IRQHandler(void);
void IERG3810_keyUP_ExtiInit(void);
void EXTI0_IRQHandler(void);
void IERG3810_PS2key_ExtiInit(void);
void EXTI15_10_IRQHandler(void);
