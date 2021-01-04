#include"foundation.h"
#include"init.h"
#include"game.h"
#include"output.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

/**/
DWORD starttime;
DWORD Time;
_unit* unit_attacked;
int choose_weapon(_map* map){
	make_blank_file(map);
	for(map->player.weapon_chosen=0;map->player.weapon_chosen<9;){
		output_choose_weapon(map);
	}
	return 0;
}
int start_battle(_map* map){
    _unit* p_unit,*pn_unit;
	//Time=GetTickCount();
	output_clear();
    output_game_starting();
    //make_blank_file(map);
    //output_fps(1000/(GetTickCount()-Time));
    
    for(;;){
    	refresh_player(map);
    	for(p_unit=map->p_unit;p_unit!=NULL;p_unit=pn_unit){
    		pn_unit=p_unit->next_unit;
    		refresh_unit(map,p_unit);
		}
		if(map->player.blood<=0)break;
    	//map->real_fps=1000/(GetTickCount()-Time+1);
        output_battle(map);
	    //Time=GetTickCount();
		
	}
	output_die(map);
    map_free(map);
/*	for(;;){
		
	}*/
	return 0;
}
int judge_legel(_map* map,int x,int y,int type_code){
	_unit* p_unit;
	if(x<0||y<0||y>=WIDTH||x>=map->length){
		return 0;
	}
	if(type_code!=PLAYER_CODE&&x==map->player.x&&y==map->player.y){
		return 3;
	}
	if(type_code!=PLAYER_CODE){
		for(p_unit=map->p_unit;p_unit!=NULL;p_unit=p_unit->next_unit){
		    if(x==p_unit->x&&y==p_unit->y&&type_code!=p_unit->type&&!(IF_WEAPON(p_unit->type))){
		    	unit_attacked=p_unit;
			    return p_unit->type;
		    }
    	}
	}
	
	
	/**/
	if(IF_WEAPON(type_code)){
		if(map->p_map[x][y]&&map->p_map[x][y]!=BLOCK_WINDOWS_CODE){
			return 0;
		}else{
			return 1;
		}
	}else if(IF_ENEMY(type_code)||type_code==HOLE_CODE){
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
				case BLOCK_LADDER_CODE:
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
	int i;
	input_battle(map);
	
	/*refresh energy*/
	map->player.energy+=10;
	
	/*refresh v_x,v_y*/
	if(map->player.press_status[1]==1){
		map->player.v_x=map->player.press_length[1]>5?-200:map->player.press_length[1]*(-40);
	}else if(map->player.press_status[3]==1){
		map->player.v_x=map->player.press_length[3]>5?200:map->player.press_length[3]*40;
	}else{
		map->player.v_x>>=1;
	}
	if(map->player.press_status[4]==1&&map->player.jump_state<2
      &&map->player.press_length[4]<10){
		map->player.v_y=33*map->player.press_length[4];
	}else if(map->player.press_status[4]==2){
		map->player.jump_state++;
	}else if(map->player.press_status[2]==1){
		map->player.v_y=-250;
	}else{
		map->player.v_y*=63;
		map->player.v_y/=64;
		map->player.v_y-=GRAVITY;
	}
	/*refresh gpa(point)*/
	if(map->player.point>map->player.blood*33+1000){
		map->player.point--;
	}else{
		map->player.point++;
	}
	/*refresh weapon_chosen*/
	
	/*refresh freeze_time*/
	for(i=0;i<9;i++){
		if(map->player.freeze_time[i]>0){
			map->player.freeze_time[i]--;
		}
	}
	
	
	
	/*fire bullet*/
	if((map->player.press_status[0]==2||
	    (map->player.press_status[0]==1&&
	     map->player.press_length[0]%weapon_time[map->player.weapon[map->player.press_weapon]-WEAPON_1_CODE]==0))
		 && map->player.freeze_time[map->player.weapon[map->player.press_weapon]-WEAPON_1_CODE]==0 &&
		 map->player.energy>weapon_energy[map->player.weapon[map->player.press_weapon]-WEAPON_1_CODE]){
		switch(map->player.press_direction){
			case 1:
				add_unit(map,map->player.x-1,map->player.y,
		        map->player._x,map->player._y,
		        -weapon_speed[map->player.weapon[map->player.press_weapon]-WEAPON_1_CODE],
				weapon_speed_[map->player.weapon[map->player.press_weapon]-WEAPON_1_CODE],
				map->player.weapon[map->player.press_weapon],1);
				break;
			case 2:
				add_unit(map,map->player.x,map->player.y-1,
		        map->player._x,map->player._y,0,
				-weapon_speed[map->player.weapon[map->player.press_weapon]-WEAPON_1_CODE],
				map->player.weapon[map->player.press_weapon],1);
				break;
			case 3:
				add_unit(map,map->player.x+1,map->player.y,
		        map->player._x,map->player._y,
		        weapon_speed[map->player.weapon[map->player.press_weapon]-WEAPON_1_CODE],
				weapon_speed_[map->player.weapon[map->player.press_weapon]-WEAPON_1_CODE],
				map->player.weapon[map->player.press_weapon],1);
				break;
			case 4:
				add_unit(map,map->player.x,map->player.y+1,
		        map->player._x,map->player._y,0,
				weapon_speed[map->player.weapon[map->player.press_weapon]-WEAPON_1_CODE],
				map->player.weapon[map->player.press_weapon],1);
				break;
			default:
			    ;
		}
		map->player.energy-=weapon_energy[map->player.weapon[map->player.press_weapon]-WEAPON_1_CODE];
	}
	/*refresh x,y*/
	move_player(map);
	
	return 0;
}
int move_player(_map* map){
	map->player._x+=map->player.v_x;
	map->player._y+=map->player.v_y;
	/*if(judge_legel(map,map->player.x,map->player.y,PLAYER_CODE)==2){
		map->player.v_y=0;
	}*/
	if(map->player._x>0){
		switch(judge_legel(map,map->player.x+1,map->player.y,PLAYER_CODE)){
			case 1:
				if(map->player._x>>9){
				    map->player._x-=1024;
				    map->player.x++;
			    }
			    break;
			case 2:
				map->player.v_x=0;
				if(map->player._x>>9){
				    map->player._x-=1024;
				    map->player.x++;
			    }
				break;
			default:
			    map->player._x=0;
			    map->player.v_x=0;
			    map->player.jump_state=0;
		}
	}else{
	    switch(judge_legel(map,map->player.x-1,map->player.y,PLAYER_CODE)){
			case 1:
				if((-map->player._x)>>9){
				    map->player._x+=1024;
				    map->player.x--;
			    }
			    break;
			case 2:
				map->player.v_x=0;
				if((-map->player._x)>>9){
				    map->player._x+=1024;
				    map->player.x--;
			    }
				break;
			default:
			    map->player._x=0;
			    map->player.v_x=0;
			    map->player.jump_state=0;
		}
	}
	if(map->player._y>0){
		switch(judge_legel(map,map->player.x,map->player.y+1,PLAYER_CODE)){
			case 1:
				if(map->player._y>>9){
				    map->player._y-=1024;
				    map->player.y++;
			    }
			    break;
			case 2:
				map->player.v_y=10;
				map->player.jump_state=0;
				if(map->player._y>>9){
				    map->player._y-=1024;
				    map->player.y++;
			    }
				break;
			default:
			    map->player._y=0;
			    map->player.v_y=-map->player.v_y;
		}
	}else{
		switch(judge_legel(map,map->player.x,map->player.y-1,PLAYER_CODE)){
			case 1:
				if((-map->player._y)>>9){
				    map->player._y+=1024;
				    map->player.y--;
			    }
			    break;
			case 2:
				map->player.v_y=10;
				map->player.jump_state=0;
					if((-map->player._y)>>9){
				    map->player._y+=1024;
				    map->player.y--;
			    }
				break;
			default:
			    map->player._y=0;
			    map->player.v_y=0;
			    map->player.jump_state=0;
		}
	}
	return 0;
}
int add_unit(_map* map,int x,int y,int _x,int _y,int v_x,int v_y,int type_code,int buff){
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
	p_unit->v_x=v_x;
	p_unit->v_y=v_y;
	p_unit->n=0;
	p_unit->buff=buff;
	p_unit->jump_state=0;
	if(IF_ENEMY(p_unit->type)){
		p_unit->blood=enemy_blood[p_unit->type-ENEMY_1_CODE];
	}else{
		p_unit->blood=1;
	}
	return 0;
}
int move_unit(_map* map,_unit* unit){
	int t=0;
	unit->_x+=unit->v_x;
	unit->_y+=unit->v_y;
	if(unit->_y>0){
		if(judge_legel(map,unit->x,unit->y+1,unit->type)){
			if(unit->_y>>9){
				unit->_y-=1024;
				unit->y++;
			}
		}else{
			unit->_y=0;
			unit->v_y=-unit->v_y;
			t=4;
			unit->jump_state=2;
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
			t=2;
			unit->jump_state=0;
		}
	}
	if(unit->_x>0){
		if(judge_legel(map,unit->x+1,unit->y,unit->type)){
			if(unit->_x>>9){
				unit->_x-=1024;
				unit->x++;
			}
		}else{
			unit->_x=0;
			unit->v_x=0;
			t=3;
			//unit->jump_state=0;
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
			//unit->jump_state=0;
		}
	}
	switch(judge_legel(map,unit->x,unit->y,unit->type)){
		case 0:case 1:case 2:
			return t;
		case 3:
			return 5;
		default:
			return 6;
	}
	return t;
}
int refresh_unit(_map* map,_unit* unit){
	if(unit->type==HOLE_CODE){
		unit->n++;
		if(unit->n>60000/(100+map->player.score)){
			if(rand()%4){
				add_unit(map,unit->x,unit->y,0,0,0,0,ENEMY_1_CODE,0);
			}else{
				add_unit(map,unit->x,unit->y,0,0,0,0,ENEMY_1_CODE+2,0);
			}
			
			unit->n-=60000/(100+map->player.score);
		}
		return 0;
	}
	if(IF_WEAPON(unit->type)){
		unit->v_y-=weapon_gravity[unit->type-WEAPON_1_CODE];
	}else if(IF_ENEMY(unit->type)){
		unit->v_y-=enemy_gravity[unit->type-ENEMY_1_CODE];
	}
	int t;
	if(unit->blood<=0){
		kill_unit(map,unit);
		return 2;
	}
	t=move_unit(map,unit);
	if(t&&IF_WEAPON(unit->type)){
		kill_unit(map,unit);
		switch(unit->type-WEAPON_1_CODE){
			case 8:
				unit->blood=0;
				goto UNDESTROY_CASE;
			case 4:
				if(t==6){
				    unit_attacked->v_y+=700;
					if(unit->v_x>0){
						unit_attacked->_x+=10000;
					}else{
						unit_attacked->_x-=10000;
					}
				}
				
			case 9:
			case 7:
			case 6:
			case 5:
			case 3:
			case 2:
			case 0:
				DESTROY_CASE:
			    switch(t){
			        case 1:
				        attack_map(map,unit->x-1,unit->y);break;
				    case 2:
					    attack_map(map,unit->x,unit->y-1);break;
    				case 3:
	    			    attack_map(map,unit->x+1,unit->y);break;
		    		case 4:
			    		attack_map(map,unit->x,unit->y+1);break;
		    		default:
			    		;
		    }
			case 1:
			case 5:
				UNDESTROY_CASE:
				switch(t){
					case 5:
					    attack_player(map,weapon_hurt[unit->type-WEAPON_1_CODE],0);break;
    				case 6:
	    				attack_unit(map,unit_attacked,weapon_hurt[unit->type-WEAPON_1_CODE],unit->buff);
	    			default:
	    				;
				}
			default:
				;	
		}
		return 1;
	}
	if(IF_ENEMY(unit->type)){
	    unit->n++;
	    if(unit->x>map->player.x){
	    	unit->v_x=-enemy_speed[unit->type-ENEMY_1_CODE];
	    	if(unit->n>20){
	    	    add_unit(map,unit->x-1,unit->y,0,0,-300,30,WEAPON_1_CODE,0);
	    	    unit->n-=20;
		}
		}else if(unit->x<map->player.x){
			unit->v_x= enemy_speed[unit->type-ENEMY_1_CODE];
			if(unit->n>20){
	    	    add_unit(map,unit->x+1,unit->y,0,0, 300,30,WEAPON_1_CODE,0);
	    	    unit->n-=20;
	        }
		}else{
			unit->v_x>>=1;
			if(unit->n>20){
	    	    add_unit(map,unit->x,unit->y+1,0,0,0,300,WEAPON_1_CODE,0);
	    	    unit->n-=20;
	    	}
		}
		if((t==1||t==3)&&unit->jump_state==0){
			unit->v_y=enemy_speed[unit->type-ENEMY_1_CODE];
		}
	    
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
int attack_player(_map* map,int hurt,int buff){
	map->player.blood-=hurt;
	return 0;
}
int attack_unit(_map* map,_unit* unit,int hurt,int buff){
	if(buff&1){
		unit->blood-=hurt;
	    if(IF_ENEMY(unit->type)&&unit->blood<=0){
		    map->player.score+=enemy_score[unit->type-ENEMY_1_CODE];
		    map->player.point+=300;
	    }
	}
	return 0;
}
int attack_map(_map* map,int x,int y){
	if(map->p_map[x][y]==BLOCK_CODE){
		map->p_map[x][y]=BLOCK_DAMAGED_CODE;
	}else{
		map->p_map[x][y]=BLANK_CODE;
	}
	return 0; 
}
