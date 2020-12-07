#ifndef FOUN_H_
#define FOUN_H_ 1
#include"values.h"


typedef struct __unit{
	struct __unit* next_unit;
	int type;
	int n;
	int blood;
	int x;int y;
	int _x;int _y;
}_unit;
/*real x equals ta x+_x/1000 */

typedef struct __player{
	int blood;
	int energy;
	int point;
	int press_length;
	int weapon[9];
	int weapon_chosen;
	int x;int y;
	int _x;int _y;
}_player;
/*point from 100(1.00) to 430(4.30) 
  defined by your playing time and your blood :) */

typedef struct __data{
	int chapter;
	int gpa;
}_data;

typedef struct __map{
	_player player;
	char (*p_map)[WIDTH];
	_data data;
	_unit *p_unit;
	int length;
	int real_fps;
	
}_map;
/*p_map[x][y],x=0 means left,y=0 means top*/



#endif
