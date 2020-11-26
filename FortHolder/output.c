#include"foundation.h"
#include"output.h"
#include<stdio.h>
#include<windows.h>
int gotoxy(int x, int y){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
	return 0;
}
int output_init(void){
	;
}
}
int output_battle(_map* map){
	int i,j;
	for(i=0;i<10;i++);
	return 0;/*wei wan*/
}
