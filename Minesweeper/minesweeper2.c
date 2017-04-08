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
		printf("Invalid Input");
		return 1; //Failed
	}
	return 0; //Passes
}


int main(void) {

	//Variable for initial input
	int row;
	int col;
	char gridInput;

	scanf("%c %d %d", &gridInput, &row, &col); //First input
//	printf("%c %d %d\n", gridInput, row, col);



	if(checkg(gridInput, row, col) == 1){ //Check if input is valid
		return 1; //Failed
	}



	Bomb bombs[10]; //Declare array for bombs

	Bomb bomb_1, bomb_2, bomb_3, bomb_4, bomb_5, bomb_6, bomb_7, bomb_8, bomb_9, bomb_10; //Declare 10 bombs

	bombs[0] = bomb_1; bombs[1] = bomb_2; bombs[2] = bomb_3; bombs[3] = bomb_4; bombs[4] = bomb_5;
	bombs[5] = bomb_6; bombs[6] = bomb_7; bombs[7] = bomb_8; bombs[8] = bomb_9; bombs[9] = bomb_10; //Store boms in the array

	//char grid2[row][col];
	char bombInput;
	int x; //Row of second grid
	int y; //Col of second grid


	scanf("%c %d %d", &bombInput, &x, &y);
	printf("%c %d %d", bombInput, x, y);


	for (int i = 0; i < 10; i++){

		if (bombInput != 'b' || x > row || y > col){
			printf("Invalid Input");
			printf("%c", bombInput);
			return 1;
		}

		bombs[i].ch = bombInput;
		bombs[i].x = x;
		bombs[i].y = y;
		for (int j = 0; j < i; j++){
			if (bombs[j].x == bombs[i].x && bombs[j].y == bombs[i].y){
				return 1;
			}
		}


	}

	return 0;
}
