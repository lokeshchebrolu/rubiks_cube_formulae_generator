#include"../includes/print.h"
#include"../includes/colour.h"
#include"../includes/cube.h"
#include<stdio.h>
#include<string.h>

void print_back(void)
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


void print_lurd(void)
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


void print_front(void)
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