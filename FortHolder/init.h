#ifndef INIT_H_
#define INIT_H_ 1
#include"foundation.h"

int init(_map* map);
int map_free(_map* map);
int make_blank_file(_map* map);
int read_file(char *_file,_map* map);
int edit_file(char *_file,_map* map);

#endif
