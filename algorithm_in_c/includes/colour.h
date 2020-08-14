#ifndef __COLOUR_H
#define __COLOUR_H

#include"types.h"

#define BLACK  'B'
#define WHITE  'w'
#define RED    'r'
#define GREEN  'g'
#define BLUE   'b'
#define YELLOW 'y'
#define ORANGE 'o'

#define SET_BLACK_COLOUR  do{printf("\033[0;40m");}while(0)
#define SET_RED_COLOUR    do{printf("\033[48;5;124;1m");}while(0)
#define SET_GREEN_COLOUR  do{printf("\033[48;5;22;1m");}while(0)
#define SET_YELLOW_COLOUR do{printf("\033[48;5;184;1m");}while(0)
#define SET_BLUE_COLOUR   do{printf("\033[48;5;26;1m");}while(0)
#define SET_ORANGE_COLOUR do{printf("\033[48;5;166;1m");}while(0)
#define SET_WHITE_COLOUR  do{printf("\033[48;5;255;1m");}while(0)
#define RESET_COLOUR      do{printf("\033[0m");}while(0)
#define CLEAR_SCREEN      do{printf("\033[H\033[0J");}while(0)

#define SET_FG_RED    do{printf("\033[38;5;124m");}while(0)
#define SET_FG_GREEN  do{printf("\033[38;5;22m");}while(0)
#define SET_FG_YELLOW do{printf("\033[38;5;184m");}while(0)
#define SET_FG_BLUE   do{printf("\033[38;5;26m");}while(0)
#define SET_FG_ORANGE do{printf("\033[38;5;166m");}while(0)
#define SET_FG_WHITE  do{printf("\033[38;5;255m");}while(0)
#define SET_FG_BLACK  do{printf("\033[38;5;0");}while(0)

extern int colour_count_valid_check(void);
extern int update_colour_count(char colour);
extern char opposite_colour(char c);
extern int side_of_center_colour(char colour);

#endif