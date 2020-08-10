#ifndef __CUBE_H
#define __CUBE_H

#include"types.h"


#define SET_BLACK_COLOUR  do{printf("\033[0;40m");}while(0)
#define SET_RED_COLOUR    do{printf("\033[48;5;124m");}while(0)
#define SET_GREEN_COLOUR  do{printf("\033[48;5;22m");}while(0)
#define SET_YELLOW_COLOUR do{printf("\033[48;5;184m");}while(0)
#define SET_BLUE_COLOUR   do{printf("\033[48;5;26m");}while(0)
#define SET_ORANGE_COLOUR do{printf("\033[48;5;166m");}while(0)
#define SET_WHITE_COLOUR  do{printf("\033[48;5;255m");}while(0)
#define RESET_COLOUR      do{printf("\033[0m");}while(0)
#define CLEAR_SCREEN      do{printf("\033[H\033[0J");}while(0)

#define SET_FG_RED    do{printf("\033[38;5;124m");}while(0)
#define SET_FG_GREEN  do{printf("\033[38;5;22m");}while(0)
#define SET_FG_YELLOW do{printf("\033[38;5;184m");}while(0)
#define SET_FG_BLUE   do{printf("\033[38;5;26m");}while(0)
#define SET_FG_ORANGE do{printf("\033[38;5;166m");}while(0)
#define SET_FG_WHITE  do{printf("\033[38;5;255m");}while(0)

#define MOVE_CURSOR(x,y) do{printf("\033[%d;%dH",(x),(y));}while(0)

extern cube_t cube;
extern colour_count_t colour_count;

extern void cube_init(void);

extern void cube_print(void);

extern int colour_count_valid_check(void);

#endif
