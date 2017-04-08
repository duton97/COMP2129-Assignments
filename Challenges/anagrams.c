#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int reduce_sentence(char* input, char* output, int length){
	int j = 0;
	for (int i = 0; i < length; i++){
		if (isalpha(input[i])){
			output[j] = tolower(input[i]);
			j++;
		}
	}
	return j;
}

int main(void){

	char input[100];
	char anagram[100];
	printf("Enter line: ");
	fgets(input, 100, stdin);
	printf("Enter anagram: ");
	fgets(anagram, 100, stdin);

	int inlength = strlen(input);
	int anlength = strlen(anagram);

	//Create new input and anagram
	char* new_input = malloc(inlength * sizeof(char));
	char* new_anagram = malloc(anlength * sizeof(char));

	//Remove unwanted characters and return new length
	int new_inlength = reduce_sentence(input, new_input, inlength);
	int new_anlength = reduce_sentence(anagram, new_anagram, anlength);

	//If different length, fail
	if(new_inlength != new_anlength){
		printf("\nNot an anagram.\n");
		free(new_input);
		free(new_anagram);
		return 1;
	}

	for (int i = 0; i < new_inlength; i++){

		int count_input = 0;
		int count_anagram = 0;

		char test = new_input[i];

		for (int j = 0; j < new_inlength; j++){
			if (new_input[j] == test){
				//printf("%c\n", new_input[j]);
				count_input++;
			}
			if(new_anagram[j] == test){
				//printf("%c\n", new_anagram[j]);
				count_anagram++;
			}
		}

		if (count_input != count_anagram){
			printf("\nNot an angram.\n");
			free(new_input);
			free(new_anagram);
			return 1;
		}

	}

	printf("\nAnagram!\n");
	free(new_input);
	free(new_anagram);

	return 0;


}
