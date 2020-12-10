#ifndef OUTPUT_H_
#define OUTPUT_H_ 1
#include"foundation.h"

int output_clear(void);
int output_init(int progress);
int output_loading(int progress);
int output_game_starting(void);
int output_menu(_map* map);
int output_introduce(void);
int output_int(int t);
int output_string(char s[]);
int output_fps(int fps);
int output_choose_weapon(_map* map);
int output_battle(_map* map);

/*return value 0 means nothing wrong,negative values means wrong*/

#endif
