/**
 * comp2129 - assignment 2
 * <your name>
 * <your unikey>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#include "snapshot.h"

//
// We recommend that you design your program to be
// modular where each function performs a small task
//
// e.g.
//
// command_bye
// command_help
// ...
// entry_add
// entry_delete
// ...
//

//void strtok_first_token(char line[], char* token){
//	//Get the first token (Command)
//	token = strtok(line, " \n");
//}

//oid strtok_second_token(char* token, char key[MAX_KEY]){
//	token = strtok(NULL, " \n");
//	sscanf(token, " %s", key);
//}

entry* check_same_key(entry* head, entry* tail, char key[]);



void command_help() {
	printf("%s\n", HELP);
}

void command_set(entry* entry, int *array, int length, char key[]) {
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key\n\n");
		return;
	}

	strcpy(entry->key, key);
	entry->length = length;

	//printf("%s\n", entry->key);

	int* ptr = (int *) malloc(length * sizeof(int));
	entry->values = ptr;
	for (int i = 0; i < length; i++){
		entry->values[i] = array[i];
		//printf("%d\n", entry->values[i]);
	}
	printf("ok\n\n");
}

//array passed contains the new values to be added
//length passed contains the length of the array passed
void command_push(entry* head, entry* tail, int *array, int length, char key[]){
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key\n\n");
		return;
	}

	entry* temp = check_same_key(head, tail, key);
	int oldLength = temp->length; //Holds old length value
	int sumLength = temp->length + length;
	int valueHolder[oldLength]; //Holds the values of the entry

	//Have valueHolder temporarily store the values of the entry(temp)
	for (int  i = 0; i < oldLength; i++){
		valueHolder[i] = temp->values[i];
	}

	temp->values = (int *) realloc(temp->values, sumLength * sizeof(int));
	temp->length = sumLength; //New length, update length

	int i = 0; //Increase index for the array of temp
	int j = length - 1; //Decrease index for the array passed with the new values
	int k = 0; //Index for valueHolder

	//Store new and old values into new array of values
	for (; i < temp->length; i++){
		//Store the new values in reverse
		if (i < length) {
			temp->values[i] = array[j];
			j--;
		}
		//Store old values
		else {
			temp->values[i] = valueHolder[k];
			k++;
		}
	}
	printf("ok\n\n");
}

//array passed contains the new values to be added
//length passed contains the length of the array passed
void command_append(entry* head, entry* tail, int *array, int length, char key[]){
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key\n\n");
		return;
	}

	entry* temp = check_same_key(head, tail, key);
	int oldLength = temp->length; //Holds old length value
	int sumLength = temp->length + length;
	int valueHolder[oldLength]; //Holds the values of the entry

	//Have valueHolder temporarily store the values of the entry(temp)
	for (int  i = 0; i < oldLength; i++){
		valueHolder[i] = temp->values[i];
	}

	temp->values = (int *) realloc(temp->values, sumLength * sizeof(int));
	temp->length = sumLength; //New length, update length

	int i = 0; //Increase index for the array of temp
	int j = 0; //Decrease index for the array passed with the new values
	int k = 0; //Index for valueHolder

	for (; i < temp->length; i++) {
		if (k < oldLength) {
			temp->values[i] = valueHolder[k];
			k++;
		} else {
			temp->values[i] = array[j];
			j++;
		}
	}
	printf("ok\n\n");
}

void command_get(entry* head, entry* tail, char key[]){
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key\n\n");
		return;
	}

	entry* temp = check_same_key(head, tail, key);

	if (temp->length == 0){
		printf("[]\n\n");
			return;
	}
	printf("[");
	int i;
	for (i = 0; i < temp->length-1; i++){
		printf("%d ", temp->values[i]);
	}
	printf("%d", temp->values[i]);
	printf("]\n\n");
}

void command_del(entry* head, entry* tail, char key[]){
	if (check_same_key(head, tail, key) == NULL){
		printf("no such key\n\n");
		return;
	}

	entry* temp = check_same_key(head, tail, key);
	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;
	free(temp->values);
	free(temp);
}

void command_min(entry* head, entry* tail, char key[]){
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key\n\n");
		return;
	}

	entry* temp = check_same_key(head, tail, key);
	if (temp->length == 0){
		printf("nil\n\n");
		return;
	}

	int min = temp->values[0];
	for (int i = 1; i < temp->length; i++){
		if (min == temp->values[i]){
			min = temp->values[i];
		}
		else if (temp->values[i] < min){
			min = temp->values[i];
		}
	}
	printf("%d\n\n", min);
}

void command_max(entry* head, entry* tail, char key[]){
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key\n\n");
		return;
	}

	entry* temp = check_same_key(head, tail, key);
	if (temp->length == 0){
		printf("nil\n\n");
		return;
	}
	int max = temp->values[0];
	for (int i = 1; i < temp->length; i++){
		if (max == temp->values[i]){
			max = temp->values[i];
		}
		else if (temp->values[i] > max){
			max = temp->values[i];
		}
	}
	printf("%d\n\n", max);
}

void command_sum(entry* head, entry* tail, char key[]){
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key);
	if (temp->length == 0){
		printf("0\n\n");
		return;
	}

	int sum = temp->values[0];
	for (int i = 1; i < temp->length; i++){
		sum = sum + temp->values[i];
	}
	printf("%d\n\n", sum);
}

void command_len(entry* head, entry* tail, char key[]){
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key);
	if (temp->length == 0){
		printf("0\n\n");
		return;
	}
	printf("%zu\n\n", temp->length);
}

void command_rev(entry* head, entry* tail, char key[]){
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key);
	int tempValues[temp->length];
	int i = 0; //Increase
	int j; // Decrease
	for (j = temp->length - 1; j >= 0; j--){
		tempValues[i] = temp->values[j];
		i++;
	}
	for (int i = 0; i < temp->length; i++){
		temp->values[i] = tempValues[i];
	}
	printf("ok\n\n");
}

void command_uniq(entry* head, entry* tail, char key[]){
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key);
	int oldLength = temp->length;
	int valueHolder[oldLength];
	int i = 0; //index for valueHolder
	int j = 0; //index for temp->values

	for (; j < oldLength - 1; j++){
		//Store first value into new array
		if (i == 0) {
			valueHolder[i] = temp->values[j];
		}

		//Check that the adjacent value is not the same, store the adjacent value into the new array
		if (valueHolder[i] != temp->values[j+1]) {
			valueHolder[i+1] = temp->values[j+1];
			i++;
		}
	}

	temp->values = (int *) realloc(temp->values, (i+1) * sizeof(int));
	temp->length = i + 1;

	for (int j = 0; j < temp->length; j++){
		temp->values[j] = valueHolder[j];
	}

	printf("ok\n\n");
}

int compare(const void* a, const void* b){
	const int *ia = (const int *)a; // casting pointer types
    const int *ib = (const int *)b;
	return *ia - *ib;
}

void command_sort(entry* head, entry* tail, char key[]){
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key);

	qsort(temp->values, temp->length, sizeof(int), compare);

	printf("ok\n\n");
}

void command_listkeys(entry* head, entry* tail){
	entry* temp = tail;

	if (temp->prev == head){
		printf("no keys\n");
	}

	while (temp->prev != head){
		temp = temp->prev;
		printf("%s\n", temp->key);

	}
	printf("\n");
}

void command_listentries(entry* head, entry* tail){
	entry* temp = tail;

	if (temp->prev == head){
		printf("no entries\n");
	}

	while (temp->prev != head){
		temp = temp->prev;
		printf("%s ", temp->key);
		if (temp->length == 0){
		printf("[]\n\n");
			return;
		}
		printf("[");
		int i;
		for (i = 0; i < temp->length-1; i++){
			printf("%d ", temp->values[i]);
		}
		printf("%d", temp->values[i]);
		printf("]\n");
	}
	printf("\n");
}

void command_pick(entry* head, entry* tail, char key[], int* index){
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key\n\n");
		return;
	}

	entry* temp = check_same_key(head, tail, key);

	if (*index > temp->length || *index == 0) {
		printf("index out of range\n\n");
		return;
	}

	printf("%d\n\n", temp->values[*index-1]);
}

void command_pluck(entry* head, entry* tail, char key[], int* index){
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key\n\n");
		return;
	}

	entry* temp = check_same_key(head, tail, key);

	if (*index > temp->length || *index == 0) {
		printf("index out of range\n\n");
		return;
	}

	int oldLength = temp->length;
	int newLength = temp->length - 1;
	int valueHolder[newLength]; //Holds the values of the entry
	int removedValue;

	int i = 0; //Index for the array values of temp
	int j = 0; //Index for the valueHolder

	//Go through array values of temp, only store the values that different from the index passed
	for (; i < oldLength; i++){
		if (i == *index - 1){
			removedValue = temp->values[i];
		} else {
			valueHolder[j] = temp->values[i];
			j++;
		}
	}

	temp->values = (int *) realloc(temp->values, newLength * sizeof(int));
	temp->length = newLength;

	//Store the values into temp
	for (int i = 0; i < temp->length; i++) {
		temp->values[i] = valueHolder[i];
		//printf("%d ", valueHolder[i]);
	}

	printf("%d\n\n", removedValue);
}

void command_pop(entry* head, entry* tail, char key[]){
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key\n\n");
		return;
	}

	entry* temp = check_same_key(head, tail, key);
	if (temp->length == 0) {
		printf("nil\n\n");
		return;
	}

	int oldLength = temp->length;
	int newLength = temp->length - 1;
	int valueHolder[newLength]; //Holds the values of the entry
	int removedValue;

	int i = 0; //Index for the array values of temp
	int j = 0; //Index for the valueHolder

	//Go through array values of temp, only store the values that different from the index passed
	for (; i < oldLength; i++){
		if (i == 0){
			removedValue = temp->values[i];
		} else {
			valueHolder[j] = temp->values[i];
			j++;
		}
	}

	temp->values = (int *) realloc(temp->values, newLength * sizeof(int));
	temp->length = newLength;

	//Store the values into temp
	for (int i = 0; i < temp->length; i++) {
		temp->values[i] = valueHolder[i];
		//printf("%d ", valueHolder[i]);
	}

	printf("%d\n\n", removedValue);
}


entry* check_same_key(entry* head, entry* tail, char key[]){
	entry* temp = tail;
	while (temp->prev != head){
		temp = temp->prev;
		if (strcmp(temp->key, key) == 0){
			return temp;
		}
	}
	return NULL; //no same key
}


void command_bye(entry* head, entry* tail) {
	entry* temp = head;
	while (temp->next != tail){
		command_del(head, tail, temp->next->key);
	}
	free(head);
	free(tail);
	printf("bye\n");
}

//Tail entry is passed and append a new entry to the end of the list
entry* create_entry(entry* tail){
	entry* list = (entry *) malloc(sizeof(entry));

	list->next = tail;
	tail->prev->next = list;
	list->prev = tail->prev;
	tail->prev = list;

	return list;
}

void initialise_list(entry* head, entry* tail){
	head->next = tail;
	head->prev = NULL;

	tail->next = NULL;
	tail->prev = head;
}

int main(void) {

	char line[MAX_LINE];

	entry* headEntry = (entry *) malloc(sizeof(entry));
	entry* tailEntry = (entry *) malloc(sizeof(entry));

	initialise_list(headEntry, tailEntry);


	while (true) {
		printf("> ");

		if (fgets(line, MAX_LINE, stdin) == NULL) {
			printf("\n");
			command_bye(headEntry, tailEntry);
			return 0;
		}

		char* token;

		// index for arrValues
		int length;
		length = 0;

		int arrValues[MAX_LINE];
		char keyHolder[MAX_KEY];
		int indexHolder = 0;


		if (strncasecmp(line, "BYE", 3) == 0){
			command_bye(headEntry, tailEntry);
			return 0;
		}
		else if (strncasecmp(line, "HELP", 4) == 0){
			command_help();
		}
		else if (strncasecmp(line, "LIST KEYS", 9) == 0){
			command_listkeys(headEntry, tailEntry);
		}
		else if (strncasecmp(line, "LIST ENTRIES", 12) == 0){
			command_listentries(headEntry, tailEntry);
		}
			else if (strncasecmp(line, "LIST SNAPSHOTS", 14) == 0){
			//TODO
		}

		else if (strncasecmp(line, "GET", 3) == 0){

		//Get first token (command)
		token = strtok(line, " \n");

		//Get second token (key or id)
		token = strtok(NULL, " \n");
		sscanf(token, " %s", keyHolder);

		command_get(headEntry, tailEntry, keyHolder);


		}

		else if (strncasecmp(line, "DEL", 3) == 0){
			//Get first token (command)
			token = strtok(line, " \n");

			//Get second token (key or id)
			token = strtok(NULL, " \n");
			sscanf(token, " %s", keyHolder);

			command_del(headEntry, tailEntry, keyHolder);
			printf("ok\n\n");

		}
			else if (strncasecmp(line, "PURGE", 5) == 0){
			command_help();
		}
		else if (strncasecmp(line, "SET", 3) == 0){ //Need to fix, if its the same key then replace

		//Get first token (command)
		token = strtok(line, " \n");

		//Get second token (key or id)
		token = strtok(NULL, " \n");
		sscanf(token, " %s", keyHolder);

		//Walk through other tokens (Values)
		while (token != NULL) {
			token = strtok(NULL, " \n");

			//Stop sscanf at the last token
			if (token != NULL) {
				sscanf(token, " %d", &arrValues[length]);
				//printf("  %d\n", arrValues[length]);
				length++;
			}
		}

		//if (check_same_key(headEntry, tailEntry, keyHolder) != NULL) {
		//	free(check_same_key(headEntry, tailEntry, keyHolder));
	//		free(check_same_key(headEntry, tailEntry, keyHolder)->values);
//		}
		command_set(create_entry(tailEntry), arrValues, length, keyHolder);


		}
			else if (strncasecmp(line, "PUSH", 4) == 0){
			//Get first token (command)
			token = strtok(line, " \n");

			//Get second token (key or id)
			token = strtok(NULL, " \n");
			sscanf(token, " %s", keyHolder);

			//Walk through other tokens (Values)
			while (token != NULL) {
				token = strtok(NULL, " \n");

				//Stop sscanf at the last token
				if (token != NULL) {
					sscanf(token, " %d", &arrValues[length]);
					//printf("  %d\n", arrValues[length]);
					length++;
				}
			}

			command_push(headEntry, tailEntry, arrValues, length, keyHolder);

		}
			else if (strncasecmp(line, "APPEND", 6) == 0){
			//Get first token (command)
			token = strtok(line, " \n");

			//Get second token (key or id)
			token = strtok(NULL, " \n");
			sscanf(token, " %s", keyHolder);

			//Walk through other tokens (Values)
			while (token != NULL) {
				token = strtok(NULL, " \n");

				//Stop sscanf at the last token
				if (token != NULL) {
					sscanf(token, " %d", &arrValues[length]);
					//printf("  %d\n", arrValues[length]);
					length++;
				}
			}

			command_append(headEntry, tailEntry, arrValues, length, keyHolder);
		}
			else if (strncasecmp(line, "PICK", 4) == 0){
			//Get first token (command)
			token = strtok(line, " \n");

			//Get second token (key or id)
			token = strtok(NULL, " \n");
			sscanf(token, " %s", keyHolder);

			//Get third token (key or id)
			token = strtok(NULL, " \n");
			sscanf(token, " %d", &indexHolder);

			command_pick(headEntry, tailEntry, keyHolder, &indexHolder);

		}
			else if (strncasecmp(line, "PLUCK", 5) == 0){
			//Get first token (command)
			token = strtok(line, " \n");

			//Get second token (key or id)
			token = strtok(NULL, " \n");
			sscanf(token, " %s", keyHolder);

			//Get third token (key or id)
			token = strtok(NULL, " \n");
			sscanf(token, " %d", &indexHolder);

			command_pluck(headEntry, tailEntry, keyHolder, &indexHolder);
		}
			else if (strncasecmp(line, "POP", 3) == 0){
			//Get first token (command)
			token = strtok(line, " \n");

			//Get second token (key or id)
			token = strtok(NULL, " \n");
			sscanf(token, " %s", keyHolder);

			command_pop(headEntry, tailEntry, keyHolder);
		}
			else if (strncasecmp(line, "DROP", 4) == 0){
			command_help();
		}
			else if (strncasecmp(line, "ROLLBACK", 8) == 0){
			command_help();
		}
			else if (strncasecmp(line, "CHECKOUT", 8) == 0){
			command_help();
		}
			else if (strncasecmp(line, "SNAPSHOT", 8) == 0){
			command_help();
		}
			else if (strncasecmp(line, "MIN", 3) == 0){
			//Get first token (command)
			token = strtok(line, " \n");

			//Get second token (key or id)
			token = strtok(NULL, " \n");
			sscanf(token, " %s", keyHolder);

			command_min(headEntry, tailEntry, keyHolder);
		}
			else if (strncasecmp(line, "MAX", 3) == 0){
			//Get first token (command)
			token = strtok(line, " \n");

			//Get second token (key or id)
			token = strtok(NULL, " \n");
			sscanf(token, " %s", keyHolder);

			command_max(headEntry, tailEntry, keyHolder);
		}
			else if (strncasecmp(line, "SUM", 3) == 0){
			//Get first token (command)
			token = strtok(line, " \n");

			//Get second token (key or id)
			token = strtok(NULL, " \n");
			sscanf(token, " %s", keyHolder);

			command_sum(headEntry, tailEntry, keyHolder);
		}
			else if (strncasecmp(line, "LEN", 3) == 0){
			//Get first token (command)
			token = strtok(line, " \n");

			//Get second token (key or id)
			token = strtok(NULL, " \n");
			sscanf(token, " %s", keyHolder);

			command_len(headEntry, tailEntry, keyHolder);
		}
			else if (strncasecmp(line, "REV", 3) == 0){
			//Get first token (command)
			token = strtok(line, " \n");

			//Get second token (key or id)
			token = strtok(NULL, " \n");
			sscanf(token, " %s", keyHolder);

			command_rev(headEntry, tailEntry, keyHolder);
		}
			else if (strncasecmp(line, "UNIQ", 4) == 0){
			//Get first token (command)
			token = strtok(line, " \n");

			//Get second token (key or id)
			token = strtok(NULL, " \n");
			sscanf(token, " %s", keyHolder);

			command_uniq(headEntry, tailEntry, keyHolder);
		}
			else if (strncasecmp(line, "SORT", 4) == 0){
			//Get first token (command)
			token = strtok(line, " \n");

			//Get second token (key or id)
			token = strtok(NULL, " \n");
			sscanf(token, " %s", keyHolder);

			command_sort(headEntry, tailEntry, keyHolder);
		}
			else if (strncasecmp(line, "DIFF", 4) == 0){
			command_help();
		}
			else if (strncasecmp(line, "INTER", 5) == 0){
			command_help();
		}
			else if (strncasecmp(line, "UNION", 5) == 0){
			command_help();
		}





		//
		// TODO
		//
  	}



	return 0;
}
