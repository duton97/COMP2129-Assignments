#include <stdio.h>
#include <string.h>

int main(void) {
	int key;
	char input[10];
	char line[100];
	int length = 0;
	int number = 0;

	printf("Enter key: ");
	fgets(input, 10, stdin);
	sscanf(input, " %d", &key);

	if (key < 0 || key > 26) {
		printf("\nInvalid key!\n");
		return 1;
	}

	printf("Enter line: ");
	fgets(line, 100, stdin);
	length = strlen(line);
	for (int i = 0; i < length - 1; i++) {
		number = (int) line[i];
		if (number >= 65 && number <= 90) {
			if (number + key > 90) {
				line[i] = (char) (((number + key) % 90) + 64);
			}
			else {
				line[i] = (char) number + key;
			}
		} else if (number >= 97 && number <= 122) {
			if (number + key > 122) {
				line[i] = (char) (((number + key) % 122) + 96);
			}
			else {
				line[i] = (char) number + key;
			}
		} else {
			line[i] = line[i];
		}
	}
	printf("\n%s", line);

	return 0;

}
