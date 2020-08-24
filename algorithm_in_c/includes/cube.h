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
#define COMPLETE (0)

#define CURRENT_FORMULA formula[formula_count - 1]

/*** Condition checks ***/
/* White cross checks */
#if 0
/* Kept for backup */
#define CROSS_01_NOT_SOLVED (((!is_white(UP_01_COLOUR)) && (!is_blue(BACK_01_COLOUR))) || \
                             ((!is_white(UP_01_COLOUR)) && (is_blue(BACK_01_COLOUR))))

#define CROSS_02_NOT_SOLVED (((!is_white(UP_10_COLOUR)) && (is_not_same_colour(LEFT_01_COLOUR, LEFT_CENTER_COLOUR))) || \
                             ((!is_white(UP_10_COLOUR)) && (is_same_colour(LEFT_01_COLOUR, LEFT_CENTER_COLOUR))))

#define CROSS_03_NOT_SOLVED (((!is_white(UP_12_COLOUR)) && (is_not_same_colour(RIGHT_01_COLOUR, RIGHT_CENTER_COLOUR))) || \
                             ((!is_white(UP_12_COLOUR)) && (is_same_colour(RIGHT_01_COLOUR, RIGHT_CENTER_COLOUR))))

#define CROSS_04_NOT_SOLVED (((!is_white(UP_21_COLOUR)) && (!is_green(FRONT_01_COLOUR))) || \
                             ((!is_white(UP_21_COLOUR)) && (is_green(FRONT_01_COLOUR))))
#endif

#define CROSS_01_SOLVED ((is_white(UP_01_COLOUR)) && (is_blue(BACK_01_COLOUR)))
#define CROSS_02_SOLVED ((is_white(UP_10_COLOUR)) && (is_same_colour(LEFT_01_COLOUR, LEFT_CENTER_COLOUR)))
#define CROSS_03_SOLVED ((is_white(UP_12_COLOUR)) && (is_same_colour(RIGHT_01_COLOUR, RIGHT_CENTER_COLOUR)))
#define CROSS_04_SOLVED ((is_white(UP_21_COLOUR)) && (is_green(FRONT_01_COLOUR)))

#define CROSS_01_NOT_SOLVED (!CROSS_01_SOLVED)
#define CROSS_02_NOT_SOLVED (!CROSS_02_SOLVED)
#define CROSS_03_NOT_SOLVED (!CROSS_03_SOLVED)
#define CROSS_04_NOT_SOLVED (!CROSS_04_SOLVED)

/* White corners checks */
#if 0
/* Kept for backup */
#define WHITE_CORNER_01_NOT_SOLVED (((!is_white(UP_00_COLOUR)) || \
                                     (!((is_blue(BACK_02_COLOUR)) && (is_same_colour(LEFT_00_COLOUR, LEFT_CENTER_COLOUR))))))

#define WHITE_CORNER_02_NOT_SOLVED (((!is_white(UP_02_COLOUR)) || \
                                     (!((is_blue(BACK_01_COLOUR)) && (is_same_colour(RIGHT_02_COLOUR, RIGHT_CENTER_COLOUR))))))

#define WHITE_CORNER_03_NOT_SOLVED (((!is_white(UP_20_COLOUR)) || \
                                     (!((is_green(FRONT_01_COLOUR)) && (is_same_colour(LEFT_02_COLOUR, LEFT_CENTER_COLOUR))))))

#define WHITE_CORNER_04_NOT_SOLVED (((!is_white(UP_22_COLOUR)) || \
                                     (!((is_green(FRONT_02_COLOUR)) && (is_same_colour(RIGHT_00_COLOUR, RIGHT_CENTER_COLOUR))))))
#endif

#define WHITE_CORNER_01_SOLVED (is_white(UP_00_COLOUR) && is_blue(BACK_02_COLOUR) && is_same_colour(LEFT_00_COLOUR, LEFT_CENTER_COLOUR))
#define WHITE_CORNER_02_SOLVED (is_white(UP_02_COLOUR) && is_blue(BACK_01_COLOUR) && is_same_colour(RIGHT_02_COLOUR, RIGHT_CENTER_COLOUR))
#define WHITE_CORNER_03_SOLVED (is_white(UP_20_COLOUR) && is_green(FRONT_01_COLOUR) && is_same_colour(LEFT_02_COLOUR, LEFT_CENTER_COLOUR))
#define WHITE_CORNER_04_SOLVED (is_white(UP_22_COLOUR) && is_green(FRONT_02_COLOUR) && is_same_colour(RIGHT_00_COLOUR, RIGHT_CENTER_COLOUR))

#define WHITE_CORNER_01_NOT_SOLVED (!WHITE_CORNER_01_SOLVED)
#define WHITE_CORNER_02_NOT_SOLVED (!WHITE_CORNER_02_SOLVED)
#define WHITE_CORNER_03_NOT_SOLVED (!WHITE_CORNER_03_SOLVED)
#define WHITE_CORNER_04_NOT_SOLVED (!WHITE_CORNER_04_SOLVED)

#define X_LINE2_SOLVED(x) ((is_same_colour(FRONT_10_COLOUR, x) && is_same_colour(LEFT_12_COLOUR, LEFT_CENTER_COLOUR)) && \
                            (is_same_colour(FRONT_12_COLOUR, x) && is_same_colour(RIGHT_10_COLOUR, RIGHT_CENTER_COLOUR)))

#define GREEN_LINE2_SOLVED  X_LINE_SOLVED(GREEN)
#define RED_LINE2_SOLVED    X_LINE_SOLVED(RED)
#define BLUE_LINE2_SOLVED   X_LINE_SOLVED(BLUE)
#define ORANGE_LINE2_SOLVED X_LINE_SOLVED(ORANGE)

#define GREEN_LINE2_NOT_SOLVED  (!(GREEN_LINE2_SOLVED))
#define RED_LINE2_NOT_SOLVED    (!(RED_LINE2_SOLVED))
#define BLUE_LINE2_NOT_SOLVED   (!(BLUE_LINE2_SOLVED))
#define ORANGE_LINE2_NOT_SOLVED (!(ORANGE_LINE2_SOLVED))


#define FRONT_00_FOUND ((is_same_colour(FRONT_00_COLOUR, face_colour)) &&                                              \
                        ((is_same_colour(UP_20_COLOUR, side_colour1) || is_same_colour(UP_20_COLOUR, side_colour2)) && \
                         (is_same_colour(LEFT_02_COLOUR, side_colour1) || is_same_colour(LEFT_02_COLOUR, side_colour2))))
#define FRONT_02_FOUND ((is_same_colour(FRONT_02_COLOUR, face_colour)) &&                                              \
                        ((is_same_colour(UP_22_COLOUR, side_colour1) || is_same_colour(UP_22_COLOUR, side_colour2)) && \
                         (is_same_colour(RIGHT_00_COLOUR, side_colour1) || is_same_colour(RIGHT_00_COLOUR, side_colour2))))
#define FRONT_20_FOUND ((is_same_colour(FRONT_20_COLOUR, face_colour)) &&                                                  \
                        ((is_same_colour(DOWN_00_COLOUR, side_colour1) || is_same_colour(DOWN_00_COLOUR, side_colour2)) && \
                         (is_same_colour(LEFT_22_COLOUR, side_colour1) || is_same_colour(LEFT_22_COLOUR, side_colour2))))
#define FRONT_22_FOUND ((is_same_colour(FRONT_22_COLOUR, face_colour)) &&                                                  \
                        ((is_same_colour(DOWN_02_COLOUR, side_colour1) || is_same_colour(DOWN_02_COLOUR, side_colour2)) && \
                         (is_same_colour(RIGHT_20_COLOUR, side_colour1) || is_same_colour(RIGHT_20_COLOUR, side_colour2))))

#define BACK_00_FOUND ((is_same_colour(BACK_00_COLOUR, face_colour)) &&                                               \
                       ((is_same_colour(UP_02_COLOUR, side_colour1) || is_same_colour(UP_02_COLOUR, side_colour2)) && \
                        (is_same_colour(RIGHT_02_COLOUR, side_colour1) || is_same_colour(RIGHT_02_COLOUR, side_colour2))))
#define BACK_02_FOUND ((is_same_colour(BACK_02_COLOUR, face_colour)) &&                                               \
                       ((is_same_colour(UP_00_COLOUR, side_colour1) || is_same_colour(UP_00_COLOUR, side_colour2)) && \
                        (is_same_colour(LEFT_00_COLOUR, side_colour1) || is_same_colour(LEFT_00_COLOUR, side_colour2))))
#define BACK_20_FOUND ((is_same_colour(BACK_20_COLOUR, face_colour)) &&                                                   \
                       ((is_same_colour(DOWN_22_COLOUR, side_colour1) || is_same_colour(DOWN_22_COLOUR, side_colour2)) && \
                        (is_same_colour(RIGHT_22_COLOUR, side_colour1) || is_same_colour(RIGHT_22_COLOUR, side_colour2))))
#define BACK_22_FOUND ((is_same_colour(BACK_22_COLOUR, face_colour)) &&                                                   \
                       ((is_same_colour(DOWN_20_COLOUR, side_colour1) || is_same_colour(DOWN_20_COLOUR, side_colour2)) && \
                        (is_same_colour(LEFT_20_COLOUR, side_colour1) || is_same_colour(LEFT_20_COLOUR, side_colour2))))

#define LEFT_00_FOUND ((is_same_colour(LEFT_00_COLOUR, face_colour)) &&                                               \
                       ((is_same_colour(UP_00_COLOUR, side_colour1) || is_same_colour(UP_00_COLOUR, side_colour2)) && \
                        (is_same_colour(BACK_02_COLOUR, side_colour1) || is_same_colour(BACK_02_COLOUR, side_colour2))))
#define LEFT_02_FOUND ((is_same_colour(LEFT_02_COLOUR, face_colour)) &&                                               \
                       ((is_same_colour(UP_20_COLOUR, side_colour1) || is_same_colour(UP_20_COLOUR, side_colour2)) && \
                        (is_same_colour(FRONT_00_COLOUR, side_colour1) || is_same_colour(FRONT_00_COLOUR, side_colour2))))
#define LEFT_20_FOUND ((is_same_colour(LEFT_20_COLOUR, face_colour)) &&                                                   \
                       ((is_same_colour(DOWN_20_COLOUR, side_colour1) || is_same_colour(DOWN_20_COLOUR, side_colour2)) && \
                        (is_same_colour(BACK_22_COLOUR, side_colour1) || is_same_colour(BACK_22_COLOUR, side_colour2))))
#define LEFT_22_FOUND ((is_same_colour(LEFT_22_COLOUR, face_colour)) &&                                                   \
                       ((is_same_colour(DOWN_00_COLOUR, side_colour1) || is_same_colour(DOWN_00_COLOUR, side_colour2)) && \
                        (is_same_colour(FRONT_20_COLOUR, side_colour1) || is_same_colour(FRONT_20_COLOUR, side_colour2))))

#define RIGHT_00_FOUND ((is_same_colour(RIGHT_00_COLOUR, face_colour)) &&                                              \
                        ((is_same_colour(UP_22_COLOUR, side_colour1) || is_same_colour(UP_22_COLOUR, side_colour2)) && \
                         (is_same_colour(FRONT_02_COLOUR, side_colour1) || is_same_colour(FRONT_02_COLOUR, side_colour2))))
#define RIGHT_02_FOUND ((is_same_colour(RIGHT_02_COLOUR, face_colour)) &&                                              \
                        ((is_same_colour(UP_02_COLOUR, side_colour1) || is_same_colour(UP_02_COLOUR, side_colour2)) && \
                         (is_same_colour(BACK_00_COLOUR, side_colour1) || is_same_colour(BACK_00_COLOUR, side_colour2))))
#define RIGHT_20_FOUND ((is_same_colour(RIGHT_20_COLOUR, face_colour)) &&                                                  \
                        ((is_same_colour(DOWN_02_COLOUR, side_colour1) || is_same_colour(DOWN_02_COLOUR, side_colour2)) && \
                         (is_same_colour(FRONT_22_COLOUR, side_colour1) || is_same_colour(FRONT_22_COLOUR, side_colour2))))
#define RIGHT_22_FOUND ((is_same_colour(RIGHT_22_COLOUR, face_colour)) &&                                                  \
                        ((is_same_colour(DOWN_22_COLOUR, side_colour1) || is_same_colour(DOWN_22_COLOUR, side_colour2)) && \
                         (is_same_colour(BACK_20_COLOUR, side_colour1) || is_same_colour(BACK_20_COLOUR, side_colour2))))

#define UP_00_FOUND ((is_same_colour(UP_00_COLOUR, face_colour)) &&                                                     \
                     ((is_same_colour(BACK_02_COLOUR, side_colour1) || is_same_colour(BACK_02_COLOUR, side_colour2)) && \
                      (is_same_colour(LEFT_00_COLOUR, side_colour1) || is_same_colour(LEFT_00_COLOUR, side_colour2))))
#define UP_02_FOUND ((is_same_colour(UP_02_COLOUR, face_colour)) &&                                                       \
                     ((is_same_colour(RIGHT_02_COLOUR, side_colour1) || is_same_colour(RIGHT_02_COLOUR, side_colour2)) && \
                      (is_same_colour(BACK_00_COLOUR, side_colour1) || is_same_colour(BACK_00_COLOUR, side_colour2))))
#define UP_20_FOUND ((is_same_colour(UP_20_COLOUR, face_colour)) &&                                                     \
                     ((is_same_colour(LEFT_02_COLOUR, side_colour1) || is_same_colour(LEFT_02_COLOUR, side_colour2)) && \
                      (is_same_colour(FRONT_00_COLOUR, side_colour1) || is_same_colour(FRONT_00_COLOUR, side_colour2))))
#define UP_22_FOUND ((is_same_colour(UP_22_COLOUR, face_colour)) &&                                                       \
                     ((is_same_colour(RIGHT_00_COLOUR, side_colour1) || is_same_colour(RIGHT_00_COLOUR, side_colour2)) && \
                      (is_same_colour(FRONT_02_COLOUR, side_colour1) || is_same_colour(FRONT_02_COLOUR, side_colour2))))

#define DOWN_00_FOUND ((is_same_colour(DOWN_00_COLOUR, face_colour)) &&                                                     \
                       ((is_same_colour(FRONT_20_COLOUR, side_colour1) || is_same_colour(FRONT_20_COLOUR, side_colour2)) && \
                        (is_same_colour(LEFT_22_COLOUR, side_colour1) || is_same_colour(LEFT_22_COLOUR, side_colour2))))
#define DOWN_02_FOUND ((is_same_colour(DOWN_02_COLOUR, face_colour)) &&                                                     \
                       ((is_same_colour(RIGHT_20_COLOUR, side_colour1) || is_same_colour(RIGHT_20_COLOUR, side_colour2)) && \
                        (is_same_colour(FRONT_22_COLOUR, side_colour1) || is_same_colour(FRONT_22_COLOUR, side_colour2))))
#define DOWN_20_FOUND ((is_same_colour(DOWN_20_COLOUR, face_colour)) &&                                                   \
                       ((is_same_colour(LEFT_20_COLOUR, side_colour1) || is_same_colour(LEFT_20_COLOUR, side_colour2)) && \
                        (is_same_colour(BACK_22_COLOUR, side_colour1) || is_same_colour(BACK_22_COLOUR, side_colour2))))
#define DOWN_22_FOUND ((is_same_colour(DOWN_22_COLOUR, face_colour)) &&                                                     \
                       ((is_same_colour(RIGHT_22_COLOUR, side_colour1) || is_same_colour(RIGHT_22_COLOUR, side_colour2)) && \
                        (is_same_colour(BACK_20_COLOUR, side_colour1) || is_same_colour(BACK_20_COLOUR, side_colour2))))

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
    VALIDATE_CROSS = 8,
    VALIDATE_WHITE_CORNERS = 9
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
    WHITE_CROSS = 1,
    WHITE_CORNERS = 2
} stage1_t;

typedef enum
{
    GREEN_LINE2 = 1,
    RED_LINE2 = 2,
    BLUE_LINE2 = 3,
    ORANGE_LINE2 = 4,
    VALIDATE_LINE2 = 5
} stage2_t;

extern cube_t cube;
extern colour_count_t colour_count;
extern formula_t *formula;
extern int formula_count;
extern int formula_to_apply;
extern char stub_cube;

extern void cube_init(void);
extern void update_cube_map(void);
extern void cube_solve(void);

#endif
