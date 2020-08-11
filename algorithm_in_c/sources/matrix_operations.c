#include"../includes/matrix_operations.h"
#include"../includes/cube.h"
#include"../includes/types.h"

static void transpose(cube_side_t *side);
static void swap(char *val1,char *val2);

void rotate_clockwise(cube_side_t *side)
{
	transpose(side);

	/* Reverse rows elements */
	for(int i=0;i<SIDE_ROWS;i++)
	{
		for(int j=0,k=SIDE_COLUMNS-1; (j<k); j++,k--)
			swap(&side->colour[i][j],&side->colour[i][k]);
	}
}

void rotate_anti_clockwise(cube_side_t *side)
{
	transpose(side);

	/* Reverse rows elements */
	for(int i=0;i<SIDE_COLUMNS;i++)
	{
		for(int j=0,k=SIDE_ROWS-1; (j<k); j++,k--)
			swap(&side->colour[j][i],&side->colour[k][i]);
	}
}

void swap_matrices(cube_side_t *side1, cube_side_t *side2)
{
	for(int i=0;i<SIDE_ROWS;i++)
	{
		for(int j=0;j<SIDE_COLUMNS;j++)
			swap(&side1->colour[i][j],&side2->colour[i][j]);
	}
}

static void transpose(cube_side_t *side)
{
	for(int i=0;i<SIDE_ROWS;i++)
	{
		for(int j=i;j<SIDE_COLUMNS;j++)
		{
			swap(&side->colour[i][j],&side->colour[j][i]);
		}
	}

}

static void swap(char *val1,char *val2)
{
	char temp = *val1;
	*val1 = *val2;
	*val2 = temp;
}

