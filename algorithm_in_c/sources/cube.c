#include "../includes/cube.h"
#include "../includes/matrix_operations.h"
#include "../includes/movements.h"
#include "../includes/colour.h"
#include "../includes/print.h"
#include "../includes/read.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

cube_t cube;
colour_count_t colour_count;
formula_t *formula;
int formula_to_apply = 0;
int formula_count = 0;

static cube_t cube_local;

static void update_cube_local(void);
static int validate_step(char *step);
static void formulae_update_step(char *step);
static void apply_formula(void);
static int search_edge_colour_of_side(int side, char colour_main, char colour_pair);
static void cube_init_temp_colour(void);

void cube_init(void)
{

	colour_count.white = 0;
	colour_count.red = 0;
	colour_count.green = 0;
	colour_count.blue = 0;
	colour_count.yellow = 0;
	colour_count.orange = 0;

	/* Init cube with black colour */
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cube.sides.front.colour[i][j] = 'B';
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cube.sides.back.colour[i][j] = 'B';
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cube.sides.left.colour[i][j] = 'B';
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cube.sides.right.colour[i][j] = 'B';
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cube.sides.up.colour[i][j] = 'B';
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cube.sides.down.colour[i][j] = 'B';
	}
	update_cube_map();
	/******************************/

	input = 1;
	print_screen();

	/* Read cube colours */
	/*cube_init_temp_colour();
	update_cube_map();
	print_screen();*/
	read_cube();

	input = 0;
}

void update_cube_map(void)
{
	/* Line 01 */ sprintf(cube.cube_map[0], "   -- Cube current colours --\n");

	/* Line 02 */ cube.cube_map[1][0] = '\n';

	/* Line 03 */ sprintf(cube.cube_map[2], "           BACK\n");

	/* Line 04 */ sprintf(cube.cube_map[3], "          %c%c%c%c%c%c\n",
						  cube.sides.back.colour[2][2], /* Back side line 1 */
						  cube.sides.back.colour[2][2],
						  cube.sides.back.colour[2][1],
						  cube.sides.back.colour[2][1],
						  cube.sides.back.colour[2][0],
						  cube.sides.back.colour[2][0]);

	/* Line 05 */ sprintf(cube.cube_map[4], "          %c%c%c%c%c%c\n",
						  cube.sides.back.colour[1][2], /* Back side line 2 */
						  cube.sides.back.colour[1][2],
						  cube.sides.back.colour[1][1],
						  cube.sides.back.colour[1][1],
						  cube.sides.back.colour[1][0],
						  cube.sides.back.colour[1][0]);

	/* Line 06 */ sprintf(cube.cube_map[5], "          %c%c%c%c%c%c\n",
						  cube.sides.back.colour[0][2], /* Back side line 3 */
						  cube.sides.back.colour[0][2],
						  cube.sides.back.colour[0][1],
						  cube.sides.back.colour[0][1],
						  cube.sides.back.colour[0][0],
						  cube.sides.back.colour[0][0]);

	/* Line 07 */ cube.cube_map[6][0] = '\n';

	/* Line 08 */ sprintf(cube.cube_map[7], "  LEFT      UP      RIGHT    DOWN\n");

	/* Line 09 */
	sprintf(cube.cube_map[8], " %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c\n",
			cube.sides.left.colour[2][0], cube.sides.left.colour[2][0], cube.sides.left.colour[1][0],
			cube.sides.left.colour[1][0], cube.sides.left.colour[0][0], cube.sides.left.colour[0][0],
			cube.sides.up.colour[0][0], cube.sides.up.colour[0][0], cube.sides.up.colour[0][1],
			cube.sides.up.colour[0][1], cube.sides.up.colour[0][2], cube.sides.up.colour[0][2],
			cube.sides.right.colour[0][2], cube.sides.right.colour[0][2], cube.sides.right.colour[1][2],
			cube.sides.right.colour[1][2], cube.sides.right.colour[2][2], cube.sides.right.colour[2][2],
			cube.sides.down.colour[2][2], cube.sides.down.colour[2][2], cube.sides.down.colour[2][1],
			cube.sides.down.colour[2][1], cube.sides.down.colour[2][0], cube.sides.down.colour[2][0]);

	/* Line 10 */
	sprintf(cube.cube_map[9], " %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c\n",
			cube.sides.left.colour[2][1], cube.sides.left.colour[2][1], cube.sides.left.colour[1][1],
			cube.sides.left.colour[1][1], cube.sides.left.colour[0][1], cube.sides.left.colour[0][1],
			cube.sides.up.colour[1][0], cube.sides.up.colour[1][0], cube.sides.up.colour[1][1],
			cube.sides.up.colour[1][1], cube.sides.up.colour[1][2], cube.sides.up.colour[1][2],
			cube.sides.right.colour[0][1], cube.sides.right.colour[0][1], cube.sides.right.colour[1][1],
			cube.sides.right.colour[1][1], cube.sides.right.colour[2][1], cube.sides.right.colour[2][1],
			cube.sides.down.colour[1][2], cube.sides.down.colour[1][2], cube.sides.down.colour[1][1],
			cube.sides.down.colour[1][1], cube.sides.down.colour[1][0], cube.sides.down.colour[1][0]);

	/* Line 11 */
	sprintf(cube.cube_map[10], " %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c\n",
			cube.sides.left.colour[2][2], cube.sides.left.colour[2][2], cube.sides.left.colour[1][2],
			cube.sides.left.colour[1][2], cube.sides.left.colour[0][2], cube.sides.left.colour[0][2],
			cube.sides.up.colour[2][0], cube.sides.up.colour[2][0], cube.sides.up.colour[2][1],
			cube.sides.up.colour[2][1], cube.sides.up.colour[2][2], cube.sides.up.colour[2][2],
			cube.sides.right.colour[0][0], cube.sides.right.colour[0][0], cube.sides.right.colour[1][0],
			cube.sides.right.colour[1][0], cube.sides.right.colour[2][0], cube.sides.right.colour[2][0],
			cube.sides.down.colour[0][2], cube.sides.down.colour[0][2], cube.sides.down.colour[0][1],
			cube.sides.down.colour[0][1], cube.sides.down.colour[0][0], cube.sides.down.colour[0][0]);

	/* Line 12 */ cube.cube_map[11][0] = '\n';

	/* Line 13 */ sprintf(cube.cube_map[12], "           FRONT\n");

	/* Line 14 */ sprintf(cube.cube_map[13], "          %c%c%c%c%c%c\n",
						  cube.sides.front.colour[0][0], /* Front side line 1 */
						  cube.sides.front.colour[0][0],
						  cube.sides.front.colour[0][1],
						  cube.sides.front.colour[0][1],
						  cube.sides.front.colour[0][2],
						  cube.sides.front.colour[0][2]);

	/* Line 15 */ sprintf(cube.cube_map[14], "          %c%c%c%c%c%c\n",
						  cube.sides.front.colour[1][0], /* Front side line 2 */
						  cube.sides.front.colour[1][0],
						  cube.sides.front.colour[1][1],
						  cube.sides.front.colour[1][1],
						  cube.sides.front.colour[1][2],
						  cube.sides.front.colour[1][2]);

	/* Line 16 */ sprintf(cube.cube_map[15], "          %c%c%c%c%c%c\n",
						  cube.sides.front.colour[2][0], /* Front side line 3 */
						  cube.sides.front.colour[2][0],
						  cube.sides.front.colour[2][1],
						  cube.sides.front.colour[2][1],
						  cube.sides.front.colour[2][2],
						  cube.sides.front.colour[2][2]);
}

void cube_solve(void)
{
	int cube_solved = 0;
	
	cube_stages_t stage = ANALYSE;
	up_edges_t stage1_substage_1 = UP_01;

	int analysis_completed = 0;
	int stage1_completed = 0;
	int stage2_completed = 0;
	int stage3_completed = 0;
	int stage4_completed = 0;

	int cross_complete = 0;

	char blue_side;
	char white_side;
	char red_side;
	char orange_side;
	char green_side;
	char yellow_side;

	formula_to_apply = 1;

	update_cube_local();

	while (!cube_solved)
	{
		switch (stage)
		{
		case ANALYSE:
			white_side = side_of_center_colour(WHITE);
			/* Move white side to UP */
			switch (white_side)
			{
			case FRONT:
				formulae_update_step(START_FORMULA);
				formulae_update_step("X");
				formulae_update_step(END_FORMULA);
				break;

			case BACK:
				formulae_update_step(START_FORMULA);
				formulae_update_step("Xi");
				formulae_update_step(END_FORMULA);
				break;

			case LEFT:
				formulae_update_step(START_FORMULA);
				formulae_update_step("Z");
				formulae_update_step(END_FORMULA);
				break;

			case RIGHT:
				formulae_update_step(START_FORMULA);
				formulae_update_step("Zi");
				formulae_update_step(END_FORMULA);
				break;

			case DOWN:
				formulae_update_step(START_FORMULA);
				formulae_update_step("X");
				formulae_update_step("X");
				formulae_update_step(END_FORMULA);
				break;

			case UP:
				/* In Position */
				break;
			}
			print_screen();
			apply_formula();
			getchar();

			blue_side = side_of_center_colour(BLUE);
			/* Move blue to back */
			switch (white_side)
			{
			case FRONT:
				formulae_update_step(START_FORMULA);
				formulae_update_step("d");
				formulae_update_step("d");
				formulae_update_step(END_FORMULA);
				break;

			case BACK:
				/* In position */
				break;

			case LEFT:
				formulae_update_step(START_FORMULA);
				formulae_update_step("di");
				formulae_update_step(END_FORMULA);
				break;

			case RIGHT:
				formulae_update_step(START_FORMULA);
				formulae_update_step("d");
				formulae_update_step(END_FORMULA);
				break;

			case DOWN:
				/* Invalid case */
				break;

			case UP:
				/* Do nothing */
				break;
			}

			red_side = side_of_center_colour(RED);
			orange_side = side_of_center_colour(ORANGE);
			yellow_side = side_of_center_colour(YELLOW);
			green_side = side_of_center_colour(GREEN);

			print_screen();
			apply_formula();
			stage = STAGE1;
			break;

		case STAGE1:
			while (!cross_complete) /* Cross not completed */
			{
				switch (stage1_substage_1)
				{
				case UP_01:
					if ((cube.sides.up.colour[0][1] != WHITE) && (cube.sides.back.colour[0][1] != BLUE))
					{
						int middle_num = 0;
						/* Search front */
						middle_num = search_edge_colour_of_side(FRONT, WHITE, BLUE);
						if (middle_num) /* Found in front */
						{
							switch (middle_num)
							{
							case 1:
								formulae_update_step(START_FORMULA);
								formulae_update_step("Fi");
								formulae_update_step("Li");
								formulae_update_step("U");
								formulae_update_step(END_FORMULA);
								break;
							case 2:
								formulae_update_step(START_FORMULA);
								formulae_update_step("Li");
								formulae_update_step("U");
								formulae_update_step(END_FORMULA);
								break;
							case 3:
								formulae_update_step(START_FORMULA);
								formulae_update_step("F");
								formulae_update_step("Li");
								formulae_update_step("U");
								formulae_update_step(END_FORMULA);
								break;
							case 4:
								formulae_update_step(START_FORMULA);
								formulae_update_step("F");
								formulae_update_step("F");
								formulae_update_step("Li");
								formulae_update_step("U");
								formulae_update_step(END_FORMULA);
								break;
							}
						}
						else
						{
							/* Search down */
							middle_num = search_edge_colour_of_side(DOWN, WHITE, BLUE);
							if (middle_num) /* Found in down */
							{
								switch (middle_num)
								{
								case 1:
									formulae_update_step(START_FORMULA);
									formulae_update_step("F");
									formulae_update_step("F");
									formulae_update_step("U");
									formulae_update_step("U");
									formulae_update_step(END_FORMULA);
									break;
								case 2:
									formulae_update_step(START_FORMULA);
									formulae_update_step("L");
									formulae_update_step("L");
									formulae_update_step("U");
									formulae_update_step(END_FORMULA);
									break;
								case 3:
									formulae_update_step(START_FORMULA);
									formulae_update_step("R");
									formulae_update_step("R");
									formulae_update_step("Ui");
									formulae_update_step(END_FORMULA);
									break;
								case 4:
									formulae_update_step(START_FORMULA);
									formulae_update_step("B");
									formulae_update_step("B");
									formulae_update_step(END_FORMULA);
									break;
								}
							}
							else
							{
								/* Search back */
								middle_num = search_edge_colour_of_side(BACK, WHITE, BLUE);
								if (middle_num) /* Found in back */
								{
									switch (middle_num)
									{
									case 1:
										formulae_update_step(START_FORMULA);
										formulae_update_step("B");
										formulae_update_step("L");
										formulae_update_step("U");
										formulae_update_step(END_FORMULA);
										break;
									case 2:
										formulae_update_step(START_FORMULA);
										formulae_update_step("Ri");
										formulae_update_step("Ui");
										formulae_update_step(END_FORMULA);
										break;
									case 3:
										formulae_update_step(START_FORMULA);
										formulae_update_step("L");
										formulae_update_step("U");
										formulae_update_step(END_FORMULA);
										break;
									case 4:
										formulae_update_step(START_FORMULA);
										formulae_update_step("B");
										formulae_update_step("Ri");
										formulae_update_step("Ui");
										formulae_update_step(END_FORMULA);
										break;
									}
								}
								else
								{
									/* Search left */
									middle_num = search_edge_colour_of_side(LEFT, WHITE, BLUE);
									if (middle_num) /* Found in left */
									{
										switch (middle_num)
										{
										case 1:
											formulae_update_step(START_FORMULA);
											formulae_update_step("Li");
											formulae_update_step("Bi");
											formulae_update_step(END_FORMULA);
											break;
										case 2:
											formulae_update_step(START_FORMULA);
											formulae_update_step("Bi");
											formulae_update_step(END_FORMULA);
											break;
										case 3:
											formulae_update_step(START_FORMULA);
											formulae_update_step("F");
											formulae_update_step("U");
											formulae_update_step("U");
											formulae_update_step(END_FORMULA);
											break;
										case 4:
											formulae_update_step(START_FORMULA);
											formulae_update_step("Li");
											formulae_update_step("Bi");
											formulae_update_step(END_FORMULA);
											break;
										}
									}
									else
									{
										/* Search right */
										middle_num = search_edge_colour_of_side(RIGHT, WHITE, BLUE);
										if (middle_num) /* Found in right */
										{
											switch (middle_num)
											{
											case 1:
												formulae_update_step(START_FORMULA);
												formulae_update_step("R");
												formulae_update_step("B");
												formulae_update_step(END_FORMULA);
												break;
											case 2:
												formulae_update_step(START_FORMULA);
												formulae_update_step("R");
												formulae_update_step("R");
												formulae_update_step("B");
												formulae_update_step(END_FORMULA);
												break;
											case 3:
												formulae_update_step(START_FORMULA);
												formulae_update_step("B");
												formulae_update_step(END_FORMULA);
												break;
											case 4:
												formulae_update_step(START_FORMULA);
												formulae_update_step("Ri");
												formulae_update_step("B");
												formulae_update_step(END_FORMULA);
												break;
											}
										}
										else
										{
											/* Search UP */
											middle_num = search_edge_colour_of_side(UP, WHITE, BLUE);
											if (middle_num) /* Found in right */
											{
												switch (middle_num)
												{
												case 1:
													/* Invalid case */
													break;
												case 2:
													formulae_update_step(START_FORMULA);
													formulae_update_step("U");
													formulae_update_step(END_FORMULA);
													break;
												case 3:
													formulae_update_step(START_FORMULA);
													formulae_update_step("Ui");
													formulae_update_step(END_FORMULA);
													break;
												case 4:
													formulae_update_step(START_FORMULA);
													formulae_update_step("U");
													formulae_update_step("U");
													formulae_update_step(END_FORMULA);
													break;
												}
											}
										}
									}
								}
							}
						}
					}
					if ((cube.sides.up.colour[0][1] == WHITE) && (cube.sides.back.colour[0][1] == BLUE))
						stage1_substage_1 = UP_10;
					print_screen();
					apply_formula();
					break;

				case UP_10:
					if ((cube.sides.up.colour[1][0] != WHITE) && (cube.sides.left.colour[0][1] != LEFT_CENTER_COLOUR))
					{
						int middle_num = 0;
						/* Search front */
						middle_num = search_edge_colour_of_side(FRONT, WHITE, LEFT_CENTER_COLOUR);
						if (middle_num) /* Found in front */
						{
							switch (middle_num)
							{
							case 1:
								formulae_update_step(START_FORMULA);
								formulae_update_step("Fi");
								formulae_update_step("Li");
								formulae_update_step(END_FORMULA);
								break;
							case 2:
								formulae_update_step(START_FORMULA);
								formulae_update_step("Li");
								formulae_update_step(END_FORMULA);
								break;
							case 3:
								formulae_update_step(START_FORMULA);
								formulae_update_step("F");
								formulae_update_step("F");
								formulae_update_step("Li");
								formulae_update_step(END_FORMULA);
								break;
							case 4:
								formulae_update_step(START_FORMULA);
								formulae_update_step("F");
								formulae_update_step("Li");
								formulae_update_step(END_FORMULA);
								break;
							}
						}
						else
						{
							/* Search down */
							middle_num = search_edge_colour_of_side(DOWN, WHITE, LEFT_CENTER_COLOUR);
							if (middle_num) /* Found in down */
							{
								switch (middle_num)
								{
								case 1:
									formulae_update_step(START_FORMULA);
									formulae_update_step("Di");
									formulae_update_step("L");
									formulae_update_step("L");
									formulae_update_step(END_FORMULA);
									break;
								case 2:
									formulae_update_step(START_FORMULA);
									formulae_update_step("L");
									formulae_update_step("L");
									formulae_update_step(END_FORMULA);
									break;
								case 3:
									formulae_update_step(START_FORMULA);
									formulae_update_step("D");
									formulae_update_step("D");
									formulae_update_step("L");
									formulae_update_step("L");
									formulae_update_step(END_FORMULA);
									break;
								case 4:
									formulae_update_step(START_FORMULA);
									formulae_update_step("D");
									formulae_update_step("L");
									formulae_update_step("L");
									formulae_update_step(END_FORMULA);
									break;
								}
							}
							else
							{
								/* Search back */
								middle_num = search_edge_colour_of_side(BACK, WHITE, LEFT_CENTER_COLOUR);
								if (middle_num) /* Found in back */
								{
									switch (middle_num)
									{
									case 1:
										/* Invalid case */
										break;
									case 2:
										formulae_update_step(START_FORMULA);
										formulae_update_step("R");
										formulae_update_step("D");
										formulae_update_step("D");
										formulae_update_step("L");
										formulae_update_step("L");
										formulae_update_step(END_FORMULA);
										break;
									case 3:
										formulae_update_step(START_FORMULA);
										formulae_update_step("L");
										formulae_update_step(END_FORMULA);
										break;
									case 4:
										formulae_update_step(START_FORMULA);
										formulae_update_step("D");
										formulae_update_step("D");
										formulae_update_step("F");
										formulae_update_step("Li");
										formulae_update_step(END_FORMULA);
										break;
									}
								}
								else
								{
									/* Search left */
									middle_num = search_edge_colour_of_side(LEFT, WHITE, LEFT_CENTER_COLOUR);
									if (middle_num) /* Found in left */
									{
										switch (middle_num)
										{
										case 1:
											formulae_update_step(START_FORMULA);
											formulae_update_step("Ui");
											formulae_update_step("Fi");
											formulae_update_step("U");
											formulae_update_step("Li");
											formulae_update_step(END_FORMULA);
											break;
										case 2:
											formulae_update_step(START_FORMULA);
											formulae_update_step("L");
											formulae_update_step("Ui");
											formulae_update_step("Fi");
											formulae_update_step("U");
											formulae_update_step("Li");
											formulae_update_step(END_FORMULA);
											break;
										case 3:
											formulae_update_step(START_FORMULA);
											formulae_update_step("L");
											formulae_update_step("L");
											formulae_update_step("Ui");
											formulae_update_step("Fi");
											formulae_update_step("U");
											formulae_update_step("Li");
											formulae_update_step(END_FORMULA);
											break;
										case 4:
											formulae_update_step(START_FORMULA);
											formulae_update_step("Li");
											formulae_update_step("Ui");
											formulae_update_step("Fi");
											formulae_update_step("U");
											formulae_update_step("Li");
											formulae_update_step(END_FORMULA);
											break;
										}
									}
									else
									{
										/* Search right */
										middle_num = search_edge_colour_of_side(RIGHT, WHITE, LEFT_CENTER_COLOUR);
										if (middle_num) /* Found in right */
										{
											switch (middle_num)
											{
											case 1:
												formulae_update_step(START_FORMULA);
												formulae_update_step("U");
												formulae_update_step("Fi");
												formulae_update_step("Ui");
												formulae_update_step("Li");
												formulae_update_step(END_FORMULA);
												break;
											case 2:
												formulae_update_step(START_FORMULA);
												formulae_update_step("R");
												formulae_update_step("U");
												formulae_update_step("Fi");
												formulae_update_step("Ui");
												formulae_update_step("Li");
												formulae_update_step(END_FORMULA);
												break;
											case 3:
												formulae_update_step(START_FORMULA);
												formulae_update_step("Ri");
												formulae_update_step("U");
												formulae_update_step("Fi");
												formulae_update_step("Ui");
												formulae_update_step("Li");
												formulae_update_step(END_FORMULA);
												break;
											case 4:
												formulae_update_step(START_FORMULA);
												formulae_update_step("R");
												formulae_update_step("R");
												formulae_update_step("U");
												formulae_update_step("Fi");
												formulae_update_step("Ui");
												formulae_update_step("Li");
												formulae_update_step(END_FORMULA);
												break;
											}
										}
										else
										{
											/* Search UP */
											middle_num = search_edge_colour_of_side(UP, WHITE, BLUE);
											if (middle_num) /* Found in right */
											{
												switch (middle_num)
												{
												case 1:
													/* Invalid case */
													break;
												case 2:
													/* In place */
													break;
												case 3:
													formulae_update_step(START_FORMULA);
													formulae_update_step("Ri");
													formulae_update_step("Ui");
													formulae_update_step("Ui");
													formulae_update_step("R");
													formulae_update_step("U");
													formulae_update_step("U");
													formulae_update_step(END_FORMULA);
													break;
												case 4:
													formulae_update_step(START_FORMULA);
													formulae_update_step("Fi");
													formulae_update_step("Ui");
													formulae_update_step("F");
													formulae_update_step("U");
													formulae_update_step(END_FORMULA);
													break;
												}
											}
										}
									}
								}
							}
						}
					}
					if ((cube.sides.up.colour[1][0] == WHITE) && (cube.sides.left.colour[0][1] == LEFT_CENTER_COLOUR))
						stage1_substage_1 = UP_12;
					print_screen();
					apply_formula();
					break;

				case UP_12:
					if ((cube.sides.up.colour[1][2] != WHITE) && (cube.sides.right.colour[0][1] != RIGHT_CENTER_COLOUR))
					{
						int middle_num = 0;
						/* Search front */
						middle_num = search_edge_colour_of_side(FRONT, WHITE, RIGHT_CENTER_COLOUR);
						if (middle_num) /* Found in front */
						{
							switch (middle_num)
							{
							case 1:
								formulae_update_step(START_FORMULA);
								formulae_update_step("F");
								formulae_update_step("R");
								formulae_update_step(END_FORMULA);
								break;
							case 2:
								formulae_update_step(START_FORMULA);
								formulae_update_step("F");
								formulae_update_step("F");
								formulae_update_step("R");
								formulae_update_step(END_FORMULA);
								break;
							case 3:
								formulae_update_step(START_FORMULA);
								formulae_update_step("R");
								formulae_update_step(END_FORMULA);
								break;
							case 4:
								formulae_update_step(START_FORMULA);
								formulae_update_step("Fi");
								formulae_update_step("R");
								formulae_update_step(END_FORMULA);
								break;
							}
						}
						else
						{
							/* Search down */
							middle_num = search_edge_colour_of_side(DOWN, WHITE, LEFT_CENTER_COLOUR);
							if (middle_num) /* Found in down */
							{
								switch (middle_num)
								{
								case 1:
									formulae_update_step(START_FORMULA);
									formulae_update_step("D");
									formulae_update_step("R");
									formulae_update_step("R");
									formulae_update_step(END_FORMULA);
									break;
								case 2:
									formulae_update_step(START_FORMULA);
									formulae_update_step("D");
									formulae_update_step("D");
									formulae_update_step("R");
									formulae_update_step("R");
									formulae_update_step(END_FORMULA);
									break;
								case 3:
									formulae_update_step(START_FORMULA);
									formulae_update_step("R");
									formulae_update_step("R");
									formulae_update_step(END_FORMULA);
									break;
								case 4:
									formulae_update_step(START_FORMULA);
									formulae_update_step("Di");
									formulae_update_step("R");
									formulae_update_step("R");
									formulae_update_step(END_FORMULA);
									break;
								}
							}
							else
							{
								/* Search back */
								middle_num = search_edge_colour_of_side(BACK, WHITE, LEFT_CENTER_COLOUR);
								if (middle_num) /* Found in back */
								{
									switch (middle_num)
									{
									case 1:
										/* Invalid case */
										break;
									case 2:
										formulae_update_step(START_FORMULA);
										formulae_update_step("Ri");
										formulae_update_step(END_FORMULA);
										break;
									case 3:
										formulae_update_step(START_FORMULA);
										formulae_update_step("Ui");
										formulae_update_step("B");
										formulae_update_step("B");
										formulae_update_step("U");
										formulae_update_step("Ri");
										formulae_update_step(END_FORMULA);
										break;
									case 4:
										formulae_update_step(START_FORMULA);
										formulae_update_step("D");
										formulae_update_step("D");
										formulae_update_step("Fi");
										formulae_update_step("R");
										formulae_update_step(END_FORMULA);
										break;
									}
								}
								else
								{
									/* Search left */
									middle_num = search_edge_colour_of_side(LEFT, WHITE, LEFT_CENTER_COLOUR);
									if (middle_num) /* Found in left */
									{
										switch (middle_num)
										{
										case 1:
											/* Invalid case */
											break;
										case 2:
											formulae_update_step(START_FORMULA);
											formulae_update_step("Ui");
											formulae_update_step("Bi");
											formulae_update_step("U");
											formulae_update_step(END_FORMULA);
											break;
										case 3:
											formulae_update_step(START_FORMULA);
											formulae_update_step("U");
											formulae_update_step("F");
											formulae_update_step("Ui");
											formulae_update_step(END_FORMULA);
											break;
										case 4:
											formulae_update_step(START_FORMULA);
											formulae_update_step("U");
											formulae_update_step("Li");
											formulae_update_step("F");
											formulae_update_step("Ui");
											formulae_update_step(END_FORMULA);
											break;
										}
									}
									else
									{
										/* Search right */
										middle_num = search_edge_colour_of_side(RIGHT, WHITE, LEFT_CENTER_COLOUR);
										if (middle_num) /* Found in right */
										{
											switch (middle_num)
											{
											case 1:
												formulae_update_step(START_FORMULA);
												formulae_update_step("R");
												formulae_update_step("Ui");
												formulae_update_step("B");
												formulae_update_step("U");
												formulae_update_step(END_FORMULA);
												break;
											case 2:
												formulae_update_step(START_FORMULA);
												formulae_update_step("U");
												formulae_update_step("Fi");
												formulae_update_step("Ui");
												formulae_update_step(END_FORMULA);
												break;
											case 3:
												formulae_update_step(START_FORMULA);
												formulae_update_step("Ui");
												formulae_update_step("B");
												formulae_update_step("U");
												formulae_update_step(END_FORMULA);
												break;
											case 4:
												formulae_update_step(START_FORMULA);
												formulae_update_step("Ri");
												formulae_update_step("Ui");
												formulae_update_step("B");
												formulae_update_step("U");
												formulae_update_step(END_FORMULA);
												break;
											}
										}
										else
										{
											/* Search UP */
											middle_num = search_edge_colour_of_side(UP, WHITE, BLUE);
											if (middle_num) /* Found in right */
											{
												switch (middle_num)
												{
												case 1:
													/* Invalid case */
													break;
												case 2:
													/* Invalid case */
													break;
												case 3:
													/* In place */
													break;
												case 4:
													formulae_update_step(START_FORMULA);
													formulae_update_step("Fi");
													formulae_update_step("U");
													formulae_update_step("F");
													formulae_update_step("Ui");
													formulae_update_step(END_FORMULA);
													break;
												}
											}
										}
									}
								}
							}
						}
					}
					if ((cube.sides.up.colour[1][2] != WHITE) && (cube.sides.right.colour[0][1] != RIGHT_CENTER_COLOUR))
						stage1_substage_1 = UP_21;
					print_screen();
					apply_formula();
					break;

				case UP_21:
					if ((cube.sides.up.colour[2][1] != WHITE) && (cube.sides.front.colour[0][1] != GREEN))
					{
						int middle_num = 0;
						/* Search front */
						middle_num = search_edge_colour_of_side(FRONT, WHITE, RIGHT_CENTER_COLOUR);
						if (middle_num) /* Found in front */
						{
							switch (middle_num)
							{
							case 1:
								formulae_update_step(START_FORMULA);
								formulae_update_step("F");
								formulae_update_step("F");
								formulae_update_step("D");
								formulae_update_step("R");
								formulae_update_step("Fi");
								formulae_update_step("Ri");
								formulae_update_step(END_FORMULA);
								break;
							case 2:
								formulae_update_step(START_FORMULA);
								formulae_update_step("Fi");
								formulae_update_step("D");
								formulae_update_step("R");
								formulae_update_step("Fi");
								formulae_update_step("Ri");
								formulae_update_step(END_FORMULA);
								break;
							case 3:
								formulae_update_step(START_FORMULA);
								formulae_update_step("F");
								formulae_update_step("D");
								formulae_update_step("R");
								formulae_update_step("Fi");
								formulae_update_step("Ri");
								formulae_update_step(END_FORMULA);
								break;
							case 4:
								formulae_update_step(START_FORMULA);
								formulae_update_step("D");
								formulae_update_step("R");
								formulae_update_step("Fi");
								formulae_update_step("Ri");
								formulae_update_step(END_FORMULA);
								break;
							}
						}
						else
						{
							/* Search down */
							middle_num = search_edge_colour_of_side(DOWN, WHITE, LEFT_CENTER_COLOUR);
							if (middle_num) /* Found in down */
							{
								switch (middle_num)
								{
								case 1:
									formulae_update_step(START_FORMULA);
									formulae_update_step("F");
									formulae_update_step("F");
									formulae_update_step(END_FORMULA);
									break;
								case 2:
									formulae_update_step(START_FORMULA);
									formulae_update_step("D");
									formulae_update_step("F");
									formulae_update_step("F");
									formulae_update_step(END_FORMULA);
									break;
								case 3:
									formulae_update_step(START_FORMULA);
									formulae_update_step("Di");
									formulae_update_step("F");
									formulae_update_step("F");
									formulae_update_step(END_FORMULA);
									break;
								case 4:
									formulae_update_step(START_FORMULA);
									formulae_update_step("D");
									formulae_update_step("D");
									formulae_update_step("F");
									formulae_update_step("F");
									formulae_update_step(END_FORMULA);
									break;
								}
							}
							else
							{
								/* Search back */
								middle_num = search_edge_colour_of_side(BACK, WHITE, LEFT_CENTER_COLOUR);
								if (middle_num) /* Found in back */
								{
									switch (middle_num)
									{
									case 1:
										/* Invalid case */
										break;
									case 2:
										formulae_update_step(START_FORMULA);
										formulae_update_step("U");
										formulae_update_step("U");
										formulae_update_step("Bi");
										formulae_update_step("U");
										formulae_update_step("U");
										formulae_update_step("Di");
										formulae_update_step("R");
										formulae_update_step("Fi");
										formulae_update_step("Ri");
										formulae_update_step(END_FORMULA);
										break;
									case 3:
										formulae_update_step(START_FORMULA);
										formulae_update_step("U");
										formulae_update_step("U");
										formulae_update_step("B");
										formulae_update_step("U");
										formulae_update_step("U");
										formulae_update_step("Di");
										formulae_update_step("R");
										formulae_update_step("Fi");
										formulae_update_step("Ri");
										formulae_update_step(END_FORMULA);
										break;
									case 4:
										formulae_update_step(START_FORMULA);
										formulae_update_step("Di");
										formulae_update_step("R");
										formulae_update_step("Fi");
										formulae_update_step("Ri");
										formulae_update_step(END_FORMULA);
										break;
									}
								}
								else
								{
									/* Search left */
									middle_num = search_edge_colour_of_side(LEFT, WHITE, LEFT_CENTER_COLOUR);
									if (middle_num) /* Found in left */
									{
										switch (middle_num)
										{
										case 1:
											/* Invalid case */
											break;
										case 2:
											formulae_update_step(START_FORMULA);
											formulae_update_step("U");
											formulae_update_step("Li");
											formulae_update_step("Li");
											formulae_update_step("Ui");
											formulae_update_step("F");
											formulae_update_step(END_FORMULA);
											break;
										case 3:
											formulae_update_step(START_FORMULA);
											formulae_update_step("F");
											formulae_update_step(END_FORMULA);
											break;
										case 4:
											formulae_update_step(START_FORMULA);
											formulae_update_step("U");
											formulae_update_step("Li");
											formulae_update_step("Ui");
											formulae_update_step("F");
											formulae_update_step(END_FORMULA);
											break;
										}
									}
									else
									{
										/* Search right */
										middle_num = search_edge_colour_of_side(RIGHT, WHITE, LEFT_CENTER_COLOUR);
										if (middle_num) /* Found in right */
										{
											switch (middle_num)
											{
											case 1:
												/* Invalid case */
												break;
											case 2:
												formulae_update_step(START_FORMULA);
												formulae_update_step("Fi");
												formulae_update_step(END_FORMULA);
												break;
											case 3:
												formulae_update_step(START_FORMULA);
												formulae_update_step("Bi");
												formulae_update_step("D");
												formulae_update_step("D");
												formulae_update_step("B");
												formulae_update_step("F");
												formulae_update_step("F");
												formulae_update_step(END_FORMULA);
												break;
											case 4:
												formulae_update_step(START_FORMULA);
												formulae_update_step("R");
												formulae_update_step("Fi");
												formulae_update_step("Ri");
												formulae_update_step(END_FORMULA);
												break;
											}
										}
										else
										{
											/* Search UP */
											middle_num = search_edge_colour_of_side(UP, WHITE, BLUE);
											if (middle_num) /* Found in right */
											{
												switch (middle_num)
												{
												case 1:
													/* Invalid case */
													break;
												case 2:
													/* Invalid case */
													break;
												case 3:
													/* Invalid case */
													break;
												case 4:
													/* In place */
													break;
												}
											}
										}
									}
								}
							}
						}
					}
					if ((cube.sides.up.colour[2][1] != WHITE) && (cube.sides.front.colour[0][1] != GREEN))
						stage1_substage_1 = VALIDATE_CROSS;
					print_screen();
					apply_formula();
					break;

				case VALIDATE_CROSS:
					if ((cube.sides.up.colour[0][1] == WHITE) && (cube.sides.back.colour[0][1] == BLUE))
					{
						if ((cube.sides.up.colour[1][0] == WHITE) && (cube.sides.left.colour[0][1] == LEFT_CENTER_COLOUR))
						{
							if ((cube.sides.up.colour[1][2] != WHITE) && (cube.sides.right.colour[0][1] != RIGHT_CENTER_COLOUR))
							{
								if ((cube.sides.up.colour[2][1] != WHITE) && (cube.sides.front.colour[0][1] != GREEN))
									cross_complete = 1;
								else
									stage1_substage_1 = UP_21;
							}
							else
								stage1_substage_1 = UP_12;
						}
						else
							stage1_substage_1 = UP_10;
					}
					else
						stage1_substage_1 = UP_01;

					break;
				}
			}

			stage = STAGE2;
			printf("\n__HOLD__\n");
			getchar();
			getchar();
			break;

		case STAGE2:
			break;

		case STAGE3:
			break;

		case STAGE4:
			break;

		default:
			stage = ANALYSE;
			break;
		}
	}
}

static void update_cube_local(void)
{
	/* Copy front side */
	for (int i = 0; i < SIDE_ROWS; i++)
	{
		for (int j = 0; j < SIDE_COLUMNS; j++)
			cube_local.sides.front.colour[i][j] = cube.sides.front.colour[i][j];
	}

	/* Copy back side */
	for (int i = 0; i < SIDE_ROWS; i++)
	{
		for (int j = 0; j < SIDE_COLUMNS; j++)
			cube_local.sides.back.colour[i][j] = cube.sides.back.colour[i][j];
	}

	/* Copy left side */
	for (int i = 0; i < SIDE_ROWS; i++)
	{
		for (int j = 0; j < SIDE_COLUMNS; j++)
			cube_local.sides.left.colour[i][j] = cube.sides.left.colour[i][j];
	}

	/* Copy right side */
	for (int i = 0; i < SIDE_ROWS; i++)
	{
		for (int j = 0; j < SIDE_COLUMNS; j++)
			cube_local.sides.right.colour[i][j] = cube.sides.right.colour[i][j];
	}

	/* Copy up side */
	for (int i = 0; i < SIDE_ROWS; i++)
	{
		for (int j = 0; j < SIDE_COLUMNS; j++)
			cube_local.sides.up.colour[i][j] = cube.sides.up.colour[i][j];
	}

	/* Copy down side */
	for (int i = 0; i < SIDE_ROWS; i++)
	{
		for (int j = 0; j < SIDE_COLUMNS; j++)
			cube_local.sides.down.colour[i][j] = cube.sides.down.colour[i][j];
	}

	/* Cube map copy */
	for (int i = 0; i < 16; i++)
	{
		strcpy(cube_local.cube_map[i], cube.cube_map[i]);
	}
}

static int validate_step(char *step)
{
	int validate_status = 0;
	switch (step[0])
	{
	case 'S':
	case 'E':
	case 'R':
	case 'L':
	case 'U':
	case 'D':
	case 'F':
	case 'B':
	case 'r':
	case 'l':
	case 'u':
	case 'd':
	case 'f':
	case 'b':
	case 'X':
	case 'Y':
	case 'Z':
		switch (step[1])
		{
		case '\0':
		case 'i':
			validate_status = 1;
			break;
		}
		break;
	default:
		break;
	}
	return validate_status;
}

static void formulae_update_step(char *step)
{
	if (!validate_step(step))
	{
		print_error("wrong step received to forumlae_update() function. Press 'Enter' to continue");
		getchar();
		getchar();
		return;
	}
	switch (step[0])
	{
	case 'S': /* Adding a new forumla */
		formula_count++;
		formula = (formula_t *)realloc(formula, sizeof(formula_t) * formula_count);
		if (!formula)
		{
			print_error("relloc() error in formulae_update_step() function");
			exit(1);
		}

		CURRENT_FORMULA.step_count = 0;
		CURRENT_FORMULA.steps = NULL;
		break;

	case 'E': /* End of Forumla */
		CURRENT_FORMULA.step_count++;
		CURRENT_FORMULA.steps = (step_t *)realloc(CURRENT_FORMULA.steps, (sizeof(step_t)) * (CURRENT_FORMULA.step_count));
		if (!CURRENT_FORMULA.steps)
		{
			print_error("relloc() error in formulae_update_step() function");
			exit(1);
		}
		strcpy(CURRENT_FORMULA.steps[(CURRENT_FORMULA.step_count - 1)].step, "END");
		break;

	default: /* Adding a new step to current formula */
		CURRENT_FORMULA.step_count++;
		CURRENT_FORMULA.steps = (step_t *)realloc(CURRENT_FORMULA.steps, (sizeof(step_t)) * (CURRENT_FORMULA.step_count));
		if (!CURRENT_FORMULA.steps)
		{
			print_error("relloc() error in formulae_update_step() function");
			exit(1);
		}
		strcpy(CURRENT_FORMULA.steps[(CURRENT_FORMULA.step_count - 1)].step, step);
		break;
	}
}

static void apply_formula(void)
{
	char temp_step[3];

	for (int i = 0; i < CURRENT_FORMULA.step_count - 1; i++)
	{
		strcpy(temp_step, CURRENT_FORMULA.steps[i].step);
		getchar();
		switch (temp_step[0])
		{
		case 'E': /* End of formula */
			break;
		case 'R':
			if (IS_INVERSE)
				Ri();
			else
				R();
			break;

		case 'L':
			if (IS_INVERSE)
				Li();
			else
				L();
			break;

		case 'U':
			if (IS_INVERSE)
				Ui();
			else
				U();
			break;

		case 'D':
			if (IS_INVERSE)
				Di();
			else
				D();
			break;

		case 'F':
			if (IS_INVERSE)
				Fi();
			else
				F();
			break;

		case 'B':
			if (IS_INVERSE)
				Bi();
			else
				B();
			break;

		case 'r':
			if (IS_INVERSE)
				ri();
			else
				r();
			break;

		case 'l':
			if (IS_INVERSE)
				li();
			else
				l();
			break;

		case 'u':
			if (IS_INVERSE)
				ui();
			else
				u();
			break;

		case 'd':
			if (IS_INVERSE)
				di();
			else
				d();
			break;

		case 'f':
			if (IS_INVERSE)
				fi();
			else
				f();
			break;

		case 'b':
			if (IS_INVERSE)
				bi();
			else
				b();
			break;

		case 'X':
			if (IS_INVERSE)
				Xi();
			else
				X();
			break;

		case 'Y':
			if (IS_INVERSE)
				Yi();
			else
				Y();
			break;

		case 'Z':
			if (IS_INVERSE)
				Zi();
			else
				Z();
			break;

		default:
			print_error("Invalid step in formula\n");
			break;
		}
		update_cube_map();
		print_screen();
	}
}

static int search_edge_colour_of_side(int side, char colour_main, char colour_pair)
{
	int middle_num = 0;
	switch (side)
	{
	case FRONT:
		if ((cube.sides.front.colour[0][1] == colour_main) && (cube.sides.up.colour[2][1] == colour_pair))
			middle_num = 1;
		else if ((cube.sides.front.colour[1][0] == colour_main) && (cube.sides.left.colour[1][2] == colour_pair))
			middle_num = 2;
		else if ((cube.sides.front.colour[1][2] == colour_main) && (cube.sides.right.colour[1][0] == colour_pair))
			middle_num = 3;
		else if ((cube.sides.front.colour[2][1] == colour_main) && (cube.sides.down.colour[0][1] == colour_pair))
			middle_num = 4;
		break;

	case BACK:
		if ((cube.sides.back.colour[0][1] == colour_main) && (cube.sides.up.colour[0][1] == colour_pair))
			middle_num = 1;
		else if ((cube.sides.back.colour[1][0] == colour_main) && (cube.sides.right.colour[1][2] == colour_pair))
			middle_num = 2;
		else if ((cube.sides.back.colour[1][2] == colour_main) && (cube.sides.left.colour[1][0] == colour_pair))
			middle_num = 3;
		else if ((cube.sides.back.colour[2][1] == colour_main) && (cube.sides.down.colour[2][1] == colour_pair))
			middle_num = 4;
		break;

	case LEFT:
		if ((cube.sides.left.colour[0][1] == colour_main) && (cube.sides.up.colour[1][0] == colour_pair))
			middle_num = 1;
		else if ((cube.sides.left.colour[1][0] == colour_main) && (cube.sides.back.colour[1][2] == colour_pair))
			middle_num = 2;
		else if ((cube.sides.left.colour[1][2] == colour_main) && (cube.sides.front.colour[1][0] == colour_pair))
			middle_num = 3;
		else if ((cube.sides.left.colour[2][1] == colour_main) && (cube.sides.down.colour[1][0] == colour_pair))
			middle_num = 4;
		break;

	case RIGHT:
		if ((cube.sides.right.colour[0][1] == colour_main) && (cube.sides.up.colour[1][2] == colour_pair))
			middle_num = 1;
		else if ((cube.sides.right.colour[1][0] == colour_main) && (cube.sides.front.colour[1][2] == colour_pair))
			middle_num = 2;
		else if ((cube.sides.right.colour[1][2] == colour_main) && (cube.sides.back.colour[1][0] == colour_pair))
			middle_num = 3;
		else if ((cube.sides.right.colour[2][1] == colour_main) && (cube.sides.down.colour[1][2] == colour_pair))
			middle_num = 4;
		break;

	case DOWN:
		if ((cube.sides.down.colour[0][1] == colour_main) && (cube.sides.front.colour[2][1] == colour_pair))
			middle_num = 1;
		else if ((cube.sides.down.colour[1][0] == colour_main) && (cube.sides.left.colour[2][1] == colour_pair))
			middle_num = 2;
		else if ((cube.sides.down.colour[1][2] == colour_main) && (cube.sides.right.colour[2][1] == colour_pair))
			middle_num = 3;
		else if ((cube.sides.down.colour[2][1] == colour_main) && (cube.sides.back.colour[2][1] == colour_pair))
			middle_num = 4;
		break;

	case UP:
		if ((cube.sides.up.colour[0][1] == colour_main) && (cube.sides.back.colour[0][1] == colour_pair))
			middle_num = 1;
		else if ((cube.sides.up.colour[1][0] == colour_main) && (cube.sides.left.colour[0][1] == colour_pair))
			middle_num = 2;
		else if ((cube.sides.up.colour[1][2] == colour_main) && (cube.sides.right.colour[0][1] == colour_pair))
			middle_num = 3;
		else if ((cube.sides.up.colour[2][1] == colour_main) && (cube.sides.front.colour[0][1] == colour_pair))
			middle_num = 4;
		break;
	}
	return middle_num;
}

static void cube_init_temp_colour(void)
{
	for (int i = 0; i < SIDE_ROWS; i++)
	{
		for (int j = 0; j < SIDE_COLUMNS; j++)
		{
			cube.sides.back.colour[i][j] = BLUE;
			update_colour_count(cube.sides.back.colour[i][j]);
		}
	}

	for (int i = 0; i < SIDE_ROWS; i++)
	{
		for (int j = 0; j < SIDE_COLUMNS; j++)
		{
			cube.sides.left.colour[i][j] = RED;
			update_colour_count(cube.sides.left.colour[i][j]);
		}
	}

	for (int i = 0; i < SIDE_ROWS; i++)
	{
		for (int j = 0; j < SIDE_COLUMNS; j++)
		{
			cube.sides.up.colour[i][j] = YELLOW;
			update_colour_count(cube.sides.up.colour[i][j]);
		}
	}

	for (int i = 0; i < SIDE_ROWS; i++)
	{
		for (int j = 0; j < SIDE_COLUMNS; j++)
		{
			cube.sides.right.colour[i][j] = ORANGE;
			update_colour_count(cube.sides.right.colour[i][j]);
		}
	}

	for (int i = 0; i < SIDE_ROWS; i++)
	{
		for (int j = 0; j < SIDE_COLUMNS; j++)
		{
			cube.sides.down.colour[i][j] = WHITE;
			update_colour_count(cube.sides.down.colour[i][j]);
		}
	}

	for (int i = 0; i < SIDE_ROWS; i++)
	{
		for (int j = 0; j < SIDE_COLUMNS; j++)
		{
			cube.sides.front.colour[i][j] = GREEN;
			update_colour_count(cube.sides.front.colour[i][j]);
		}
	}
}