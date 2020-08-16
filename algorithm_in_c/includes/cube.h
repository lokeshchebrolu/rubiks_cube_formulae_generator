#ifndef __CUBE_H
#define __CUBE_H

#include "types.h"

#define MOVE_CURSOR(x, y)                \
    do                                   \
    {                                    \
        printf("\033[%d;%dH", (x), (y)); \
    } while (0)

#define MOVE_CURSOR_UP(x)                \
    do                                   \
    {                                    \
        printf("\033[%dA", (x)); \
    } while (0)

#define MOVE_CURSOR_FORWARD(x)                \
    do                                   \
    {                                    \
        printf("\033[%dC", (x)); \
    } while (0)

#define MOVE_CURSOR_BACK(x)                \
    do                                   \
    {                                    \
        printf("\033[%dD", (x)); \
    } while (0)

#define IS_INVERSE (temp_step[1] == 'i')
#define START_FORMULA "S"
#define END_FORMULA "E"

#define CURRENT_FORMULA formula[formula_count - 1]

#define UP_CENTER_COLOUR cube.sides.up.colour[1][1]
#define DOWN_CENTER_COLOUR cube.sides.down.colour[1][1]
#define LEFT_CENTER_COLOUR cube.sides.left.colour[1][1]
#define RIGHT_CENTER_COLOUR cube.sides.right.colour[1][1]
#define FRONT_CENTER_COLOUR cube.sides.front.colour[1][1]
#define BACK_CENTER_COLOUR cube.sides.back.colour[1][1]

typedef enum
{
    ANALYSE = 0, /* Analyse the input given cube state */
    STAGE1 = 1,  /* White colour completion */
    STAGE2 = 2,  /* Line 2 completion */
    STAGE3 = 3,  /* Top layer completion */
    STAGE4 = 4  /* Top side line completion */
} cube_stages_t;

typedef enum
{
    UP_01 = 0,
    UP_10 = 1,
    UP_12 = 2,
    UP_21 = 3,
    VALIDATE_CROSS = 4
}up_edges_t;

extern cube_t cube;
extern colour_count_t colour_count;
extern formula_t *formula;
extern int formula_count;
extern int formula_to_apply;

extern void cube_init(void);
extern void update_cube_map(void);
extern void cube_solve(void);

#endif
