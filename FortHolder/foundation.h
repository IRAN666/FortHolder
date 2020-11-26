#ifndef FOUN_H_
#define FOUN_H_ 1
#include"values.h"


typedef struct __unit{
	int type;
	int num;
	int blood;
	int x;int y;
	int _x;int _y;
}_unit;
/*real x equals ta x+_x/1000 */

typedef struct _block{
	struct _block *nextblock;
	struct _block *prevblock;
	int num_units;
	_unit unit[NUMBER_OF_UNITS];
	char block_map[LENGTH_BLOCK][WIDTH];
}block;

typedef struct __player{
	int blood;
	int energy;
	int x;int y;
	int _x;int _y;
}_player;

typedef struct __map{
	_player player;
	block *central_block;
}_map;



#endif
