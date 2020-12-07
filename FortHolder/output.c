#include<stdio.h>
#include<windows.h>
#include"foundation.h"
#include"output.h"

char print_string[LENGTH+1];

int gotoxy(int x, int y){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
	return 0;
}
int output_clear(void){
	int i,j;
	for(j=0;j<WIDTH+6;j++){
		gotoxy(0,j);
		for(i=0;i<LENGTH>>3;i++){
			printf("        ");
		}
	}
	return 0;
}
int output_loading(int progress){
	gotoxy(OUTPUT_LOADING_X,OUTPUT_LOADING_Y+0);printf(OUTPUT_LOADING_STRING_0);
	gotoxy(OUTPUT_LOADING_X,OUTPUT_LOADING_Y+1);printf(OUTPUT_LOADING_STRING_1);
	gotoxy(OUTPUT_LOADING_X,OUTPUT_LOADING_Y+2);printf(OUTPUT_LOADING_STRING_2);
	gotoxy(OUTPUT_LOADING_X,OUTPUT_LOADING_Y+3);printf(OUTPUT_LOADING_STRING_3);
	gotoxy(OUTPUT_LOADING_X,OUTPUT_LOADING_Y+4);printf(OUTPUT_LOADING_STRING_4);
	for(;progress>0;progress--){
		printf("  #");
	}
	return 0;
}
int output_game_starting(void){
	gotoxy(OUTPUT_GAME_STARTING_ENERGY_X      ,OUTPUT_GAME_STARTING_ENERGY_Y);      printf("ENERGY");
	gotoxy(OUTPUT_GAME_STARTING_FPS_X         ,OUTPUT_GAME_STARTING_FPS_Y);         printf("FPS:");
	gotoxy(OUTPUT_GAME_STARTING_BLOOD_X       ,OUTPUT_GAME_STARTING_BLOOD_Y);       printf("BLOOD:");
	gotoxy(OUTPUT_GAME_STARTING_ENERGY_LEFT_X ,OUTPUT_GAME_STARTING_ENERGY_LEFT_Y); printf("??!");
	gotoxy(OUTPUT_GAME_STARTING_ENERGY_RIGHT_X,OUTPUT_GAME_STARTING_ENERGY_RIGHT_Y);printf("??!");
	gotoxy(OUTPUT_GAME_STARTING_GPA_X         ,OUTPUT_GAME_STARTING_GPA_Y);         printf("GPA:");
	return 0;
}

int output_string(char s[]){
	gotoxy(0,WIDTH+5);
	printf("%s",s);
	printf("                ");
	return 0;
}

int output_fps(int fps){
	gotoxy(OUTPUT_GAME_STARTING_FPS_X+4,OUTPUT_GAME_STARTING_FPS_Y);
	printf("%d",fps);
	return 0;
}

int output_battle(_map* map){
	int i,j;
	int n;
	/*calculate the starting point*/
	n=map->player.x-PLAYER_POSITION;
	if(n+LENGTH>map->length){
		n=map->length-LENGTH;
	}
	if(n<0){
		n=0;
	}
	
	/*print map*/
	for(j=0;j<WIDTH;j++){
		gotoxy(0,WIDTH+2-j);
		for(i=0;i<LENGTH;i++){
			switch(map->p_map[i+n][j]){
				case BLANK_CODE:
					print_string[i]=BLANK_CHAR;
					break;
				case BLOCK_CODE:
					print_string[i]=BLOCK_CHAR;
					break;
				default:
					print_string[i]=UNKNOWN_CHAR;
			}
		}
		print_string[LENGTH]='\0';
		printf("%s",print_string);
	}
	
	/*print units*/
	;
	
	/*print player*/
	gotoxy(map->player.x-n,WIDTH+2-map->player.y);
	printf("$");
	
	return 0;
}
