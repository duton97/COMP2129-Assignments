#include <stdio.h>
#include <string.h>

int main(void){
	int j = 0;
	char str[10][500];
	char reverse[10][500];

	for(j = 0; (fgets(str[j], 500, stdin) != NULL); j++);

	for(int k = 0; k <= j; k++){
		for(int i = 0; (str[k][i] != '\0') && i <= 500; i++){
			reverse[k][i] = str[k][(strlen(str[k])-2)-i];
			reverse[k][strlen(str[k])-1] = str[k][strlen(str[k])-1];
			reverse[k][strlen(str[k])] = str[k][strlen(str[k])];
		}
	}

	for(int k = 0; k < j; k++){
		printf("%s", reverse[k]);
	}
	return 0;
}
