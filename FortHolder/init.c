#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#include"foundation.h"
#include"values.h"
#include"output.h"

int read_block(void);

int init(_map* map){
	int i;
	system("mode con  cols=128 lines=38");
	for(i=0;i<=3;i++){
		output_loading(i);
		Sleep(1000);
	}
	map->p_map=NULL;

	return 0;
}
int map_free(_map* map){
	free(map->p_map);
	return 0;
}
int make_blank_file(_map* map){
	map->length=256;
	map->p_map=(char (*)[WIDTH])malloc(map->length*WIDTH*sizeof(char));
	map->player.x=25;
	map->player.y=9;
	int i,j;
	for(i=0;i<map->length;i++){
		for(j=0;j<WIDTH;j++){
			map->p_map[i][j]=j<8?1:0;
		}
	}
	return 0;
}
/*
int read_block(block *this_block){
	int i,j;
	for(i=0;i<WIDTH;i++){
		for(j=0;j<LENGTH_BLOCK;j++){
			;
		}
	}
}*/

int read_file(char *_file,_map* map){
    ;
}

