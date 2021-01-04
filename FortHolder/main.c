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
	
	for(;;){
		choose_weapon(&map);
	    start_battle(&map);
	}
	return 0;
}
