/* display.c: C source file for game view */
#include "stm32f10x.h"
#include "IERG3810_LED.h"
#include "IERG3810_USART.h"
#include "IERG3810_TFTLCD.h"
#include "calculate.h"
#include "display.h"
#include "display_USART.h"
#include "game.h"
#include "global.h"
#include "input.h"

#include <stdlib.h>
#include <math.h>

// clean whole game screen
void cleanScreen(){
	IERG3810_TFTLCD_FillRectangle(0xFFFF, 0, 240, 0, 320);
}

// print out start screen
void printStartScreen(){
	cleanScreen();
	// print game name
	IERG3810_TFTLCD_ShowChar_NF(52, 252, 'Q', color);
	IERG3810_TFTLCD_ShowChar_NF(60, 252, 'u', color);
	IERG3810_TFTLCD_ShowChar_NF(68, 252, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(76, 252, 'c', color);
	IERG3810_TFTLCD_ShowChar_NF(84, 252, 'k', color);
	IERG3810_TFTLCD_ShowChar_NF(92, 252, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(100, 252, 'C', color);
	IERG3810_TFTLCD_ShowChar_NF(108, 252, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(116, 252, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(124, 252, 'c', color);
	IERG3810_TFTLCD_ShowChar_NF(132, 252, 'u', color);
	IERG3810_TFTLCD_ShowChar_NF(140, 252, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(148, 252, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(156, 252, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(164, 252, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(172, 252, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(180, 252, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(188, 252, ' ', color);

	IERG3810_TFTLCD_ShowChar_NF(56, 236, 'G', color);
	IERG3810_TFTLCD_ShowChar_NF(64, 236, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(72, 236, 'm', color);
	IERG3810_TFTLCD_ShowChar_NF(80, 236, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(88, 236, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(96, 236, 'w', color);
	IERG3810_TFTLCD_ShowChar_NF(104, 236, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(112, 236, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(120, 236, 'h', color);
	IERG3810_TFTLCD_ShowChar_NF(128, 236, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(136, 236, 'S', color);
	IERG3810_TFTLCD_ShowChar_NF(144, 236, 'k', color);
	IERG3810_TFTLCD_ShowChar_NF(152, 236, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(160, 236, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(168, 236, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(176, 236, 's', color);

	// print difficulties
	IERG3810_TFTLCD_ShowChar_NF(36, 200, 'S', color);
	IERG3810_TFTLCD_ShowChar_NF(44, 200, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(52, 200, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(60, 200, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(68, 200, 'c', color);
	IERG3810_TFTLCD_ShowChar_NF(76, 200, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(84, 200, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(92, 200, 'G', color);
	IERG3810_TFTLCD_ShowChar_NF(100, 200, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(108, 200, 'm', color);
	IERG3810_TFTLCD_ShowChar_NF(116, 200, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(124, 200, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(132, 200, 'D', color);
	IERG3810_TFTLCD_ShowChar_NF(140, 200, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(148, 200, 'f', color);
	IERG3810_TFTLCD_ShowChar_NF(156, 200, 'f', color);
	IERG3810_TFTLCD_ShowChar_NF(164, 200, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(172, 200, 'c', color);
	IERG3810_TFTLCD_ShowChar_NF(180, 200, 'u', color);
	IERG3810_TFTLCD_ShowChar_NF(188, 200, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(196, 200, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(204, 200, 'y', color);

	IERG3810_TFTLCD_ShowChar_NF(60, 176, '[', color);
	IERG3810_TFTLCD_ShowChar_NF(68, 176, diff == 0 ? '*':' ', color);
	IERG3810_TFTLCD_ShowChar_NF(76, 176, ']', color);
	IERG3810_TFTLCD_ShowChar_NF(84, 176, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(92, 176, 'B', color);
	IERG3810_TFTLCD_ShowChar_NF(100, 176, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(108, 176, 'g', color);
	IERG3810_TFTLCD_ShowChar_NF(116, 176, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(124, 176, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(132, 176, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(140, 176, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(148, 176, 'r', color);

	IERG3810_TFTLCD_ShowChar_NF(60, 160, '[', color);
	IERG3810_TFTLCD_ShowChar_NF(68, 160, diff == 1 ? '*':' ', color);
	IERG3810_TFTLCD_ShowChar_NF(76, 160, ']', color);
	IERG3810_TFTLCD_ShowChar_NF(84, 160, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(92, 160, 'N', color);
	IERG3810_TFTLCD_ShowChar_NF(100, 160, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(108, 160, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(116, 160, 'm', color);
	IERG3810_TFTLCD_ShowChar_NF(124, 160, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(132, 160, 'l', color);

	IERG3810_TFTLCD_ShowChar_NF(60, 144, '[', color);
	IERG3810_TFTLCD_ShowChar_NF(68, 144, diff == 2 ? '*':' ', color);
	IERG3810_TFTLCD_ShowChar_NF(76, 144, ']', color);
	IERG3810_TFTLCD_ShowChar_NF(84, 144, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(92, 144, 'E', color);
	IERG3810_TFTLCD_ShowChar_NF(100, 144, 'x', color);
	IERG3810_TFTLCD_ShowChar_NF(108, 144, 'p', color);
	IERG3810_TFTLCD_ShowChar_NF(116, 144, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(124, 144, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(132, 144, 't', color); 

	// print name
	IERG3810_TFTLCD_ShowChinChar_NF(136, 116, 0, color);
	IERG3810_TFTLCD_ShowChinChar_NF(152, 116, 1, color);
	IERG3810_TFTLCD_ShowChinChar_NF(168, 116, 2, color);
	IERG3810_TFTLCD_ShowChinChar_NF(136, 100, 3, color);
	IERG3810_TFTLCD_ShowChinChar_NF(152, 100, 4, color);
	IERG3810_TFTLCD_ShowChinChar_NF(168, 100, 5, color);

	// print SID
	IERG3810_TFTLCD_ShowChar_NF(56, 100, 0x31, color);
	IERG3810_TFTLCD_ShowChar_NF(64, 100, 0x31, color);
	IERG3810_TFTLCD_ShowChar_NF(72, 100, 0x35, color);
	IERG3810_TFTLCD_ShowChar_NF(80, 100, 0x35, color);
	IERG3810_TFTLCD_ShowChar_NF(88, 100, 0x31, color);
	IERG3810_TFTLCD_ShowChar_NF(96, 100, 0x32, color);
	IERG3810_TFTLCD_ShowChar_NF(104, 100, 0x37, color);
	IERG3810_TFTLCD_ShowChar_NF(112, 100, 0x34, color);
	IERG3810_TFTLCD_ShowChar_NF(120, 100, 0x35, color);
	IERG3810_TFTLCD_ShowChar_NF(128, 100, 0x37, color);
	IERG3810_TFTLCD_ShowChar_NF(56, 116, 0x31, color);
	IERG3810_TFTLCD_ShowChar_NF(64, 116, 0x31, color);
	IERG3810_TFTLCD_ShowChar_NF(72, 116, 0x35, color);
	IERG3810_TFTLCD_ShowChar_NF(80, 116, 0x35, color);
	IERG3810_TFTLCD_ShowChar_NF(88, 116, 0x31, color);
	IERG3810_TFTLCD_ShowChar_NF(96, 116, 0x32, color);
	IERG3810_TFTLCD_ShowChar_NF(104, 116, 0x37, color);
	IERG3810_TFTLCD_ShowChar_NF(112, 116, 0x30, color);
	IERG3810_TFTLCD_ShowChar_NF(120, 116, 0x36, color);
	IERG3810_TFTLCD_ShowChar_NF(128, 116, 0x39, color);

	// print key operations
	IERG3810_TFTLCD_ShowChar_NF(46, 40, '[', color);
	IERG3810_TFTLCD_ShowChar_NF(54, 40, '<', color);
	IERG3810_TFTLCD_ShowChar_NF(62, 40, ':', color);
	IERG3810_TFTLCD_ShowChar_NF(70, 40, 'R', color);
	IERG3810_TFTLCD_ShowChar_NF(78, 40, 'u', color);
	IERG3810_TFTLCD_ShowChar_NF(86, 40, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(94, 40, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(102, 40, ']', color);

	IERG3810_TFTLCD_ShowChar_NF(130, 40, '[', color);
	IERG3810_TFTLCD_ShowChar_NF(138, 40, '>', color);
	IERG3810_TFTLCD_ShowChar_NF(146, 40, ':', color);
	IERG3810_TFTLCD_ShowChar_NF(154, 40, 'S', color);
	IERG3810_TFTLCD_ShowChar_NF(162, 40, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(170, 40, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(178, 40, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(186, 40, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(194, 40, ']', color);
}

// print out game rule
void printRule(){
	cleanScreen();
	// print title
	IERG3810_TFTLCD_ShowChar_NF(80, 288, 'G', color);
	IERG3810_TFTLCD_ShowChar_NF(88, 288, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(96, 288, 'm', color);
	IERG3810_TFTLCD_ShowChar_NF(104, 288, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(112, 288, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(120, 288, 'R', color);
	IERG3810_TFTLCD_ShowChar_NF(128, 288, 'u', color);
	IERG3810_TFTLCD_ShowChar_NF(136, 288, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(144, 288, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(152, 288, ':', color);

	// print basic description
	IERG3810_TFTLCD_ShowChar_NF(20, 264, '-', color);
	IERG3810_TFTLCD_ShowChar_NF(28, 264, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(36, 264, 'C', color);
	IERG3810_TFTLCD_ShowChar_NF(44, 264, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(52, 264, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(60, 264, 'c', color);
	IERG3810_TFTLCD_ShowChar_NF(68, 264, 'u', color);
	IERG3810_TFTLCD_ShowChar_NF(76, 264, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(84, 264, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(92, 264, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(100, 264, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(108, 264, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(116, 264, 'q', color);
	IERG3810_TFTLCD_ShowChar_NF(124, 264, 'u', color);
	IERG3810_TFTLCD_ShowChar_NF(132, 264, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(140, 264, 's', color);
	IERG3810_TFTLCD_ShowChar_NF(148, 264, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(156, 264, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(164, 264, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(172, 264, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(180, 264, 's', color);

	IERG3810_TFTLCD_ShowChar_NF(36, 248, 'd', color);
	IERG3810_TFTLCD_ShowChar_NF(44, 248, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(52, 248, 's', color);
	IERG3810_TFTLCD_ShowChar_NF(60, 248, 'p', color);
	IERG3810_TFTLCD_ShowChar_NF(68, 248, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(76, 248, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(84, 248, 'y', color);
	IERG3810_TFTLCD_ShowChar_NF(92, 248, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(100, 248, 'd', color);
	IERG3810_TFTLCD_ShowChar_NF(108, 248, ',', color);
	IERG3810_TFTLCD_ShowChar_NF(116, 248, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(124, 248, 'm', color);
	IERG3810_TFTLCD_ShowChar_NF(132, 248, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(140, 248, 'v', color);
	IERG3810_TFTLCD_ShowChar_NF(148, 248, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(156, 248, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(164, 248, 'p', color);
	IERG3810_TFTLCD_ShowChar_NF(172, 248, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(180, 248, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(188, 248, 'y', color);
	IERG3810_TFTLCD_ShowChar_NF(196, 248, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(204, 248, 'r', color);

	IERG3810_TFTLCD_ShowChar_NF(36, 232, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(44, 232, 'c', color);
	IERG3810_TFTLCD_ShowChar_NF(52, 232, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(60, 232, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(68, 232, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(76, 232, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(84, 232, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(92, 232, 'd', color);
	IERG3810_TFTLCD_ShowChar_NF(100, 232, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(108, 232, 'd', color);
	IERG3810_TFTLCD_ShowChar_NF(116, 232, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(124, 232, 's', color);
	IERG3810_TFTLCD_ShowChar_NF(132, 232, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(140, 232, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(148, 232, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(156, 232, 'y', color);
	IERG3810_TFTLCD_ShowChar_NF(164, 232, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(172, 232, 'b', color);
	IERG3810_TFTLCD_ShowChar_NF(180, 232, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(188, 232, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(196, 232, 'c', color);
	IERG3810_TFTLCD_ShowChar_NF(204, 232, 'k', color);
	IERG3810_TFTLCD_ShowChar_NF(212, 232, 's', color);

	// print difficulty description
	IERG3810_TFTLCD_ShowChar_NF(20, 208, '-', color);
	IERG3810_TFTLCD_ShowChar_NF(28, 208, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(36, 208, 'B', color);
	IERG3810_TFTLCD_ShowChar_NF(44, 208, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(52, 208, 'g', color);
	IERG3810_TFTLCD_ShowChar_NF(60, 208, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(68, 208, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(76, 208, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(84, 208, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(92, 208, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(100, 208, ':', color);
	IERG3810_TFTLCD_ShowChar_NF(108, 208, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(116, 208, '+', color);
	IERG3810_TFTLCD_ShowChar_NF(124, 208, ',', color);
	IERG3810_TFTLCD_ShowChar_NF(132, 208, '-', color);
	IERG3810_TFTLCD_ShowChar_NF(140, 208, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(148, 208, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(156, 208, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(164, 208, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(172, 208, 'y', color);

	IERG3810_TFTLCD_ShowChar_NF(20, 192, '-', color);
	IERG3810_TFTLCD_ShowChar_NF(28, 192, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(36, 192, 'N', color);
	IERG3810_TFTLCD_ShowChar_NF(44, 192, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(52, 192, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(60, 192, 'm', color);
	IERG3810_TFTLCD_ShowChar_NF(68, 192, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(76, 192, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(84, 192, ':', color);
	IERG3810_TFTLCD_ShowChar_NF(92, 192, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(100, 192, '+', color);
	IERG3810_TFTLCD_ShowChar_NF(108, 192, ',', color);
	IERG3810_TFTLCD_ShowChar_NF(116, 192, '-', color);
	IERG3810_TFTLCD_ShowChar_NF(124, 192, ',', color);
	IERG3810_TFTLCD_ShowChar_NF(132, 192, '*', color);
	IERG3810_TFTLCD_ShowChar_NF(140, 192, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(148, 192, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(156, 192, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(164, 192, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(172, 192, 'y', color);

	IERG3810_TFTLCD_ShowChar_NF(20, 176, '-', color);
	IERG3810_TFTLCD_ShowChar_NF(28, 176, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(36, 176, 'E', color);
	IERG3810_TFTLCD_ShowChar_NF(44, 176, 'x', color);
	IERG3810_TFTLCD_ShowChar_NF(52, 176, 'p', color);
	IERG3810_TFTLCD_ShowChar_NF(60, 176, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(68, 176, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(76, 176, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(84, 176, ':', color);
	IERG3810_TFTLCD_ShowChar_NF(92, 176, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(100, 176, '+', color);
	IERG3810_TFTLCD_ShowChar_NF(108, 176, ',', color);
	IERG3810_TFTLCD_ShowChar_NF(116, 176, '-', color);
	IERG3810_TFTLCD_ShowChar_NF(124, 176, ',', color);
	IERG3810_TFTLCD_ShowChar_NF(132, 176, '*', color);
	IERG3810_TFTLCD_ShowChar_NF(140, 176, ',', color);
	IERG3810_TFTLCD_ShowChar_NF(148, 176, '%', color);
	IERG3810_TFTLCD_ShowChar_NF(156, 176, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(164, 176, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(172, 176, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(180, 176, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(188, 176, 'y', color);
	IERG3810_TFTLCD_ShowChar_NF(196, 176, ',', color);

	IERG3810_TFTLCD_ShowChar_NF(100, 160, '2', color);
	IERG3810_TFTLCD_ShowChar_NF(108, 160, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(116, 160, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(124, 160, 'p', color);
	IERG3810_TFTLCD_ShowChar_NF(132, 160, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(140, 160, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(148, 160, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(156, 160, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(164, 160, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(172, 160, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(180, 160, 's', color);
	
	// print key description
	IERG3810_TFTLCD_ShowChar_NF(20, 136, '-', color);
	IERG3810_TFTLCD_ShowChar_NF(28, 136, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(36, 136, 'K', color);
	IERG3810_TFTLCD_ShowChar_NF(44, 136, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(52, 136, 'y', color);
	IERG3810_TFTLCD_ShowChar_NF(60, 136, ':', color);
	IERG3810_TFTLCD_ShowChar_NF(68, 136, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(76, 136, '<', color);
	IERG3810_TFTLCD_ShowChar_NF(84, 136, '>', color);
	IERG3810_TFTLCD_ShowChar_NF(92, 136, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(100, 136, 'm', color);
	IERG3810_TFTLCD_ShowChar_NF(108, 136, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(116, 136, 'v', color);
	IERG3810_TFTLCD_ShowChar_NF(124, 136, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(132, 136, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(140, 136, 'p', color);
	IERG3810_TFTLCD_ShowChar_NF(148, 136, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(156, 136, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(164, 136, 'y', color);
	IERG3810_TFTLCD_ShowChar_NF(172, 136, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(180, 136, 'r', color);

	IERG3810_TFTLCD_ShowChar_NF(76, 120, '^', color);
	IERG3810_TFTLCD_ShowChar_NF(84, 120, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(92, 120, 's', color);
	IERG3810_TFTLCD_ShowChar_NF(100, 120, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(108, 120, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(116, 120, 'p', color);
	IERG3810_TFTLCD_ShowChar_NF(124, 120, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(132, 120, '5', color);
	IERG3810_TFTLCD_ShowChar_NF(140, 120, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(148, 120, 's', color);
	IERG3810_TFTLCD_ShowChar_NF(156, 120, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(164, 120, 'c', color);
	IERG3810_TFTLCD_ShowChar_NF(172, 120, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(180, 120, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(188, 120, 'd', color);
	IERG3810_TFTLCD_ShowChar_NF(196, 120, 's', color);

	IERG3810_TFTLCD_ShowChar_NF(76, 104, 'v', color);
	IERG3810_TFTLCD_ShowChar_NF(84, 104, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(92, 104, 'd', color);
	IERG3810_TFTLCD_ShowChar_NF(100, 104, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(108, 104, 's', color);
	IERG3810_TFTLCD_ShowChar_NF(116, 104, 'p', color);
	IERG3810_TFTLCD_ShowChar_NF(124, 104, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(132, 104, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(140, 104, 'y', color);
	IERG3810_TFTLCD_ShowChar_NF(148, 104, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(156, 104, '1', color);
	IERG3810_TFTLCD_ShowChar_NF(164, 104, 's', color);
	IERG3810_TFTLCD_ShowChar_NF(172, 104, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(180, 104, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(188, 104, 'd', color);
	IERG3810_TFTLCD_ShowChar_NF(196, 104, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(204, 104, 'g', color);
	IERG3810_TFTLCD_ShowChar_NF(212, 104, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(220, 104, 't', color);
	
	// print keyboard description
	IERG3810_TFTLCD_ShowChar_NF(20, 80, '-', color);
	IERG3810_TFTLCD_ShowChar_NF(28, 80, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(36, 80, 'K', color);
	IERG3810_TFTLCD_ShowChar_NF(44, 80, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(52, 80, 'y', color);
	IERG3810_TFTLCD_ShowChar_NF(60, 80, 'b', color);
	IERG3810_TFTLCD_ShowChar_NF(68, 80, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(76, 80, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(84, 80, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(92, 80, 'd', color);
	IERG3810_TFTLCD_ShowChar_NF(100, 80, ':', color);
	IERG3810_TFTLCD_ShowChar_NF(108, 80, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(116, 80, '0', color);
	IERG3810_TFTLCD_ShowChar_NF(124, 80, '-', color);
	IERG3810_TFTLCD_ShowChar_NF(132, 80, '9', color);
	IERG3810_TFTLCD_ShowChar_NF(140, 80, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(148, 80, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(156, 80, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(164, 80, 'p', color);
	IERG3810_TFTLCD_ShowChar_NF(172, 80, 'u', color);
	IERG3810_TFTLCD_ShowChar_NF(180, 80, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(188, 80, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(196, 80, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(204, 80, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(212, 80, 's', color);

	IERG3810_TFTLCD_ShowChar_NF(36, 64, 'E', color);
	IERG3810_TFTLCD_ShowChar_NF(44, 64, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(52, 64, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(60, 64, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(68, 64, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(76, 64, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(84, 64, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(92, 64, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(100, 64, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(108, 64, '/', color);
	IERG3810_TFTLCD_ShowChar_NF(116, 64, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(124, 64, 'd', color);
	IERG3810_TFTLCD_ShowChar_NF(132, 64, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(140, 64, 's', color);
	IERG3810_TFTLCD_ShowChar_NF(148, 64, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(156, 64, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(164, 64, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(172, 64, 'y', color);
	IERG3810_TFTLCD_ShowChar_NF(180, 64, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(188, 64, 'b', color);
	IERG3810_TFTLCD_ShowChar_NF(196, 64, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(204, 64, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(212, 64, 'c', color);
	IERG3810_TFTLCD_ShowChar_NF(220, 64, 'k', color);
	
	// print key operations
	IERG3810_TFTLCD_ShowChar_NF(46, 40, '[', color);
	IERG3810_TFTLCD_ShowChar_NF(54, 40, '<', color);
	IERG3810_TFTLCD_ShowChar_NF(62, 40, ':', color);
	IERG3810_TFTLCD_ShowChar_NF(70, 40, 'B', color);
	IERG3810_TFTLCD_ShowChar_NF(78, 40, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(86, 40, 'c', color);
	IERG3810_TFTLCD_ShowChar_NF(94, 40, 'k', color);
	IERG3810_TFTLCD_ShowChar_NF(102, 40, ']', color);

	IERG3810_TFTLCD_ShowChar_NF(130, 40, '[', color);
	IERG3810_TFTLCD_ShowChar_NF(138, 40, '>', color);
	IERG3810_TFTLCD_ShowChar_NF(146, 40, ':', color);
	IERG3810_TFTLCD_ShowChar_NF(154, 40, 'S', color);
	IERG3810_TFTLCD_ShowChar_NF(162, 40, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(170, 40, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(178, 40, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(186, 40, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(194, 40, ']', color);
}

// print out an integer, noBg: print without background, hide: replace every digit by '_'
int printInt(int num, int x, int y, int noBg, int hide){
	int i;
	char digit;
	// print '-' for negative number
	if (num < 0){
		if (noBg)
			IERG3810_TFTLCD_ShowChar_NF(x, y, '-', color);
		else IERG3810_TFTLCD_ShowChar(x, y, '-', color, bgcolor);
		num = -num;
		x += 8;
	}
	
	// print the integer digit by digit
	for(i = abs(getNumOfDigit(num)) - 1; i >= 0; i--, x += 8){
		if (hide){
			digit = '_';
			y -= 4;
		} else digit = '0' + (num / (int) pow(10, i)) % 10;
		if (noBg)
			IERG3810_TFTLCD_ShowChar_NF(x, y, digit, color);
		else IERG3810_TFTLCD_ShowChar(x, y, digit, color, bgcolor);
		if (hide)
			y += 4;
	}
	return x; // return current x position
}

// print out an operator
int printOpt(int opt, int x, int y){
	IERG3810_TFTLCD_ShowChar(x, y, ' ', color, bgcolor);
	x += 8;
	switch(opt){
		case 0:
			IERG3810_TFTLCD_ShowChar(x, y, '+', color, bgcolor);
			break;
		case 1:
			IERG3810_TFTLCD_ShowChar(x, y, '-', color, bgcolor);
			break;
		case 2:
			IERG3810_TFTLCD_ShowChar(x, y, 'x', color, bgcolor);
			break;
		case 3:
			IERG3810_TFTLCD_ShowChar(x, y, '%', color, bgcolor);
			break;
	}
	x += 8;
	IERG3810_TFTLCD_ShowChar(x, y, ' ', color, bgcolor);
	
	return x + 8; // return current x position
}

// print out an equation
void printEqt(int x, int y){
	if(diff < 2){
		// 1 operation for beginner and normal
		x = printInt(left, x, y, 0, 0);
		x = printOpt(opt1, x, y);
		x = printInt(right, x, y, 0, 0);
	} else {
		// 2 operations for expert
		IERG3810_TFTLCD_ShowChar(x, y, '(', color, bgcolor);
		x += 8;
		x = printInt(left, x, y, 0, 0);
		x = printOpt(opt1, x, y);
		x = printInt(mid, x, y, 0, 0);
		IERG3810_TFTLCD_ShowChar(x, y, ')', color, bgcolor);
		x += 8;
		x = printOpt(opt2, x, y);
		x = printInt(right, x, y, 0, 0);
	}
	block_end = x; // set block_end as current x position
}

// print out upper panel
void printUpperPanel(){
	int i;
	int x = 20;
	IERG3810_TFTLCD_FillRectangle(0xFFFF, 0, 240, 240, 80);
	
	// print score
	IERG3810_TFTLCD_ShowChar_NF(x, 280, 'S', color);
	IERG3810_TFTLCD_ShowChar_NF(x+8, 280, 'c', color);
	IERG3810_TFTLCD_ShowChar_NF(x+16, 280, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(x+24, 280, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(x+32, 280, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(x+40, 280, ':', color);
	x = printInt(score, x+56, 280, 1, 0);
	
	// print number of skill left
	IERG3810_TFTLCD_ShowChar_NF(x+8, 280, 'S', color);
	IERG3810_TFTLCD_ShowChar_NF(x+16, 280, 'k', color);
	IERG3810_TFTLCD_ShowChar_NF(x+24, 280, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(x+32, 280, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(x+40, 280, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(x+48, 280, ':', color);
	x = printInt(skill, x+64, 280, 1, 0);
	
	// print number of life left
	for(i = 1; i <= life; i++){
		IERG3810_TFTLCD_ShowSpecial_NF(x+(16*i), 280, 0x2, 0xF800);
	}
}

// print out main screen
void printMainScreen(){
	// print rocket move animation
	if (rocketMove == 1){ // rocket not missed
		IERG3810_TFTLCD_FillRectangle(0xFFFF, rocket_x, 16, rocket_y, 16);
		if (rocket_y < 240 - count){
			rocket_y += 16; // move rocket up
			IERG3810_TFTLCD_ShowSpecial_NF(rocket_x, rocket_y, 0x1, color); // print rocket
		} else {
			// rocket touched the block
			rocket_y = 116; // reset rocket position
			rocketMove = 0; // stop rocket movement
			refreshPending = 1; // waiting to check answer
		}
	} else if (rocketMove == -1){ // rocket missed
		IERG3810_TFTLCD_FillRectangle(0xFFFF, rocket_x, 16, rocket_y, 16);
		if (rocket_y < 240){
			rocket_y += 16; // move rocket up
			IERG3810_TFTLCD_ShowSpecial_NF(rocket_x, rocket_y, 0x1, color); // print rocket
		} else {
			// rocket reached the top
			USART_print(2, " Rocket missed...");
			rocket_y = 116; // reset rocket position
			rocketMove = 0; // stop rocket movement
			clearInput();
			ans_actualX = ans_defaultX;
			input_pos = 0; // reset input potiion
			hintDisplayed = 0; // reset hint displayed
			IERG3810_DS0_On();
		}
	}
	// print block move animation
	if (count != 0)
		IERG3810_TFTLCD_FillRectangle(0xFFFF, block_pos, block_end - block_pos, 240 - count, 32); 
	printEqt(block_pos, 240 - count);
}

// print out player icon
void printPlayerIcon(){
	IERG3810_TFTLCD_FillRectangle(0xFFFF, 0, 240, 100, 16);
	IERG3810_TFTLCD_ShowSpecial_NF(player_pos, 100, 0x0, color);
}

// print out lower panel
void printLowerPanel(){
	IERG3810_TFTLCD_FillRectangle(0xFFFF, 0, 240, 0, 96);
	
	// print answer panel
	IERG3810_TFTLCD_ShowChar_NF(70, 80, 'A', color);
	IERG3810_TFTLCD_ShowChar_NF(78, 80, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(86, 80, 's', color);
	IERG3810_TFTLCD_ShowChar_NF(94, 80, 'w', color);
	IERG3810_TFTLCD_ShowChar_NF(102, 80, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(110, 80, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(118, 80, ':', color);
	printInt(ans, 134, 80, 1, 1);
	
	// print key operations
	IERG3810_TFTLCD_ShowChar_NF(50, 40, '[', color);
	IERG3810_TFTLCD_ShowChar_NF(58, 40, '^', color);
	IERG3810_TFTLCD_ShowChar_NF(66, 40, ':', color);
	IERG3810_TFTLCD_ShowChar_NF(74, 40, 'S', color);
	IERG3810_TFTLCD_ShowChar_NF(82, 40, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(90, 40, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(98, 40, 'p', color);
	IERG3810_TFTLCD_ShowChar_NF(106, 40, ']', color);
	
	IERG3810_TFTLCD_ShowChar_NF(134, 40, '[', color);
	IERG3810_TFTLCD_ShowChar_NF(142, 40, 'v', color);
	IERG3810_TFTLCD_ShowChar_NF(150, 40, ':', color);
	IERG3810_TFTLCD_ShowChar_NF(158, 40, 'H', color);
	IERG3810_TFTLCD_ShowChar_NF(166, 40, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(172, 40, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(180, 40, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(188, 40, ']', color);
}

// print end game screen
void printEndGame(){
	cleanScreen();
	
	// print title
	IERG3810_TFTLCD_ShowChar_NF(85, 252, 'G', color);
	IERG3810_TFTLCD_ShowChar_NF(93, 252, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(101, 252, 'm', color);
	IERG3810_TFTLCD_ShowChar_NF(109, 252, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(117, 252, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(125, 252, 'O', color);
	IERG3810_TFTLCD_ShowChar_NF(133, 252, 'v', color);
	IERG3810_TFTLCD_ShowChar_NF(141, 252, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(149, 252, 'r', color);
	
	// print score bar
	IERG3810_TFTLCD_ShowChar_NF(min(41 + 2*score, 191), 210, 'v', 0x0000);
	
	IERG3810_TFTLCD_FillRectangle(0xF800, 45, 20, 190, 20); // red, rank D-F
	IERG3810_TFTLCD_FillRectangle(0xFFE0, 65, 20, 190, 20); // yellow, rank B-C
	IERG3810_TFTLCD_FillRectangle(color, 85, 40, 190, 20); // blue, rank S-A
	IERG3810_TFTLCD_FillRectangle(0x07E0, 125, 70, 190, 20); // green, rank SSS-SS
	
	IERG3810_TFTLCD_ShowChar_NF(41, 170, 'F', 0x0000);
	IERG3810_TFTLCD_ShowChar_NF(61, 170, 'C', 0x0000);
	IERG3810_TFTLCD_ShowChar_NF(81, 170, 'A', 0x0000);
	IERG3810_TFTLCD_ShowChar_NF(117, 170, 'S', 0x0000);
	IERG3810_TFTLCD_ShowChar_NF(125, 170, 'S', 0x0000);
	IERG3810_TFTLCD_ShowChar_NF(183, 170, 'S', 0x0000);
	IERG3810_TFTLCD_ShowChar_NF(191, 170, 'S', 0x0000);
	IERG3810_TFTLCD_ShowChar_NF(199, 170, 'S', 0x0000);
	
	// print final score
	IERG3810_TFTLCD_ShowChar_NF(50, 120, 'Y', color);
	IERG3810_TFTLCD_ShowChar_NF(58, 120, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(66, 120, 'u', color);
	IERG3810_TFTLCD_ShowChar_NF(74, 120, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(82, 120, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(90, 120, 'F', color);
	IERG3810_TFTLCD_ShowChar_NF(98, 120, 'i', color);
	IERG3810_TFTLCD_ShowChar_NF(106, 120, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(114, 120, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(122, 120, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(130, 120, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(138, 120, 'S', color);
	IERG3810_TFTLCD_ShowChar_NF(146, 120, 'c', color);
	IERG3810_TFTLCD_ShowChar_NF(154, 120, 'o', color);
	IERG3810_TFTLCD_ShowChar_NF(162, 120, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(170, 120, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(178, 120, ':', color);
	printInt(score, 194, 120, 1, 0);
	
	// print player rank
	IERG3810_TFTLCD_ShowChar_NF(66, 80, 'P', color);
	IERG3810_TFTLCD_ShowChar_NF(74, 80, 'l', color);
	IERG3810_TFTLCD_ShowChar_NF(82, 80, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(90, 80, 'y', color);
	IERG3810_TFTLCD_ShowChar_NF(98, 80, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(106, 80, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(114, 80, ' ', color);
	IERG3810_TFTLCD_ShowChar_NF(122, 80, 'R', color);
	IERG3810_TFTLCD_ShowChar_NF(130, 80, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(138, 80, 'n', color);
	IERG3810_TFTLCD_ShowChar_NF(146, 80, 'k', color);
	IERG3810_TFTLCD_ShowChar_NF(154, 80, ':', color);
	
	if (score < 3) IERG3810_TFTLCD_ShowChar_NF(170, 80, 'F', color);
	else if (score < 6) IERG3810_TFTLCD_ShowChar_NF(170, 80, 'E', color);
	else if (score < 10) IERG3810_TFTLCD_ShowChar_NF(170, 80, 'D', color);
	else if (score < 15) IERG3810_TFTLCD_ShowChar_NF(170, 80, 'C', color);
	else if (score < 20) IERG3810_TFTLCD_ShowChar_NF(170, 80, 'B', color);
	else if (score < 30) IERG3810_TFTLCD_ShowChar_NF(170, 80, 'A', color);
	else IERG3810_TFTLCD_ShowChar_NF(170, 80, 'S', color);
	if (score >= 40) IERG3810_TFTLCD_ShowChar_NF(178, 80, 'S', color);
	if (score >= 75) IERG3810_TFTLCD_ShowChar_NF(186, 80, 'S', color);
	
	// print key operations
	IERG3810_TFTLCD_ShowChar_NF(50, 40, '[', color);
	IERG3810_TFTLCD_ShowChar_NF(58, 40, '<', color);
	IERG3810_TFTLCD_ShowChar_NF(66, 40, ':', color);
	IERG3810_TFTLCD_ShowChar_NF(74, 40, 'R', color);
	IERG3810_TFTLCD_ShowChar_NF(82, 40, 'e', color);
	IERG3810_TFTLCD_ShowChar_NF(90, 40, 't', color);
	IERG3810_TFTLCD_ShowChar_NF(98, 40, 'r', color);
	IERG3810_TFTLCD_ShowChar_NF(106, 40, 'y', color);
	IERG3810_TFTLCD_ShowChar_NF(114, 40, ']', color);
	
	IERG3810_TFTLCD_ShowChar_NF(138, 40, '[', color);
	IERG3810_TFTLCD_ShowChar_NF(146, 40, '>', color);
	IERG3810_TFTLCD_ShowChar_NF(154, 40, ':', color);
	IERG3810_TFTLCD_ShowChar_NF(162, 40, 'B', color);
	IERG3810_TFTLCD_ShowChar_NF(170, 40, 'a', color);
	IERG3810_TFTLCD_ShowChar_NF(178, 40, 'c', color);
	IERG3810_TFTLCD_ShowChar_NF(186, 40, 'k', color);
	IERG3810_TFTLCD_ShowChar_NF(194, 40, ']', color);
}

// print out hint
int printHint(){
	int firstDigit = getFirstDigit(ans);
	if (firstDigit == -1) // hint is not available
		return 0;
	USART_print(2, " Hint displayed: ");
	printInt_USART(firstDigit);
	clearInput();
	// input the first digit for user
	input[0] = firstDigit;
	IERG3810_TFTLCD_FillRectangle(0xFFFF, ans_defaultX, 240, 80, 96);
	IERG3810_TFTLCD_ShowChar_NF(ans_defaultX, 80, '0' + firstDigit, color);
	return 1;
}

// print out stop screen
void printStop(){
	int current = task1HeartBeat;
	
	// print stop message
	IERG3810_TFTLCD_ShowChar_NF(112, 20, 'S', 0xF800);
	IERG3810_TFTLCD_ShowChar_NF(120, 20, 'T', 0xF800);
	IERG3810_TFTLCD_ShowChar_NF(128, 20, 'O', 0xF800);
	IERG3810_TFTLCD_ShowChar_NF(136, 20, 'P', 0xF800);
	
	// wait for 2 seconds
	while(task1HeartBeat < current + 200);
	
	task1HeartBeat = current; // reset task1HeartBeat
	IERG3810_TFTLCD_FillRectangle(0xFFFF, 112, 32, 20, 16); // clear stop message
}
