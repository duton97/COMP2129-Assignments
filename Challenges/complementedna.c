#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
	char string[50];
	//int length = 0;

	printf("Enter strand: ");

	if (fgets(string, 50, stdin) != NULL) {
		int i = 0;
		while (string[i] != '\n') {
			if (string[i] == 'A') {
				string[i] = 'T';
			}
			else if (string[i] == 'a') {
				string[i] = 't';
			}
			else if (string[i] == 'T') {
				string[i] = 'A';
			}
			else if (string[i] == 't') {
				string[i] = 'a';
			}
			else if (string[i] == 'G') {
				string[i] = 'C';
			}
			else if (string[i] == 'g') {
				string[i] = 'c';
			}
			else if (string[i] == 'C') {
				string[i] = 'G';
			}
			else if (string[i] == 'c') {
				string[i] = 'g';
			}
			else {

				string[i] = 'x';

			}
			i++;
		}
	}
	else {
		printf("\n\nNo strand provided.\n");
		return 1;
	}

	printf("\nComplementary strand is %s", string);
	return 0;
}
