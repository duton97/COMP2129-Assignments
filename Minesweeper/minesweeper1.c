/**
 * comp2129 - assignment 1
 * Vincent Zhang
 * vzha7446
 */

#include <stdio.h>


void createGrid(int rownum, int colnum){
	char grid1[rownum][colnum]; //Create grid with size input

	printf("+ "); //Upper Border
	for (int a = 0; a < colnum; a++){
		printf("- ");
	}
	printf("+\n");

	for (int i = 0; i < rownum; i++){
		for (int j = 0; j < colnum; j++){
			if (j == 0) { //Print the border at the beginning of each row
				printf("|");
			}
			grid1[i][j] = '*';
			printf(" %c", grid1[i][j]);
			if (j == colnum-1) {
				printf("|"); //Print the border at the end of each row
			}
		}
		printf("\n");
	}

	printf("+ "); //Lower Border
	for (int a = 0; a < colnum; a++){
		printf("- ");
	}
	printf("+\n");

}


int main(void) {

	int row;
	int col;
	char gridInput;

	scanf("%c %d %d", &gridInput, &row, &col);

	if (gridInput != 'g' || row*col < 9) { //Check for initial input of size grid
		printf("Invalid Input");
		return 0;
	}

	//char grid2[row][col];
	int x = 0; //Row of second grid
	int y = 0;; //Col of second grid
	char bombInput;

	for (int i = 1; i <= 10; i++){ //Ten inputs for bombs, cant be placed in the same position!!
		scanf("%c %d %d", &bombInput, &x, &y);
		//if (bombInput != 'b' || x >= row || y >= col){
		//	printf("Invalid Input");
		//	return 0;
		//}
		//grid2[x][y] = 'b';
		//printf("%d %d", x, y);
	}

	createGrid(row, col);



	return 0;
}
