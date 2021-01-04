#ifndef VALUES_H_
#define VALUES_H_ 1

#define LENGTH 128
#define WIDTH 32
#define UNIT_LENGTH 8
#define UNIT_WIDTH 15
#define PLAYER_POSITION 64
#define LENGTH_BLOCK 16
#define NUMBER_OF_UNITS 64
#define DARK_BLUE EGERGB(0,0,0x20)
#define FPS 60
/*physical quantities*/
#define GRAVITY 10
/*output*/
#define OUTPUT_LOADING_X 36
#define OUTPUT_LOADING_Y 16
#define OUTPUT_LOADING_STRING_0 "L      OOOO     A    DDDD   III  N   N   GGG "
#define OUTPUT_LOADING_STRING_1 "L     O    O   A A   D   D   I   NN  N  G    "
#define OUTPUT_LOADING_STRING_2 "L     O    O  A   A  D   D   I   N N N  G  GG"
#define OUTPUT_LOADING_STRING_3 "L     O    O  AAAAA  D   D   I   N  NN  G   G"
#define OUTPUT_LOADING_STRING_4 "LLLLL  OOOO   A   A  DDDD   III  N   N   GGG "

#define OUTPUT_GAME_ENERGY_X 480
#define OUTPUT_GAME_ENERGY_Y 0
#define OUTPUT_GAME_FPS_X 830
#define OUTPUT_GAME_FPS_X_ 870
#define OUTPUT_GAME_FPS_Y 0
#define OUTPUT_GAME_BLOOD_X 32
#define OUTPUT_GAME_BLOOD_Y 15
#define OUTPUT_GAME_ENERGY_LEFT_X 336
#define OUTPUT_GAME_ENERGY_LEFT_Y 15
#define OUTPUT_GAME_ENERGY_RIGHT_X 672
#define OUTPUT_GAME_ENERGY_RIGHT_Y 15
#define OUTPUT_GAME_ENERGY_LENGTH 336
#define OUTPUT_GAME_GPA_X 780
#define OUTPUT_GAME_GPA_Y 15
#define OUTPUT_GAME_UPPER_LINE_Y 40
#define OUTPUT_GAME_LOWER_LINE_Y 530
#define OUTPUT_GAME_WEAPON_Y 542
#define OUTPUT_GAME_WEAPON_Y_UP 538
#define OUTPUT_GAME_WEAPON_Y_DOWN 562
#define OUTPUT_GAME_WEAPON_X 443
#define OUTPUT_GAME_WEAPON_X_LEFT 437
#define OUTPUT_GAME_WEAPON_X_RIGHT 587
#define OUTPUT_GAME_COMMON_X 10
#define OUTPUT_GAME_COMMON_Y 540

/*blocks*/
#define BLANK_CODE 0
#define BLOCK_CODE 1
#define BLOCK_DAMAGED_CODE 2
#define BLOCK_WINDOWS_CODE 3
#define BLOCK_HIDDEN_CODE 4
#define BLOCK_LADDER_CODE 5
#define BLOCK_STAIR_LEFT_CODE 6
#define BLOCK_STAIR_RIGHT_CODE 7

#define UNKNOWN_CHAR '?'
#define BLANK_CHAR ' '
#define BLOCK_CHAR '#'
#define BLOCK_WINDOWS_CHAR '|'
#define BLOCK_LADDER_CHAR 'H'
#define BLOCK_STAIR_LEFT_CHAR '/'
#define BLOCK_STAIR_RIGHT_CHAR '\''

#define SETBLOCK(x,y,code) (map->p_map[x][y]=(code))
/*player and enemy*/
#define PLAYER_CHAR '$'

/*weapon*/
#define NUMBER_WEAPON 16
#define NUMBER_WEAPON_CARRIED 9
#define IF_WEAPON(type_code) ((type_code)>=WEAPON_1_CODE&&(type_code)<WEAPON_1_CODE+NUMBER_WEAPON)
extern char weapon_char[16];
extern int weapon_energy[16];
extern int weapon_time[16];
extern int weapon_speed[16];
extern int weapon_speed_[16];
extern int weapon_gravity[16];
extern int weapon_hurt[16];
/*enemy*/
#define NUMBER_ENEMY 10
extern char enemy_char[10];
extern int enemy_speed[10];
extern int enemy_gravity[10];
extern int enemy_blood[10];
extern int enemy_score[10];
#define IF_ENEMY(type_code) (type_code)>=ENEMY_1_CODE&&(type_code)<ENEMY_1_CODE+NUMBER_ENEMY

#define HOLE_CHAR 'X'

/*can/can't move*/
#define CANMOVE 1
/*type code*/
#define PLAYER_CODE 0
#define BOUND_TEST_CODE 1
#define BACKGROUND_CODE 2
#define BUILD_CODE 3
#define WEAPON_1_CODE 4
#define ENEMY_1_CODE 20
#define HOLE_CODE 30


#endif
