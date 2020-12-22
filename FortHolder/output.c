#include<stdio.h>
#include<windows.h>
#include<graphics.h>
#include"foundation.h"
#include"output.h"

char print_string[LENGTH+1];
key_msg kMsg;
int output_interface(void);

int output_battle_init(void);

int output_init(void){
	initgraph(LENGTH*UNIT_LENGTH,(WIDTH+6)*UNIT_WIDTH,INIT_RENDERMANUAL);
	setcaption("FortHolder");
	setbkcolor(DARK_BLUE);
	delay_ms(0);
	return 0;
}
int output_clear(void){
	cleardevice();
	return 0;
}
int output_loading(int progress){
	;
}
int output_battle_init(void){
	cleardevice();
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	setfont(UNIT_WIDTH, 0, "Consolas");	
	xyprintf(OUTPUT_GAME_ENERGY_X ,OUTPUT_GAME_ENERGY_Y,"ENERGY");
	xyprintf(OUTPUT_GAME_FPS_X    ,OUTPUT_GAME_FPS_Y,   "FPS:");
	xyprintf(OUTPUT_GAME_BLOOD_X  ,OUTPUT_GAME_BLOOD_Y ,"BLOOD:");
	xyprintf(OUTPUT_GAME_GPA_X    ,OUTPUT_GAME_GPA_Y,   "GPA:");
	line(OUTPUT_GAME_ENERGY_LEFT_X,UNIT_WIDTH,
	    OUTPUT_GAME_ENERGY_LEFT_X,2*UNIT_WIDTH);
	line(OUTPUT_GAME_ENERGY_RIGHT_X,UNIT_WIDTH,
	    OUTPUT_GAME_ENERGY_RIGHT_X,2*UNIT_WIDTH);
	
	setcolor(DARKGRAY);
	line(3,OUTPUT_GAME_UPPER_LINE_Y,
	    UNIT_LENGTH*LENGTH-3,OUTPUT_GAME_UPPER_LINE_Y);
	line(3,OUTPUT_GAME_LOWER_LINE_Y,
	    UNIT_LENGTH*LENGTH-3,OUTPUT_GAME_LOWER_LINE_Y);
	setcolor(LIGHTGRAY);
	rectangle(OUTPUT_GAME_WEAPON_X_LEFT,OUTPUT_GAME_WEAPON_Y_UP,
	    OUTPUT_GAME_WEAPON_X_RIGHT,OUTPUT_GAME_WEAPON_Y_DOWN);
	
	return 0;
}
int output_game_starting(void){
	output_battle_init();
	delay_ms(0);
	return 0;
}
int output_menu(_map* map){
	;
}
int output_introduce(void){
	;
}
int output_int(int t){
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	xyprintf(OUTPUT_GAME_COMMON_X,OUTPUT_GAME_COMMON_Y,
	    ">%d",t);
	return 0;
}
int output_string(char s[]){
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	xyprintf(OUTPUT_GAME_COMMON_X,OUTPUT_GAME_COMMON_Y,
	    ">%s",s);
	return 0;
}
int output_fps(int fps){
	setcolor(WHITE);
	setbkmode(TRANSPARENT);
	xyprintf(OUTPUT_GAME_FPS_X_,OUTPUT_GAME_FPS_Y,"%d",fps);
	return 0;
}
int output_choose_weapon(_map* map){
	;
}
int output_battle(_map* map){
	output_battle_init();
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
	output_int(n);
	setcolor(LIGHTGRAY);
	setfont(UNIT_WIDTH+1, 0, "Consolas");	
	for(j=0;j<WIDTH;j++){
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
		xyprintf(0,UNIT_WIDTH*(WIDTH+2-j),"%s",print_string);
		
    }
    
    /*print player*/
    setcolor(EGERGB(218,178,115));
    xyprintf(UNIT_LENGTH*(map->player.x-n),UNIT_WIDTH*(WIDTH+2-map->player.y),"%c",PLAYER_CHAR);
    
    /*print fps*/
    output_fps(map->real_fps);
    /*show*/
    delay_fps(FPS);
    cleardevice();
	return 0;
}
int input_battle(_map* map){
	int key=5;
	memset(map->player.press_status,0,5*sizeof(int));
	while(kbmsg()){
		kMsg=getkey();
		switch(kMsg.key){
			case 'A':key=1;break;
			case 'S':key=2;break;
			case 'D':key=3;break;
			case 'W':key=4;break;
			case ' ':key=0;break;
			default: key=-1;
		}
		if(key>=0){
			if(kMsg.msg==key_msg_down){
				map->player.press_length[key]++;
				map->player.press_status[key]=1;
			}else if(kMsg.msg==key_msg_up){
				map->player.press_status[key]=2;
			}
		}
	}
	if(key==5){
		memset(map->player.press_length,0,5*sizeof(int));
		return 0;
	}
	return 1;
}
