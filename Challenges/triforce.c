#include <stdio.h>

int main(void) {
	int height;

	printf("Enter height: ");

	if (scanf(" %d", &height) == 1) {
			if (height >= 2 && height <= 20) {
			char array[height*2][height*4];

			//initiliase array to empty char
			for (int i = 0; i < height*2; i++) {
				for (int j = 0; j < height*4; j++) {
					array[i][j] = ' ';
				}
			}

			int x = 0; // Index for the outer left side, decrease
			int a = 0; // Index for the inner left side, increase
			int y = 0; // index for the outer right side, increase
			int b = 0; // Index for the inner right side, decrease
			for (int i = 0; i < height*2; i++) {
				for (int j = 0; j < height*4; j++) {

					//first bottom layer
					if (i == height - 1) {
						if (j > height && j < (height*3) - 1) {
							array[i][j] = '_';
						}
					}

					//second bottom later
					if (i == (height*2)-1) {
						array[i][j] = '_';
					}


					//left side
					if (j == ((height*4)/2) - x - 1) {
						array[i][j] = '/';
						x++;
					}

					//inner left side
					if (i >= height && i <= (height*2) - 1) {
						if (j == height + a) {
							array[i][j] = '\\';
						}
					}

					//right side
					if (j == ((((height*4)/2)+1)) + y - 1) {
						array[i][j] = '\\';
					}

					//inner right side
					if (i >= height && i <= (height*2) - 1) {
						if (j == (height*3) - 1 - b) {
							array[i][j] = '/';
							b++;
						}
					}

				}
				y++;
				if (i >= height && i <= (height*2) - 1) {
					a++;
				}

			}


			int z = 0;
			//print
			printf("\n");
			for (int i = 0; i < height*2; i++) {
				for (int j = 0; j < height*4; j++) {
					if (j <= height*2 + z) {
						printf("%c", array[i][j]);
					}
				}
				z++;
				printf("\n");
			}



		} else {
			printf("\nInvalid height.\n");
		}
	} else {
		printf("\nInvalid height.\n");
	}
}
