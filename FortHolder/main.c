#include<stdio.h>
#include<windows.h>
#include"output.h"
#include"values.h"
#include"foundation.h"
#include"init.h"
#include"game.h"

int main(void){
	_map map;
	init(&map);
	start_battle(&map);
	for(;;){
		;
	}
	return 0;
}
