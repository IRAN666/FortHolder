#ifndef GAME_H_
#define GAME_H_ 1
#include"foundation.h"

int menu(_map* map);
int choose_weapon(_map* map);
int start_battle(_map* map);

int stop_battle(_map* map);
/*0 means continue,1 mean quit,2 means restart*/
int end_battle(_map* map);

int refresh_player(_map* map);
int refresh_unit(_map* map,_unit* unit);
int move_player(_map* map);
int move_unit(_map* map,_unit* unit);
/* 0 means success to move*/

int judge_legel(_map* map,int x,int y,int type_code);
/*0 is legel to mave to,1 is illegel to move,2 is ladder,3 is player,other is unit*/

int add_unit(_map* map,int x,int y,int _x,int _y,int v_x,int v_y,int type_code,int buff);
int attack_map(_map* map,int x,int y);
int attack_player(_map* map,int hurt,int buff);
int attack_unit(_map* map,_unit* unit,int hurt,int buff);
int kill_unit(_map* map,_unit* unit);

#endif
