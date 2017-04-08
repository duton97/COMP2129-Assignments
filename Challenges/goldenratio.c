#include <stdio.h>
#include <math.h>
#include <string.h>

int main(void) {
	double num1;
	double num2;
	char check1[15];
	char check2[15];
	char buffer[50];
	double calculation1;
	double calculation2;
	double calculation3;
	double calculation4;

	printf("Enter two numbers: ");
	fgets(buffer, 50, stdin);

	sscanf(buffer, " %s %s", check1, check2);
	if (strlen(check1) < 2 || strlen(check2) < 2) {
		printf("\nInvalid input.\n");
		return 1;
	}

	sscanf(buffer, " %lf %lf", &num1, &num2);

	calculation1 = round(((num1+num2)/num1)*1000)/1000;
	calculation2 = round((num1/num2)*1000)/1000;

	calculation3 = round(((num2+num1)/num2)*1000)/1000;
	calculation4 = round((num2/num1)*1000)/1000;

	if (calculation1 != calculation2) {
		if (calculation3 != calculation4) {
			printf("\nMaybe next time.\n");
			return 1;
		}
	}

	printf("\nGolden ratio!\n");

}
