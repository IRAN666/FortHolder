#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#include"foundation.h"
#include"values.h"
#include"output.h"


int init(_map* map){
	output_init();
	map->p_map=NULL;
	return 0;
}
int map_free(_map* map){
	free(map->p_map);
	_unit* p_u1,*p_u2;
	for(p_u2=map->p_unit;p_u2!=NULL;){
		p_u1=p_u2;
		p_u2=p_u1->next_unit;
		free(p_u1);
	}
	return 0;
}
int make_blank_file(_map* map){
	int i,j;
	
	map->length=256;
	map->p_map=(char (*)[WIDTH])malloc(map->length*WIDTH*sizeof(char));
	map->player.x=70;
	map->player.y=9;
	map->player.energy=0;
	map->player._x=200;
	map->player._y=200;
	map->player.v_x=-200;
	map->player.v_y=0;
	map->gpa=430;
	map->player.weapon[0]=WEAPON_1_CODE;
	map->p_unit=NULL;
	memset(map->player.press_status,0,5*sizeof(int));
	memset(map->player.press_length,0,5*sizeof(int));

	for(i=0;i<map->length;i++){
		for(j=0;j<WIDTH;j++){
			map->p_map[i][j]=(j<8||i+j<32)?1:0;
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

