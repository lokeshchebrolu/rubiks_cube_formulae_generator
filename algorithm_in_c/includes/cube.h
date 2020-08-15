#ifndef __CUBE_H
#define __CUBE_H

#include "types.h"

#define MOVE_CURSOR(x, y)                \
    do                                   \
    {                                    \
        printf("\033[%d;%dH", (x), (y)); \
    } while (0)

#define IS_INVERSE (temp_step[1] == 'i')
#define START_FORMULA "S"
#define END_FORMULA "E"

#define CURRENT_FORMULA formula[formula_count - 1]

typedef enum
{
    ANALYSE = 0, /* Analyse the input given cube state */
    STAGE1 = 1,  /* White colour completion */
    STAGE2 = 2,  /* Line 2 completion */
    STAGE3 = 3,  /* Top layer completion */
    STAGE4 = 4,  /* Top side line completion */
} cube_stages_t;

extern cube_t cube;
extern colour_count_t colour_count;
extern formula_t *formula;
extern int formula_count;
extern int formula_to_apply;

extern void cube_init(void);
extern void update_cube_map(void);
extern void cube_print(void);
extern void cube_solve(void);

#endif
