#ifndef __COLOUR_H
#define __COLOUR_H

#include "types.h"

#define BLACK 'B'
#define WHITE 'w'
#define RED 'r'
#define GREEN 'g'
#define BLUE 'b'
#define YELLOW 'y'
#define ORANGE 'o'

/* Up colours */
#define UP_00_COLOUR cube.sides.up.colour[0][0]
#define UP_01_COLOUR cube.sides.up.colour[0][1]
#define UP_02_COLOUR cube.sides.up.colour[0][2]
#define UP_10_COLOUR cube.sides.up.colour[1][0]
#define UP_11_COLOUR cube.sides.up.colour[1][1]
#define UP_12_COLOUR cube.sides.up.colour[1][2]
#define UP_20_COLOUR cube.sides.up.colour[2][0]
#define UP_21_COLOUR cube.sides.up.colour[2][1]
#define UP_22_COLOUR cube.sides.up.colour[2][2]
#define UP_CENTER_COLOUR UP_11_COLOUR
/* Down colours */
#define DOWN_00_COLOUR cube.sides.down.colour[0][0]
#define DOWN_01_COLOUR cube.sides.down.colour[0][1]
#define DOWN_02_COLOUR cube.sides.down.colour[0][2]
#define DOWN_10_COLOUR cube.sides.down.colour[1][0]
#define DOWN_11_COLOUR cube.sides.down.colour[1][1]
#define DOWN_12_COLOUR cube.sides.down.colour[1][2]
#define DOWN_20_COLOUR cube.sides.down.colour[2][0]
#define DOWN_21_COLOUR cube.sides.down.colour[2][1]
#define DOWN_22_COLOUR cube.sides.down.colour[2][2]
#define DOWN_CENTER_COLOUR DOWN_11_COLOUR
/* Left colours */
#define LEFT_00_COLOUR cube.sides.left.colour[0][0]
#define LEFT_01_COLOUR cube.sides.left.colour[0][1]
#define LEFT_02_COLOUR cube.sides.left.colour[0][2]
#define LEFT_10_COLOUR cube.sides.left.colour[1][0]
#define LEFT_11_COLOUR cube.sides.left.colour[1][1]
#define LEFT_12_COLOUR cube.sides.left.colour[1][2]
#define LEFT_20_COLOUR cube.sides.left.colour[2][0]
#define LEFT_21_COLOUR cube.sides.left.colour[2][1]
#define LEFT_22_COLOUR cube.sides.left.colour[2][2]
#define LEFT_CENTER_COLOUR LEFT_11_COLOUR
/* Right colours */
#define RIGHT_00_COLOUR cube.sides.right.colour[0][0]
#define RIGHT_01_COLOUR cube.sides.right.colour[0][1]
#define RIGHT_02_COLOUR cube.sides.right.colour[0][2]
#define RIGHT_10_COLOUR cube.sides.right.colour[1][0]
#define RIGHT_11_COLOUR cube.sides.right.colour[1][1]
#define RIGHT_12_COLOUR cube.sides.right.colour[1][2]
#define RIGHT_20_COLOUR cube.sides.right.colour[2][0]
#define RIGHT_21_COLOUR cube.sides.right.colour[2][1]
#define RIGHT_22_COLOUR cube.sides.right.colour[2][2]
#define RIGHT_CENTER_COLOUR RIGHT_11_COLOUR
/* Front colours */
#define FRONT_00_COLOUR cube.sides.front.colour[0][0]
#define FRONT_01_COLOUR cube.sides.front.colour[0][1]
#define FRONT_02_COLOUR cube.sides.front.colour[0][2]
#define FRONT_10_COLOUR cube.sides.front.colour[1][0]
#define FRONT_11_COLOUR cube.sides.front.colour[1][1]
#define FRONT_12_COLOUR cube.sides.front.colour[1][2]
#define FRONT_20_COLOUR cube.sides.front.colour[2][0]
#define FRONT_21_COLOUR cube.sides.front.colour[2][1]
#define FRONT_22_COLOUR cube.sides.front.colour[2][2]
#define FRONT_CENTER_COLOUR FRONT_11_COLOUR
/* Back colours */
#define BACK_00_COLOUR cube.sides.back.colour[0][0]
#define BACK_01_COLOUR cube.sides.back.colour[0][1]
#define BACK_02_COLOUR cube.sides.back.colour[0][2]
#define BACK_10_COLOUR cube.sides.back.colour[1][0]
#define BACK_11_COLOUR cube.sides.back.colour[1][1]
#define BACK_12_COLOUR cube.sides.back.colour[1][2]
#define BACK_20_COLOUR cube.sides.back.colour[2][0]
#define BACK_21_COLOUR cube.sides.back.colour[2][1]
#define BACK_22_COLOUR cube.sides.back.colour[2][2]
#define BACK_CENTER_COLOUR BACK_11_COLOUR


#define SET_BLACK_COLOUR      \
    do                        \
    {                         \
        printf("\033[0;40m"); \
    } while (0)
#define SET_RED_COLOUR              \
    do                              \
    {                               \
        printf("\033[48;5;124;1m"); \
    } while (0)
#define SET_GREEN_COLOUR           \
    do                             \
    {                              \
        printf("\033[48;5;22;1m"); \
    } while (0)
#define SET_YELLOW_COLOUR           \
    do                              \
    {                               \
        printf("\033[48;5;184;1m"); \
    } while (0)
#define SET_BLUE_COLOUR            \
    do                             \
    {                              \
        printf("\033[48;5;26;1m"); \
    } while (0)
#define SET_ORANGE_COLOUR           \
    do                              \
    {                               \
        printf("\033[48;5;166;1m"); \
    } while (0)
#define SET_WHITE_COLOUR            \
    do                              \
    {                               \
        printf("\033[48;5;255;1m"); \
    } while (0)
#define RESET_COLOUR       \
    do                     \
    {                      \
        printf("\033[0m"); \
    } while (0)
#define CLEAR_SCREEN             \
    do                           \
    {                            \
        printf("\033[H\033[0J"); \
    } while (0)

#define SET_FG_RED                \
    do                            \
    {                             \
        printf("\033[38;5;124m"); \
    } while (0)
#define SET_FG_GREEN             \
    do                           \
    {                            \
        printf("\033[38;5;22m"); \
    } while (0)
#define SET_FG_YELLOW             \
    do                            \
    {                             \
        printf("\033[38;5;184m"); \
    } while (0)
#define SET_FG_BLUE              \
    do                           \
    {                            \
        printf("\033[38;5;26m"); \
    } while (0)
#define SET_FG_ORANGE             \
    do                            \
    {                             \
        printf("\033[38;5;166m"); \
    } while (0)
#define SET_FG_WHITE              \
    do                            \
    {                             \
        printf("\033[38;5;255m"); \
    } while (0)
#define SET_FG_BLACK           \
    do                         \
    {                          \
        printf("\033[38;5;0"); \
    } while (0)

#define is_green(colour) (((colour)==GREEN)?1:0)
#define is_blue(colour) (((colour)==BLUE)?1:0)
#define is_white(colour) (((colour)==WHITE)?1:0)
#define is_yellow(colour) (((colour)==YELLOW)?1:0)
#define is_red(colour) (((colour)==RED)?1:0)
#define is_orange(colour) (((colour)==ORANGE)?1:0)
#define is_same_colour(colour1,colour2) (((colour1)==(colour2))?1:0)
#define is_not_same_colour(colour1,colour2) (((colour1)!=(colour2))?1:0)

extern int colour_count_valid_check(void);
extern int update_colour_count(char colour);
extern char opposite_colour(char c);
extern int side_of_center_colour(char colour);

#endif