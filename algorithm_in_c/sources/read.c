#include "../includes/read.h"
#include "../includes/cube.h"
#include "../includes/colour.h"
#include "../includes/print.h"
#include <stdio.h>
#include <stdlib.h>

static int cursor_x, cursor_y;
static int row, column;
static int nullify;

static void read_back(void);
static void read_left(void);
static void read_up(void);
static void read_right(void);
static void read_down(void);
static void read_front(void);

void read_cube(void)
{
	cursor_x = 12;
	cursor_y = 11;

	/* Caution: Don't change the below calling order of functions */
	read_back();  /* Read BACK colours */
	read_left();  /* Read Left colours */
	read_up();	  /* Read UP colours */
	read_right(); /* Read Right colours */
	read_down();  /* Read Down colours */
	read_front(); /* Read Front colours */
}

static void read_back(void)
{
	for (row = SIDE_ROWS - 1; row >= 0; row--)
	{
		for (column = SIDE_COLUMNS - 1; column >= 0; column--)
		{
			MOVE_CURSOR(cursor_x, cursor_y);
			nullify = scanf(" %c", &cube.sides.back.colour[row][column]);

			/* Set opposite side's center to opposite colour of current center */
			if (!(row ^ 1) && !(column ^ 1))
			{
				cube.sides.front.colour[row][column] = opposite_colour(cube.sides.back.colour[row][column]);
			}

			if (cube.sides.back.colour[row][column] == 'x')
			{
				CLEAR_SCREEN;
				exit(0);
			}

			/* Entered input colour validation */
			if (!update_colour_count(cube.sides.back.colour[row][column]))
			{
				MOVE_CURSOR(27, 1);

				print_error("Invalid colour entered.Please enter valid colour");

				MOVE_CURSOR(cursor_x, cursor_y);
				SET_BLACK_COLOUR;
				printf(" ");
				RESET_COLOUR;

				MOVE_CURSOR(cursor_x, cursor_y);
				column++;
				continue;
			}

			update_cube_map();
			print_screen();
			cursor_y += 2;
		}
		cursor_x++;
		cursor_y = 11;
	}
}

static void read_left(void)
{
	cursor_x += 2;
	cursor_y = 2;
	for (column = 0; column < SIDE_COLUMNS; column++)
	{
		for (row = SIDE_ROWS - 1; row >= 0; row--)
		{
			MOVE_CURSOR(cursor_x, cursor_y);
			nullify = scanf(" %c", &cube.sides.left.colour[row][column]);

			/* Set opposite side's center to opposite colour of current center */
			if (!(row ^ 1) && !(column ^ 1))
			{
				cube.sides.right.colour[row][column] = opposite_colour(cube.sides.left.colour[row][column]);
			}

			if (cube.sides.left.colour[row][column] == 'x')
			{
				CLEAR_SCREEN;
				exit(0);
			}

			/* Entered input colour validation */
			if (!update_colour_count(cube.sides.left.colour[row][column]))
			{
				MOVE_CURSOR(27, 1);

				print_error("Invalid colour entered.Please enter valid colour");

				MOVE_CURSOR(cursor_x, cursor_y);
				SET_BLACK_COLOUR;
				printf(" ");
				RESET_COLOUR;

				MOVE_CURSOR(cursor_x, cursor_y);
				row++;
				continue;
			}

			update_cube_map();
			print_screen();
			cursor_y += 2;
		}
		cursor_x++;
		cursor_y = 2;
	}
}

static void read_up(void)
{
	cursor_x -= 3;
	cursor_y = 11;
	for (row = 0; row < SIDE_ROWS; row++)
	{
		for (column = 0; column < SIDE_COLUMNS; column++)
		{
			MOVE_CURSOR(cursor_x, cursor_y);
			nullify = scanf(" %c", &cube.sides.up.colour[row][column]);

			/* Set opposite side's center to opposite colour of current center */
			if (!(row ^ 1) && !(column ^ 1))
			{
				cube.sides.down.colour[row][column] = opposite_colour(cube.sides.up.colour[row][column]);
			}

			if (cube.sides.up.colour[row][column] == 'x')
			{
				CLEAR_SCREEN;
				exit(0);
			}

			/* Entered input colour validation */
			if (!update_colour_count(cube.sides.up.colour[row][column]))
			{
				MOVE_CURSOR(27, 1);

				print_error("Invalid colour entered.Please enter valid colour");

				MOVE_CURSOR(cursor_x, cursor_y);
				SET_BLACK_COLOUR;
				printf(" ");
				RESET_COLOUR;

				MOVE_CURSOR(cursor_x, cursor_y);
				column--;
				continue;
			}

			update_cube_map();
			print_screen();
			cursor_y += 2;
		}
		cursor_x++;
		cursor_y = 11;
	}
}

static void read_right(void)
{
	cursor_x -= 3;
	cursor_y = 20;
	for (column = SIDE_COLUMNS - 1; column >= 0; column--)
	{
		for (row = 0; row < SIDE_ROWS; row++)
		{
			/* Right center updated already in Left center reading */
			if (!(row ^ 1) && !(column ^ 1))
			{
				cursor_y += 2;
				continue;
			}

			MOVE_CURSOR(cursor_x, cursor_y);
			nullify = scanf(" %c", &cube.sides.right.colour[row][column]);

			if (cube.sides.right.colour[row][column] == 'x')
			{
				CLEAR_SCREEN;
				exit(0);
			}

			/* Entered input colour validation */
			if (!update_colour_count(cube.sides.right.colour[row][column]))
			{
				MOVE_CURSOR(27, 1);

				print_error("Invalid colour entered.Please enter valid colour");

				MOVE_CURSOR(cursor_x, cursor_y);
				SET_BLACK_COLOUR;
				printf(" ");
				RESET_COLOUR;

				MOVE_CURSOR(cursor_x, cursor_y);
				row--;
				continue;
			}

			update_cube_map();
			print_screen();
			cursor_y += 2;
		}
		cursor_x++;
		cursor_y = 20;
	}
}

static void read_down(void)
{
	cursor_x -= 3;
	cursor_y = 29;
	for (row = SIDE_ROWS - 1; row >= 0; row--)
	{
		for (column = SIDE_COLUMNS - 1; column >= 0; column--)
		{
			/* Down center updated already in Up center reading */
			if (!(row ^ 1) && !(column ^ 1))
			{
				cursor_y += 2;
				continue;
			}

			MOVE_CURSOR(cursor_x, cursor_y);
			nullify = scanf(" %c", &cube.sides.down.colour[row][column]);

			/* Set opposite side's center to opposite colour of current center */
			if (!(row ^ 1) && !(column ^ 1))
			{
				cube.sides.up.colour[row][column] = opposite_colour(cube.sides.down.colour[row][column]);
			}

			if (cube.sides.down.colour[row][column] == 'x')
			{
				CLEAR_SCREEN;
				exit(0);
			}

			/* Entered input colour validation */
			if (!update_colour_count(cube.sides.down.colour[row][column]))
			{
				MOVE_CURSOR(27, 1);

				print_error("Invalid colour entered.Please enter valid colour");

				MOVE_CURSOR(cursor_x, cursor_y);
				SET_BLACK_COLOUR;
				printf(" ");
				RESET_COLOUR;

				MOVE_CURSOR(cursor_x, cursor_y);
				column++;
				continue;
			}

			update_cube_map();
			print_screen();
			cursor_y += 2;
		}
		cursor_x++;
		cursor_y = 29;
	}
}

static void read_front(void)
{
	cursor_x += 3;
	cursor_y = 11;
	for (row = 0; row < SIDE_ROWS; row++)
	{
		for (column = 0; column < SIDE_COLUMNS; column++)
		{
			/* Front center updated already in Back center reading */
			if (!(row ^ 1) && !(column ^ 1))
			{
				cursor_y += 2;
				continue;
			}

			MOVE_CURSOR(cursor_x, cursor_y);
			nullify = scanf(" %c", &cube.sides.front.colour[row][column]);

			if (cube.sides.front.colour[row][column] == 'x')
			{
				CLEAR_SCREEN;
				exit(0);
			}

			/* Entered input colour validation */
			if (!update_colour_count(cube.sides.front.colour[row][column]))
			{
				MOVE_CURSOR(27, 1);

				print_error("Invalid colour entered.Please enter valid colour");

				MOVE_CURSOR(cursor_x, cursor_y);
				SET_BLACK_COLOUR;
				printf(" ");
				RESET_COLOUR;

				MOVE_CURSOR(cursor_x, cursor_y);
				column--;
				continue;
			}

			update_cube_map();
			print_screen();
			cursor_y += 2;
		}
		cursor_x++;
		cursor_y = 11;
	}
}
