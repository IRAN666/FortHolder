#include"foundation.h"
#include"init.h"
#include"game.h"
#include"output.h"
#include<stdio.h>
#include<time.h>
#include<windows.h>

/**/
DWORD starttime;
DWORD Time;

int start_battle(_map* map){
    _unit* p_unit,*pn_unit;
	Time=GetTickCount();
	output_clear();
    output_game_starting();
    make_blank_file(map);
    //output_fps(1000/(GetTickCount()-Time));
    
    for(;;){
    	refresh_player(map);
    	for(p_unit=map->p_unit;p_unit!=NULL;p_unit=pn_unit){
    		pn_unit=p_unit->next_unit;
    		refresh_unit(map,p_unit);
		}
    	map->real_fps=1000/(GetTickCount()-Time+1);
        output_battle(map);
	    Time=GetTickCount();
		
	}
    map_free(map);
/*	for(;;){
		
	}*/
	return 0;
}
int judge_legel(_map* map,int x,int y,int type_code){
	if(x<0||y<0||y>=WIDTH||x>=map->length){
		return 0;
	}
	if(IF_WEAPON(type_code)){
		if(map->p_map[x][y]){
			return 0;
		}else{
			return 1;
		}
	}
	switch(type_code){
		case PLAYER_CODE:
			switch(map->p_map[x][y]){
				case BLANK_CODE:
					return 1;
				case BLOCK_CODE:
					return 0;
				case BLOCK_DAMAGED_CODE:
					return 0;
				case BLOCK_HIDDEN_CODE:
					return 0;
				case BLOCK_LADDER_CHAR:
					return 2;
				default:
					return 0;
			}
			
		case BOUND_TEST_CODE:
			return 1;
		case BACKGROUND_CODE:
			return map->p_map[x][y]?1:0;
		case BUILD_CODE:
			return map->p_map[x][y]?0:1;
		case WEAPON_1_CODE:
			switch(map->p_map[x][y]){
				case BLANK_CODE:
					return 1;
				case BLOCK_CODE:
					return 0;
				default:
					return 0;
			}
		default:
			return 0;
	}
}
int refresh_player(_map* map){
	/*refresh press_status,length,weapon*/
	input_battle(map);
	
	/*refresh energy*/
	map->player.energy++;
	
	/*refresh v_x,v_y*/
	if(map->player.press_status[1]==1){
		map->player.v_x=-200;
	}else if(map->player.press_status[3]==1){
		map->player.v_x=200;
	}else{
		map->player.v_x=0;
	}
	if(map->player.press_status[4]==1){
		map->player.v_y=250;
	}else{
		map->player.v_y*=63;
		map->player.v_y/=64;
		map->player.v_y-=GRAVITY;
	}
	
	/*refresh weapon_chosen*/
	
	/*refresh freeze_time*/
	
	/*refresh gpa(point)*/
	
	/*fire bullet*/
	if(map->player.energy>10){
		add_unit(map,map->player.x,map->player.y+1,
		        map->player._x,map->player._y,WEAPON_1_CODE+map->player.press_weapon);
		map->player.energy-=10;
	}
	/*refresh x,y*/
	move_player(map);
	
	return 0;
}
int move_player(_map* map){
	map->player._x+=map->player.v_x;
	map->player._y+=map->player.v_y;
	if(map->player._x>0){
		if(judge_legel(map,map->player.x+1,map->player.y,PLAYER_CODE)){
			if(map->player._x>>9){
				map->player._x-=1024;
				map->player.x++;
			}
		}else{
			map->player._x=0;
			map->player.v_x=0;
		}
	}else{
		if(judge_legel(map,map->player.x-1,map->player.y,PLAYER_CODE)){
			if((-map->player._x)>>9){
				map->player._x+=1024;
				map->player.x--;
			}
		}else{
			map->player._x=0;
			map->player.v_x=0;
		}
	}
	if(map->player._y>0){
		if(judge_legel(map,map->player.x,map->player.y+1,PLAYER_CODE)){
			if(map->player._y>>9){
				map->player._y-=1024;
				map->player.y++;
			}
		}else{
			map->player._y=0;
			map->player.v_y=-map->player.v_y;
		}
	}else{
		if(judge_legel(map,map->player.x,map->player.y-1,PLAYER_CODE)){
			if((-map->player._y)>>9){
				map->player._y+=1024;
				map->player.y--;
			}
		}else{
			map->player._y=0;
			map->player.v_y=0;
		}
	}
	return 0;
}
int add_unit(_map* map,int x,int y,int _x,int _y,int type_code){
	_unit* p_unit;
	if(!judge_legel(map,x,y,type_code)){
		return 1;
	}
	p_unit=(_unit*)malloc(sizeof(_unit));
	if(p_unit==NULL){
		return -1;
	}
	p_unit->pre_unit=NULL;
	p_unit->next_unit=map->p_unit;
	if(map->p_unit!=NULL){
		map->p_unit->pre_unit=p_unit;
	}
	map->p_unit=p_unit;
	p_unit->type=type_code;
	p_unit->x=x;p_unit->y=y;
	p_unit->_x=_x;p_unit->_y=_y;
	/*    */
	p_unit->v_x=-450;
	p_unit->v_y=0;
	
	
	p_unit->buff=0;
	
	return 0;
}
int move_unit(_map* map,_unit* unit){
	int t=0;
	unit->_x+=unit->v_x;
	unit->_y+=unit->v_y;
	if(unit->_x>0){
		if(judge_legel(map,unit->x+1,unit->y,unit->type)){
			if(unit->_x>>9){
				unit->_x-=1024;
				unit->x++;
			}
		}else{
			unit->_x=0;
			unit->v_x=0;
			t=1;
		}
	}else{
		if(judge_legel(map,unit->x-1,unit->y,unit->type)){
			if((-unit->_x)>>9){
				unit->_x+=1024;
				unit->x--;
			}
		}else{
			unit->_x=0;
			unit->v_x=0;
			t=1;
		}
	}
	if(unit->_y>0){
		if(judge_legel(map,unit->x,unit->y+1,unit->type)){
			if(unit->_y>>9){
				unit->_y-=1024;
				unit->y++;
			}
		}else{
			unit->_y=0;
			unit->v_y=-unit->v_y;
			t=1;
		}
	}else{
		if(judge_legel(map,unit->x,unit->y-1,unit->type)){
			if((-unit->_y)>>9){
				unit->_y+=1024;
				unit->y--;
			}
		}else{
			unit->_y=0;
			unit->v_y=0;
			t=1;
		}
	}
	return t;
}
int refresh_unit(_map* map,_unit* unit){
	int t;
	t=move_unit(map,unit);
	if(t&&IF_WEAPON(unit->type)){
		kill_unit(map,unit);
		return 1;
	}
	return 0; 
}
int kill_unit(_map* map,_unit* unit){
	if(unit->pre_unit!=NULL){
		unit->pre_unit->next_unit=unit->next_unit;
	}else{
		map->p_unit=unit->next_unit;
	}
	if(unit->next_unit!=NULL){
		unit->next_unit->pre_unit=unit->pre_unit;
	}
	free(unit);
	return 0;
}


