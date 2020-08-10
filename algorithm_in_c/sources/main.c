/* File Description: main application file*/

/*** Heade file inclusion ***/
#include"../includes/cube.h"
#include<stdio.h>

/* main function */
int main(int argc,char *argv[])
{
	int correct_input=0;
	char opt;
	do
	{
		CLEAR_SCREEN;
		cube_init();
		cube_print();

		correct_input = colour_count_valid_check();
		if(!correct_input)
		{
			printf("Please enter colours correctly. Press <Enter> to continue");
			getchar();
			continue;
		}

		printf("Verify the cube sides you entered.\nWant to change cube colours?[y/n]:");
		scanf(" %c",&opt);
		switch(opt)
		{
			case 'y':
			case 'Y':
				correct_input=0;
				break;

			case 'n':
			case 'N':
				correct_input=1;
				break;

			default:
				printf("Invalid option\n");
				break;
		}
	}while(!correct_input);
	printf("DONE\n");
	return 0;
}
