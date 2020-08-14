#include"../includes/cube.h"
#include"../includes/matrix_operations.h"
#include"../includes/movements.h"
#include"../includes/colour.h"
#include"../includes/print.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

cube_t cube;
colour_count_t colour_count;

static int input;
static int nullify;
static formula_t formula;

static void update_cube_map(void);
static void apply_formula(formula_t fr);

void temp_cube_init(void)
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			cube.sides.front.colour[i][j] = 'y';
	}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			cube.sides.back.colour[i][j] = 'w';
	}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			cube.sides.left.colour[i][j] = 'b';
	}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			cube.sides.right.colour[i][j] = 'g';
	}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			cube.sides.up.colour[i][j] = 'o';
	}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			cube.sides.down.colour[i][j] = 'r';
	}
}

void cube_init(void)
{
	int row=0,column=0;
	int cursor_x,cursor_y;

	colour_count.white = 0;
	colour_count.red = 0;
	colour_count.green = 0;
	colour_count.blue = 0;
	colour_count.yellow = 0;
	colour_count.orange = 0;

	/* Init cube with black colour */
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			cube.sides.front.colour[i][j] = 'B';
	}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			cube.sides.back.colour[i][j] = 'B';
	}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			cube.sides.left.colour[i][j] = 'B';
	}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			cube.sides.right.colour[i][j] = 'B';
	}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			cube.sides.up.colour[i][j] = 'B';
	}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			cube.sides.down.colour[i][j] = 'B';
	}
	update_cube_map();
	/******************************/

	input=1;
	cube_print();

	/* Read cube colours */
	/****************************** Test *************************************
	temp_cube_init();
	formula.step_count = 6;
	formula.steps = (step_t*)calloc(formula.step_count,sizeof(step_t));
	strcpy(formula.steps[0].step,"X");
	strcpy(formula.steps[1].step,"Xi");
	strcpy(formula.steps[2].step,"Y");
	strcpy(formula.steps[3].step,"Yi");
	strcpy(formula.steps[4].step,"Z");
	strcpy(formula.steps[5].step,"Zi");

	apply_formula(formula);
	**************************************************************************/
	/* Read BACK colours */
	cursor_x = 12; 
	cursor_y = 11;
	for(row=SIDE_ROWS-1;row>=0;row--)
	{
		for(column=SIDE_COLUMNS-1;column>=0;column--)
		{
			MOVE_CURSOR(cursor_x,cursor_y);
			nullify = scanf(" %c",&cube.sides.back.colour[row][column]);

			/* Set opposite side's center to opposite colour of current center */
			if(!(row^1)&&!(column^1))
			{
				cube.sides.front.colour[row][column] = opposite_colour(cube.sides.back.colour[row][column]);
			}

			if(cube.sides.back.colour[row][column] == 'x')
			{
				CLEAR_SCREEN;
				exit(0);
			}

			/* Entered input colour validation */
			if(!update_colour_count(cube.sides.back.colour[row][column]))
			{
				MOVE_CURSOR(27,1);

				printf("[ ");
				SET_FG_RED;
				printf("Error");
				RESET_COLOUR;
				printf(" ] : Invalid colour entered.Please enter valid colour");

				MOVE_CURSOR(cursor_x,cursor_y);
				SET_BLACK_COLOUR;
				printf(" ");
				RESET_COLOUR;

				MOVE_CURSOR(cursor_x,cursor_y);
				column++;
				continue;
			}

			update_cube_map();
			cube_print();
			cursor_y += 2;
		}
		cursor_x++;
		cursor_y = 11;
	}

	/* Read Left colours */
	cursor_x += 2;
	cursor_y = 2;
	for(column=0;column<SIDE_COLUMNS;column++)
	{
		for(row=SIDE_ROWS-1;row>=0;row--)
		{
			MOVE_CURSOR(cursor_x,cursor_y);
			nullify = scanf(" %c",&cube.sides.left.colour[row][column]);

			/* Set opposite side's center to opposite colour of current center */
			if(!(row^1)&&!(column^1))
			{
				cube.sides.right.colour[row][column] = opposite_colour(cube.sides.left.colour[row][column]);
			}

			if(cube.sides.left.colour[row][column] == 'x')
			{
				CLEAR_SCREEN;
				exit(0);
			}

			/* Entered input colour validation */
			if(!update_colour_count(cube.sides.left.colour[row][column]))
			{
				MOVE_CURSOR(27,1);

				printf("[ ");
				SET_FG_RED;
				printf("Error");
				RESET_COLOUR;
				printf(" ] : Invalid colour entered.Please enter valid colour");

				MOVE_CURSOR(cursor_x,cursor_y);
				SET_BLACK_COLOUR;
				printf(" ");
				RESET_COLOUR;

				MOVE_CURSOR(cursor_x,cursor_y);
				row++;
				continue;
			}

			update_cube_map();
			cube_print();
			cursor_y += 2;
		}
		cursor_x++;
		cursor_y = 2;
	}

	/* Read UP colours */
	cursor_x -= 3;
	cursor_y = 11;
	for(row=0;row<SIDE_ROWS;row++)
	{
		for(column=0;column<SIDE_COLUMNS;column++)
		{
			MOVE_CURSOR(cursor_x,cursor_y);
			nullify = scanf(" %c",&cube.sides.up.colour[row][column]);

			/* Set opposite side's center to opposite colour of current center */
			if(!(row^1)&&!(column^1))
			{
				cube.sides.down.colour[row][column] = opposite_colour(cube.sides.up.colour[row][column]);
			}

			if(cube.sides.up.colour[row][column] == 'x')
			{
				CLEAR_SCREEN;
				exit(0);
			}

			/* Entered input colour validation */
			if(!update_colour_count(cube.sides.up.colour[row][column]))
			{
				MOVE_CURSOR(27,1);

				printf("[ ");
				SET_FG_RED;
				printf("Error");
				RESET_COLOUR;
				printf(" ] : Invalid colour entered.Please enter valid colour");

				MOVE_CURSOR(cursor_x,cursor_y);
				SET_BLACK_COLOUR;
				printf(" ");
				RESET_COLOUR;

				MOVE_CURSOR(cursor_x,cursor_y);
				column--;
				continue;
			}

			update_cube_map();
			cube_print();
			cursor_y += 2;
		}
		cursor_x++;
		cursor_y = 11;
	}

	/* Read Right colours */
	cursor_x -= 3;
	cursor_y = 20;
	for(column=SIDE_COLUMNS-1;column>=0;column--)
	{
		for(row=0;row<SIDE_ROWS;row++)
		{
			/* Right center updated already in Left center reading */
			if(!(row^1)&&!(column^1))
			{
				cursor_y += 2;
				continue;
			}

			MOVE_CURSOR(cursor_x,cursor_y);
			nullify = scanf(" %c",&cube.sides.right.colour[row][column]);

			if(cube.sides.right.colour[row][column] == 'x')
			{
				CLEAR_SCREEN;
				exit(0);
			}

			/* Entered input colour validation */
			if(!update_colour_count(cube.sides.right.colour[row][column]))
			{
				MOVE_CURSOR(27,1);

				printf("[ ");
				SET_FG_RED;
				printf("Error");
				RESET_COLOUR;
				printf(" ] : Invalid colour entered.Please enter valid colour");

				MOVE_CURSOR(cursor_x,cursor_y);
				SET_BLACK_COLOUR;
				printf(" ");
				RESET_COLOUR;

				MOVE_CURSOR(cursor_x,cursor_y);
				row--;
				continue;
			}

			update_cube_map();
			cube_print();
			cursor_y += 2;
		}
		cursor_x++;
		cursor_y = 20;
	}

	/* Read Down colours */
	cursor_x -= 3;
	cursor_y = 29;
	for(row=SIDE_ROWS-1;row>=0;row--)
	{
		for(column=SIDE_COLUMNS-1;column>=0;column--)
		{
			/* Down center updated already in Up center reading */
			if(!(row^1)&&!(column^1))
			{
				cursor_y += 2;
				continue;
			}

			MOVE_CURSOR(cursor_x,cursor_y);
			nullify = scanf(" %c",&cube.sides.down.colour[row][column]);

			/* Set opposite side's center to opposite colour of current center */
			if(!(row^1)&&!(column^1))
			{
				cube.sides.up.colour[row][column] = opposite_colour(cube.sides.down.colour[row][column]);
			}

			if(cube.sides.down.colour[row][column] == 'x')
			{
				CLEAR_SCREEN;
				exit(0);
			}

			/* Entered input colour validation */
			if(!update_colour_count(cube.sides.down.colour[row][column]))
			{
				MOVE_CURSOR(27,1);

				printf("[ ");
				SET_FG_RED;
				printf("Error");
				RESET_COLOUR;
				printf(" ] : Invalid colour entered.Please enter valid colour");

				MOVE_CURSOR(cursor_x,cursor_y);
				SET_BLACK_COLOUR;
				printf(" ");
				RESET_COLOUR;

				MOVE_CURSOR(cursor_x,cursor_y);
				column++;
				continue;
			}

			update_cube_map();
			cube_print();
			cursor_y += 2;
		}
		cursor_x++;
		cursor_y = 29;
	}

	/* Read Front colours */
	cursor_x += 3;
	cursor_y = 11;
	for(row=0;row<SIDE_ROWS;row++)
	{
		for(column=0;column<SIDE_COLUMNS;column++)
		{
			/* Front center updated already in Back center reading */
			if(!(row^1)&&!(column^1))
			{
				cursor_y += 2;
				continue;
			}

			MOVE_CURSOR(cursor_x,cursor_y);
			nullify = scanf(" %c",&cube.sides.front.colour[row][column]);

			if(cube.sides.front.colour[row][column] == 'x')
			{
				CLEAR_SCREEN;
				exit(0);
			}

			/* Entered input colour validation */
			if(!update_colour_count(cube.sides.front.colour[row][column]))
			{
				MOVE_CURSOR(27,1);

				printf("[ ");
				SET_FG_RED;
				printf("Error");
				RESET_COLOUR;
				printf(" ] : Invalid colour entered.Please enter valid colour");

				MOVE_CURSOR(cursor_x,cursor_y);
				SET_BLACK_COLOUR;
				printf(" ");
				RESET_COLOUR;

				MOVE_CURSOR(cursor_x,cursor_y);
				column--;
				continue;
			}

			update_cube_map();
			cube_print();
			cursor_y += 2;
		}
		cursor_x++;
		cursor_y = 11;
	}

	input=0;

	formula.step_count = 2;
	formula.steps = (step_t*)calloc(formula.step_count,sizeof(step_t));
	strcpy(formula.steps[6].step,"B");
	strcpy(formula.steps[7].step,"Bi");

	apply_formula(formula);

}

void cube_print(void)
{
	/* Clears screen */
	CLEAR_SCREEN;

	if(input)
	{
		printf("Colour codes :\n");
		SET_FG_WHITE;
		printf(" WHITE   :  'w'");
		RESET_COLOUR;		
		printf("<enter>\n");

		SET_FG_RED;
		printf(" RED     :  'r'");
		RESET_COLOUR;		
		printf("<enter>\n");

		SET_FG_GREEN;
		printf(" GREEN   :  'g'");
		RESET_COLOUR;		
		printf("<enter>\n");

		SET_FG_BLUE;
		printf(" BLUE    :  'b'");
		RESET_COLOUR;		
		printf("<enter>\n");

		SET_FG_YELLOW;
		printf(" YELLOW  :  'y'");
		RESET_COLOUR;		
		printf("<enter>\n");

		SET_FG_ORANGE;
		printf(" ORANGE  :  'o'");
		RESET_COLOUR;		
		printf("<enter>\n");

		printf(" EXIT    :  'x'<enter>\n");
	}

	/* Set background to black for two lines */
	printf("%s%s",cube.cube_map[0],cube.cube_map[1]);
	/* Print back */
	print_back();

	/* Print LEFT,UP,RIGHT,DOWN in order */
	print_lurd();

	/* Print front */
	print_front();

	RESET_COLOUR;
	printf("\n\n");
}


static void update_cube_map(void) 
{
	/* Line 01 */sprintf(cube.cube_map[0],"   -- Cube current colours --\n");

	/* Line 02 */cube.cube_map[1][0] = '\n';

	/* Line 03 */sprintf(cube.cube_map[2],"           BACK\n");

	/* Line 04 */sprintf(cube.cube_map[3],"          %c%c%c%c%c%c\n",
			cube.sides.back.colour[2][2],/* Back side line 1 */
			cube.sides.back.colour[2][2],
			cube.sides.back.colour[2][1],
			cube.sides.back.colour[2][1],
			cube.sides.back.colour[2][0],
			cube.sides.back.colour[2][0]);

	/* Line 05 */sprintf(cube.cube_map[4],"          %c%c%c%c%c%c\n",
			cube.sides.back.colour[1][2],/* Back side line 2 */
			cube.sides.back.colour[1][2],
			cube.sides.back.colour[1][1],
			cube.sides.back.colour[1][1],
			cube.sides.back.colour[1][0],
			cube.sides.back.colour[1][0]);

	/* Line 06 */sprintf(cube.cube_map[5],"          %c%c%c%c%c%c\n",
			cube.sides.back.colour[0][2],/* Back side line 3 */
			cube.sides.back.colour[0][2],
			cube.sides.back.colour[0][1],
			cube.sides.back.colour[0][1],
			cube.sides.back.colour[0][0],
			cube.sides.back.colour[0][0]);

	/* Line 07 */cube.cube_map[6][0] = '\n';

	/* Line 08 */sprintf(cube.cube_map[7],"  LEFT      UP      RIGHT    DOWN\n");

	/* Line 09 */
	sprintf(cube.cube_map[8]," %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c\n",
			cube.sides.left.colour[2][0],cube.sides.left.colour[2][0],cube.sides.left.colour[1][0],
			cube.sides.left.colour[1][0],cube.sides.left.colour[0][0],cube.sides.left.colour[0][0],
			cube.sides.up.colour[0][0],cube.sides.up.colour[0][0],cube.sides.up.colour[0][1],
			cube.sides.up.colour[0][1],cube.sides.up.colour[0][2],cube.sides.up.colour[0][2],
			cube.sides.right.colour[0][2],cube.sides.right.colour[0][2],cube.sides.right.colour[1][2],
			cube.sides.right.colour[1][2],cube.sides.right.colour[2][2],cube.sides.right.colour[2][2],
			cube.sides.down.colour[2][2],cube.sides.down.colour[2][2],cube.sides.down.colour[2][1],
			cube.sides.down.colour[2][1],cube.sides.down.colour[2][0],cube.sides.down.colour[2][0]);

	/* Line 10 */
	sprintf(cube.cube_map[9]," %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c\n",
			cube.sides.left.colour[2][1],cube.sides.left.colour[2][1],cube.sides.left.colour[1][1],
			cube.sides.left.colour[1][1],cube.sides.left.colour[0][1],cube.sides.left.colour[0][1],
			cube.sides.up.colour[1][0],cube.sides.up.colour[1][0],cube.sides.up.colour[1][1],
			cube.sides.up.colour[1][1],cube.sides.up.colour[1][2],cube.sides.up.colour[1][2],
			cube.sides.right.colour[0][1],cube.sides.right.colour[0][1],cube.sides.right.colour[1][1],
			cube.sides.right.colour[1][1],cube.sides.right.colour[2][1],cube.sides.right.colour[2][1],
			cube.sides.down.colour[1][2],cube.sides.down.colour[1][2],cube.sides.down.colour[1][1],
			cube.sides.down.colour[1][1],cube.sides.down.colour[1][0],cube.sides.down.colour[1][0]);

	/* Line 11 */
	sprintf(cube.cube_map[10]," %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c\n",
			cube.sides.left.colour[2][2],cube.sides.left.colour[2][2],cube.sides.left.colour[1][2],
			cube.sides.left.colour[1][2],cube.sides.left.colour[0][2],cube.sides.left.colour[0][2],
			cube.sides.up.colour[2][0],cube.sides.up.colour[2][0],cube.sides.up.colour[2][1],
			cube.sides.up.colour[2][1],cube.sides.up.colour[2][2],cube.sides.up.colour[2][2],
			cube.sides.right.colour[0][0],cube.sides.right.colour[0][0],cube.sides.right.colour[1][0],
			cube.sides.right.colour[1][0],cube.sides.right.colour[2][0],cube.sides.right.colour[2][0],
			cube.sides.down.colour[0][2],cube.sides.down.colour[0][2],cube.sides.down.colour[0][1],
			cube.sides.down.colour[0][1],cube.sides.down.colour[0][0],cube.sides.down.colour[0][0]);

	/* Line 12 */cube.cube_map[11][0] = '\n';

	/* Line 13 */sprintf(cube.cube_map[12],"           FRONT\n");

	/* Line 14 */sprintf(cube.cube_map[13],"          %c%c%c%c%c%c\n",
			cube.sides.front.colour[0][0],/* Front side line 1 */
			cube.sides.front.colour[0][0],
			cube.sides.front.colour[0][1],
			cube.sides.front.colour[0][1],
			cube.sides.front.colour[0][2],
			cube.sides.front.colour[0][2]);

	/* Line 15 */sprintf(cube.cube_map[14],"          %c%c%c%c%c%c\n",
			cube.sides.front.colour[1][0],/* Front side line 2 */
			cube.sides.front.colour[1][0],
			cube.sides.front.colour[1][1],
			cube.sides.front.colour[1][1],
			cube.sides.front.colour[1][2],
			cube.sides.front.colour[1][2]);

	/* Line 16 */sprintf(cube.cube_map[15],"          %c%c%c%c%c%c\n",
			cube.sides.front.colour[2][0],/* Front side line 3 */
			cube.sides.front.colour[2][0],
			cube.sides.front.colour[2][1],
			cube.sides.front.colour[2][1],
			cube.sides.front.colour[2][2],
			cube.sides.front.colour[2][2]);
} 


static void apply_formula(formula_t fr)
{
	char temp_step[3];
	for(int i=0;i<fr.step_count;i++)
	{
		strcpy(temp_step,fr.steps[i].step);
		printf("%s\n",temp_step);
		getchar();
		switch(temp_step[0])
		{
			case 'R' :
				if(IS_INVERSE)
				{
					Ri();
				}
				else
				{
					R();
				}
				break;
			
			case 'L' :
				if(IS_INVERSE)
				{
					Li();
				}
				else
				{
					L();
				}
				break;
			
			case 'U' :
				if(IS_INVERSE)
				{
					Ui();
				}
				else
				{
					U();
				}
				break;
			
			case 'D' :
				if(IS_INVERSE)
				{
					Di();
				}
				else
				{
					D();
				}
				break;
			
			case 'F' :
				if(IS_INVERSE)
				{
					Fi();
				}
				else
				{
					F();
				}
				break;
			
			case 'B' :
				if(IS_INVERSE)
				{
					Bi();
				}
				else
				{
					B();
				}
				break;
			
			case 'r' :
				if(IS_INVERSE)
				{
					ri();
				}
				else
				{
					r();
				}
				break;
			
			case 'l' :
				if(IS_INVERSE)
				{
					li();
				}
				else
				{
					l();
				}
				break;
			
			case 'u' :
				if(IS_INVERSE)
				{
					ui();
				}
				else
				{
					u();
				}
				break;
			
			case 'd' :
				if(IS_INVERSE)
				{
					di();
				}
				else
				{
					d();
				}
				break;
			
			case 'f' :
				if(IS_INVERSE)
				{
					fi();
				}
				else
				{
					f();
				}
				break;
			
			case 'b' :
				if(IS_INVERSE)
				{
					bi();
				}
				else
				{
					b();
				}
				break;
			
			case 'X' :
				if(IS_INVERSE)
				{
					Xi();
				}
				else
				{
					X();
				}
				break;
			
			case 'Y' :
				if(IS_INVERSE)
				{
					Yi();
				}
				else
				{
					Y();
				}
				break;
			
			case 'Z' :
				if(IS_INVERSE)
				{
					Zi();
				}
				else
				{
					Z();
				}
				break;
			
			default:
				printf("[ ");
				SET_FG_RED;
				printf("Error");
				RESET_COLOUR;
				printf(" ] : Invalid step in formula\n");
				break;

		}
		update_cube_map();
		cube_print();
	}
}

