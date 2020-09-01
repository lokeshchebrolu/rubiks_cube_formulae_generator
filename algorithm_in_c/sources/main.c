/* File Description: main application file*/

/*** Heade file inclusion ***/
#include "../includes/cube.h"
#include "../includes/colour.h"
#include "../includes/print.h"
#include <stdio.h>

static int nullify;

/* main function */
int main(int argc, char *argv[])
{
	int correct_input = 0;
	char opt;
	do
	{
		CLEAR_SCREEN;
		cube_init();
		print_screen();

		correct_input = colour_count_valid_check();
		wait_for_enter("");
		if (!correct_input)
		{
			printf(" Please enter colours correctly. Press <Enter> to continue");
			getchar();
			continue;
		}

		if (stub_cube != 'y')
		{
			printf(" Verify the cube sides you entered.\n Want to change cube colours?[y/n]:");
			nullify = scanf(" %c", &opt);
			switch (opt)
			{
			case 'y':
			case 'Y':
				correct_input = 0;
				break;

			case 'n':
			case 'N':
				correct_input = 1;
				break;

			default:
				printf(" Invalid option\n");
				break;
			}
		}
		else
		{
			correct_input = 1;
			stub_cube = 'n';
		}

	} while (!correct_input);

	cube_solve();

	return 0;
}
