#ifndef __PRINT_H
#define __PRINT_H

#include "types.h"

extern int input;

extern void print_back(void);
extern void print_front(void);
extern void print_lurd(void);
extern void print_colour(char colour, char *msg);
extern void print_error(char *msg);
extern void print_yellow_msg(char *title, char *msg);
extern void print_input_message(void);
extern void print_formula(void);
extern void print_cube(void);
extern void print_screen(void);
#endif