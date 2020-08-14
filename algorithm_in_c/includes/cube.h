#ifndef __CUBE_H
#define __CUBE_H

#include"types.h"

#define MOVE_CURSOR(x,y) do{printf("\033[%d;%dH",(x),(y));}while(0)

#define IS_INVERSE (temp_step[1]=='i')

extern cube_t cube;
extern colour_count_t colour_count;
extern formula_t formula;

extern void cube_init(void);
extern void update_cube_map(void);
extern void cube_print(void);

#endif
