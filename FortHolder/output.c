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
	int i,j;
	int n,_n;
	_unit* p_unit;
	
	output_battle_init();
	
	/*calculate the starting point*/
	n=map->player.x-PLAYER_POSITION;
	_n=map->player._x/128;
	if(n+LENGTH>map->length){
		n=map->length-LENGTH;
		_n=0;
	}
	if(n<0){
		n=0;
		_n=0;
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
		xyprintf(-_n,UNIT_WIDTH*(WIDTH+2-j),"%s",print_string);
		
    }
    /*print unit*/
    int u_x;
    for(p_unit=map->p_unit;p_unit!=NULL;p_unit=p_unit->next_unit){
    	u_x=p_unit->x-n;
    	if(u_x>=0 && u_x<LENGTH){
    		if(IF_WEAPON(p_unit->type)){
    	    	xyprintf(UNIT_LENGTH*u_x+p_unit->_x/128-_n,
	              UNIT_WIDTH*(WIDTH+2-p_unit->y)-p_unit->_y/64,
				  "%c",weapon_char[p_unit->type-WEAPON_1_CODE]);
			
		    }
		}
    	
	}
    /*print player*/
    setcolor(EGERGB(218,178,115));
    if(_n){
	    xyprintf(UNIT_LENGTH*PLAYER_POSITION,
		        UNIT_WIDTH*(WIDTH+2-map->player.y)-map->player._y/64,"%c",PLAYER_CHAR);
	}else{
	    xyprintf(UNIT_LENGTH*(map->player.x-n)+map->player._x/128,
		        UNIT_WIDTH*(WIDTH+2-map->player.y)-map->player._y/64,"%c",PLAYER_CHAR);
	}
    
    
    /*print fps*/
    output_fps(map->real_fps);
    /*show*/
    delay_fps(FPS);
    cleardevice();
	return 0;
}
int input_battle(_map* map){
	int i;
	/*int key=5;
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
	flushkey();
	*/
	if(keystate('A')){
		map->player.press_status[1]=1;
		map->player.press_length[1]++;
	}else{
		map->player.press_status[1]=0;
		map->player.press_length[1]=0;
	}
	if(keystate('S')){
		map->player.press_status[2]=1;
		map->player.press_length[2]++;
	}else{
		map->player.press_status[2]=0;
		map->player.press_length[2]=0;
	}
	if(keystate('D')){
		map->player.press_status[3]=1;
		map->player.press_length[3]++;
	}else{
		map->player.press_status[3]=0;
		map->player.press_length[3]=0;
	}
	if(keystate('W')){
		map->player.press_status[4]=1;
		map->player.press_length[4]++;
	}else{
		map->player.press_status[4]=0;
		map->player.press_length[4]=0;
	}
	if(keystate(' ')||keystate('J')){
		switch(map->player.press_status[0]){
			case 1:
				map->player.press_length[0]++;
				break;
			case 0: case 2:
			default:
				map->player.press_status[0]=1;
				map->player.press_length[0]=1;
		}
	}else{
		switch(map->player.press_status[0]){
			case 0:
				map->player.press_length[0]=0;
				break;
			case 1:
				map->player.press_status[0]=2;
				break;
			case 2:
				map->player.press_status[0]=0;
				break;
			default:
				;
		}
	}
	for(i=0;i<9;i++){
		if(keystate('1'+i)){
			map->player.press_weapon=i;
			break;
		}
	}
    flushkey();
	return 1;
}
