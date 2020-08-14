#include"../includes/movements.h"
#include"../includes/cube.h"
#include"../includes/matrix_operations.h"

/* Cube rotation functions */
void R(void)
{
	rotate_clockwise(&cube.sides.right);
	up_line_move(UP_COLUMN2);
}

void Ri(void)
{
	rotate_anti_clockwise(&cube.sides.right);
	up_line_move(UP_COLUMN2_i);
}

void L(void)
{
	rotate_clockwise(&cube.sides.left);
	up_line_move(UP_COLUMN0_i);
}

void Li(void)
{
	rotate_anti_clockwise(&cube.sides.left);
	up_line_move(UP_COLUMN0);
}

void U(void)
{
	rotate_clockwise(&cube.sides.up);
    front_line_move(FRONT_ROW0);
}

void Ui(void)
{
	rotate_anti_clockwise(&cube.sides.up);
    front_line_move(FRONT_ROW0_i);
}

void D(void)
{
	rotate_clockwise(&cube.sides.down);
    front_line_move(FRONT_ROW2_i);
}

void Di(void)
{
	rotate_anti_clockwise(&cube.sides.down);
    front_line_move(FRONT_ROW2);
}

void F(void)
{
	rotate_clockwise(&cube.sides.front);
	up_line_move(UP_ROW2);
}

void Fi(void)
{
	rotate_anti_clockwise(&cube.sides.front);
	up_line_move(UP_ROW2_i);
}

void B(void)
{
	rotate_clockwise(&cube.sides.back);
	up_line_move(UP_ROW0_i);
}

void Bi(void)
{
	rotate_anti_clockwise(&cube.sides.back);
	up_line_move(UP_ROW0);
}

void r(void)
{
	R();
	up_line_move(UP_COLUMN1);
}

void ri(void)
{
	Ri();
	up_line_move(UP_COLUMN1_i);
}

void l(void)
{
	L();
	up_line_move(UP_COLUMN1_i);
}

void li(void)
{
	Li();
	up_line_move(UP_COLUMN1);
}

void u(void)
{
    U();
    front_line_move(FRONT_ROW1);
}

void ui(void)
{
    Ui();
    front_line_move(FRONT_ROW1_i);
}

void d(void)
{
    D();
    front_line_move(FRONT_ROW1_i);
}

void di(void)
{
    Di();
    front_line_move(FRONT_ROW1);
}

void f(void)
{
	F();
	up_line_move(UP_ROW1);
}

void fi(void)
{
	Fi();
	up_line_move(UP_ROW1_i);
}

void b(void)
{
	B();
	up_line_move(UP_ROW1_i);
}

void bi(void)
{
	Bi();
	up_line_move(UP_ROW1);
}

void X(void)
{
	front_line_move(FRONT_COLUMN0);
	front_line_move(FRONT_COLUMN1);
	front_line_move(FRONT_COLUMN2);
}

void Y(void)
{
	front_line_move(FRONT_ROW0);
	front_line_move(FRONT_ROW1);
	front_line_move(FRONT_ROW2);
}

void Z(void)
{
	up_line_move(UP_ROW0);
	up_line_move(UP_ROW1);
	up_line_move(UP_ROW2);
}

void Xi(void)
{
	front_line_move(FRONT_COLUMN0_i);
	front_line_move(FRONT_COLUMN1_i);
	front_line_move(FRONT_COLUMN2_i);
}

void Yi(void)
{
	front_line_move(FRONT_ROW0_i);
	front_line_move(FRONT_ROW1_i);
	front_line_move(FRONT_ROW2_i);
}

void Zi(void)
{
	up_line_move(UP_ROW0_i);
	up_line_move(UP_ROW1_i);
	up_line_move(UP_ROW2_i);
}

void up_line_move(int line)
{
	char temp[3];
	int row_index=0,column_index=0;
	int up_rotate_direction=0;

	switch(line)
	{
		case UP_ROW0 :
			up_rotate_direction = UP_ROW_CLOCKWISE;
			row_index = 0;
			break;

		case UP_ROW1 :
			up_rotate_direction = UP_ROW_CLOCKWISE;
			row_index = 1;
			break;
			
		case UP_ROW2 :
			up_rotate_direction = UP_ROW_CLOCKWISE;
			row_index = 2;
			break;
			
		case UP_COLUMN0 :
			up_rotate_direction = UP_COLUMN_CLOCKWISE;
			column_index = 0;
			break;
			
		case UP_COLUMN1 :
			up_rotate_direction = UP_COLUMN_CLOCKWISE;
			column_index = 1;
			break;
			
		case UP_COLUMN2 :
			up_rotate_direction = UP_COLUMN_CLOCKWISE;
			column_index = 2;
			break;

		case UP_ROW0_i :
			up_rotate_direction = UP_ROW_ANTI_CLOCKWISE;
			row_index = 0;
			break;

		case UP_ROW1_i :
			up_rotate_direction = UP_ROW_ANTI_CLOCKWISE;
			row_index = 1;
			break;
			
		case UP_ROW2_i :
			up_rotate_direction = UP_ROW_ANTI_CLOCKWISE;
			row_index = 2;
			break;
			
		case UP_COLUMN0_i :
			up_rotate_direction = UP_COLUMN_ANTI_CLOCKWISE;
			column_index = 0;
			break;
			
		case UP_COLUMN1_i :
			up_rotate_direction = UP_COLUMN_ANTI_CLOCKWISE;
			column_index = 1;
			break;
			
		case UP_COLUMN2_i :
			up_rotate_direction = UP_COLUMN_ANTI_CLOCKWISE;
			column_index = 2;
			break;
			
	}
	switch(up_rotate_direction)
	{
		case UP_ROW_CLOCKWISE :
			temp[0] = cube.sides.up.colour[row_index][0];
			temp[1] = cube.sides.up.colour[row_index][1];
			temp[2] = cube.sides.up.colour[row_index][2];

			cube.sides.up.colour[row_index][0] = cube.sides.left.colour[2][row_index];
			cube.sides.up.colour[row_index][1] = cube.sides.left.colour[1][row_index];
			cube.sides.up.colour[row_index][2] = cube.sides.left.colour[0][row_index];

			cube.sides.left.colour[2][row_index] = cube.sides.down.colour[2-row_index][2];
			cube.sides.left.colour[1][row_index] = cube.sides.down.colour[2-row_index][1];
			cube.sides.left.colour[0][row_index] = cube.sides.down.colour[2-row_index][0];

			cube.sides.down.colour[2-row_index][2] = cube.sides.right.colour[0][2-row_index];
			cube.sides.down.colour[2-row_index][1] = cube.sides.right.colour[1][2-row_index];
			cube.sides.down.colour[2-row_index][0] = cube.sides.right.colour[2][2-row_index];

			cube.sides.right.colour[0][2-row_index] = temp[0];
			cube.sides.right.colour[1][2-row_index] = temp[1];
			cube.sides.right.colour[2][2-row_index] = temp[2];
			break;

		case UP_ROW_ANTI_CLOCKWISE :
			temp[0] = cube.sides.up.colour[row_index][0];
			temp[1] = cube.sides.up.colour[row_index][1];
			temp[2] = cube.sides.up.colour[row_index][2];

			cube.sides.up.colour[row_index][0] = cube.sides.right.colour[0][2-row_index];
			cube.sides.up.colour[row_index][1] = cube.sides.right.colour[1][2-row_index];
			cube.sides.up.colour[row_index][2] = cube.sides.right.colour[2][2-row_index];

			cube.sides.right.colour[0][2-row_index] = cube.sides.down.colour[2-row_index][2];
			cube.sides.right.colour[1][2-row_index] = cube.sides.down.colour[2-row_index][1];
			cube.sides.right.colour[2][2-row_index] = cube.sides.down.colour[2-row_index][0];

			cube.sides.down.colour[2-row_index][2] = cube.sides.left.colour[2][row_index];
			cube.sides.down.colour[2-row_index][1] = cube.sides.left.colour[1][row_index];
			cube.sides.down.colour[2-row_index][0] = cube.sides.left.colour[0][row_index];

			cube.sides.left.colour[2][row_index] = temp[0];
			cube.sides.left.colour[1][row_index] = temp[1];
			cube.sides.left.colour[0][row_index] = temp[2];

			break;

		case UP_COLUMN_CLOCKWISE :
			temp[0] = cube.sides.up.colour[0][column_index];
			temp[1] = cube.sides.up.colour[1][column_index];
			temp[2] = cube.sides.up.colour[2][column_index];

			cube.sides.up.colour[0][column_index] = cube.sides.front.colour[0][column_index];
			cube.sides.up.colour[1][column_index] = cube.sides.front.colour[1][column_index];
			cube.sides.up.colour[2][column_index] = cube.sides.front.colour[2][column_index];

			cube.sides.front.colour[0][column_index] = cube.sides.down.colour[0][column_index];
			cube.sides.front.colour[1][column_index] = cube.sides.down.colour[1][column_index];
			cube.sides.front.colour[2][column_index] = cube.sides.down.colour[2][column_index];
			
			cube.sides.down.colour[0][column_index] = cube.sides.back.colour[2][2-column_index];
			cube.sides.down.colour[1][column_index] = cube.sides.back.colour[1][2-column_index];
			cube.sides.down.colour[2][column_index] = cube.sides.back.colour[0][2-column_index];

			cube.sides.back.colour[2][2-column_index] = temp[0];
			cube.sides.back.colour[1][2-column_index] = temp[1];
			cube.sides.back.colour[0][2-column_index] = temp[2];

			break;

		case UP_COLUMN_ANTI_CLOCKWISE :
			temp[0] = cube.sides.up.colour[0][column_index];
			temp[1] = cube.sides.up.colour[1][column_index];
			temp[2] = cube.sides.up.colour[2][column_index];

			cube.sides.up.colour[0][column_index] = cube.sides.back.colour[2][2-column_index];
			cube.sides.up.colour[1][column_index] = cube.sides.back.colour[1][2-column_index];
			cube.sides.up.colour[2][column_index] = cube.sides.back.colour[0][2-column_index];

			cube.sides.back.colour[2][2-column_index] = cube.sides.down.colour[0][column_index];
			cube.sides.back.colour[1][2-column_index] = cube.sides.down.colour[1][column_index];
			cube.sides.back.colour[0][2-column_index] = cube.sides.down.colour[2][column_index];

			cube.sides.down.colour[0][column_index] = cube.sides.front.colour[0][column_index];
			cube.sides.down.colour[1][column_index] = cube.sides.front.colour[1][column_index];
			cube.sides.down.colour[2][column_index] = cube.sides.front.colour[2][column_index];

			cube.sides.front.colour[0][column_index] = temp[0];
			cube.sides.front.colour[1][column_index] = temp[1];
			cube.sides.front.colour[2][column_index] = temp[2];
						
			break;
	}
}



void front_line_move(int line)
{
	char temp[3];
	int row_index=0,column_index=0;
	int front_rotate_direction=0;

	switch(line)
	{
		case FRONT_ROW0 :
			front_rotate_direction = FRONT_ROW_CLOCKWISE;
			row_index = 0;
			break;

		case FRONT_ROW1 :
			front_rotate_direction = FRONT_ROW_CLOCKWISE;
			row_index = 1;
			break;
			
		case FRONT_ROW2 :
			front_rotate_direction = FRONT_ROW_CLOCKWISE;
			row_index = 2;
			break;
			
		case FRONT_COLUMN0 :
			front_rotate_direction = FRONT_COLUMN_CLOCKWISE;
			column_index = 0;
			break;
			
		case FRONT_COLUMN1 :
			front_rotate_direction = FRONT_COLUMN_CLOCKWISE;
			column_index = 1;
			break;
			
		case FRONT_COLUMN2 :
			front_rotate_direction = FRONT_COLUMN_CLOCKWISE;
			column_index = 2;
			break;

		case FRONT_ROW0_i :
			front_rotate_direction = FRONT_ROW_ANTI_CLOCKWISE;
			row_index = 0;
			break;

		case FRONT_ROW1_i :
			front_rotate_direction = FRONT_ROW_ANTI_CLOCKWISE;
			row_index = 1;
			break;
			
		case FRONT_ROW2_i :
			front_rotate_direction = FRONT_ROW_ANTI_CLOCKWISE;
			row_index = 2;
			break;
			
		case FRONT_COLUMN0_i :
			front_rotate_direction = FRONT_COLUMN_ANTI_CLOCKWISE;
			column_index = 0;
			break;
			
		case FRONT_COLUMN1_i :
			front_rotate_direction = FRONT_COLUMN_ANTI_CLOCKWISE;
			column_index = 1;
			break;
			
		case FRONT_COLUMN2_i :
			front_rotate_direction = FRONT_COLUMN_ANTI_CLOCKWISE;
			column_index = 2;
			break;
			
	}
	switch(front_rotate_direction)
	{
		case FRONT_ROW_CLOCKWISE :
			temp[0] = cube.sides.front.colour[row_index][0];
			temp[1] = cube.sides.front.colour[row_index][1];
			temp[2] = cube.sides.front.colour[row_index][2];

			cube.sides.front.colour[row_index][0] = cube.sides.right.colour[row_index][0];
			cube.sides.front.colour[row_index][1] = cube.sides.right.colour[row_index][1];
			cube.sides.front.colour[row_index][2] = cube.sides.right.colour[row_index][2];

			cube.sides.right.colour[row_index][0] = cube.sides.back.colour[row_index][0];
			cube.sides.right.colour[row_index][1] = cube.sides.back.colour[row_index][1];
			cube.sides.right.colour[row_index][2] = cube.sides.back.colour[row_index][2];

			cube.sides.back.colour[row_index][0] = cube.sides.left.colour[row_index][0];
			cube.sides.back.colour[row_index][1] = cube.sides.left.colour[row_index][1];
			cube.sides.back.colour[row_index][2] = cube.sides.left.colour[row_index][2];

			cube.sides.left.colour[row_index][0] = temp[0];
			cube.sides.left.colour[row_index][1] = temp[1];
			cube.sides.left.colour[row_index][2] = temp[2];
			break;

		case FRONT_ROW_ANTI_CLOCKWISE :
			temp[0] = cube.sides.front.colour[row_index][0];
			temp[1] = cube.sides.front.colour[row_index][1];
			temp[2] = cube.sides.front.colour[row_index][2];

			cube.sides.front.colour[row_index][0] = cube.sides.left.colour[row_index][0];
			cube.sides.front.colour[row_index][1] = cube.sides.left.colour[row_index][1];
			cube.sides.front.colour[row_index][2] = cube.sides.left.colour[row_index][2];

			cube.sides.left.colour[row_index][0] = cube.sides.back.colour[row_index][0];
			cube.sides.left.colour[row_index][1] = cube.sides.back.colour[row_index][1];
			cube.sides.left.colour[row_index][2] = cube.sides.back.colour[row_index][2];

			cube.sides.back.colour[row_index][0] = cube.sides.right.colour[row_index][0];
			cube.sides.back.colour[row_index][1] = cube.sides.right.colour[row_index][1];
			cube.sides.back.colour[row_index][2] = cube.sides.right.colour[row_index][2];

			cube.sides.right.colour[row_index][0] = temp[0];
			cube.sides.right.colour[row_index][1] = temp[1];
			cube.sides.right.colour[row_index][2] = temp[2];

			break;

		case FRONT_COLUMN_CLOCKWISE :
			temp[0] = cube.sides.front.colour[0][column_index];
			temp[1] = cube.sides.front.colour[1][column_index];
			temp[2] = cube.sides.front.colour[2][column_index];

			cube.sides.front.colour[0][column_index] = cube.sides.down.colour[0][column_index];
			cube.sides.front.colour[1][column_index] = cube.sides.down.colour[1][column_index];
			cube.sides.front.colour[2][column_index] = cube.sides.down.colour[2][column_index];

			cube.sides.down.colour[0][column_index] = cube.sides.back.colour[2][2-column_index];
			cube.sides.down.colour[1][column_index] = cube.sides.back.colour[1][2-column_index];
			cube.sides.down.colour[2][column_index] = cube.sides.back.colour[0][2-column_index];

			cube.sides.back.colour[2][2-column_index] = cube.sides.up.colour[0][column_index];
			cube.sides.back.colour[1][2-column_index] = cube.sides.up.colour[1][column_index];
			cube.sides.back.colour[0][2-column_index] = cube.sides.up.colour[2][column_index];

			cube.sides.up.colour[0][column_index] = temp[0];
			cube.sides.up.colour[1][column_index] = temp[1];
			cube.sides.up.colour[2][column_index] = temp[2];

			break;

		case FRONT_COLUMN_ANTI_CLOCKWISE :
			temp[0] = cube.sides.front.colour[0][column_index];
			temp[1] = cube.sides.front.colour[1][column_index];
			temp[2] = cube.sides.front.colour[2][column_index];

			cube.sides.front.colour[0][column_index] = cube.sides.up.colour[0][column_index];
			cube.sides.front.colour[1][column_index] = cube.sides.up.colour[1][column_index];
			cube.sides.front.colour[2][column_index] = cube.sides.up.colour[2][column_index];

			cube.sides.up.colour[0][column_index] = cube.sides.back.colour[2][2-column_index];
			cube.sides.up.colour[1][column_index] = cube.sides.back.colour[1][2-column_index];
			cube.sides.up.colour[2][column_index] = cube.sides.back.colour[0][2-column_index];

			cube.sides.back.colour[2][2-column_index] = cube.sides.down.colour[0][column_index];
			cube.sides.back.colour[1][2-column_index] = cube.sides.down.colour[1][column_index];
			cube.sides.back.colour[0][2-column_index] = cube.sides.down.colour[2][column_index];

			cube.sides.down.colour[0][column_index] = temp[0];
			cube.sides.down.colour[1][column_index] = temp[1];
			cube.sides.down.colour[2][column_index] = temp[2];
						
			break;
	}
}
