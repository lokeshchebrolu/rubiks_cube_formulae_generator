#include"../includes/cube.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

cube_t cube;
colour_count_t colour_count;

static int input;

static void update_cube_map(void);
static void print_back(void);
static void print_front(void);
static void print_lurd(void);
static int update_colour_count(char colour);

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

	/* Read BACK colours */
	cursor_x = 12; 
	cursor_y = 11;
	for(row=SIDE_ROWS-1;row>=0;row--)
	{
		for(column=SIDE_COLUMNS-1;column>=0;column--)
		{
			MOVE_CURSOR(cursor_x,cursor_y);
			scanf(" %c",&cube.sides.back.colour[row][column]);

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
			scanf(" %c",&cube.sides.left.colour[row][column]);
			
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
			scanf(" %c",&cube.sides.up.colour[row][column]);
			
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
			MOVE_CURSOR(cursor_x,cursor_y);
			scanf(" %c",&cube.sides.right.colour[row][column]);
			
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
			MOVE_CURSOR(cursor_x,cursor_y);
			scanf(" %c",&cube.sides.down.colour[row][column]);
			
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
			MOVE_CURSOR(cursor_x,cursor_y);
			scanf(" %c",&cube.sides.front.colour[row][column]);
			
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
	getchar();
	getchar();

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

int colour_count_valid_check(void)
{
	int valid = 1;
	if(colour_count.red<1 || colour_count.red>9)
	{
		printf("[ ");
		SET_FG_RED;
		printf("Error");
		RESET_COLOUR;
		printf(" ] : ");
		
		SET_FG_RED;
		printf("RED ");
		RESET_COLOUR;
		printf("colour count is wrongly entered as %d\n",colour_count.red);

		valid=0;
	}

	if(colour_count.green<1 || colour_count.green>9)
	{
		printf("[ ");
		SET_FG_RED;
		printf("Error");
		RESET_COLOUR;
		printf(" ] : ");
		
		SET_FG_GREEN;
		printf("GREEN ");
		RESET_COLOUR;
		printf("colour count is wrongly entered as %d\n",colour_count.green);

		valid=0;
	}

	if(colour_count.blue<1 || colour_count.blue>9)
	{
		printf("[ ");
		SET_FG_RED;
		printf("Error");
		RESET_COLOUR;
		printf(" ] : ");
		
		SET_FG_BLUE;
		printf("BLUE ");
		RESET_COLOUR;
		printf("colour count is wrongly entered as %d\n",colour_count.blue);

		valid=0;
	}

	if(colour_count.yellow<1 || colour_count.yellow>9)
	{
		printf("[ ");
		SET_FG_RED;
		printf("Error");
		RESET_COLOUR;
		printf(" ] : ");
		
		SET_FG_YELLOW;
		printf("YELLOW ");
		RESET_COLOUR;
		printf("colour count is wrongly entered as %d\n",colour_count.yellow);

		valid=0;
	}

	if(colour_count.orange<1 || colour_count.orange>9)
	{
		printf("[ ");
		SET_FG_RED;
		printf("Error");
		RESET_COLOUR;
		printf(" ] : ");
		
		SET_FG_ORANGE;
		printf("ORANGE ");
		RESET_COLOUR;
		printf("colour count is wrongly entered as %d\n",colour_count.orange);

		valid=0;
	}

	if(colour_count.white<1 || colour_count.white>9)
	{
		printf("[ ");
		SET_FG_RED;
		printf("Error");
		RESET_COLOUR;
		printf(" ] : ");
		
		SET_FG_WHITE;
		printf("WHITE ");
		RESET_COLOUR;
		printf("colour count is wrongly entered as %d\n",colour_count.white);

		valid=0;
	}


	return valid;

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


static void print_back(void)
{
	RESET_COLOUR;
	printf("%s",cube.cube_map[2]);

	for(int j=3;j<6;j++)
	{
		for(int i=0;i<strlen(cube.cube_map[j]);i++)
		{

			switch(cube.cube_map[j][i])
			{
				case RED:
					SET_RED_COLOUR;
					break;
				case GREEN:
					SET_GREEN_COLOUR;
					break;
				case BLUE:
					SET_BLUE_COLOUR;
					break;
				case ORANGE:
					SET_ORANGE_COLOUR;
					break;
				case WHITE:
					SET_WHITE_COLOUR;
					break;
				case YELLOW:
					SET_YELLOW_COLOUR;
					break;
				case BLACK:
					SET_BLACK_COLOUR;
					break;
				case ' ':
				case '\n':
					RESET_COLOUR;
					break;
			}
			if(cube.cube_map[j][i] == '\n')
				printf("\n");
			else
				printf(" ");
		}
	}
	RESET_COLOUR;
}


static void print_lurd(void)
{
	RESET_COLOUR;
	printf("%s%s",cube.cube_map[6],cube.cube_map[7]);

	for(int j=0;j<3;j++)
	{
		j += 8;
		for(int i=0;i<strlen(cube.cube_map[j]);i++)
		{
			switch(cube.cube_map[j][i])
			{
				case RED:
					SET_RED_COLOUR;
					break;
				case GREEN:
					SET_GREEN_COLOUR;
					break;
				case BLUE:
					SET_BLUE_COLOUR;
					break;
				case ORANGE:
					SET_ORANGE_COLOUR;
					break;
				case WHITE:
					SET_WHITE_COLOUR;
					break;
				case YELLOW:
					SET_YELLOW_COLOUR;
					break;
				case BLACK:
					SET_BLACK_COLOUR;
					break;
				case ' ':
				case '\n':
					RESET_COLOUR;
					break;
			}
			if(cube.cube_map[j][i] == '\n')
				printf("\n");
			else
				printf(" ");
		}
	}
	RESET_COLOUR;
}


static void print_front(void)
{
	RESET_COLOUR;
	printf("%s%s",cube.cube_map[11],cube.cube_map[12]);

	for(int j=13;j<16;j++)
	{
		for(int i=0;i<strlen(cube.cube_map[j]);i++)
		{
			switch(cube.cube_map[j][i])
			{
				case RED:
					SET_RED_COLOUR;
					break;
				case GREEN:
					SET_GREEN_COLOUR;
					break;
				case BLUE:
					SET_BLUE_COLOUR;
					break;
				case ORANGE:
					SET_ORANGE_COLOUR;
					break;
				case WHITE:
					SET_WHITE_COLOUR;
					break;
				case YELLOW:
					SET_YELLOW_COLOUR;
					break;
				case BLACK:
					SET_BLACK_COLOUR;
					break;
				case ' ':
				case '\n':
					RESET_COLOUR;
					break;
			}
			if(cube.cube_map[j][i] == '\n')
				printf("\n");
			else
				printf(" ");
		}
	}
	RESET_COLOUR;
}


static int update_colour_count(char colour)
{
	int valid=1;
	switch(colour)
	{
		case RED:
			colour_count.red++;
			break;
		
		case GREEN:
			colour_count.green++;
			break;
		
		case BLUE:
			colour_count.blue++;
			break;
		
		case ORANGE:
			colour_count.orange++;
			break;
		
		case WHITE:
			colour_count.white++;
			break;
		
		case YELLOW:
			colour_count.yellow++;
			break;

		default:
			valid=0;
			break;
	}

	return valid;
}








