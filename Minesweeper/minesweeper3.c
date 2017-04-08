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
	if (word != 'g' || num1*num2 < 9) { //Check for initial input of size grid
		//printf("%c", word);
		return 1; //Failed
	}
	return 0; //Passes
}


int main(void){
	char gridInput[6]; //5 inputs + null terminator
	int row;
	int col;
	char gridL;

//	char bombInput[6];
//	int coorx;
//	int coory;
//	char bombCh;

	fgets(gridInput, 6, stdin);
	gridL = gridInput[0];
	sscanf(&gridInput[2], " %d", &row);
	sscanf(&gridInput[4], " %d", &col);

	if (checkg(gridL, row, col) == 1){
		printf("Invalid Input");
		return 1;
	}


	Bomb bombs[10]; //Declare array for bombs

	Bomb bomb_1, bomb_2, bomb_3, bomb_4, bomb_5, bomb_6, bomb_7, bomb_8, bomb_9, bomb_10; //Declare 10 bombs

	bombs[0] = bomb_1; bombs[1] = bomb_2; bombs[2] = bomb_3; bombs[3] = bomb_4; bombs[4] = bomb_5;
	bombs[5] = bomb_6; bombs[6] = bomb_7; bombs[7] = bomb_8; bombs[8] = bomb_9; bombs[9] = bomb_10; //Store boms in the array

	int line;
	char bombInput[10][6]; //10 rows, 10 inputs, 6 colums for 5 characters + 1 null terminator
	for (line = 0; line < 10; line++){
		fgets(bombInput[line], 6, stdin);

	}

	printf("%c", bombInput[0][0]);





}
