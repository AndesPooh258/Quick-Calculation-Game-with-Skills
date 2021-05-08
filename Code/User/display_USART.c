/* display_USART.c: C source file for debug view */
#include "stm32f10x.h"
#include "IERG3810_USART.h"
#include "IERG3810_TFTLCD.h"
#include "calculate.h"
#include "display.h"
#include "global.h"

#include <stdlib.h>
#include <math.h>

// print out an integer using USART
void printInt_USART(int num){
	int i;
	char digit[2] = {'0', '\0'};
	// print '-' for negative number
	if (num < 0){
		USART_print(2, "-");
		num = -num;
	}
	
	// print the integer digit by digit
	for (i = abs(getNumOfDigit(num)) - 1; i >= 0; i--){
		digit[0] = '0' + (num / (int) pow(10, i)) % 10;
		USART_print(2, digit);
	}
}

// print out an operator using USART
void printOpt_USART(int opt){
	USART_print(2, " ");
	switch(opt){
		case 0:
			USART_print(2, "+");
			break;
		case 1:
			USART_print(2, "-");
			break;
		case 2:
			USART_print(2, "x");
			break;
		case 3:
			USART_print(2, "%");
			break;
	}
	USART_print(2, " ");
}

// print out an equation using USART
void printEqt_USART(){
	if(diff < 2){
		// 1 operation for beginner and normal
		printInt_USART(left);
		printOpt_USART(opt1);
		printInt_USART(right);
	} else {
		// 2 operations for expert
		USART_print(2, "(");
		printInt_USART(left);
		printOpt_USART(opt1);
		printInt_USART(mid);
		USART_print(2, ")");
		printOpt_USART(opt2);
		printInt_USART(right);
	}
}
