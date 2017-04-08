/**
 * comp2129 - assignment 2
 * <Vincent Zhang>
 * <vzha7446
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#include "snapshot.h"

entry* check_same_key(entry* head, entry* tail, char key[]);

//Checks if entry with given key exists, and return the pointer of such entry
entry* check_same_key(entry* head, entry* tail, char key[]){
	entry* temp = tail;
	//Loop from the end of the linked list
	while (temp->prev != head) {
		temp = temp->prev;
		if (strcmp(temp->key, key) == 0){
			return temp;
		}
	}
	return NULL; //Entry with key is non existen
}

void command_help() {
	printf("%s\n", HELP);
}

//Function used in command set when there is already an existing entry with given key. Replace the values with the new values from input
void command_replace(entry* entry, int* array, int *length){
	free(entry->values);
	entry->length = *length; //Update length to the new length of the array with new values
	int* ptr = (int *) malloc(*length * sizeof(int));
	entry->values = ptr;

	//Store new values into the array of entry
	for (int i = 0; i < *length; i++){
		entry->values[i] = array[i];
	}
	printf("ok\n\n");
}

void command_set(entry* head, entry* tail, entry* entry, int *array, int *length, char key[]) {
	//Use head entry and tail entry to check if entry with given key already exists
	if (check_same_key(head, tail, key) != NULL){
		//Replace the values instead of creating a duplicate entry
		command_replace(check_same_key(head, tail, key), array, length);
	}
	//Fill in the entry struct with the given inputs (key, values and length)
	else {
		strcpy(entry->key, key);
		entry->length = *length;
		int* ptr = (int *) malloc(*length * sizeof(int));
		entry->values = ptr;
		//Store values into array of entry
		for (int i = 0; i < *length; i++){
			entry->values[i] = array[i];
		}
		printf("ok\n\n");
	}
}

//New values to be push are passed as an array with its length
void command_push(entry* head, entry* tail, int *array, int *length, char key[]) {
	//Use head entry and tail entry to check if entry with given key already exists
	if (check_same_key(head, tail, key) == NULL){
		printf("no such key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key); //Temporary entry points to the entry with given key
	int oldLength = temp->length; //Holds old length value
	int sumLength = temp->length + *length; //New added length
	int valueHolder[oldLength]; //Temporarily holds the values of entry

	//store the values of the entry(temp) into valueHolder
	for (int  i = 0; i < oldLength; i++){
		valueHolder[i] = temp->values[i];
	}
	temp->values = (int *) realloc(temp->values, sumLength * sizeof(int));
	temp->length = sumLength; //Update length
	int i = 0; //Increase index for the array of temp
	int j = *length - 1; //Decrease index for the array passed with the new values
	int k = 0; //Index for valueHolder

	//Store new and old values into new array of entry
	for (; i < temp->length; i++) {
		//Store the new values in reverse
		if (i < *length) {
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

void command_append(entry* head, entry* tail, int *array, int *length, char key[]) {
	//Use head entry and tail entry to check if entry with given key already exists
	if (check_same_key(head, tail, key) == NULL){
		printf("no such key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key); //Temporary entry points to the entry with given key
	int oldLength = temp->length; //Holds old length value
	int sumLength = temp->length + *length; //New length
	int valueHolder[oldLength]; //Temporarily holds the values of entry

	//store the values of the entry(temp) into valueHolder
	for (int  i = 0; i < oldLength; i++){
		valueHolder[i] = temp->values[i];
	}

	temp->values = (int *) realloc(temp->values, sumLength * sizeof(int));
	temp->length = sumLength; //Update length
	int i = 0; //Increase index for the array of temp
	int j = 0; //Decrease index for the array passed with the new values
	int k = 0; //Index for valueHolder

	//Store new and old values into new array of entry
	for (; i < temp->length; i++) {
		//Restore the old values first
		if (k < oldLength) {
			temp->values[i] = valueHolder[k];
			k++;
		}
		//Store the new values at the back of the array
		else {
			temp->values[i] = array[j];
			j++;
		}
	}
	printf("ok\n\n");
}

void command_get(entry* head, entry* tail, char key[]) {
	//Use head entry and tail entry to check if entry with given key already exists
	if (check_same_key(head, tail, key) == NULL) {
		printf("no such key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key); //Temporary entry points to the entry with given key

	//No values
	if (temp->length == 0){
		printf("[]\n\n");
			return;
	}
	printf("[");
	int i;

	//Print all values except last one with space following the value
	for (i = 0; i < temp->length-1; i++){
		printf("%d ", temp->values[i]);
	}

	//Print last value without space
	printf("%d", temp->values[i]);
	printf("]\n\n");
}

void command_del(entry* head, entry* tail, char key[]){
	//Use head entry and tail entry to check if entry with given key already exists
	if (check_same_key(head, tail, key) == NULL){
		return;
	}
	entry* temp = check_same_key(head, tail, key); //Temporary entry points to the entry with given key
	temp->next->prev = temp->prev; //Set current's next entry to point to current's previous entry
	temp->prev->next = temp->next; //Set current's previous entry to point to current's next entry
	free(temp->values);
	free(temp);
}

//Needs fixing to include snapshots
void command_purge(entry* head, entry* tail, snapshot* headSP, snapshot* tailSP, char key[]){
	//Use head entry and tail entry to check if entry with given key already exists
	if (check_same_key(head, tail, key) == NULL){
		//printf("no such key\n\n");
		printf("ok\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key); //Temporary entry points to the entry with given key
	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;
	free(temp->values);
	free(temp);
	//printf("ok\n\n");
}

void command_min(entry* head, entry* tail, char key[]){
	//Use head entry and tail entry to check if entry with given key already exists
	if (check_same_key(head, tail, key) == NULL){
		printf("no such key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key); //Temporary entry points to the entry with given key

	//No Values
	if (temp->length == 0){
		printf("nil\n\n");
		return;
	}
	int min = temp->values[0]; //Variable min to store the lowest value

	//Compare the first value to the other values in the array
	for (int i = 1; i < temp->length; i++) {
		//If min is equal to the next value, store the next value in min
		if (min == temp->values[i]) {
			min = temp->values[i];
		}
		//If min is higher than the next value, store the next value in min
		else if (temp->values[i] < min) {
			min = temp->values[i];
		}
	}
	printf("%d\n\n", min);
}

void command_max(entry* head, entry* tail, char key[]){
	//Use head entry and tail entry to check if entry with given key already exists
	if (check_same_key(head, tail, key) == NULL) {
		printf("no such key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key); //Temporary entry points to the entry with given key

	//No values
	if (temp->length == 0) {
		printf("nil\n\n");
		return;
	}
	int max = temp->values[0]; //Varimax to store the maximum value

	//Compare the first value to the other values in the array
	for (int i = 1; i < temp->length; i++) {
		//If max is equal to the next value, store the next value in max
		if (max == temp->values[i]) {
			max = temp->values[i];
		}
		//If max is higher than the next vale, store the next value in max
		else if (temp->values[i] > max) {
			max = temp->values[i];
		}
	}
	printf("%d\n\n", max);
}

void command_sum(entry* head, entry* tail, char key[]) {
	//Use head entry and tail entry to check if entry with given key already exists
	if (check_same_key(head, tail, key) == NULL) {
		printf("no such key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key); //Temporary entry points to the entry with given key
	if (temp->length == 0) {
		printf("0\n\n");
		return;
	}
	int sum = temp->values[0]; //Sum variable, holds first value

	//Add following values in the array to the first value
	for (int i = 1; i < temp->length; i++) {
		sum = sum + temp->values[i];
	}
	printf("%d\n\n", sum);
}

void command_len(entry* head, entry* tail, char key[]){
	//Use head entry and tail entry to check if entry with given key already exists
	if (check_same_key(head, tail, key) == NULL) {
		printf("no such key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key); //Temporary entry points to the entry with given key
	//No values
	if (temp->length == 0) {
		printf("0\n\n");
		return;
	}
	//Print the length of the array containing the values
	printf("%zu\n\n", temp->length);
}

void command_rev(entry* head, entry* tail, char key[]){
	//Use head entry and tail entry to check if entry with given key already exists
	if (check_same_key(head, tail, key) == NULL) {
		printf("no such key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key); //Temporary entry points to the entry with given key
	int valueHolder[temp->length]; //Temporary array to store the values of the entry
	int i = 0; //Increase index to iterate from the front of the temporary array
	int j; // Decrease index to iterate from the back of the array of the entry

	//Iterate over both arrays and store the values in reverse into the temporary array
	for (j = temp->length - 1; j >= 0; j--) {
		valueHolder[i] = temp->values[j];
		i++;
	}
	//Store the reversed values from the temporary array into the array of entry
	for (int i = 0; i < temp->length; i++) {
		temp->values[i] = valueHolder[i];
	}
	printf("ok\n\n");
}

void command_uniq(entry* head, entry* tail, char key[]) {
	//Use head entry and tail entry to check if entry with given key already exists
	if (check_same_key(head, tail, key) == NULL) {
		printf("no such key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key); //Temporary entry points to the entry with given key
	int oldLength = temp->length; //Store the old length of the array of entry as it will have to be updated
	int valueHolder[oldLength]; //Temporary array with size of old length to hold values
	int i = 0; //index to iterate over the array valueHolder, and used to count how many checks has been done
	int j = 0; //index to iterate over the array of entry

	//Iterate over the array of entry
	for (; j < oldLength - 1; j++) {
		//Store first value into new array
		if (i == 0) {
			valueHolder[i] = temp->values[j];
		}

		//Check adjacent value is not the same, store the adjacent value into the new array. If its the same, then ignore and skip onto the next index
		if (valueHolder[i] != temp->values[j+1]) {
			valueHolder[i+1] = temp->values[j+1];
			i++; //Only iterate over the array valueHolder once a value has been stored
		}
	}
	temp->values = (int *) realloc(temp->values, (i+1) * sizeof(int));
	temp->length = i + 1; //Update new length to the number of checks made plus 1

	//Store the new values in the array of entry
	for (int j = 0; j < temp->length; j++) {
		temp->values[j] = valueHolder[j];
	}
	printf("ok\n\n");
}

//Used in command sort
int compare(const void* a, const void* b) {
	const int *ia = (const int *)a; // casting pointer types
  const int *ib = (const int *)b;
	return *ia - *ib;
}

void command_sort(entry* head, entry* tail, char key[]) {
	//Use head entry and tail entry to check if entry with given key already exists
	if (check_same_key(head, tail, key) == NULL) {
		printf("no such key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key); //Temporary entry points to the entry with given key

	//qsort from lib
	qsort(temp->values, temp->length, sizeof(int), compare);
	printf("ok\n\n");
}

void command_listkeys(entry* head, entry* tail) {
	entry* temp = tail; //Temporary entry points to tail of list

	//No entries, no keys
	if (temp->prev == head) {
		printf("no keys\n");
	}

	//Iterate backwards from the list
	while (temp->prev != head) {
		temp = temp->prev;
		printf("%s\n", temp->key);
	}
	printf("\n");
}

void command_listentries(entry* head, entry* tail) {
	entry* temp = tail; //Temporary entry points to tail of list

	//No entries, no keys
	if (temp->prev == head) {
		printf("no entries\n");
	}

	//Iterate going backwards
	while (temp->prev != head) {
		temp = temp->prev;
		printf("%s ", temp->key);
		//Entry with no values
		if (temp->length == 0) {
		printf("[]\n\n");
			return;
		}
		printf("[");
		int i;
		//Print values except for the last value with space
		for (i = 0; i < temp->length-1; i++) {
			printf("%d ", temp->values[i]);
		}
		//Print last value without space
		printf("%d", temp->values[i]);
		printf("]\n");
	}
	printf("\n");
}

//Needs fixing
void command_listsnapshots(snapshot* head, snapshot* tail) {
	snapshot* temp = tail; //Temporary entry points to tail of list

	//No snapshots
	if (temp->prev == head) {
		printf("no snapshots\n");
	}

	//Iterate over list of snapshots
	while (temp->prev != head) {
		temp = temp->prev;
		printf("%d\n", temp->id);
	}
	printf("\n");
}

void command_pick(entry* head, entry* tail, char key[], int* index) {
	//Use head entry and tail entry to check if entry with given key already exists
	if (check_same_key(head, tail, key) == NULL){
		printf("no such key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key); //Temporary entry points to the entry with given key
	//Index given is out of range
	if (*index > temp->length || *index == 0) {
		printf("index out of range\n\n");
		return;
	}
	//Print the value from given index
	printf("%d\n\n", temp->values[*index-1]);
}

void command_pluck(entry* head, entry* tail, char key[], int* index) {
	//Use head entry and tail entry to check if entry with given key already exists
	if (check_same_key(head, tail, key) == NULL) {
		printf("no such key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key); //Temporary entry points to the entry with given key
	//Index given is out of range
	if (*index > temp->length || *index == 0) {
		printf("index out of range\n\n");
		return;
	}
	int oldLength = temp->length; //Variable stores length
	int newLength = temp->length - 1; //Variable stores update length
	int valueHolder[newLength]; //Holds the values of the entry
	int removedValue; //Variable stores the removed value from the array of entry
	int i = 0; //Index for the array values of temp
	int j = 0; //Index for the valueHolder

	//Go through array values of temp, only store the values that are different from the index passed
	for (; i < oldLength; i++){
		//At given index, do not store into the valueHolder array and update removedValue
		if (i == *index - 1){
			removedValue = temp->values[i];
		} else {
			valueHolder[j] = temp->values[i];
			j++;
		}
	}
	temp->values = (int *) realloc(temp->values, newLength * sizeof(int));
	temp->length = newLength; //Update length

	//Store the values into temp
	for (int i = 0; i < temp->length; i++) {
		temp->values[i] = valueHolder[i];
	}
	printf("%d\n\n", removedValue);
}

void command_pop(entry* head, entry* tail, char key[]) {
	//Use head entry and tail entry to check if entry with given key already exists
	if (check_same_key(head, tail, key) == NULL) {
		printf("no such key\n\n");
		return;
	}
	entry* temp = check_same_key(head, tail, key); //Temporary entry points to the entry with given key
	//No values in the entry
	if (temp->length == 0) {
		printf("nil\n\n");
		return;
	}
	int oldLength = temp->length; //Variable to store length
	int newLength = temp->length - 1; //Variable to store updated length
	int valueHolder[newLength]; //Holds the values of the entry
	int removedValue; //Variable to store the removed value
	int i = 0; //Index for the array values of temp
	int j = 0; //Index for the valueHolder

	//Go through array values of temp, only store the values after the first value
	for (; i < oldLength; i++) {
		//Skip over the first value and update removedValue
		if (i == 0) {
			removedValue = temp->values[i];
		} else {
			valueHolder[j] = temp->values[i];
			j++;
		}
	}
	temp->values = (int *) realloc(temp->values, newLength * sizeof(int));
	temp->length = newLength; //Update length

	//Store the values into temp
	for (int i = 0; i < temp->length; i++) {
		temp->values[i] = valueHolder[i];
	}
	printf("%d\n\n", removedValue);
}

void command_bye(entry* head, entry* tail, snapshot* headSP, snapshot* tailSP) {
	entry* temp = head; //Temporary entry to point at head
	//Iterate over list and delete entries
	while (temp->next != tail){
		command_del(head, tail, temp->next->key);
	}
	free(head); //Free head entry
	free(tail); //Free tail entry
	free(headSP); //Free head snapshot
	free(tailSP); //Free tail snapshot
	printf("bye\n");
}

//Tail entry is passed and append a new entry to the end of the list
entry* create_entry(entry* tail){
	entry* temp = (entry *) malloc(sizeof(entry)); //Allocate memory for the new entry

	//Append to the end of the list, before tail
	temp->next = tail;
	tail->prev->next = temp;
	temp->prev = tail->prev;
	tail->prev = temp;
	return temp;
}

//Initialise list by linking head and tail
void initialise_list(entry* head, entry* tail) {
	head->next = tail;
	head->prev = NULL;

	tail->next = NULL;
	tail->prev = head;
}

//Initialise snapshot list by linking head and tail
void initialise_listSP(snapshot* head, snapshot* tail) {
	head->next = tail;
	head->prev = NULL;

	tail->next = NULL;
	tail->prev = head;
}

//Choose command
void select_command(char line[], entry* headEntry, entry* tailEntry, snapshot* headSP, snapshot* tailSP) {
	char* token;
	int arrValues[MAX_LINE]; //Array to store the values given from input
	char keyHolder[MAX_KEY]; //Char array to store the string key from given input
	int length = 0; //Used as length of entry and as index for the array arrValues
	int indexHolder = 0; //Integer to store the index given from input

	if (strncasecmp(line, "BYE", 3) == 0) {
		command_bye(headEntry, tailEntry, headSP, tailSP);
		exit(0);
	}
	else if (strncasecmp(line, "HELP", 4) == 0) {
		command_help();
	}
	else if (strncasecmp(line, "LIST KEYS", 9) == 0) {
		command_listkeys(headEntry, tailEntry);
	}
	else if (strncasecmp(line, "LIST ENTRIES", 12) == 0) {
		command_listentries(headEntry, tailEntry);
	}
	else if (strncasecmp(line, "LIST SNAPSHOTS", 14) == 0) {
		command_listsnapshots(headSP, tailSP);
	}
	else if (strncasecmp(line, "GET", 3) == 0) {
		//Get first token (command)
		token = strtok(line, " \n");

		//Get second token (key or id)
		token = strtok(NULL, " \n");
		sscanf(token, " %s", keyHolder);

		command_get(headEntry, tailEntry, keyHolder);
	}
	else if (strncasecmp(line, "DEL", 3) == 0) {
		//Get first token (command)
		token = strtok(line, " \n");

		//Get second token (key or id)
		token = strtok(NULL, " \n");
		sscanf(token, " %s", keyHolder);

		if (check_same_key(headEntry, tailEntry, keyHolder) == NULL) {
			printf("no such key\n\n");
		} else {
			command_del(headEntry, tailEntry, keyHolder);
			printf("ok\n\n");
		}

	}
	else if (strncasecmp(line, "PURGE", 5) == 0) {
		//Get first token (command)
		token = strtok(line, " \n");

		//Get second token (key or id)
		token = strtok(NULL, " \n");
		sscanf(token, " %s", keyHolder);

		command_purge(headEntry, tailEntry, headSP, tailSP, keyHolder);
	}
	else if (strncasecmp(line, "SET", 3) == 0) { //Need to fix, if its the same key then replace

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
				length++;
			}
		}
		command_set(headEntry, tailEntry, create_entry(tailEntry), arrValues, &length, keyHolder);

	}
	else if (strncasecmp(line, "PUSH", 4) == 0) {
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
		command_push(headEntry, tailEntry, arrValues, &length, keyHolder);

	}
	else if (strncasecmp(line, "APPEND", 6) == 0) {
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
				length++;
			}
		}

		command_append(headEntry, tailEntry, arrValues, &length, keyHolder);
	}
	else if (strncasecmp(line, "PICK", 4) == 0) {
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
	else if (strncasecmp(line, "PLUCK", 5) == 0) {
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
	else if (strncasecmp(line, "DROP", 4) == 0) {

	}
	else if (strncasecmp(line, "ROLLBACK", 8) == 0) {

	}
	else if (strncasecmp(line, "CHECKOUT", 8) == 0) {

	}
	else if (strncasecmp(line, "SNAPSHOT", 8) == 0) {

	}
	else if (strncasecmp(line, "MIN", 3) == 0) {
		//Get first token (command)
		token = strtok(line, " \n");

		//Get second token (key or id)
		token = strtok(NULL, " \n");
		sscanf(token, " %s", keyHolder);

		command_min(headEntry, tailEntry, keyHolder);
	}
	else if (strncasecmp(line, "MAX", 3) == 0) {
		//Get first token (command)
		token = strtok(line, " \n");

		//Get second token (key or id)
		token = strtok(NULL, " \n");
		sscanf(token, " %s", keyHolder);

		command_max(headEntry, tailEntry, keyHolder);
	}
	else if (strncasecmp(line, "SUM", 3) == 0) {
		//Get first token (command)
		token = strtok(line, " \n");

		//Get second token (key or id)
		token = strtok(NULL, " \n");
		sscanf(token, " %s", keyHolder);

		command_sum(headEntry, tailEntry, keyHolder);
	}
	else if (strncasecmp(line, "LEN", 3) == 0) {
		//Get first token (command)
		token = strtok(line, " \n");

		//Get second token (key or id)
		token = strtok(NULL, " \n");
		sscanf(token, " %s", keyHolder);

		command_len(headEntry, tailEntry, keyHolder);
	}
	else if (strncasecmp(line, "REV", 3) == 0) {
		//Get first token (command)
		token = strtok(line, " \n");

		//Get second token (key or id)
		token = strtok(NULL, " \n");
		sscanf(token, " %s", keyHolder);

		command_rev(headEntry, tailEntry, keyHolder);
	}
	else if (strncasecmp(line, "UNIQ", 4) == 0) {
		//Get first token (command)
		token = strtok(line, " \n");

		//Get second token (key or id)
		token = strtok(NULL, " \n");
		sscanf(token, " %s", keyHolder);

		command_uniq(headEntry, tailEntry, keyHolder);
	}
	else if (strncasecmp(line, "SORT", 4) == 0) {
		//Get first token (command)
		token = strtok(line, " \n");

		//Get second token (key or id)
		token = strtok(NULL, " \n");
		sscanf(token, " %s", keyHolder);

		command_sort(headEntry, tailEntry, keyHolder);
	}
	else if (strncasecmp(line, "DIFF", 4) == 0) {

	}
	else if (strncasecmp(line, "INTER", 5) == 0) {

	}
	else if (strncasecmp(line, "UNION", 5) == 0) {

	}

}

int main(void) {

	char line[MAX_LINE];

	entry* headEntry = (entry *) malloc(sizeof(entry));
	entry* tailEntry = (entry *) malloc(sizeof(entry));
	initialise_list(headEntry, tailEntry);

	snapshot* headSP = (snapshot *) malloc(sizeof(snapshot));
	snapshot* tailSP = (snapshot *) malloc(sizeof(snapshot));
	initialise_listSP(headSP, tailSP);

	while (true) {
		printf("> ");

		if (fgets(line, MAX_LINE, stdin) == NULL) {
			printf("\n");
			command_bye(headEntry, tailEntry, headSP, tailSP);
			return 0;
		}

		select_command(line, headEntry, tailEntry, headSP, tailSP);
  }
	return 0;
}
