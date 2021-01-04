#include<stdio.h>
#include<windows.h>
#include<graphics.h>
#include"foundation.h"
#include"output.h"

char print_string[LENGTH+1];
key_msg kMsg;
int output_interface(void);

int output_battle_init(void);

int output_die(_map* map){
	cleardevice();
	xyprintf(480,250,"YOU DIE!");
	xyprintf(470,275,"score:%d",map->player.score);
	xyprintf(440,290,"press 's' to restart");
	delay_ms(0);
	for(;!keystate('S');){
		delay_ms(30);
	} 
	return 0;
}
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
	xyprintf(OUTPUT_GAME_FPS_X    ,OUTPUT_GAME_FPS_Y,   "SCORE:");
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
    //340,190 684,380
    
    cleardevice();
    setcolor(LIGHTGRAY);
    
    rectangle(256,125,768,415);
    setfont(UNIT_WIDTH, 0, "Consolas");
	xyprintf(460,135,"choose weapon");
    xyprintf(270,150,"1. '~' common bullet");
    xyprintf(270,165,"2. '.' cheap bullet");
    xyprintf(270,180,"3. ':' heavy bullet");
    xyprintf(270,195,"4. '@' extra heavy bullet");
    xyprintf(270,210,"5. '+' powerful bullet");
    xyprintf(270,225,"6. '-' fast bullet");
    xyprintf(270,240,"7. 'X' freezing bullet");
    xyprintf(270,255,"8. '=' sword");
    xyprintf(270,270,"9. '%%' non-gravity bullet");
    xyprintf(270,285,"A. '|' shield");
    xyprintf(270,300,"B. '!' ");
    xyprintf(270,315,"C. 'v' nuclear bomb");
    xyprintf(270,330,"D. '#' builder");
    xyprintf(270,345,"E. 'N' ");
    xyprintf(270,360,"F. 'W' ");
    xyprintf(270,375,"G. 'H' ladder builder");
    //'@', '+', '-', 'X', '=', '%', '|', '!', 'v', '#', 'N', 'W', 'H'
    /*input*/
    
    int i,j,k,l;
    for(i=0,j=-1;i<9;i++){
    	if(keystate('1'+i)){
    		l=1;
    		for(k=0;k<map->player.weapon_chosen;k++){
    			if(map->player.weapon[k]==i+WEAPON_1_CODE){
    				l=0;
				}
			}
			if(l){
				j=i;
    		    break;
			}
		}
	}
	for(i=0;i<7;i++){
		if(keystate('A'+i)){
			j=i+8;
			break;
		}
	}
	output_int(map->player.weapon_chosen);
	if(j>=0){
		map->player.weapon[map->player.weapon_chosen]=j+WEAPON_1_CODE;
	    map->player.weapon_chosen++;
	}
    delay_fps(60);
    
    flushkey();
    return 0;
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
	//output_int(n);
	setcolor(LIGHTGRAY);
	setfont(UNIT_WIDTH+1, 0, "Consolas");	
	for(j=0;j<WIDTH;j++){
		for(i=0;i<LENGTH;i++){
			switch(map->p_map[i+n][j]){
				case BLANK_CODE:
				case BLOCK_HIDDEN_CODE:
					print_string[i]=BLANK_CHAR;
					break;	
				case BLOCK_CODE:
				case BLOCK_DAMAGED_CODE:
					print_string[i]=BLOCK_CHAR;
					break;
				case BLOCK_WINDOWS_CODE:
					print_string[i]=BLOCK_WINDOWS_CHAR;
					break;
				case BLOCK_LADDER_CODE:
					print_string[i]=BLOCK_LADDER_CHAR;
					break;
				default:
					print_string[i]=map->p_map[i+n][j];
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
		    }else if(IF_ENEMY(p_unit->type)){
		    	xyprintf(UNIT_LENGTH*u_x+p_unit->_x/128-_n,
	              UNIT_WIDTH*(WIDTH+2-p_unit->y)-p_unit->_y/64,
				  "%c",enemy_char[p_unit->type-ENEMY_1_CODE]);
			}else if(p_unit->type==HOLE_CODE){
				xyprintf(UNIT_LENGTH*u_x+p_unit->_x/128-_n,
	              UNIT_WIDTH*(WIDTH+2-p_unit->y)-p_unit->_y/64,
				  "%c",HOLE_CHAR);
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
    
    /*print gpa*/
    xyprintf(OUTPUT_GAME_GPA_X+38,OUTPUT_GAME_GPA_Y,
	        "%d.%d",map->player.point/1000,(map->player.point%1000)/10);
    /*print fps*/
    output_fps(map->player.score);
    
    /*print blood*/
    xyprintf(OUTPUT_GAME_BLOOD_X+UNIT_LENGTH*6,
	        OUTPUT_GAME_BLOOD_Y,"%d",map->player.blood);
    /*print energy*/
    setfillcolor(LIGHTCYAN);
    int bar_length=map->player.energy>>6;
    if(bar_length>330){
    	bar_length=330;
	}
    bar(OUTPUT_GAME_ENERGY_LEFT_X+3,UNIT_WIDTH+3,
	   OUTPUT_GAME_ENERGY_LEFT_X+3+bar_length,2*UNIT_WIDTH-3);
	/*print weapon*/
	xyprintf(OUTPUT_GAME_WEAPON_X,OUTPUT_GAME_WEAPON_Y,
	        "%c %c %c %c %c %c %c %c %c",
			weapon_char[map->player.weapon[0]-WEAPON_1_CODE],
			weapon_char[map->player.weapon[1]-WEAPON_1_CODE],
			weapon_char[map->player.weapon[2]-WEAPON_1_CODE],
			weapon_char[map->player.weapon[3]-WEAPON_1_CODE],
			weapon_char[map->player.weapon[4]-WEAPON_1_CODE],
			weapon_char[map->player.weapon[5]-WEAPON_1_CODE],
			weapon_char[map->player.weapon[6]-WEAPON_1_CODE],
			weapon_char[map->player.weapon[7]-WEAPON_1_CODE],
			weapon_char[map->player.weapon[8]-WEAPON_1_CODE]);
	
    /*show*/
    delay_fps(FPS);
    cleardevice();
	return 0;
}
int input_battle(_map* map){
	int i;
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
	}if(keystate('W')){
		switch(map->player.press_status[4]){
			case 1:
				map->player.press_length[4]++;
				break;
			case 0: case 2:
			default:
				map->player.press_status[4]=1;
				map->player.press_length[4]=1;
		}
	}else{
		switch(map->player.press_status[4]){
			case 0:
				map->player.press_length[4]=0;
				break;
			case 1:
				map->player.press_status[4]=2;
				break;
			case 2:
				map->player.press_status[4]=0;
				break;
			default:
				;
		}
	}
	if(keystate('J')){
		map->player.press_direction=1;
	}else if(keystate('K')){
		map->player.press_direction=2;
	}else if(keystate('L')){
		map->player.press_direction=3;
	}else if(keystate('I')){
		map->player.press_direction=4;
	}
	if(keystate(' ')){
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
