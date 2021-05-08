/* IERG3810_TIM.h: header file for timer operations, defined in lab 5 */
#include "stm32f10x.h"

void IERG3810_TIM3_Init(u16, u16);
void IERG3810_TIM4_Init(u16, u16);
void IERG3810_SYSTICK_Init10ms(void);
void IERG3810_TIM3_PwmInit(u16, u16);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void DS0_turnOff(void);
void DS0_turnOff2(void);
