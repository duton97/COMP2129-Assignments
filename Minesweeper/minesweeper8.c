/**
 * comp2129 - assignment 1
 * Vincent Zhang
 * vzha7446
 */

#include <stdio.h>

struct bomb {
	char ch; //command
	int x; //coordinate x
	int y; //coordinate y
};
typedef struct bomb Bomb;

void outputGrid(int *width, int *height, char array[*height][*width]){

	printf("+"); //Upper Border
	for (int a = 0; a < *width; a++){
		printf("-");
	}
	printf("+\n");

	for (int i = 0; i < *height; i++){
		for (int j = 0; j < *width; j++){
			if (j == 0) { //Print the border at the beginning of each row
				printf("|");
			}
			printf("%c", array[i][j]);
			if (j == *width-1) {
				printf("|"); //Print the border at the end of each row
			}
		}
		printf("\n");
	}

	printf("+"); //Lower Border
	for (int a = 0; a < *width; a++){
		printf("-");
	}
	printf("+\n");

}


int checkg(char *word, int *num1, int *num2){
	if (*word != 'g' || *num1 * *num2 < 9 || *num1 > 100 || *num2 > 100 || *num1 < 1 || *num2 < 1) { //Check for initial input of size grid
		return 1; //Failed
	}
	return 0; //Passes
}

int checkb(Bomb *bomb1, Bomb *bomb2, int *width, int *height){ //Pointer to bomb, second bomb, row and col of the grid
	if (bomb1->ch!='b' || bomb1->x >= *height || bomb1->y >= *height || (bomb1->x==bomb2->x && bomb1->y==bomb2->y) || bomb1->x < 0 || bomb1->y < 0) {
		//Check if input has b
		//Check if coordinate x of the bomb is smaller than row
		//Check if coordinate y of the bomb is smaller than col
		//Check if the bomb's coordinates are the same to other boms
		return 1;
	}
	return 0;
}

int uncoverCell(int *coorx, int *coory, int *width, int *height, char array[*height][*width]){
	int numBombs = 0;
	for (int i = *coorx-1; i <= *coorx+1; i++){ //Go through row
		if (i >= 0 && i <= *height-1){ //Boundary
			for (int j = *coory-1; j <= *coory+1; j++){ //Go through col
				if (j >= 0 && j <= *width-1){ //Boundary
					if(array[i][j] == 'b'){ //Check if the cell contains a bomb
						numBombs = numBombs + 1;
					}
				}
			}
		}
	}
	return numBombs;
}

void outputInstruction(char *ch, int *width, int *height){
	printf("%c %d %d\n", *ch, *width, *height);
}

int main(void) {

	char instruction[10];
	int width, height;
	char command;
	int invalidInput = 0; //Int used to check if there are more than 3 inputs

	fgets(instruction, 10, stdin);
	sscanf(instruction, " %c %d %d %d\n", &command, &width, &height, &invalidInput);

	if ((checkg(&command, &width, &height) == 1) || invalidInput != 0){
		printf("error\n");
		return 1; //Failed
	}

	outputInstruction(&command, &width, &height);

	char bombGrid[height][width]; //Create grid to place the bombs

	for (int i = 0; i < height; i++){ //Initialise all cells to 'e' to indicate that its empty
		for (int j = 0; j < width; j++){
			bombGrid[i][j] = 'e'; //Empty
		}
	}

	Bomb bombs[10]; //Declare array to hold the bombs

	Bomb bomb_1, bomb_2, bomb_3, bomb_4, bomb_5, bomb_6, bomb_7, bomb_8, bomb_9, bomb_10; //Declare 10 bombs

	bombs[0] = bomb_1; bombs[1] = bomb_2; bombs[2] = bomb_3; bombs[3] = bomb_4; bombs[4] = bomb_5;
	bombs[5] = bomb_6; bombs[6] = bomb_7; bombs[7] = bomb_8; bombs[8] = bomb_9; bombs[9] = bomb_10; //Store boms in the array


	//char bombInput[10][15]; //10 rows, 10 inputs
	for (int line = 0; line < 10; line++){ //10 inputs for bombs
		fgets(instruction, 10, stdin);
		sscanf(instruction, " %c %d %d %d", &bombs[line].ch, &bombs[line].y, &bombs[line].x, &invalidInput);

		if ( invalidInput != 0) {
			printf("error\n");
			return 1;
		}

		if(line == 0){ //Check for validation of the first input
			if (bombs[line].ch != 'b' || bombs[line].x >= height || bombs[line].y >= width || bombs[line].x < 0 || bombs[line].y < 0){
				printf("error\n");
				return 1; //fail
			}
		}

		for (int indexB = 0; indexB < line; indexB++){ //To compare to other bombs and if its valid
			if (checkb(&bombs[line], &bombs[indexB], &width, &height) == 1){
				printf("error\n");
				return 1;
			}
		}

		bombGrid[bombs[line].x][bombs[line].y] = bombs[line].ch; //Place the bomb into the bombGrid according to bombs' coordinates
		outputInstruction(&bombs[line].ch, &bombs[line].y, &bombs[line].x);
	}

	char displayGrid[height][width]; //Create grid size heightxwidth, grid that will be displayed

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			displayGrid[i][j] = '*';
		}
	}

	outputGrid(&width, &height, displayGrid); //Print grid

	//Second part

	//To check that instructions are not the same, create an array to hold both integers (coordinates) of each instruction.
	//Then at each instruction, save both integers along side each other
	//Then compare both integers to integers from previous instructions, in sets of 2, to compare x and y coordinates

	//Variables used for the second part (after bomb instructions and displaying first grid)
	int numInstructions = width * height; //Number of instructions
	int coorInstructions[numInstructions*2]; //Array to hold both integers/coordinates along side, thus double size of instruction
	int coorx, coory; //Coordinate X and Coordiante Y
	int numFlag = 0; //Number of flags
	int arrIndex = 0; //index of the array coorInstructions
	char c; //char to hold a converted int to char

	for (int i = 0; i < numInstructions; i++){
		fgets(instruction, 10, stdin);
		sscanf(instruction, " %c %d %d %d", &command, &coory, &coorx, &invalidInput);

		if(command == 'u' || command == 'f'){
			if (invalidInput != 0 || numFlag >= 10 || coorx < 0 || coory < 0 || coorx >= height || coory >= width){
				printf("error\n");
				return 1;
			}
			if (command == 'f'){ //If flag, increment num of flag
			numFlag = numFlag + 1;
			}

			coorInstructions[arrIndex] = coorx; //Save first integer at the beginning of the array
			coorInstructions[arrIndex+1] = coory; //Save second integer next to the first integer

			for (int j = 0; j < arrIndex; j = j + 2){
				if (coorInstructions[arrIndex] == coorInstructions[j] && coorInstructions[arrIndex+1] == coorInstructions[j+1]){
					printf("error\n");
					return 1;
				}
			}

			arrIndex = arrIndex + 2; //Increment index by 2, in order to skip over the second integer already stored

			outputInstruction(&command, &coory, &coorx);

			//Validation complete

			if (command == 'f'){
				displayGrid[coorx][coory] = 'f';
				outputGrid(&width, &height, displayGrid);
			}

			if (command == 'u'){
				if (bombGrid[coorx][coory] == 'b'){
					printf("lost\n");
					return 1;
				}
				if (bombGrid[coorx][coory] == 'e'){
					int numBombs = uncoverCell(&coorx, &coory, &width, &height, bombGrid);
					c = numBombs + '0';
					displayGrid[coorx][coory] = c;
					outputGrid(&width, &height, displayGrid);
				}
			}

		} else {
			printf("error\n");
			return 1;
		}

	}

	printf("won\n");
	return 0;
}
