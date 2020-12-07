#include<stdio.h>
#include<windows.h>
#include"output.h"
#include"values.h"
#include"foundation.h"

int main(void){
	_map map;
	init(&map);
	start_battle(&map);
	return 0;
}
