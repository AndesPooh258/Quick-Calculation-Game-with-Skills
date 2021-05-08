/* calculate.c: C source file for game model */
#include "calculate.h"
#include "global.h"
#include <stdlib.h>
#include <math.h>

// get the number of digit given an integer, return negative value if the integer is negative
int getNumOfDigit(int num){
	int counter = 1;
	for (; abs(num) >= 10; num /= 10, counter++);
	return num >= 0? counter: -counter;
}

// get the first digit given an integer, return -1 if the integer has only 1 digit
int getFirstDigit(int ans){
	ans = abs(ans);
	if (ans < 10) return -1; // hint is not available
	else for (; ans >= 10; ans /= 10);
	return ans;
}

// perform arithmetic operation given an operator and 2 operands
int doOpt(int left, int right, int opt){
	switch(opt){
		case 0:
			return left + right;
		case 1:
			return left - right;
		case 2:
			return left * right;
		case 3:
			return left % right;
		default:
			return -1;
	}
}

// generate a new equation
void genEqt(){
	left = rand() % (20 * (diff + 1));
	right = rand() % (20 * (diff + 1));
	opt1 = rand() % (diff + 2);
    
	switch(diff){
		case 0: // beginner: +, - only (1 operation)
		case 1: // normal: +, -, * only (1 operation)
			ans = doOpt(left, right, opt1);
			break;
		case 2: // expert: +, -, *, % only (2 operations)
			mid = rand() % 20;
			opt2 = rand() % (diff + 2);
			ans = doOpt(doOpt(left, mid, opt1), right, opt2);
			break;
		default:
			return;
	}
}
