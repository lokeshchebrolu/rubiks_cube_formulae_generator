#include"../includes/cube.h"
#include<stdio.h>

cube_t cube;

static void reposition_cube(void);
static void swap(char *val1,char *val2);
static void print_back(void);
static void print_lurd(void);
static void print_front(void);

void cube_init(void)
{
	int side=0,row=0,column=0;

	printf("Colour codes :\n");
	printf(" WHITE   :  'w'\n");
	printf(" RED     :  'r'\n");
	printf(" GREEN   :  'g'\n");
	printf(" BLUE    :  'b'\n");
	printf(" YELLOW  :  'y'\n");
	printf(" ORANGE  :  'o'\n\n");

	/* Read cube colours */
	for(side=0;side<CUBE_SIDES;side++)
	{
		switch(side)
		{
			case FRONT:
				printf("Enter Front side colours:\n");
				break;

			case BACK:
				printf("Enter Back side colours:\n");
				break;

			case	LEFT:
				printf("Enter Left side colours:\n");
				break;

			case RIGHT:
				printf("Enter Right side colours:\n");
				break;

			case UP:
				printf("Enter Up side colours:\n");
				break;

			case DOWN:
				printf("Enter Down side colours:\n");
				break;
		}

		for(;row<(CUBE_SIZE*(side+1));row++)
		{
			for(column=0;column<SIDE_COLUMNS;column++)
			{
				scanf(" %c",&cube.cube_map[row][column]);
			}
		}
	}

	reposition_cube();
}

void cube_print(void)
{
	/* Clears screen */
	CLEAR_SCREEN;

	/* Set background to black for two lines */
	RESET_COLOUR;
	printf("\n");
	printf("   -- Cube current colours --\n\n");
	/* Print back */
	print_back();

	/* Print LEFT,UP,RIGHT,DOWN in order */
	print_lurd();

	/* Print front */
	print_front();

	RESET_COLOUR;
	printf("\n\n");
}

static void reposition_cube(void)
{
	/* Front no need any reposition */
	
	/* Up no need any reposition */
	
	/* Back reposition */
	for(int i=0,j=2,k=0;k<SIDE_COLUMNS;k++)
		swap(&cube.sides.back.colour[i][k],&cube.sides.back.colour[j][k]);
	for(int i=0,j=2,k=0;k<SIDE_COLUMNS;k++)
		swap(&cube.sides.back.colour[k][i],&cube.sides.back.colour[k][j]);
	
	/* Left reposition */
	for(int i=0,j=2,k=0;k<SIDE_COLUMNS;k++)
		swap(&cube.sides.left.colour[i][k],&cube.sides.left.colour[j][k]);
	for(int i=0,j=2,k=0;k<SIDE_COLUMNS;k++)
		swap(&cube.sides.left.colour[k][i],&cube.sides.left.colour[k][j]);

	/* Right reposition */
	for(int i=0,j=2,k=0;k<SIDE_COLUMNS;k++)
		swap(&cube.sides.right.colour[i][k],&cube.sides.right.colour[j][k]);
	for(int i=0,j=2,k=0;k<SIDE_COLUMNS;k++)
		swap(&cube.sides.right.colour[k][i],&cube.sides.right.colour[k][j]);

	/* Down reposition */
	for(int i=0,j=2,k=0;k<SIDE_COLUMNS;k++)
		swap(&cube.sides.down.colour[i][k],&cube.sides.down.colour[j][k]);
	for(int i=0,j=2,k=0;k<SIDE_COLUMNS;k++)
		swap(&cube.sides.down.colour[k][i],&cube.sides.down.colour[k][j]);

}

static void swap(char *val1,char *val2)
{
	char c = *val1;
	*val1 = *val2;
	*val2 = c;
}

static void print_back(void)
{
	printf("           BACK\n");
	for(int i=0;i<SIDE_ROWS;i++)
	{
		RESET_COLOUR;
		printf("          ");

		for(int j=0;j<SIDE_COLUMNS;j++)
		{
			switch(cube.sides.back.colour[i][j])
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
					SET_MAGENTA_COLOUR;
					break;
				case WHITE:
					SET_WHITE_COLOUR;
					break;
				case YELLOW:
					SET_YELLOW_COLOUR;
					break;
			}
			printf("  ");
		}
		RESET_COLOUR;
		printf("\n");
	}
	RESET_COLOUR;
	printf("\n");
}


static void print_lurd(void)
{
	RESET_COLOUR;
	printf("  LEFT      UP      RIGHT    DOWN \n");
	for(int i=0;i<SIDE_ROWS;i++)
	{
		RESET_COLOUR;
		printf(" ");

		/* Left */
		for(int j=0;j<SIDE_COLUMNS;j++)
		{
			switch(cube.sides.left.colour[i][j])
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
					SET_MAGENTA_COLOUR;
					break;
				case WHITE:
					SET_WHITE_COLOUR;
					break;
				case YELLOW:
					SET_YELLOW_COLOUR;
					break;
			}
			printf("  ");
		}
		RESET_COLOUR;
		printf("   ");

		/* Up */
		for(int j=0;j<SIDE_COLUMNS;j++)
		{
			switch(cube.sides.up.colour[i][j])
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
					SET_MAGENTA_COLOUR;
					break;
				case WHITE:
					SET_WHITE_COLOUR;
					break;
				case YELLOW:
					SET_YELLOW_COLOUR;
					break;
			}
			printf("  ");
		}
		RESET_COLOUR;
		printf("   ");

		/* right */
		for(int j=0;j<SIDE_COLUMNS;j++)
		{
			switch(cube.sides.right.colour[i][j])
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
					SET_MAGENTA_COLOUR;
					break;
				case WHITE:
					SET_WHITE_COLOUR;
					break;
				case YELLOW:
					SET_YELLOW_COLOUR;
					break;
			}
			printf("  ");
		}
		RESET_COLOUR;
		printf("   ");


		/* Down */
		for(int j=0;j<SIDE_COLUMNS;j++)
		{
			switch(cube.sides.down.colour[i][j])
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
					SET_MAGENTA_COLOUR;
					break;
				case WHITE:
					SET_WHITE_COLOUR;
					break;
				case YELLOW:
					SET_YELLOW_COLOUR;
					break;
			}
			printf("  ");
		}
		RESET_COLOUR;
		printf("   ");
		printf("\n");
	}
	RESET_COLOUR;
	printf("\n");
}


static void print_front(void)
{
	printf("          FRONT\n");
	for(int i=0;i<SIDE_ROWS;i++)
	{
		RESET_COLOUR;
		printf("          ");

		for(int j=0;j<SIDE_COLUMNS;j++)
		{
			switch(cube.sides.front.colour[i][j])
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
					SET_MAGENTA_COLOUR;
					break;
				case WHITE:
					SET_WHITE_COLOUR;
					break;
				case YELLOW:
					SET_YELLOW_COLOUR;
					break;
			}
			printf("  ");
		}
		RESET_COLOUR;
		printf("\n");
	}
	RESET_COLOUR;
	printf("\n");
}










