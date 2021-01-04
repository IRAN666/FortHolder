#ifndef FOUN_H_
#define FOUN_H_ 1
#include"values.h"


typedef struct __unit{
	struct __unit* next_unit;
	struct __unit* pre_unit;
	int type;
	int n;
	int buff;
	int blood;
	int jump_state;
	int x;int y;
	int _x;int _y;
	int v_x;int v_y;
}_unit;
/*real x equals ta x+_x/1024 */

typedef struct __player{
	int blood;
	int energy;
	int score;
	int point;
	int jump_state;
	char press_weapon;
	char press_direction;
	char press_status[5];
	char weapon[9];
	char freeze_time[9];
	char weapon_chosen;
	int press_length[5];
	int buff;
	int x;int y;
	int _x;int _y;
	int v_x;int v_y;
}_player;
/*
 *point from 1000(1.00) to 4300(4.30) 
 *defined by your playing time and your blood :) 
 *press_length[0] is the length of press space
 *1 for 'A',2 for 'S',3 for 'D',4 for 'W'
 *each bit of "buff" means a buff 
 */
  

/*
typedef struct __data{
	int chapter;
	int gpa;
}_data;
*/
typedef struct __map{
	_player player;
	char (*p_map)[WIDTH];
	int gpa;
	int high_score;
	_unit *p_unit;
	int length;
	int real_fps;
	
}_map;
/*p_map[x][y],x=0 means left,y=0 means top*/

#define BETWEEN(x,a,b) (a<x)&&(x<b)

#endif
