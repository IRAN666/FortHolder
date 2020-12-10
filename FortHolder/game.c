#include"foundation.h"
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
    make_blank_file(&map);
    output_battle(&map);
    output_fps(1000/(GetTickCount()-Time));
    for(;;){
        map->player.x++;
        
        output_battle(&map);
        Sleep(20);
        output_fps(1000/(GetTickCount()-Time+1));
		Time=GetTickCount();
	}
    map_free(&map);
/*	for(;;){
		
	}*/
	return 0;
}

int refresh_player(_map* map){
	;
}
