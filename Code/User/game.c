/* game.c: C source file for game control */
#include "stm32f10x.h"
#include "IERG3810_LED.h"
#include "IERG3810_KEY.h"
#include "IERG3810_Buzzer.h"
#include "IERG3810_Clock.h"
#include "IERG3810_USART.h"
#include "IERG3810_TFTLCD.h"
#include "IERG3810_EXTI.h"
#include "IERG3810_TIM.h"
#include "calculate.h"
#include "display.h"
#include "display_USART.h"
#include "input.h"
#include "game.h"
#include "global.h"

#include <stdlib.h>

// initialize hardware components for the game
void Game_Init(){
	IERG3810_clock_tree_init();
	IERG3810_LED_Init();
	IERG3810_KEY_Init();
	IERG3810_Buzzer_Init();
	IERG3810_USART2_init(36, 9600);
	IERG3810_TFTLCD_Init();
	IERG3810_NVIC_SetPriorityGroup(5);
	IERG3810_keyUP_ExtiInit();
	IERG3810_PS2key_ExtiInit();
	IERG3810_SYSTICK_Init10ms();
}

// initialize a question
void Question_Init(){
	// generate an equation and print it out using USART
	genEqt();
	USART_print(2, " Equation: ");
	printEqt_USART();
	USART_print(2, " Expected: ");
	printInt_USART(ans);
	
	// evaluate default x position
	if (ans >= 0)
		ans_defaultX = 134;
	else ans_defaultX = 142;
	ans_actualX = ans_defaultX;
	
	// calculate maximum x position
	ans_maxX = ans_defaultX + abs(getNumOfDigit(ans)) * 8;
	
	clearInput();
	
	// set input and block position
	input_pos = 0; 
	block_pos = rand() % 80 + 20;
	
	// print screen
	cleanScreen();
	printUpperPanel();
	printMainScreen();
	printPlayerIcon();
	printLowerPanel();
	
	// turn off LED
	IERG3810_DS0_Off();
	IERG3810_DS1_Off();
}

// clear input
void clearInput(){
	int i;
	for (i=0; i<6; i++){
		input[i] = 0;
	}
	if(state == 1)
		printLowerPanel();
}

// restart game without back to the start screen
void restartGame(){
	count = 100; state = 1;
	score = 0; skill = 2; life = 3;
	ruleDisplayed = 0; hintDisplayed = 0;
	clearInput();
	solved = 1; 
	rocketMove = 0; refreshPending = 0;
	player_pos = 112;
	rocket_x = 112; rocket_y = 116;
	ps2count = 0; ps2key = 0; ps2dataReady = 0;
}

// restart game and back to the start screen
void resetGame(){
	count = 0; state = 0; diff = 0;
	score = 0; skill = 2; life = 3;
	ruleDisplayed = 0; hintDisplayed = 0;
	clearInput();
	solved = 1;
	rocketMove = 0; refreshPending = 0;
	player_pos = 112;
	rocket_x = 112; rocket_y = 116;
	ps2count = 0; ps2key = 0; ps2dataReady = 0;
}
