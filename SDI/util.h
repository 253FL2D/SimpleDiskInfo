#ifndef _UTIL_H_
#define _UTIL_H_

#include "main.h"

#ifndef KEY_CODE
#define KEY_CODE

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32

#endif

int keyControl();
void titleDraw();
int menuDraw(int, int);
void init();
void gotoxy(int, int);
void textcolor(int);

#endif