#ifndef __MOVEMENTS_H
#define __MOVEMENTS_H

#include"types.h"

#define UP_ROW0 (1)
#define UP_ROW1 (2)
#define UP_ROW2 (3)
#define UP_COLUMN0 (4)
#define UP_COLUMN1 (5)
#define UP_COLUMN2 (6)
#define UP_ROW0_i (-1)
#define UP_ROW1_i (-2)
#define UP_ROW2_i (-3)
#define UP_COLUMN0_i (-4)
#define UP_COLUMN1_i (-5)
#define UP_COLUMN2_i (-6)
#define UP_ROW_CLOCKWISE (1) /* This is similar to F step */
#define UP_ROW_ANTI_CLOCKWISE (-1) /* This is similar to Fi step */
#define UP_COLUMN_CLOCKWISE (2) /* This is similar to R step */
#define UP_COLUMN_ANTI_CLOCKWISE (-2) /* This is similar to Ri step */

#define FRONT_ROW0 (1)
#define FRONT_ROW1 (2)
#define FRONT_ROW2 (3)
#define FRONT_COLUMN0 (4)
#define FRONT_COLUMN1 (5)
#define FRONT_COLUMN2 (6)
#define FRONT_ROW0_i (-1)
#define FRONT_ROW1_i (-2)
#define FRONT_ROW2_i (-3)
#define FRONT_COLUMN0_i (-4)
#define FRONT_COLUMN1_i (-5)
#define FRONT_COLUMN2_i (-6)
#define FRONT_ROW_CLOCKWISE (1) /* This is similar to U step */
#define FRONT_ROW_ANTI_CLOCKWISE (-1) /* This is similar to Ui step */
#define FRONT_COLUMN_CLOCKWISE (2) /* This is similar to R step */
#define FRONT_COLUMN_ANTI_CLOCKWISE (-2) /* This is similar to Ri step */

/* Cube rotation functions */
extern void R(void);
extern void Ri(void);
extern void L(void);
extern void Li(void);
extern void U(void);
extern void Ui(void);
extern void D(void);
extern void Di(void);
extern void F(void);
extern void Fi(void);
extern void B(void);
extern void Bi(void);
extern void r(void);
extern void ri(void);
extern void l(void);
extern void li(void);
extern void u(void);
extern void ui(void);
extern void d(void);
extern void di(void);
extern void f(void);
extern void fi(void);
extern void b(void);
extern void bi(void);
extern void X(void);
extern void Y(void);
extern void Z(void);
extern void Xi(void);
extern void Yi(void);
extern void Zi(void);

extern void up_line_move(int line);
extern void front_line_move(int line);

#endif