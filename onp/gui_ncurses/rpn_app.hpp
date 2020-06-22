#ifndef __RPN_GUI_APP
#define __RPN_GUI_APP

#include <ncurses.h>

#define MAIN_WIN_H      30
#define MAIN_WIN_W      100

#define SUB_WIN_H       MAIN_WIN_H - 10
#define SUB_WIN_W       MAIN_WIN_W - 6
#define SUB_WIN_Y       6
#define SUB_WIN_X       4

#define STACK_BASE_H    4
#define STACK_BASE_W    30
#define STACK_ELEMENT_H 3
#define STACK_ELEMENT_W 20
#define STACK_Y         SUB_WIN_H + 2
#define STACK_X         SUB_WIN_W - STACK_BASE_W - 4 

void RunRPN();

#endif