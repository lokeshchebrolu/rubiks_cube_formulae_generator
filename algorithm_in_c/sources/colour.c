#include"../includes/colour.h"
#include"../includes/movements.h"
#include"../includes/cube.h"
#include"../includes/matrix_operations.h"
#include<stdio.h>

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


int update_colour_count(char colour)
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

char opposite_colour(char c)
{
	char opp_colour='B';
	switch(c)
	{
		case RED:
			opp_colour = 'o';
			break;

		case GREEN:
			opp_colour = 'b';
			break;

		case BLUE:
			opp_colour = 'g';
			break;

		case ORANGE:
			opp_colour = 'r';
			break;

		case WHITE:
			opp_colour = 'y';
			break;

		case YELLOW:
			opp_colour = 'w';
			break;

		default:
			opp_colour = 'B';
			break;
	}
	return opp_colour;
}
