#include "../includes/cube.h"
#include "../includes/matrix_operations.h"
#include "../includes/movements.h"
#include "../includes/colour.h"
#include "../includes/print.h"
#include "../includes/read.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

cube_t cube;
colour_count_t colour_count;
formula_t *formula;
int formula_to_apply;
int formula_count;
char stub_cube;
char OLL_case[57][22] = {OLL1, OLL2, OLL3, OLL4, OLL5, OLL6, OLL7, OLL8, OLL9, OLL10, OLL11, OLL12, OLL13, OLL14, OLL15, OLL16, OLL17, OLL18, OLL19, OLL20, OLL21, OLL22, OLL23, OLL24, OLL25, OLL26, OLL27, OLL28, OLL29, OLL30, OLL31, OLL32, OLL33, OLL34, OLL35, OLL36, OLL37, OLL38, OLL39, OLL40, OLL41, OLL42, OLL43, OLL44, OLL45, OLL46, OLL47, OLL48, OLL49, OLL50, OLL51, OLL52, OLL53, OLL54, OLL55, OLL56, OLL57};
char FORMULA_OLL[57][40] = {FORMULA_OLL1, FORMULA_OLL2, FORMULA_OLL3, FORMULA_OLL4, FORMULA_OLL5, FORMULA_OLL6, FORMULA_OLL7, FORMULA_OLL8, FORMULA_OLL9, FORMULA_OLL10, FORMULA_OLL11, FORMULA_OLL12, FORMULA_OLL13, FORMULA_OLL14, FORMULA_OLL15, FORMULA_OLL16, FORMULA_OLL17, FORMULA_OLL18, FORMULA_OLL19, FORMULA_OLL20, FORMULA_OLL21, FORMULA_OLL22, FORMULA_OLL23, FORMULA_OLL24, FORMULA_OLL25, FORMULA_OLL26, FORMULA_OLL27, FORMULA_OLL28, FORMULA_OLL29, FORMULA_OLL30, FORMULA_OLL31, FORMULA_OLL32, FORMULA_OLL33, FORMULA_OLL34, FORMULA_OLL35, FORMULA_OLL36, FORMULA_OLL37, FORMULA_OLL38, FORMULA_OLL39, FORMULA_OLL40, FORMULA_OLL41, FORMULA_OLL42, FORMULA_OLL43, FORMULA_OLL44, FORMULA_OLL45, FORMULA_OLL46, FORMULA_OLL47, FORMULA_OLL48, FORMULA_OLL49, FORMULA_OLL50, FORMULA_OLL51, FORMULA_OLL52, FORMULA_OLL53, FORMULA_OLL54, FORMULA_OLL55, FORMULA_OLL56, FORMULA_OLL57};

static cube_t cube_local;

static void update_cube_local(void);
static int validate_step(char *step);
static void add_formula(char *formula_new, char *description);
static void formulae_update_step(char *step, char *formula_description);
static void apply_formula(void);
static int search_edge_colour_of_side(int side, char colour_main, char colour_pair);
static int search_corner_colour_of_side(int side, char face_colour, char side_colour1, char side_colour2);
static void cube_init_temp_colour(void);
static int cube_which_OLL_case(void);
static void cube_solve_OLL(void);
static int OLL_solved(void);
static void cube_solve_PLL(void);
static int PLL_solved(void);
static void cube_shuffle(void);
static void free_formula(void);

void cube_init(void)
{

	colour_count.white = 0;
	colour_count.red = 0;
	colour_count.green = 0;
	colour_count.blue = 0;
	colour_count.yellow = 0;
	colour_count.orange = 0;
	stub_cube = 'n';
	formula_count = 0;
	formula_to_apply = 0;

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

	printf("Stub cube?[y/n]: ");
	scanf(" %c", &stub_cube);

	if (stub_cube == 'y')
	{
		/* Stub cube */
		cube_init_temp_colour();
		cube_shuffle();
		update_cube_map();
		print_screen();
	}
	else
	{
		update_cube_map();

		input = 1;
		print_screen();
		/* Read cube colours */
		read_cube();
		input = 0;
	}
	stub_cube = 'n';
}

void update_cube_map(void)
{
	/* Line 01 */ sprintf(cube.cube_map[0], "   -- Cube current colours --\n");

	/* Line 02 */ cube.cube_map[1][0] = '\n';

	/* Line 03 */ sprintf(cube.cube_map[2], "           BACK\n");

	/* Line 04 */ sprintf(cube.cube_map[3], "          %c%c%c%c%c%c\n",
						  BACK_22_COLOUR, /* Back side line 1 */
						  BACK_22_COLOUR,
						  BACK_21_COLOUR,
						  BACK_21_COLOUR,
						  BACK_20_COLOUR,
						  BACK_20_COLOUR);

	/* Line 05 */ sprintf(cube.cube_map[4], "          %c%c%c%c%c%c\n",
						  BACK_12_COLOUR, /* Back side line 2 */
						  BACK_12_COLOUR,
						  BACK_11_COLOUR,
						  BACK_11_COLOUR,
						  BACK_10_COLOUR,
						  BACK_10_COLOUR);

	/* Line 06 */ sprintf(cube.cube_map[5], "          %c%c%c%c%c%c\n",
						  BACK_02_COLOUR, /* Back side line 3 */
						  BACK_02_COLOUR,
						  BACK_01_COLOUR,
						  BACK_01_COLOUR,
						  BACK_00_COLOUR,
						  BACK_00_COLOUR);

	/* Line 07 */ cube.cube_map[6][0] = '\n';

	/* Line 08 */ sprintf(cube.cube_map[7], "  LEFT      UP      RIGHT    DOWN\n");

	/* Line 09 */
	sprintf(cube.cube_map[8], " %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c\n",
			LEFT_20_COLOUR, LEFT_20_COLOUR, LEFT_10_COLOUR,
			LEFT_10_COLOUR, LEFT_00_COLOUR, LEFT_00_COLOUR,
			UP_00_COLOUR, UP_00_COLOUR, UP_01_COLOUR,
			UP_01_COLOUR, UP_02_COLOUR, UP_02_COLOUR,
			RIGHT_02_COLOUR, RIGHT_02_COLOUR, RIGHT_12_COLOUR,
			RIGHT_12_COLOUR, RIGHT_22_COLOUR, RIGHT_22_COLOUR,
			DOWN_22_COLOUR, DOWN_22_COLOUR, DOWN_21_COLOUR,
			DOWN_21_COLOUR, DOWN_20_COLOUR, DOWN_20_COLOUR);

	/* Line 10 */
	sprintf(cube.cube_map[9], " %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c\n",
			LEFT_21_COLOUR, LEFT_21_COLOUR, LEFT_11_COLOUR,
			LEFT_11_COLOUR, LEFT_01_COLOUR, LEFT_01_COLOUR,
			UP_10_COLOUR, UP_10_COLOUR, UP_11_COLOUR,
			UP_11_COLOUR, UP_12_COLOUR, UP_12_COLOUR,
			RIGHT_01_COLOUR, RIGHT_01_COLOUR, RIGHT_11_COLOUR,
			RIGHT_11_COLOUR, RIGHT_21_COLOUR, RIGHT_21_COLOUR,
			DOWN_12_COLOUR, DOWN_12_COLOUR, DOWN_11_COLOUR,
			DOWN_11_COLOUR, DOWN_10_COLOUR, DOWN_10_COLOUR);

	/* Line 11 */
	sprintf(cube.cube_map[10], " %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c   %c%c%c%c%c%c\n",
			LEFT_22_COLOUR, LEFT_22_COLOUR, LEFT_12_COLOUR,
			LEFT_12_COLOUR, LEFT_02_COLOUR, LEFT_02_COLOUR,
			UP_20_COLOUR, UP_20_COLOUR, UP_21_COLOUR,
			UP_21_COLOUR, UP_22_COLOUR, UP_22_COLOUR,
			RIGHT_00_COLOUR, RIGHT_00_COLOUR, RIGHT_10_COLOUR,
			RIGHT_10_COLOUR, RIGHT_20_COLOUR, RIGHT_20_COLOUR,
			DOWN_02_COLOUR, DOWN_02_COLOUR, DOWN_01_COLOUR,
			DOWN_01_COLOUR, DOWN_00_COLOUR, DOWN_00_COLOUR);

	/* Line 12 */ cube.cube_map[11][0] = '\n';

	/* Line 13 */ sprintf(cube.cube_map[12], "           FRONT\n");

	/* Line 14 */ sprintf(cube.cube_map[13], "          %c%c%c%c%c%c\n",
						  FRONT_00_COLOUR, /* Front side line 1 */
						  FRONT_00_COLOUR,
						  FRONT_01_COLOUR,
						  FRONT_01_COLOUR,
						  FRONT_02_COLOUR,
						  FRONT_02_COLOUR);

	/* Line 15 */ sprintf(cube.cube_map[14], "          %c%c%c%c%c%c\n",
						  FRONT_10_COLOUR, /* Front side line 2 */
						  FRONT_10_COLOUR,
						  FRONT_11_COLOUR,
						  FRONT_11_COLOUR,
						  FRONT_12_COLOUR,
						  FRONT_12_COLOUR);

	/* Line 16 */ sprintf(cube.cube_map[15], "          %c%c%c%c%c%c\n",
						  FRONT_20_COLOUR, /* Front side line 3 */
						  FRONT_20_COLOUR,
						  FRONT_21_COLOUR,
						  FRONT_21_COLOUR,
						  FRONT_22_COLOUR,
						  FRONT_22_COLOUR);
}

void cube_solve(void)
{
	int cube_solved = 0;

	cube_stages_t stage = ANALYSE;
	up_t stage1_substage_1 = UP_01;
	up_t stage1_substage_2 = UP_00;

	int analysis_completed = 0;
	stage1_t stage1_completed = WHITE_CROSS;
	stage2_t stage2_completed = LINE2_SIDE1;
	int stage3_completed = 0;
	int stage4_completed = 0;

	int cross_complete = 0;
	int white_corners_complete = 0;

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
				add_formula("X", "  WHITE TO UP1 ");
				break;

			case BACK:
				add_formula("Xi", "  WHITE TO UP1 ");
				break;

			case LEFT:
				add_formula("Z", "  WHITE TO UP1 ");
				break;

			case RIGHT:
				add_formula("Zi", "  WHITE TO UP1 ");
				break;

			case DOWN:
				add_formula("X X", "  WHITE TO UP1 ");
				break;

			case UP:
				/* In Position */
				formula_to_apply = 0;
				break;
			}
			print_screen();
			wait_for_enter(NULL);
			apply_formula();

			blue_side = side_of_center_colour(BLUE);
			formula_to_apply = 1;
			/* Move blue to back */
			switch (blue_side)
			{
			case FRONT:
				add_formula("d d", "  BLUE TO BACK ");
				break;

			case BACK:
				/* In position */
				formula_to_apply = 0;
				break;

			case LEFT:
				add_formula("di", "  BLUE TO BACK ");
				break;

			case RIGHT:
				add_formula("d", "  BLUE TO BACK ");
				break;

			case DOWN:
				/* Invalid case */
				formula_to_apply = 0;
				break;

			case UP:
				/* Do nothing */
				formula_to_apply = 0;
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

			formula_to_apply = 1;
			while (stage1_completed != COMPLETE) /* Top white not completed */
			{
				switch (stage1_completed)
				{
				case WHITE_CROSS:
					while (!cross_complete) /* Cross not completed */
					{
						switch (stage1_substage_1)
						{
						case UP_01:
							if (CROSS_01_NOT_SOLVED)
							{
								int middle_num = 0;
								/* Search front */
								middle_num = search_edge_colour_of_side(FRONT, WHITE, BLUE);
								if (middle_num) /* Found in front */
								{
									switch (middle_num)
									{
									case 1:
										add_formula("Fi Li U", "   SOLVE UP01  ");
										break;
									case 2:
										add_formula("Li U", "   SOLVE UP01  ");
										break;
									case 3:
										add_formula("F Li U", "   SOLVE UP01  ");
										break;
									case 4:
										add_formula("F F Li U", "   SOLVE UP01  ");
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
											add_formula("F F U U", "   SOLVE UP01  ");
											break;
										case 2:
											add_formula("L L U", "   SOLVE UP01  ");
											break;
										case 3:
											add_formula("R R Ui", "   SOLVE UP01  ");
											break;
										case 4:
											add_formula("B B", "   SOLVE UP01  ");
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
												add_formula("B L U", "   SOLVE UP01  ");
												break;
											case 2:
												add_formula("Ri Ui", "   SOLVE UP01  ");
												break;
											case 3:
												add_formula("L U", "   SOLVE UP01  ");
												break;
											case 4:
												add_formula("B Ri Ui", "   SOLVE UP01  ");
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
													add_formula("Li Bi", "   SOLVE UP01  ");
													break;
												case 2:
													add_formula("Bi", "   SOLVE UP01  ");
													break;
												case 3:
													add_formula("F U U", "   SOLVE UP01  ");
													break;
												case 4:
													add_formula("L Bi", "   SOLVE UP01  ");
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
														add_formula("R B", "   SOLVE UP01  ");
														break;
													case 2:
														add_formula("R R B", "   SOLVE UP01  ");
														break;
													case 3:
														add_formula("B", "   SOLVE UP01  ");
														break;
													case 4:
														add_formula("Ri B", "   SOLVE UP01  ");
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
															add_formula("U", "   SOLVE UP01  ");
															break;
														case 3:
															add_formula("Ui", "   SOLVE UP01  ");
															break;
														case 4:
															add_formula("U U", "   SOLVE UP01  ");
															break;
														}
													}
												}
											}
										}
									}
								}
								print_screen();
								apply_formula();
							}
							if (CROSS_01_SOLVED)
								stage1_substage_1 = UP_10;
							break;

						case UP_10:
							if (CROSS_02_NOT_SOLVED)
							{
								int middle_num = 0;
								/* Search front */
								middle_num = search_edge_colour_of_side(FRONT, WHITE, LEFT_CENTER_COLOUR);
								if (middle_num) /* Found in front */
								{
									switch (middle_num)
									{
									case 1:
										add_formula("Fi Li", "   SOLVE UP10  ");
										break;
									case 2:
										add_formula("Li", "   SOLVE UP10  ");
										break;
									case 3:
										add_formula("F F Li", "   SOLVE UP10  ");
										break;
									case 4:
										add_formula("F Li", "   SOLVE UP10  ");
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
											add_formula("Di L L", "   SOLVE UP10  ");
											break;
										case 2:
											add_formula("L L", "   SOLVE UP10  ");
											break;
										case 3:
											add_formula("D D L L", "   SOLVE UP10  ");
											break;
										case 4:
											add_formula("D L L", "   SOLVE UP10  ");
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
												add_formula("R D D L L", "   SOLVE UP10  ");
												break;
											case 3:
												add_formula("L", "   SOLVE UP10  ");
												break;
											case 4:
												add_formula("D D F Li", "   SOLVE UP10  ");
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
													add_formula("Ui Fi U Li", "   SOLVE UP10  ");
													break;
												case 2:
													add_formula("L Ui Fi U Li", "   SOLVE UP10  ");
													break;
												case 3:
													add_formula("L L Ui Fi U Li", "   SOLVE UP10  ");
													break;
												case 4:
													add_formula("Li Ui Fi U Li", "   SOLVE UP10  ");
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
														add_formula("U Fi Ui Li", "   SOLVE UP10  ");
														break;
													case 2:
														add_formula("R U Fi Ui Li", "   SOLVE UP10  ");
														break;
													case 3:
														add_formula("Ri U Fi Ui Li", "   SOLVE UP10  ");
														break;
													case 4:
														add_formula("R R U Fi Ui Li", "   SOLVE UP10  ");
														break;
													}
												}
												else
												{
													/* Search UP */
													middle_num = search_edge_colour_of_side(UP, WHITE, LEFT_CENTER_COLOUR);
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
															add_formula("Ri Ui Ui R U U", "   SOLVE UP10  ");
															break;
														case 4:
															add_formula("Fi Ui F U", "   SOLVE UP10  ");
															break;
														}
													}
												}
											}
										}
									}
								}
								print_screen();
								apply_formula();
							}
							if (CROSS_02_SOLVED)
								stage1_substage_1 = UP_12;
							break;

						case UP_12:
							if (CROSS_03_NOT_SOLVED)
							{
								int middle_num = 0;
								/* Search front */
								middle_num = search_edge_colour_of_side(FRONT, WHITE, RIGHT_CENTER_COLOUR);
								if (middle_num) /* Found in front */
								{
									switch (middle_num)
									{
									case 1:
										add_formula("F R", "   SOLVE UP12  ");
										break;
									case 2:
										add_formula("F F R", "   SOLVE UP12  ");
										break;
									case 3:
										add_formula("R", "   SOLVE UP12  ");
										break;
									case 4:
										add_formula("Fi R", "   SOLVE UP12  ");
										break;
									}
								}
								else
								{
									/* Search down */
									middle_num = search_edge_colour_of_side(DOWN, WHITE, RIGHT_CENTER_COLOUR);
									if (middle_num) /* Found in down */
									{
										switch (middle_num)
										{
										case 1:
											add_formula("D R R", "   SOLVE UP12  ");
											break;
										case 2:
											add_formula("D D R R", "   SOLVE UP12  ");
											break;
										case 3:
											add_formula("R R", "   SOLVE UP12  ");
											break;
										case 4:
											add_formula("Di R R", "   SOLVE UP12  ");
											break;
										}
									}
									else
									{
										/* Search back */
										middle_num = search_edge_colour_of_side(BACK, WHITE, RIGHT_CENTER_COLOUR);
										if (middle_num) /* Found in back */
										{
											switch (middle_num)
											{
											case 1:
												/* Invalid case */
												break;
											case 2:
												add_formula("Ri", "   SOLVE UP12  ");
												break;
											case 3:
												add_formula("Ui B B U Ri", "   SOLVE UP12  ");
												break;
											case 4:
												add_formula("D D Fi R", "   SOLVE UP12  ");
												break;
											}
										}
										else
										{
											/* Search left */
											middle_num = search_edge_colour_of_side(LEFT, WHITE, RIGHT_CENTER_COLOUR);
											if (middle_num) /* Found in left */
											{
												switch (middle_num)
												{
												case 1:
													/* Invalid case */
													break;
												case 2:
													add_formula("Ui Bi U", "   SOLVE UP12  ");
													break;
												case 3:
													add_formula("U F Ui", "   SOLVE UP12  ");
													break;
												case 4:
													add_formula("U Li F Ui", "   SOLVE UP12  ");
													break;
												}
											}
											else
											{
												/* Search right */
												middle_num = search_edge_colour_of_side(RIGHT, WHITE, RIGHT_CENTER_COLOUR);
												if (middle_num) /* Found in right */
												{
													switch (middle_num)
													{
													case 1:
														add_formula("R Ui B U", "   SOLVE UP12  ");
														break;
													case 2:
														add_formula("U Fi Ui", "   SOLVE UP12  ");
														break;
													case 3:
														add_formula("Ui B U", "   SOLVE UP12  ");
														break;
													case 4:
														add_formula("Ri Ui B U", "   SOLVE UP12  ");
														break;
													}
												}
												else
												{
													/* Search UP */
													middle_num = search_edge_colour_of_side(UP, WHITE, RIGHT_CENTER_COLOUR);
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
															add_formula("Fi U F Ui", "   SOLVE UP12  ");
															break;
														}
													}
												}
											}
										}
									}
								}
								print_screen();
								apply_formula();
							}
							if (CROSS_03_SOLVED)
								stage1_substage_1 = UP_21;
							break;

						case UP_21:
							if (CROSS_04_NOT_SOLVED)
							{
								int middle_num = 0;
								/* Search front */
								middle_num = search_edge_colour_of_side(FRONT, WHITE, GREEN);
								if (middle_num) /* Found in front */
								{
									switch (middle_num)
									{
									case 1:
										add_formula("F F D R Fi Ri", "   SOLVE UP21  ");
										break;
									case 2:
										add_formula("Fi D R Fi Ri", "   SOLVE UP21  ");
										break;
									case 3:
										add_formula("F D R Fi Ri", "   SOLVE UP21  ");
										break;
									case 4:
										add_formula("D R Fi Ri", "   SOLVE UP21  ");
										break;
									}
								}
								else
								{
									/* Search down */
									middle_num = search_edge_colour_of_side(DOWN, WHITE, GREEN);
									if (middle_num) /* Found in down */
									{
										switch (middle_num)
										{
										case 1:
											add_formula("F F", "   SOLVE UP21  ");
											break;
										case 2:
											add_formula("D F F", "   SOLVE UP21  ");
											break;
										case 3:
											add_formula("Di F F", "   SOLVE UP21  ");
											break;
										case 4:
											add_formula("D D F F", "   SOLVE UP21  ");
											break;
										}
									}
									else
									{
										/* Search back */
										middle_num = search_edge_colour_of_side(BACK, WHITE, GREEN);
										if (middle_num) /* Found in back */
										{
											switch (middle_num)
											{
											case 1:
												/* Invalid case */
												break;
											case 2:
												add_formula("U U Bi U U Di R Fi Ri", "   SOLVE UP21  ");
												break;
											case 3:
												add_formula("U U B U U Di R Fi Ri", "   SOLVE UP21  ");
												break;
											case 4:
												add_formula("Di R Fi Ri", "   SOLVE UP21  ");
												break;
											}
										}
										else
										{
											/* Search left */
											middle_num = search_edge_colour_of_side(LEFT, WHITE, GREEN);
											if (middle_num) /* Found in left */
											{
												switch (middle_num)
												{
												case 1:
													/* Invalid case */
													break;
												case 2:
													add_formula("U Li Li Ui F", "   SOLVE UP21  ");
													break;
												case 3:
													add_formula("F", "   SOLVE UP21  ");
													break;
												case 4:
													add_formula("U Li Ui F", "   SOLVE UP21  ");
													break;
												}
											}
											else
											{
												/* Search right */
												middle_num = search_edge_colour_of_side(RIGHT, WHITE, GREEN);
												if (middle_num) /* Found in right */
												{
													switch (middle_num)
													{
													case 1:
														/* Invalid case */
														break;
													case 2:
														add_formula("Fi", "   SOLVE UP21  ");
														break;
													case 3:
														add_formula("Bi D D B F F", "   SOLVE UP21  ");
														break;
													case 4:
														add_formula("R Fi Ri", "   SOLVE UP21  ");
														break;
													}
												}
												else
												{
													/* Search UP */
													middle_num = search_edge_colour_of_side(UP, WHITE, GREEN);
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
								print_screen();
								apply_formula();
							}
							if (CROSS_04_SOLVED)
								stage1_substage_1 = VALIDATE_CROSS;
							break;

						case VALIDATE_CROSS:
							if (CROSS_01_SOLVED)
							{
								if (CROSS_02_SOLVED)
								{
									if (CROSS_03_SOLVED)
									{
										if (CROSS_04_SOLVED)
										{
											cross_complete = 1;
										}
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
					/* White cross solved */
					stage1_completed = WHITE_CORNERS;
					break;

				case WHITE_CORNERS:
					while (!white_corners_complete) /* White corners not completed */
					{
						switch (stage1_substage_2)
						{
						case UP_00:
							if (WHITE_CORNER_01_NOT_SOLVED)
							{
								int corner_num = 0;
								corner_num = search_corner_colour_of_side(FRONT, WHITE, BLUE, LEFT_CENTER_COLOUR);
								if (corner_num) /* Found in Front side */
								{
									switch (corner_num)
									{
									case 1:
										add_formula("Fi B Di Bi F", "WHITE CORNER 00");
										break;
									case 2:
										add_formula("F Li Di Di L Fi", "WHITE CORNER 00");
										break;
									case 3:
										add_formula("B Di Bi", "WHITE CORNER 00");
										break;
									case 4:
										add_formula("Li D D L", "WHITE CORNER 00");
										break;
									}
								}
								else
								{
									corner_num = search_corner_colour_of_side(BACK, WHITE, BLUE, LEFT_CENTER_COLOUR);
									if (corner_num) /* Found in Back side */
									{
										switch (corner_num)
										{
										case 1:
											add_formula("Bi Di B B Di Di Bi", "WHITE CORNER 00");
											break;
										case 2:
											add_formula("B D Bi D Li D D L", "WHITE CORNER 00");
											break;
										case 3:
											add_formula("Di B D D Bi", "WHITE CORNER 00");
											break;
										case 4:
											add_formula("B D Bi", "WHITE CORNER 00");
											break;
										}
									}
									else
									{
										corner_num = search_corner_colour_of_side(RIGHT, WHITE, BLUE, LEFT_CENTER_COLOUR);
										if (corner_num) /* Found in Right side */
										{
											switch (corner_num)
											{
											case 1:
												add_formula("Ri B Di Di Bi R", "WHITE CORNER 00");
												break;
											case 2:
												add_formula("R Li D L Ri", "WHITE CORNER 00");
												break;
											case 3:
												add_formula("B Di Di Bi", "WHITE CORNER 00");
												break;
											case 4:
												add_formula("Li D Li", "WHITE CORNER 00");
												break;
											}
										}
										else
										{
											corner_num = search_corner_colour_of_side(LEFT, WHITE, BLUE, LEFT_CENTER_COLOUR);
											if (corner_num) /* Found in Left side */
											{
												switch (corner_num)
												{
												case 1:
													add_formula("Li Di Di L B Di Di Bi", "WHITE CORNER 00");
													break;
												case 2:
													add_formula("L D Li Li D D L", "WHITE CORNER 00");
													break;
												case 3:
													add_formula("D B Di Bi", "WHITE CORNER 00");
													break;
												case 4:
													add_formula("D Li D D L", "WHITE CORNER 00");
													break;
												}
											}
											else
											{
												corner_num = search_corner_colour_of_side(DOWN, WHITE, BLUE, LEFT_CENTER_COLOUR);
												if (corner_num) /* Found in Down side */
												{
													switch (corner_num)
													{
													case 1:
														add_formula("L Di Li Li D L", "WHITE CORNER 00");
														break;
													case 2:
														add_formula("Di L Di Li Li D L", "WHITE CORNER 00");
														break;
													case 3:
														add_formula("D L Di Li Li D L", "WHITE CORNER 00");
														break;
													case 4:
														add_formula("D D L Di Li Li D L", "WHITE CORNER 00");
														break;
													}
												}
												else
												{
													corner_num = search_corner_colour_of_side(UP, WHITE, BLUE, LEFT_CENTER_COLOUR);
													if (corner_num) /* Found in UP side */
													{
														switch (corner_num)
														{
														case 1:
															/* In place */
															break;
														case 2:
															add_formula("Bi Di B Li D D L", "WHITE CORNER 00");
															break;
														case 3:
															add_formula("L D Li B D D Bi", "WHITE CORNER 00");
															break;
														case 4:
															add_formula("F Di Fi Li D D L", "WHITE CORNER 00");
															break;
														}
													}
												}
											}
										}
									}
								}
								print_screen();
								apply_formula();
							}
							if (WHITE_CORNER_01_SOLVED)
								stage1_substage_2 = UP_02;
							break;

						case UP_02:
							if (WHITE_CORNER_02_NOT_SOLVED)
							{
								int corner_num = 0;
								corner_num = search_corner_colour_of_side(FRONT, WHITE, BLUE, RIGHT_CENTER_COLOUR);
								if (corner_num) /* Found in Front side */
								{
									switch (corner_num)
									{
									case 1:
										add_formula("Fi Di F R Di Ri", "WHITE CORNER 02");
										break;
									case 2:
										add_formula("F Bi D Fi B", "WHITE CORNER 02");
										break;
									case 3:
										add_formula("R D D Ri", "WHITE CORNER 02");
										break;
									case 4:
										add_formula("Bi D B", "WHITE CORNER 02");
										break;
									}
								}
								else
								{
									corner_num = search_corner_colour_of_side(BACK, WHITE, BLUE, RIGHT_CENTER_COLOUR);
									if (corner_num) /* Found in Back side */
									{
										switch (corner_num)
										{
										case 1:
											add_formula("Bi D D B R D D Ri", "WHITE CORNER 02");
											break;
										case 2:
											/* Solved */
											break;
										case 3:
											add_formula("D R Di Ri", "WHITE CORNER 02");
											break;
										case 4:
											add_formula("D Bi D D B", "WHITE CORNER 02");
											break;
										}
									}
									else
									{
										corner_num = search_corner_colour_of_side(RIGHT, WHITE, BLUE, RIGHT_CENTER_COLOUR);
										if (corner_num) /* Found in Right side */
										{
											switch (corner_num)
											{
											case 1:
												add_formula("Ri Di R R D D Ri", "WHITE CORNER 02");
												break;
											case 2:
												add_formula("R D D Ri Bi D D B", "WHITE CORNER 02");
												break;
											case 3:
												add_formula("Di R D D Ri", "WHITE CORNER 02");
												break;
											case 4:
												add_formula("Di Bi D B", "WHITE CORNER 02");
												break;
											}
										}
										else
										{
											corner_num = search_corner_colour_of_side(LEFT, WHITE, BLUE, RIGHT_CENTER_COLOUR);
											if (corner_num) /* Found in Left side */
											{
												switch (corner_num)
												{
												case 1:
													/* Solved */
													break;
												case 2:
													add_formula("L Bi D D B Li", "WHITE CORNER 02");
													break;
												case 3:
													add_formula("R Di Ri", "WHITE CORNER 02");
													break;
												case 4:
													add_formula("Bi D D B", "WHITE CORNER 02");
													break;
												}
											}
											else
											{
												corner_num = search_corner_colour_of_side(DOWN, WHITE, BLUE, RIGHT_CENTER_COLOUR);
												if (corner_num) /* Found in Down side */
												{
													switch (corner_num)
													{
													case 1:
														add_formula("Bi L Di Li B", "WHITE CORNER 02");
														break;
													case 2:
														add_formula("Di Bi L Di Li B", "WHITE CORNER 02");
														break;
													case 3:
														add_formula("D Bi L Di Li B", "WHITE CORNER 02");
														break;
													case 4:
														add_formula("D D Bi L Di Li B", "WHITE CORNER 02");
														break;
													}
												}
												else
												{
													corner_num = search_corner_colour_of_side(UP, WHITE, BLUE, RIGHT_CENTER_COLOUR);
													if (corner_num) /* Found in UP side */
													{
														switch (corner_num)
														{
														case 1:
															/* Solved */
															break;
														case 2:
															/* In place */
															break;
														case 3:
															add_formula("L R D D Ri Li", "WHITE CORNER 02");
															break;
														case 4:
															add_formula("Ri Di R Bi D D B", "WHITE CORNER 02");
															break;
														}
													}
												}
											}
										}
									}
								}
								print_screen();
								apply_formula();
							}
							if (WHITE_CORNER_02_SOLVED)
								stage1_substage_2 = UP_20;
							break;

						case UP_20:
							if (WHITE_CORNER_03_NOT_SOLVED)
							{
								int corner_num = 0;
								corner_num = search_corner_colour_of_side(FRONT, WHITE, GREEN, LEFT_CENTER_COLOUR);
								if (corner_num) /* Found in Front side */
								{
									switch (corner_num)
									{
									case 1:
										add_formula("Fi Di Di F L D D Li", "WHITE CORNER 20");
										break;
									case 2:
										add_formula("F D D Fi Fi D F", "WHITE CORNER 20");
										break;
									case 3:
										add_formula("D L Di Li", "WHITE CORNER 20");
										break;
									case 4:
										add_formula("D Fi D D F", "WHITE CORNER 20");
										break;
									}
								}
								else
								{
									corner_num = search_corner_colour_of_side(BACK, WHITE, GREEN, LEFT_CENTER_COLOUR);
									if (corner_num) /* Found in Back side */
									{
										switch (corner_num)
										{
										case 1:
											/* Solved */
											break;
										case 2:
											/* Solved */
											break;
										case 3:
											add_formula("L D D Li", "WHITE CORNER 20");
											break;
										case 4:
											add_formula("Fi D F", "WHITE CORNER 20");
											break;
										}
									}
									else
									{
										corner_num = search_corner_colour_of_side(RIGHT, WHITE, GREEN, LEFT_CENTER_COLOUR);
										if (corner_num) /* Found in Right side */
										{
											switch (corner_num)
											{
											case 1:
												add_formula("Ri L Di Li R", "WHITE CORNER 20");
												break;
											case 2:
												/* Solved */
												break;
											case 3:
												add_formula("L Di Li", "WHITE CORNER 20");
												break;
											case 4:
												add_formula("Fi D D F", "WHITE CORNER 20");
												break;
											}
										}
										else
										{
											corner_num = search_corner_colour_of_side(LEFT, WHITE, GREEN, LEFT_CENTER_COLOUR);
											if (corner_num) /* Found in Left side */
											{
												switch (corner_num)
												{
												case 1:
													/* Solved */
													break;
												case 2:
													add_formula("L D D Li Fi D D F", "WHITE CORNER 20");
													break;
												case 3:
													add_formula("Di L D D Li", "WHITE CORNER 20");
													break;
												case 4:
													add_formula("Di Fi D F", "WHITE CORNER 20");
													break;
												}
											}
											else
											{
												corner_num = search_corner_colour_of_side(DOWN, WHITE, GREEN, LEFT_CENTER_COLOUR);
												if (corner_num) /* Found in Down side */
												{
													switch (corner_num)
													{
													case 1:
														add_formula("L Di Li Fi D D F", "WHITE CORNER 20");
														break;
													case 2:
														add_formula("Di L Di Li Fi D D F", "WHITE CORNER 20");
														break;
													case 3:
														add_formula("D L Di Li Fi D D F", "WHITE CORNER 20");
														break;
													case 4:
														add_formula("D D L Di Li Fi D D F", "WHITE CORNER 20");
														break;
													}
												}
												else
												{
													corner_num = search_corner_colour_of_side(UP, WHITE, GREEN, LEFT_CENTER_COLOUR);
													if (corner_num) /* Found in UP side */
													{
														switch (corner_num)
														{
														case 1:
															/* Solved */
															break;
														case 2:
															/* Solved */
															break;
														case 3:
															/* In place */
															break;
														case 4:
															add_formula("Ri D R L Di Li", "WHITE CORNER 20");
															break;
														}
													}
												}
											}
										}
									}
								}
								print_screen();
								apply_formula();
							}
							if (WHITE_CORNER_03_SOLVED)
								stage1_substage_2 = UP_22;
							break;

						case UP_22:
							if (WHITE_CORNER_04_NOT_SOLVED)
							{
								int corner_num = 0;
								corner_num = search_corner_colour_of_side(FRONT, WHITE, GREEN, RIGHT_CENTER_COLOUR);
								if (corner_num) /* Found in Front side */
								{
									switch (corner_num)
									{
									case 1:
										/* Solved */
										break;
									case 2:
										add_formula("Ri D R F D Fi", "WHITE CORNER 22");
										break;
									case 3:
										add_formula("D Ri Di R", "WHITE CORNER 22");
										break;
									case 4:
										add_formula("F D Fi", "WHITE CORNER 22");
										break;
									}
								}
								else
								{
									corner_num = search_corner_colour_of_side(BACK, WHITE, GREEN, RIGHT_CENTER_COLOUR);
									if (corner_num) /* Found in Back side */
									{
										switch (corner_num)
										{
										case 1:
											/* Solved */
											break;
										case 2:
											/* Solved */
											break;
										case 3:
											add_formula("F Di Fi", "WHITE CORNER 22");
											break;
										case 4:
											add_formula("Ri D D R", "WHITE CORNER 22");
											break;
										}
									}
									else
									{
										corner_num = search_corner_colour_of_side(RIGHT, WHITE, GREEN, RIGHT_CENTER_COLOUR);
										if (corner_num) /* Found in Right side */
										{
											switch (corner_num)
											{
											case 1:
												add_formula("Ri Di R D Ri Di R", "WHITE CORNER 22");
												break;
											case 2:
												/* Solved */
												break;
											case 3:
												add_formula("Ri Di R", "WHITE CORNER 22");
												break;
											case 4:
												add_formula("Di F D Fi", "WHITE CORNER 22");
												break;
											}
										}
										else
										{
											corner_num = search_corner_colour_of_side(LEFT, WHITE, GREEN, RIGHT_CENTER_COLOUR);
											if (corner_num) /* Found in Left side */
											{
												switch (corner_num)
												{
												case 1:
													/* Solved */
													break;
												case 2:
													/* Solved */
													break;
												case 3:
													add_formula("F D D Fi", "WHITE CORNER 22");
													break;
												case 4:
													add_formula("Ri D R", "WHITE CORNER 22");
													break;
												}
											}
											else
											{
												corner_num = search_corner_colour_of_side(DOWN, WHITE, GREEN, RIGHT_CENTER_COLOUR);
												if (corner_num) /* Found in Down side */
												{
													switch (corner_num)
													{
													case 1:
														add_formula("D Ri D R F D D Fi", "WHITE CORNER 22");
														break;
													case 2:
														add_formula("Ri D R F D D Fi", "WHITE CORNER 22");
														break;
													case 3:
														add_formula("D D Ri D R F D D Fi", "WHITE CORNER 22");
														break;
													case 4:
														add_formula("Di Ri D R F D D Fi", "WHITE CORNER 22");
														break;
													}
												}
												else
												{
													corner_num = search_corner_colour_of_side(UP, WHITE, GREEN, RIGHT_CENTER_COLOUR);
													if (corner_num) /* Found in UP side */
													{
														switch (corner_num)
														{
														case 1:
															/* Solved */
															break;
														case 2:
															/* Solved */
															break;
														case 3:
															/* Solved */
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
								print_screen();
								apply_formula();
							}
							if (WHITE_CORNER_04_SOLVED)
								stage1_substage_2 = VALIDATE_WHITE_CORNERS;
							break;

						case VALIDATE_WHITE_CORNERS:
							if (WHITE_CORNER_01_SOLVED)
							{
								if (WHITE_CORNER_02_SOLVED)
								{
									if (WHITE_CORNER_03_SOLVED)
									{
										if (WHITE_CORNER_04_SOLVED)
										{
											white_corners_complete = 1;
										}
										else
										{
											stage1_substage_2 = UP_22;
										}
									}
									else
									{
										stage1_substage_2 = UP_20;
									}
								}
								else
								{
									stage1_substage_2 = UP_02;
								}
							}
							else
								stage1_substage_2 = UP_00;
							break;
						}
					}
					/* White corners solved */
					stage1_completed = COMPLETE;
					break;
				}
			}

			stage = STAGE2;
			break;

		case STAGE2:
			/* Move White top to down */
			add_formula("Z Z", " WHITE TO DOWN ");
			print_screen();
			apply_formula();
			if (LINE2_NOT_SOLVED)
			{
				for (stage2_completed = LINE2_SIDE1; stage2_completed <= LINE2_SIDE4; stage2_completed++)
				{
					while (LINE2_FRONT_NOT_SOLVED)
					{
						if (LINE2_MIRROR_CHECK)
						{
							add_formula("F F U U F F U U F F", "  FRONT MIRROR ");
						}
						else
						{
							if (LINE2_FRONT_10_NOT_SOLVED)
							{
								int line2_num = 0;
								/* Search all sides */
								line2_num = search_edge_colour_of_side(FRONT, FRONT_CENTER_COLOUR, LEFT_CENTER_COLOUR);
								if (line2_num) /* Found in front */
								{
									switch (line2_num)
									{
									case 1:
										/* Front Line 2 10 standard formula */
										add_formula("Ui Li U L U F Ui Fi", "    FRONT 10   ");
										break;
									case 2:
										/* In place */
										break;
									case 3:
										/* Solved in mirror case  */
										break;
									case 4:
										/* Invalid case */
										break;
									}
								}
								else
								{
									line2_num = search_edge_colour_of_side(BACK, FRONT_CENTER_COLOUR, LEFT_CENTER_COLOUR);
									if (line2_num) /* Found in back */
									{
										switch (line2_num)
										{
										case 1:
											add_formula("U Li U L U F Ui Fi", "    FRONT 10   ");
											break;
										case 2:
											add_formula("Y U R Ui Ri Ui Fi U F Ui Yi Ui Li U L U F Ui Fi", "    FRONT 10   ");
											break;
										case 3:
											add_formula("Yi Ui Li U L U F Ui Fi U Y Ui Li U L U F Ui Fi", "    FRONT 10   ");
											break;
										case 4:
											/* Invalid case */
											break;
										}
									}
									else
									{
										line2_num = search_edge_colour_of_side(LEFT, FRONT_CENTER_COLOUR, LEFT_CENTER_COLOUR);
										if (line2_num) /* Found in left */
										{
											switch (line2_num)
											{
											case 1:
												add_formula("U U Li U L U F Ui Fi", "    FRONT 10   ");
												break;
											case 2:
												add_formula("Y Y U R Ui Ri Ui Fi U F Y Y Ui Li U L U F Ui Fi", "    FRONT 10   ");
												break;
											case 3:
												add_formula("Ui Li U L U F Ui Fi U U Ui Li U L U F Ui Fi", "    FRONT 10   ");
												break;
											case 4:
												/* Invalid case */
												break;
											}
										}
										else
										{
											line2_num = search_edge_colour_of_side(RIGHT, FRONT_CENTER_COLOUR, LEFT_CENTER_COLOUR);
											if (line2_num) /* Found in right */
											{
												switch (line2_num)
												{
												case 1:
													add_formula("Li U L U F Ui Fi", "    FRONT 10   ");
													break;
												case 2:
													add_formula("U R Ui Ri Ui Fi U F U U Ui Li U L U F Ui Fi", "    FRONT 10   ");
													break;
												case 3:
													add_formula("Y Y Ui Li U L U F Ui Fi Y Y Ui Li U L U F Ui Fi", "    FRONT 10   ");
													break;
												case 4:
													/* Invalid case */
													break;
												}
											}
											else
											{
												line2_num = search_edge_colour_of_side(UP, FRONT_CENTER_COLOUR, LEFT_CENTER_COLOUR);
												if (line2_num) /* Found in UP */
												{
													switch (line2_num)
													{
													case 1:
														add_formula("Yi R Ui Ri Ui Fi U F Y", "    FRONT 10   ");
														break;
													case 2:
														add_formula("Yi U R Ui Ri Ui Fi U F Y", "    FRONT 10   ");
														break;
													case 3:
														add_formula("Yi Ui R Ui Ri Ui Fi U F Y", "    FRONT 10   ");
														break;
													case 4:
														add_formula("Yi U U R Ui Ri Ui Fi U F Y", "    FRONT 10   ");
														break;
													}
												}
												else
												{
													/* Down case is Invalid */
												}
											}
										}
									}
								}
							}
							else if (LINE2_FRONT_12_NOT_SOLVED)
							{
								int line2_num = 0;
								/* Search all sides */
								line2_num = search_edge_colour_of_side(FRONT, FRONT_CENTER_COLOUR, RIGHT_CENTER_COLOUR);
								if (line2_num) /* Found in front */
								{
									switch (line2_num)
									{
									case 1:
										/* Front Line 2 12 standard formula */
										add_formula("U R Ui Ri Ui Fi U F", "    FRONT 12   ");
										break;
									case 2:
										/* Solved */
										break;
									case 3:
										/* In place  */
										break;
									case 4:
										/* Invalid case */
										break;
									}
								}
								else
								{
									line2_num = search_edge_colour_of_side(BACK, FRONT_CENTER_COLOUR, RIGHT_CENTER_COLOUR);
									if (line2_num) /* Found in back */
									{
										switch (line2_num)
										{
										case 1:
											add_formula("Ui R Ui Ri Ui Fi U F", "    FRONT 12   ");
											break;
										case 2:
											add_formula("Y U R Ui Ri Ui Fi U F Yi R Ui Ri Ui Fi U F", "    FRONT 12   ");
											break;
										case 3:
											add_formula("Yi Ui Li U L U F Ui Fi U U Y R Ui Ri Ui Fi U F", "    FRONT 12   ");
											break;
										case 4:
											/* Invalid case */
											break;
										}
									}
									else
									{
										line2_num = search_edge_colour_of_side(LEFT, FRONT_CENTER_COLOUR, RIGHT_CENTER_COLOUR);
										if (line2_num) /* Found in left */
										{
											switch (line2_num)
											{
											case 1:
												add_formula("R Ui Ri Ui Fi U F", "    FRONT 12   ");
												break;
											case 2:
												add_formula("Y Y U R Ui Ri Ui Fi U F Y Y U R Ui Ri Ui Fi U F", "    FRONT 12   ");
												break;
											case 3:
												/* Solved */
												break;
											case 4:
												/* Invalid case */
												break;
											}
										}
										else
										{
											line2_num = search_edge_colour_of_side(RIGHT, FRONT_CENTER_COLOUR, RIGHT_CENTER_COLOUR);
											if (line2_num) /* Found in right */
											{
												switch (line2_num)
												{
												case 1:
													add_formula("U U R Ui Ri Ui Fi U F", "    FRONT 12   ");
													break;
												case 2:
													add_formula("U R Ui Ri Ui Fi U F Ui R Ui Ri Ui Fi U F", "    FRONT 12   ");
													break;
												case 3:
													add_formula("Y Y Ui Li U L U F Ui Fi Y Y U R Ui Ri Ui Fi U F", "    FRONT 12   ");
													break;
												case 4:
													/* Invalid case */
													break;
												}
											}
											else
											{
												line2_num = search_edge_colour_of_side(UP, FRONT_CENTER_COLOUR, RIGHT_CENTER_COLOUR);
												if (line2_num) /* Found in UP */
												{
													switch (line2_num)
													{
													case 1:
														add_formula("Y Li U L U F Ui Fi Yi", "    FRONT 12   ");
														break;
													case 2:
														add_formula("Y U Li U L U F Ui Fi Yi", "    FRONT 12   ");
														break;
													case 3:
														add_formula("Y Ui Li U L U F Ui Fi Yi", "    FRONT 12   ");
														break;
													case 4:
														add_formula("Y U U Li U L U F Ui Fi Yi", "    FRONT 12   ");
														break;
													}
												}
												else
												{
													/* Down case is Invalid */
												}
											}
										}
									}
								}
							}
						}
						print_screen();
						apply_formula();
					}
					add_formula("Yi", "LINE2 NEXT SIDE");
					print_screen();
					apply_formula();
				}
			}
			if (LINE2_SOLVED)
			{
				stage = STAGE3;
			}
			break;

		case STAGE3:
			if (!OLL_solved())
				cube_solve_OLL();
			else
				stage = STAGE4;
			break;

		case STAGE4:
			if(!PLL_solved())
				cube_solve_PLL();
			else
				cube_solved = 1;
			break;

		default:
			stage = ANALYSE;
			break;
		}
	}
	free_formula();
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
	case 'M':
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

static void formulae_update_step(char *step, char *formula_description)
{
	if (!validate_step(step))
	{
		printf(" : Step '%s'", step);
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
		CURRENT_FORMULA.executed = 0;
		strcpy(CURRENT_FORMULA.formula_description, formula_description);

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

static void add_formula(char *formula_new, char *description)
{
	char *token;
	int len = strlen(formula_new);

	char *temp_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp_str)
	{
		print_error("malloc() error in add_formula()");
		exit(1);
	}
	strcpy(temp_str, formula_new);

	formulae_update_step(START_FORMULA, description);

	token = strtok(temp_str, " ");
	int temp = 1;
	while (token)
	{
		formulae_update_step(token, NULL);
		token = strtok(NULL, " ");
	}
	formulae_update_step(END_FORMULA, NULL);

	free(temp_str);
}

static void apply_formula(void)
{
	char temp_step[3];
	for (int i = 0; (i < CURRENT_FORMULA.step_count - 1) || (i == 0); i++)
	{
		MOVE_CURSOR_UP(1);
		MOVE_CURSOR_FORWARD(41);
		for (int j = 0; j < i; j++)
		{
			SET_GREEN_COLOUR;
			SET_FG_WHITE;
			printf("%s", CURRENT_FORMULA.steps[j].step);
			RESET_COLOUR;
			printf(" ");
		}
		strcpy(temp_step, CURRENT_FORMULA.steps[i].step);
		if (stub_cube != 'y')
			wait_for_enter(NULL);

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

		case 'M':
			if (IS_INVERSE)
				Mi();
			else
				M();
			break;

		default:
			print_error("Invalid step in formula\n");
			break;
		}
		update_cube_map();
		print_screen();
	}
	CURRENT_FORMULA.executed = 1;
	printf("\n");
}

static int search_edge_colour_of_side(int side, char face_colour, char colour_pair)
{
	int middle_num = 0;
	switch (side)
	{
	case FRONT:
		if (FRONT_01_FOUND)
			middle_num = 1;
		else if (FRONT_10_FOUND)
			middle_num = 2;
		else if (FRONT_12_FOUND)
			middle_num = 3;
		else if (FRONT_21_FOUND)
			middle_num = 4;
		break;

	case BACK:
		if (BACK_01_FOUND)
			middle_num = 1;
		else if (BACK_10_FOUND)
			middle_num = 2;
		else if (BACK_12_FOUND)
			middle_num = 3;
		else if (BACK_21_FOUND)
			middle_num = 4;
		break;

	case LEFT:
		if (LEFT_01_FOUND)
			middle_num = 1;
		else if (LEFT_10_FOUND)
			middle_num = 2;
		else if (LEFT_12_FOUND)
			middle_num = 3;
		else if (LEFT_21_FOUND)
			middle_num = 4;
		break;

	case RIGHT:
		if (RIGHT_01_FOUND)
			middle_num = 1;
		else if (RIGHT_10_FOUND)
			middle_num = 2;
		else if (RIGHT_12_FOUND)
			middle_num = 3;
		else if (RIGHT_21_FOUND)
			middle_num = 4;
		break;

	case DOWN:
		if (DOWN_01_FOUND)
			middle_num = 1;
		else if (DOWN_10_FOUND)
			middle_num = 2;
		else if (DOWN_12_FOUND)
			middle_num = 3;
		else if (DOWN_21_FOUND)
			middle_num = 4;
		break;

	case UP:
		if (UP_01_FOUND)
			middle_num = 1;
		else if (UP_10_FOUND)
			middle_num = 2;
		else if (UP_12_FOUND)
			middle_num = 3;
		else if (UP_21_FOUND)
			middle_num = 4;
		break;
	}
	return middle_num;
}

static int search_corner_colour_of_side(int side, char face_colour, char side_colour1, char side_colour2)
{
	int corner_num = 0;
	switch (side)
	{
	case FRONT:
		if (FRONT_00_FOUND)
			corner_num = 1;
		else if (FRONT_02_FOUND)
			corner_num = 2;
		else if (FRONT_20_FOUND)
			corner_num = 3;
		else if (FRONT_22_FOUND)
			corner_num = 4;
		break;

	case BACK:
		if (BACK_00_FOUND)
			corner_num = 1;
		else if (BACK_02_FOUND)
			corner_num = 2;
		else if (BACK_20_FOUND)
			corner_num = 3;
		else if (BACK_22_FOUND)
			corner_num = 4;
		break;

	case LEFT:
		if (LEFT_00_FOUND)
			corner_num = 1;
		else if (LEFT_02_FOUND)
			corner_num = 2;
		else if (LEFT_20_FOUND)
			corner_num = 3;
		else if (LEFT_22_FOUND)
			corner_num = 4;
		break;

	case RIGHT:
		if (RIGHT_00_FOUND)
			corner_num = 1;
		else if (RIGHT_02_FOUND)
			corner_num = 2;
		else if (RIGHT_20_FOUND)
			corner_num = 3;
		else if (RIGHT_22_FOUND)
			corner_num = 4;
		break;

	case DOWN:
		if (DOWN_00_FOUND)
			corner_num = 1;
		else if (DOWN_02_FOUND)
			corner_num = 2;
		else if (DOWN_20_FOUND)
			corner_num = 3;
		else if (DOWN_22_FOUND)
			corner_num = 4;
		break;

	case UP:
		if (UP_00_FOUND)
			corner_num = 1;
		else if (UP_02_FOUND)
			corner_num = 2;
		else if (UP_20_FOUND)
			corner_num = 3;
		else if (UP_22_FOUND)
			corner_num = 4;
		break;
	}
	return corner_num;
}

static void cube_init_temp_colour(void)
{
	BACK_00_COLOUR = BLUE;
	BACK_01_COLOUR = BLUE;
	BACK_02_COLOUR = BLUE;
	BACK_10_COLOUR = BLUE;
	BACK_11_COLOUR = BLUE;
	BACK_12_COLOUR = BLUE;
	BACK_20_COLOUR = BLUE;
	BACK_21_COLOUR = BLUE;
	BACK_22_COLOUR = BLUE;

	LEFT_00_COLOUR = RED;
	LEFT_01_COLOUR = RED;
	LEFT_02_COLOUR = RED;
	LEFT_10_COLOUR = RED;
	LEFT_11_COLOUR = RED;
	LEFT_12_COLOUR = RED;
	LEFT_20_COLOUR = RED;
	LEFT_21_COLOUR = RED;
	LEFT_22_COLOUR = RED;

	UP_00_COLOUR = YELLOW;
	UP_01_COLOUR = YELLOW;
	UP_02_COLOUR = YELLOW;
	UP_10_COLOUR = YELLOW;
	UP_11_COLOUR = YELLOW;
	UP_12_COLOUR = YELLOW;
	UP_20_COLOUR = YELLOW;
	UP_21_COLOUR = YELLOW;
	UP_22_COLOUR = YELLOW;

	RIGHT_00_COLOUR = ORANGE;
	RIGHT_01_COLOUR = ORANGE;
	RIGHT_02_COLOUR = ORANGE;
	RIGHT_10_COLOUR = ORANGE;
	RIGHT_11_COLOUR = ORANGE;
	RIGHT_12_COLOUR = ORANGE;
	RIGHT_20_COLOUR = ORANGE;
	RIGHT_21_COLOUR = ORANGE;
	RIGHT_22_COLOUR = ORANGE;

	DOWN_00_COLOUR = WHITE;
	DOWN_01_COLOUR = WHITE;
	DOWN_02_COLOUR = WHITE;
	DOWN_10_COLOUR = WHITE;
	DOWN_11_COLOUR = WHITE;
	DOWN_12_COLOUR = WHITE;
	DOWN_20_COLOUR = WHITE;
	DOWN_21_COLOUR = WHITE;
	DOWN_22_COLOUR = WHITE;

	FRONT_00_COLOUR = GREEN;
	FRONT_01_COLOUR = GREEN;
	FRONT_02_COLOUR = GREEN;
	FRONT_10_COLOUR = GREEN;
	FRONT_11_COLOUR = GREEN;
	FRONT_12_COLOUR = GREEN;
	FRONT_20_COLOUR = GREEN;
	FRONT_21_COLOUR = GREEN;
	FRONT_22_COLOUR = GREEN;

	colour_count.blue = 9;
	colour_count.green = 9;
	colour_count.orange = 9;
	colour_count.red = 9;
	colour_count.white = 9;
	colour_count.yellow = 9;
}

static int cube_which_OLL_case(void)
{
	int case_pass = -1;
	int break_case = 0;
	int three_check = 0;
	while (three_check < 3)
	{
		case_pass = -1;
		for (int i = 0; (i < 57) && (case_pass == -1); i++)
		{
			break_case = 0;
			int side_x = 0, side_y = 0, OLL_trav = 0;
			/* Checking up */
			for (side_x = 0; (side_x < 3) && (!break_case); side_x++)
			{
				for (side_y = 0; (side_y < 3) && (!break_case); side_y++, OLL_trav++)
				{
					switch (OLL_case[i][OLL_trav])
					{
					case 'x':
						if (is_yellow(cube.sides.up.colour[side_x][side_y]))
							break_case = 1;
						break;
					case 'y':
						if (!is_yellow(cube.sides.up.colour[side_x][side_y]))
							break_case = 1;
						break;
					}
				}
			}
			if (break_case)
				continue;
			
			/* Checking back */
			side_x = 0;
			side_y = 2;
			for (OLL_trav = 9; (OLL_trav <= 11) && (!break_case); OLL_trav++)
			{
				switch (OLL_case[i][OLL_trav])
				{
				case 'x':
					if (is_yellow(cube.sides.back.colour[side_x][side_y--]))
						break_case = 1;
					break;
				case 'y':
					if (!is_yellow(cube.sides.back.colour[side_x][side_y--]))
						break_case = 1;
					break;
				}
			}
			if (break_case)
				continue;

			/* Checking right */
			side_x = 0;
			side_y = 2;
			for (OLL_trav = 12; (OLL_trav <= 14) && (!break_case); OLL_trav++)
			{
				switch (OLL_case[i][OLL_trav])
				{
				case 'x':
					if (is_yellow(cube.sides.right.colour[side_x][side_y--]))
						break_case = 1;
					break;
				case 'y':
					if (!is_yellow(cube.sides.right.colour[side_x][side_y--]))
						break_case = 1;
					break;
				}
			}
			if (break_case)
				continue;

			/* Checking front */
			side_x = 0;
			side_y = 2;
			for (OLL_trav = 15; (OLL_trav <= 17) && (!break_case); OLL_trav++)
			{
				switch (OLL_case[i][OLL_trav])
				{
				case 'x':
					if (is_yellow(cube.sides.front.colour[side_x][side_y--]))
						break_case = 1;
					break;
				case 'y':
					if (!is_yellow(cube.sides.front.colour[side_x][side_y--]))
						break_case = 1;
					break;
				}
			}
			if (break_case)
				continue;

			/* Checking left */
			side_x = 0;
			side_y = 2;
			for (OLL_trav = 18; (OLL_trav <= 20) && (!break_case); OLL_trav++)
			{
				switch (OLL_case[i][OLL_trav])
				{
				case 'x':
					if (is_yellow(cube.sides.left.colour[side_x][side_y--]))
						break_case = 1;
					break;
				case 'y':
					if (!is_yellow(cube.sides.left.colour[side_x][side_y--]))
						break_case = 1;
					break;
				}
			}
			if (break_case)
				continue;
			else
				case_pass = i;
		}

		if (case_pass == -1)
		{
			add_formula("U", "   OLL ROTATE  ");
			print_screen();
			apply_formula();
			three_check++;
		}
		else
			break;
	}
	return case_pass;
}

static void cube_solve_OLL(void)
{
	int OLL_case_num = cube_which_OLL_case();
	char msg[20];
	sprintf(msg,"  TOP YELLOW %2d",OLL_case_num);
	add_formula(FORMULA_OLL[OLL_case_num], msg);
	print_screen();
	apply_formula();
}

static int OLL_solved(void)
{
	int solved = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (!is_yellow(cube.sides.up.colour[i][j]))
			{
				solved = 0;
			}
			if (!solved)
				break;
		}
		if (!solved)
			break;
	}
	return solved;
}

static void cube_solve_PLL(void)
{

}

static int PLL_solved(void)
{
	/* Return 1 if solved else returns >1 with different numbers of cases of PLL*/
}

static void cube_shuffle(void)
{
	/* Random number generation */
	time_t rawtime;
	struct tm *timeinfo;

	char time_val[20];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	sprintf(time_val, "%d%d%d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

	int opt = atoi(time_val) % 7;

	switch (opt)
	{
	case 0:
		add_formula("D D U F F Ri U U Fi L B Fi L L Di Ri D B B Ri U U F F R R B Ri Di Ri Bi D U U L L R F Li Fi", "SHUFFLE CUBE");
		break;
	case 1:
		add_formula("Ri Bi U Fi L R Ui Bi L Di Bi F F Li R D B B Fi U L D Bi L R U L U B F Ri D", "SHUFFLE CUBE");
		break;
	case 2:
		add_formula("L L R R F L R Bi U U F F D D Ri Di L Ri D D Ui F L L Ri F F D D B B U U B B Ri F F D D Li U Ri U U", "SHUFFLE CUBE");
		break;
	case 3:
		add_formula("B Fi L L F R R Fi D U U L Bi Ri D Bi F F U L L U U F D U U R D L D U U Bi U U L L D Fi", "SHUFFLE CUBE");
		break;
	case 4:
		add_formula("D D F D D Ui Fi Di Ui Bi Fi L B D Bi Fi Di U U Bi D Li B D Bi U B B Fi L L Di U L L Bi", "SHUFFLE CUBE");
		break;
	case 5:
		add_formula("Ri B L Ri D D Bi Li U F L L R R U U B Ui Li U Bi Di Li D D R D D F Li U U B Ri D D F L", "SHUFFLE CUBE");
		break;
	case 6:
		add_formula("Ri D Bi Li U U Fi L L F U Fi D D U Li Bi Li Ri F F U Bi L D L L R D D Fi D D B B Li B D", "SHUFFLE CUBE");
		break;
	default:
		add_formula("F D D L Bi Li U U B Ui Ri B L L F Di Ui Bi Fi L D D Ui B B Fi D Bi D D Ui Li R R D D F R", "SHUFFLE CUBE");
		break;
	}

	apply_formula();
	free_formula();
}

static void free_formula(void)
{
	for (int i = 0; i < formula_count; i++)
	{
		free((formula + i)->steps);
		(formula + i)->steps = NULL;
	}

	free(formula);
	formula = NULL;
	formula_count = 0;
}