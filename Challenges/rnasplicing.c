#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(void){
	char input[100];
	printf("Input strand: ");
	fgets(input, 100, stdin);
	int index = 0;
	bool condition = false;
	char result[strlen(input)];
	for(int i = 0; i < strlen(input) - 1; i++){
		if(condition == false){
			//Skip over following elements
			if(input[i] == 'G' && input[i+1] == 'U' && input[i+2] == 'G' && input[i+3] == 'U'){
				condition = true;
			}
			//Only add elements into array if not inside the exon
			else{
				result[index] = input[i];
				index++;
			}
		}
		else{
			//Skip over elements until AGAG is reached, and skip over AGAG as well
			if(input[i] == 'A' && input[i+1] == 'G' && input[i+2] == 'A' && input[i+3] == 'G'){
				condition = false;
				i+= 3;
			}
		}
	}
	result[index] = '\0';
	printf("\nOutput is %s\n", result);

	return 0;
}
