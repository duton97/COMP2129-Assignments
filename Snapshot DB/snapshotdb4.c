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

void command_bye(entry* head, entry* tail) {
	free(head);
	free(tail);
	printf("bye\n");
}

void command_help() {
	printf("%s\n", HELP);
}

void command_set(entry* entry, int *array, int length, char key[]) {
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

void command_get(entry* head, entry* tail, char key[]){
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key");
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
		printf("no suck key");
		return;
	}

	entry* temp = check_same_key(head, tail, key);
	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;
	free(temp->values);
	free(temp);
	printf("ok\n\n");
}

void command_min(entry* head, entry* tail, char key[]){
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key");
		return;
	}

	entry* temp = check_same_key(head, tail, key);
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
		printf("no suck key");
		return;
	}

	entry* temp = check_same_key(head, tail, key);
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
		printf("no suck key");
		return;
	}
	entry* temp = check_same_key(head, tail, key);
	int sum = temp->values[0];
	for (int i = 1; i < temp->length; i++){
		sum = sum + temp->values[i];
	}
	printf("%d\n\n", sum);
}

void command_len(entry* head, entry* tail, char key[]){
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key");
		return;
	}
	entry* temp = check_same_key(head, tail, key);
	printf("%zu\n\n", temp->length);
}

void command_rev(entry* head, entry* tail, char key[]){
	if (check_same_key(head, tail, key) == NULL){
		printf("no suck key");
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
		printf("no suck key");
		return;
	}

	entry* temp = check_same_key(head, tail, key);

	if (*index > temp->length || *index == 0) {
		printf("index out of range\n\n");
		return;
	}

	printf("%d\n\n", temp->values[*index-1]);
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

		int length; // index for array of value
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
			printf("hello");

		}
			else if (strncasecmp(line, "APPEND", 6) == 0){
			command_help();
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
			command_help();
		}
			else if (strncasecmp(line, "POP", 3) == 0){
			command_help();
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
			else if (strncasecmp(line, "SORT", 4) == 0){
			command_help();
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
