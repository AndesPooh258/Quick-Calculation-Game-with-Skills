/* main.c: C source file for main program */
#include "stm32f10x.h"
#include "IERG3810_LED.h"
#include "IERG3810_KEY.h"
#include "IERG3810_Buzzer.h"
#include "IERG3810_Clock.h"
#include "IERG3810_USART.h"
#include "IERG3810_TFTLCD.h"
#include "IERG3810_EXTI.h"
#include "IERG3810_TIM.h"
#include "global.h"
#include "calculate.h"
#include "display.h"
#include "display_USART.h"
#include "game.h"
#include "input.h"

#include <stdlib.h>
#include <math.h>

/* timer variables */
u8 task1HeartBeat;
int count = 0;

/* state variables */
int state = 0; // 0: start page, 1: game page, 2: end page
int diff = 0; int score = 0; int skill = 2; int life = 3;
int ruleDisplayed = 0; int hintDisplayed = 0;
int input[6]; int solved = 1;
int rocketMove = 0; int refreshPending = 0;

/* equation definition variables */
int left, mid, right, opt1, opt2, ans;

/* display variables */
u16 color = 0x001F; u16 bgcolor = 0xFFE0;
int player_pos = 112;
int block_pos = 0; int block_end = 0; int input_pos = 0;
int rocket_x = 112; int rocket_y = 116;
int ans_defaultX, ans_actualX, ans_maxX;

int main(void){
	Game_Init();
	while(1){
		if (task1HeartBeat >= 10){
			
			task1HeartBeat = 0;
			if(count % 3 == 2){
				IERG3810_DS0_Off();
				IERG3810_DS1_Off();
				IERG3810_Buzzer_Off();
			}
			
			if (state == 0){
				if (count == 0){
					USART_print(2, "Game Start ->");
					printStartScreen();
				}
				if (count % 2 == 0){
					checkState0KeyInput();
				}
			}
			
			if (checkKeyboardInput()) continue;
			
			if (state == 1){
				if (count >= 100){
					count = 0; // reset timer count
					rocketMove = 0; // stop rocket movement
					if (checkTimeout()) continue;
				}
				printPlayerIcon();
				checkState1KeyInput();
				printMainScreen();
				checkAns();
			}
			
			if (state == 2){
				if (count == 0){
					USART_print(2, " Game Over! ");
					printEndGame();
				}
				checkState2KeyInput();
			}
			count++;
		}
	}
}
