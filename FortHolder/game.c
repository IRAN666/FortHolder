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
	Time=GetTickCount();
	output_clear();
    output_game_starting();
    make_blank_file(map);
    //output_fps(1000/(GetTickCount()-Time));
    
    for(;;){
    	refresh_player(map);
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
	if(x<0||y<0||y>WIDTH||x>map->length){
		return 0;
	}
	switch(type_code){
		case PLAYER_CODE:
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
	input_battle(map);
	if(map->player.press_status[1]==1){
		map->player.v_x=-200;
	}else if(map->player.press_status[3]==1){
		map->player.v_x=200;
	}else if(map->player.press_status[1]==2
	       ||map->player.press_status[3]==2){
		map->player.v_x=0;
	}
	if(map->player.press_status[4]==1){
		map->player.v_y=300;
	}else{
		map->player.v_y-=GRAVITY;
	}
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
	}if(map->player._y>0){
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
