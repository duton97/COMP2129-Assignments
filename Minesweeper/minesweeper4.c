/**
 * comp2129 - assignment 1
 * Vincent Zhang
 * vzha7446
 */

#include <stdio.h>

struct bomb {
	char ch;
	int x;
	int y;
};
typedef struct bomb Bomb;

int checkg(char word, int num1, int num2){
	if (word != 'g' || num1*num2 < 9 || num1 > 100 || num2 > 100 || num1 < 1 || num2 < 1) { //Check for initial input of size grid
		return 1; //Failed
	}
	return 0; //Passes
}

int checkb(Bomb* bomb1, Bomb* bomb2, int row, int col){ //Pointer to bomb, second bomb, row and col of the grid
	if (bomb1->ch!='b' || bomb1->x >= row || bomb1->y >= col || (bomb1->x==bomb2->x && bomb1->y==bomb2->y) || bomb1->x < 1 || bomb1->y < 1) {
		//Check if input has b
		//Check if coordinate x of the bomb is smaller than row
		//Check if coordinate y of the bomb is smaller than col
		//Check if the bomb's coordinates are the same to other boms

		printf("%d %d %d %d", bomb1->x, bomb1->y, bomb2->x, bomb2->y);
		return 1;
	}
	return 0;
}


int main(void){
	char gridInput[15]; //5 inputs + null terminator
	int row;
	int col;
	char gridL;


	fgets(gridInput, 15, stdin);
	gridL = gridInput[0];
	sscanf(&gridInput[2], " %d", &row);

	int i = 0;
	while (gridInput[4+i] == '0' || gridInput[4+i] == ' '){ //For width and length of more than 1 digit
		i = i + 1;
	}
	sscanf(&gridInput[4+i], " %d", &col);

	if (checkg(gridL, row, col) == 1){
		printf("Invalid Input");
		return 1;
	}

	Bomb bombGrid[row][col]; //Create grid to place the bombs

	Bomb bombs[10]; //Declare array to hold the bombs

	Bomb bomb_1, bomb_2, bomb_3, bomb_4, bomb_5, bomb_6, bomb_7, bomb_8, bomb_9, bomb_10; //Declare 10 bombs

	bombs[0] = bomb_1; bombs[1] = bomb_2; bombs[2] = bomb_3; bombs[3] = bomb_4; bombs[4] = bomb_5;
	bombs[5] = bomb_6; bombs[6] = bomb_7; bombs[7] = bomb_8; bombs[8] = bomb_9; bombs[9] = bomb_10; //Store boms in the array

	int line;
	char bombInput[10][15]; //10 rows, 10 inputs
	for (line = 0; line < 10; line++){
		fgets(bombInput[line], 10, stdin);
		sscanf(&bombInput[line][0], " %c", &bombs[line].ch); //Place the letter of input as ch of bomb
		sscanf(&bombInput[line][2], " %d", &bombs[line].x); //Place the first int of input as x of bomb
		sscanf(&bombInput[line][4], " %d", &bombs[line].y); //Place the second int of input as y of bomb

		//printf("%c %c %d %d", bombInput[line][2], bombInput[line][4], bombs[line].x, bombs[line].y);

		bombGrid[bombs[line].x][bombs[line].y] = bombs[line]; //Place the bomb into the bombGrid

		printf("%d", bombGrid[bombs[line].x][bombs[line].y].x);

		if(line == 0){ //Check for validation of the first input
			if (bombs[line].ch != 'b' || bombs[line].x >= row || bombs[line].y >= col){
				printf("Error");
				return 1; //fail
			}
		}

		for (int indexB = 0; indexB < line; indexB++){ //To compare to other bombs and if its valid
			if (checkb(&bombs[line], &bombs[indexB], row, col) == 1){
				printf("Error");
				return 1;
			}
		}
	}

	return 0;

}

int grid[10]; //Array
int *ptr = &grid; //Pointer to the array

int *pointer[]; //Array of pointers
