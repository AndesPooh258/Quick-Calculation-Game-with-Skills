#ifndef __GLOBAL
#define __GLOBAL
#include "stm32f10x.h"

#define min(a, b) a <= b ? a : b
#define max(a, b) a >= b ? a : b

/* timer variables */
extern u8 task1HeartBeat;
extern int count;

/* state variables */
extern int state; // 0: start page, 1: in progress, 2: end page
extern int diff, score, skill, life;
extern int ruleDisplayed, hintDisplayed;
extern int input[6]; 
extern int solved;
extern int rocketMove, refreshPending;

/* equation definition variables */
extern int left, mid, right, opt1, opt2, ans;

/* display variables */
extern u16 color, bgcolor;
extern int player_pos;
extern int block_pos, block_end, input_pos;
extern int rocket_x, rocket_y;
extern int ans_defaultX, ans_actualX, ans_maxX;

#endif
