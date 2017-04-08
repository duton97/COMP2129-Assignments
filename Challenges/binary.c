#include <stdio.h>
#include <math.h>

int main(void) {
	char buffer[50];
	int numHolder[50];
	int decimalNum = 0;

	printf("Enter binary: ");
	fgets(buffer, 50, stdin);
	int i = 0;
 	while (buffer[i] != '\n'){
		if (buffer[i] != '0' && buffer[i] != '1'){
			printf("\nNot binary!\n");
			return 1;
		}
		numHolder[i] = buffer[i] - '0';
		i++;
	}

	int length = i;
	for (int j = 0; j < length; j++) {
		decimalNum = decimalNum + (numHolder[j] * pow(2, i-1));
		i--;
	}

	printf("\n%d in decimal\n", decimalNum);

	return 0;
}
