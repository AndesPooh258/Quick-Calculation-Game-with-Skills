/* Board.c: C source file for generic operations */
#include "stm32f10x.h"
#include "Board.h"

void Delay(u32 count){
	u32 i;
	for(i=0; i<count; i++);
}
