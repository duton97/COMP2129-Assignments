#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main(void){

	int length = 0;
	float array[100];

	printf("Enter data set:\n");
	float number;

	// Read and append numbers until invalid input or EOF
	while (scanf(" %f", &number) != EOF) {
		array[length] = number;
		length++;
	}

	if(length == 0){
		printf("\nNo data!\n");
		return 1;
	}

	printf("\n");
    float avg, var, dev, sum = 0, sum1 = 0;

	//Sum of elements
    for (int i = 0; i < length; i++){
        sum = sum + array[i];
    }

    avg = sum / (float)length;

	//Variance and deviation
    for (int i = 0; i < length; i++) {
		sum1 = sum1 + pow((array[i] - avg), 2);
    }

    var = sum1 / (float)length;
    dev = sqrt(var);

    printf("Mean = %.4f\n", avg);
    printf("Variance = %.4f\n", var);
    printf("Standard deviation = %.4f\n", dev);

	return 0;
}
