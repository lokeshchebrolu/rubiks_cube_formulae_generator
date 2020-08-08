#ifndef __CUBE_H
#define __CUBE_H

#include"types.h"

#define SET_BLACK_COLOUR do{printf("\033[0;40m");}while(0)
#define SET_RED_COLOUR do{printf("\033[0;41m");}while(0)
#define SET_GREEN_COLOUR do{printf("\033[0;42m");}while(0)
#define SET_YELLOW_COLOUR do{printf("\033[0;43m");}while(0)
#define SET_BLUE_COLOUR do{printf("\033[0;44m");}while(0)
#define SET_MAGENTA_COLOUR do{printf("\033[0;101m");}while(0)
#define SET_WHITE_COLOUR do{printf("\033[0;47m");}while(0)
#define RESET_COLOUR do{printf("\033[0m");}while(0)
#define CLEAR_SCREEN do{printf("\033[H\033[0J");}while(0)

extern cube_t cube;

extern void cube_init(void);

extern void cube_print(void);

#endif
