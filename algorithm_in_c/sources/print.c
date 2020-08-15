#include "../includes/print.h"
#include "../includes/colour.h"
#include "../includes/cube.h"
#include <stdio.h>
#include <string.h>

int input;

void print_back(void)
{
    RESET_COLOUR;
    printf("%s", cube.cube_map[2]);

    for (int j = 3; j < 6; j++)
    {
        for (int i = 0; i < strlen(cube.cube_map[j]); i++)
        {

            switch (cube.cube_map[j][i])
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
            if (cube.cube_map[j][i] == '\n')
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
    printf("%s%s", cube.cube_map[6], cube.cube_map[7]);

    for (int j = 0; j < 3; j++)
    {
        j += 8;
        for (int i = 0; i < strlen(cube.cube_map[j]); i++)
        {
            switch (cube.cube_map[j][i])
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
            if (cube.cube_map[j][i] == '\n')
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
    printf("%s%s", cube.cube_map[11], cube.cube_map[12]);

    for (int j = 13; j < 16; j++)
    {
        for (int i = 0; i < strlen(cube.cube_map[j]); i++)
        {
            switch (cube.cube_map[j][i])
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
            if (cube.cube_map[j][i] == '\n')
                printf("\n");
            else
                printf(" ");
        }
    }
    RESET_COLOUR;
}

void print_colour(char colour, char *msg)
{
    switch (colour)
    {
    case RED:
        SET_FG_RED;
        break;
    case GREEN:
        SET_FG_GREEN;
        break;
    case BLUE:
        SET_FG_BLUE;
        break;
    case ORANGE:
        SET_FG_ORANGE;
        break;
    case WHITE:
        SET_FG_WHITE;
        break;
    case YELLOW:
        SET_FG_YELLOW;
        break;
    case BLACK:
        SET_FG_BLACK;
        break;
    }
    printf("%s", msg);
    RESET_COLOUR;
}

void print_error(char *msg)
{
    printf("[ ");
    print_colour(RED, "Error");
    printf(" ] : %s\n", msg);
}

void print_green_msg(char *title, char *msg)
{
    printf("[ ");
    print_colour(GREEN, title);
    printf(" ] : %s\n", msg);
}

void print_input_message(void)
{
    printf("Colour codes :\n");

    print_colour(WHITE, " WHITE ");
    printf("   :  ");
    print_colour(WHITE, "w ");
    printf("<enter>\n");

    print_colour(RED, " RED   ");
    printf("   :  ");
    print_colour(RED, "r");
    printf("<enter>\n");

    print_colour(GREEN, " GREEN ");
    printf("   :  ");
    print_colour(GREEN, "g");
    printf("<enter>\n");

    print_colour(BLUE, " BLUE  ");
    printf("   :  ");
    print_colour(BLUE, "b");
    printf("<enter>\n");

    print_colour(YELLOW, " YELLOW");
    printf("   :  ");
    print_colour(YELLOW, "y");
    printf("<enter>\n");

    print_colour(ORANGE, " ORANGE");
    printf("   :  ");
    print_colour(ORANGE, "o");
    printf("<enter>\n");

    printf(" EXIT     :  'x'<enter>\n");
}

void print_cube(void)
{
    /* Set background to black for two lines */
    printf("%s%s", cube.cube_map[0], cube.cube_map[1]);
    /* Print back */
    print_back();

    /* Print LEFT,UP,RIGHT,DOWN in order */
    print_lurd();

    /* Print front */
    print_front();
}

void print_screen(void)
{
    /* Clears screen */
    CLEAR_SCREEN;

    if (input)
    {
        print_input_message();
    }

    print_cube();

    if (formula_to_apply)
    {
        print_formula();
    }
    printf("\n");
    RESET_COLOUR;
}

void print_formula(void)
{
    char temp_title[12];

    sprintf(temp_title, "Formula - %2d", formula_count);

    print_green_msg(temp_title, "");

    for (int i = 0; i < CURRENT_FORMULA.step_count - 1; i++)
    {
        printf("%s ", CURRENT_FORMULA.steps[i]);
    }
    printf("\n");
}