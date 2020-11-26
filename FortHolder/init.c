#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include "foundation.h"
#include"values.h"
#include"output.h"

int read_block(void);

int init(_map* map){
	system("mode con  cols=128 lines=38");
	/*gotoxy(56,16);
	printf("LOADING");*/
	output_init(void);
	map->central_block=NULL;

	return 0;
}
int read_block(block *this_block){
	int i,j;
	for(i=0;i<WIDTH;i++){
		for(j=0;j<LENGTH_BLOCK;j++){
			;
		}
	}
}
int read_file(char *_file,_map* map){
	FILE * fp;
	int i,j;
	block *this_block;
	
	
	map->player.blood=10;
	map->player.energy=2;
	map->player.x=8;
	map->player.y=5;
	map->player._x=0;
	map->player._y=0;
	map->central_block=(block *)malloc(sizeof(block));
	this_block=map_central_block;
	this_block->num_units=0;
	
	
	/*fp=fopen(_file,"s");
	for(i=0;i<10;i++){
		fscanf(fp,"%d",&j);
		printf("%d",j);
	}*/
	return 0;
}

