/* input.c: C source file for game input */
#include "stm32f10x.h"
#include "IERG3810_LED.h"
#include "IERG3810_KEY.h"
#include "IERG3810_Buzzer.h"
#include "IERG3810_USART.h"
#include "IERG3810_TFTLCD.h"
#include "IERG3810_EXTI.h"
#include "calculate.h"
#include "display.h"
#include "display_USART.h"
#include "game.h"
#include "global.h"
#include "input.h"

#include <math.h>

// check timeout of the game
int checkTimeout(){
	if (solved){
		// generate new equation if the problem is solved
		solved = 0;
		Question_Init();
	} else {
		// life - 1 if the problem is not solved
		life--;
		USART_print(2, " Timeout... Life: ");
		printInt_USART(life);
		if (life <= 0){ 
			// end current game if life = 0
			IERG3810_Buzzer_On();
			state = 2;
			return 1;
		} else {
			// generate new equation if the problem is solved
			Question_Init();
		}
	}
	return 0;
}

// check user keyboard input
int checkKeyboardInput(){
	if (ps2count >= 11){
		ps2dataReady = 1;
		if (ps2key == 0x7C){ // *
			USART_print(2, " Game Reset! ");
			resetGame();
			return 1;
		} else if (state == 1){
			if (ans_actualX < ans_maxX){
				switch(ps2key){
					// append the received digit to input[]  
					case 0x70: // 0
						input[input_pos++] = 0;
						IERG3810_TFTLCD_ShowChar_NF(ans_actualX, 80, '0', color);
						ans_actualX += 8;
						break;
					case 0x69: // 1
						input[input_pos++] = 1;
						IERG3810_TFTLCD_ShowChar_NF(ans_actualX, 80, '1', color);
						ans_actualX += 8;
						break;
					case 0x72: // 2
						input[input_pos++] = 2;
						IERG3810_TFTLCD_ShowChar_NF(ans_actualX, 80, '2', color);
						ans_actualX += 8;
						break;
					case 0x7A: // 3
						input[input_pos++] = 3;
						IERG3810_TFTLCD_ShowChar_NF(ans_actualX, 80, '3', color);
						ans_actualX += 8;
						break;
					case 0x6B: // 4
						input[input_pos++] = 4;
						IERG3810_TFTLCD_ShowChar_NF(ans_actualX, 80, '4', color);
						ans_actualX += 8;
						break;
					case 0x73: // 5
						input[input_pos++] = 5;
						IERG3810_TFTLCD_ShowChar_NF(ans_actualX, 80, '5', color);
						ans_actualX += 8;
						break;
					case 0x74: // 6
						input[input_pos++] = 6;
						IERG3810_TFTLCD_ShowChar_NF(ans_actualX, 80, '6', color);
						ans_actualX += 8;
						break;
					case 0x6C: // 7
						input[input_pos++] = 7;
						IERG3810_TFTLCD_ShowChar_NF(ans_actualX, 80, '7', color);
						ans_actualX += 8;
						break;
					case 0x75: // 8
						input[input_pos++] = 8;
						IERG3810_TFTLCD_ShowChar_NF(ans_actualX, 80, '8', color);
						ans_actualX += 8;
						break;
					case 0x7D: // 9
						input[input_pos++] = 9;
						IERG3810_TFTLCD_ShowChar_NF(ans_actualX, 80, '9', color);
						ans_actualX += 8;
						break;
				}
			} else if (ps2key == 0xE0){ // ENTER or /
				// move the rocket
				rocket_x = player_pos;
				if(player_pos >= block_pos - 8 && player_pos < block_end - 8){
					rocketMove = 1;
				} else rocketMove = -1;
			}
		}
		// reset ps2 variables
		ps2count = 0;
		ps2key = 0;
		ps2dataReady = 0;
	}
	return 0;
}

// check user key input when state = 0
void checkState0KeyInput(){
	// change difficulty
	if (IERG3810_KEYUP_Pressed()){
		diff = max(diff - 1, 0);
		printStartScreen();
	}
	if (IERG3810_KEY1_Pressed()){
		diff = min(diff + 1, 2);
		printStartScreen();
	}
	
	// toggle start page / game rule
	if (IERG3810_KEY2_Pressed()){
		if(!ruleDisplayed){
			ruleDisplayed = 1;
			printRule();
		} else {
			ruleDisplayed = 0;
			printStartScreen();
		}
	}
	
	// start the game
	if (IERG3810_KEY0_Pressed()){
		state = 1;
		count = 100;
		USART_print(2, " Difficulty: ");
		printInt_USART(diff);
	}
}

// check user key input when state = 1
void checkState1KeyInput(){
	// move player icon
	if (IERG3810_KEY2_Pressed() && player_pos > 20){
		player_pos -= 4;
		USART_print(2, " Player go left: ");
		printInt_USART(player_pos);
	}
	if (IERG3810_KEY0_Pressed() && player_pos < 200){
		player_pos += 4;
		USART_print(2, " Player go right: ");
		printInt_USART(player_pos);
	}
	
	// display hint
	if (IERG3810_KEY1_Pressed() && hintDisplayed == 0 && skill > 0){
		if(printHint()){
			input_pos++;
			ans_actualX = ans_defaultX + 8;
			hintDisplayed = 1;
			skill--;
			printUpperPanel();
		}
	}	
}

// check user key input when state = 2
void checkState2KeyInput(){
	// try again
	if (IERG3810_KEY2_Pressed() && player_pos > 20){
		restartGame();
		cleanScreen();
		USART_print(2, "Restart ->");
	}
	
	// back to start page
	if (IERG3810_KEY0_Pressed() && player_pos < 200){
		resetGame();
		count = -1;
		USART_print(2, "Reset -> ");
	}
}

// check user answer
void checkAns(){
	int i;
	int inputAns = 0;
	int numOfDigit = getNumOfDigit(ans);
	if (refreshPending){
		USART_print(2, " Received: ");
		if(numOfDigit >= 0){
			for (i=1; i <= numOfDigit; i++){
				inputAns += (int) input[i-1] * pow(10, numOfDigit - i);
				printInt_USART(input[i-1]);
			}
		} else {
			USART_print(2, "-");
			for (i=1; i <= -numOfDigit; i++){
				inputAns -= (int) input[i-1] * pow(10, -numOfDigit - i);
				printInt_USART(input[i-1]);
			}
		}
		
		// compare the expected answer and received answer
		if (inputAns == ans){
			// update score
			score += (diff + 1);
			
			// reset variables
			solved = 1;
			count = 100;
			
			// turn on green LED
			IERG3810_DS1_On();
			USART_print(2, " (Correct)");
		} else {
			// reset variables
			clearInput();
			ans_actualX = ans_defaultX;
			input_pos = 0;
			hintDisplayed = 0;
			
			// turn on red LED
			IERG3810_DS0_On();
			USART_print(2, " (Wrong)");
		}
		refreshPending = 0;
	}
}
