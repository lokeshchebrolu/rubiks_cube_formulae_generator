#ifndef __CUBE_H
#define __CUBE_H

#include "types.h"
#include "colour.h"

#define MOVE_CURSOR(x, y)                \
    do                                   \
    {                                    \
        printf("\033[%d;%dH", (x), (y)); \
    } while (0)

#define MOVE_CURSOR_UP(x)        \
    do                           \
    {                            \
        printf("\033[%dA", (x)); \
    } while (0)

#define MOVE_CURSOR_FORWARD(x)   \
    do                           \
    {                            \
        printf("\033[%dC", (x)); \
    } while (0)

#define MOVE_CURSOR_BACK(x)      \
    do                           \
    {                            \
        printf("\033[%dD", (x)); \
    } while (0)

#define IS_INVERSE (temp_step[1] == 'i')
#define START_FORMULA "S"
#define END_FORMULA "E"

#define CURRENT_FORMULA formula[formula_count - 1]

/* Condition checks */
/* White cross checks */
#define CROSS_01_NOT_SOLVED (((!is_white(UP_01_COLOUR)) && (!is_blue(BACK_01_COLOUR))) || \
                             ((!is_white(UP_01_COLOUR)) && (is_blue(BACK_01_COLOUR))))

#define CROSS_02_NOT_SOLVED (((!is_white(UP_10_COLOUR)) && (is_not_same_colour(LEFT_01_COLOUR, LEFT_CENTER_COLOUR))) || \
                             ((!is_white(UP_10_COLOUR)) && (is_same_colour(LEFT_01_COLOUR, LEFT_CENTER_COLOUR))))

#define CROSS_03_NOT_SOLVED (((!is_white(UP_12_COLOUR)) && (is_not_same_colour(RIGHT_01_COLOUR, RIGHT_CENTER_COLOUR))) || \
                             ((!is_white(UP_12_COLOUR)) && (is_same_colour(RIGHT_01_COLOUR, RIGHT_CENTER_COLOUR))))

#define CROSS_04_NOT_SOLVED (((!is_white(UP_21_COLOUR)) && (!is_green(FRONT_01_COLOUR))) || \
                             ((!is_white(UP_21_COLOUR)) && (is_green(FRONT_01_COLOUR))))

#define CROSS_01_SOLVED ((is_white(UP_01_COLOUR)) && (is_blue(BACK_01_COLOUR)))
#define CROSS_02_SOLVED ((is_white(UP_10_COLOUR)) && (is_same_colour(LEFT_01_COLOUR, LEFT_CENTER_COLOUR)))
#define CROSS_03_SOLVED ((is_white(UP_12_COLOUR)) && (is_same_colour(RIGHT_01_COLOUR, RIGHT_CENTER_COLOUR)))
#define CROSS_04_SOLVED ((is_white(UP_21_COLOUR)) && (is_green(FRONT_01_COLOUR)))

typedef enum
{
    ANALYSE = 0, /* Analyse the input given cube state */
    STAGE1 = 1,  /* White colour completion */
    STAGE2 = 2,  /* Line 2 completion */
    STAGE3 = 3,  /* Top layer completion */
    STAGE4 = 4   /* Top side line completion */
} cube_stages_t;

typedef enum
{
    UP_00 = 0,
    UP_01 = 1,
    UP_02 = 2,
    UP_10 = 3,
    UP_12 = 4,
    UP_20 = 5,
    UP_21 = 6,
    UP_22 = 7,
    VALIDATE_CROSS = 8
} up_t;

typedef enum
{
    DOWN_00 = 0,
    DOWN_01 = 1,
    DOWN_02 = 2,
    DOWN_10 = 3,
    DOWN_12 = 4,
    DOWN_20 = 5,
    DOWN_21 = 6,
    DOWN_22 = 7
} down_t;

typedef enum
{
    LEFT_00 = 0,
    LEFT_01 = 1,
    LEFT_02 = 2,
    LEFT_10 = 3,
    LEFT_12 = 4,
    LEFT_20 = 5,
    LEFT_21 = 6,
    LEFT_22 = 7
} left_t;

typedef enum
{
    RIGHT_00 = 0,
    RIGHT_01 = 1,
    RIGHT_02 = 2,
    RIGHT_10 = 3,
    RIGHT_12 = 4,
    RIGHT_20 = 5,
    RIGHT_21 = 6,
    RIGHT_22 = 7
} right_t;

typedef enum
{
    FRONT_00 = 0,
    FRONT_01 = 1,
    FRONT_02 = 2,
    FRONT_10 = 3,
    FRONT_12 = 4,
    FRONT_20 = 5,
    FRONT_21 = 6,
    FRONT_22 = 7
} front_t;

typedef enum
{
    BACK_00 = 0,
    BACK_01 = 1,
    BACK_02 = 2,
    BACK_10 = 3,
    BACK_12 = 4,
    BACK_20 = 5,
    BACK_21 = 6,
    BACK_22 = 7
} back_t;

typedef enum
{
    COMPLETE = 0,
    WHITE_CROSS = 1,
    WHITE_CORNERS = 2
} stage1_t;

extern cube_t cube;
extern colour_count_t colour_count;
extern formula_t *formula;
extern int formula_count;
extern int formula_to_apply;

extern void cube_init(void);
extern void update_cube_map(void);
extern void cube_solve(void);

#endif
