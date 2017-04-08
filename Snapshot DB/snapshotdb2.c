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

void strtok_first_token(char line[], char* token){
	//Get the first token (Command)
	token = strtok(line, " \n");
}

void strtok_second_token(char* token, char key[MAX_KEY]){
	token = strtok(NULL, " \n");
	sscanf(token, " %s", key);
}

void command_bye() {
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
	printf("ok\n");
}

int command_get(entry* head, entry* tail, char key[]){
	entry* temp = head;

	while (temp != tail){

		if (strcmp(temp->key, key) == 0){
			printf("[");
			for (int i = 0; i < temp->length; i++){
				printf("%d ", temp->values[i]);
			}
			printf("]\n"); //Fix later
			return 0; //Passed
		}

		temp = temp->next;
	}

	printf("no such key\n");
	return 1;
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
	int arrValues[MAX_LINE];
	char keyHolder[MAX_KEY];
	char* token;
	int length; // index for array of value
	entry* headEntry = (entry *) malloc(sizeof(entry));
	entry* tailEntry = (entry *) malloc(sizeof(entry));

	initialise_list(headEntry, tailEntry);


	while (true) {
		printf("> ");

		if (fgets(line, MAX_LINE, stdin) == NULL) {
			printf("\n");
			command_bye();
			return 0;
		}

		length = 0;





		if (strncasecmp(line, "BYE", 3) == 0){
			command_bye();
			return 0;
		}
		else if (strncasecmp(line, "HELP", 4) == 0){
			command_help();
		}
		else if (strncasecmp(line, "LIST KEYS", 9) == 0){
			command_listkeys(headEntry, tailEntry);
		}
		else if (strncasecmp(line, "LIST ENTRIES", 12) == 0){
			command_help();
		}
			else if (strncasecmp(line, "LIST SNAPSHOTS", 14) == 0){
			command_help();
		}

		else if (strncasecmp(line, "GET", 3) == 0){

		//Get first token (command)
		strtok_first_token(line, token);

		//Get second token (key or id)
		strtok_second_token(token, keyHolder);

		command_get(headEntry, tailEntry, keyHolder);


		}
			else if (strncasecmp(line, "DEL", 3) == 0){
			command_help();
		}
			else if (strncasecmp(line, "PURGE", 5) == 0){
			command_help();
		}
		else if (strncasecmp(line, "SET", 3) == 0){

		//Get first token (command)
		strtok_first_token(line, token);

		//Get second token (key or id)
		strtok_second_token(token, keyHolder);

		//printf("%s", keyHolder);


		//Walk through other tokens (Values)
		while (token != NULL) {
			token = strtok(NULL, " \n");

			//Stop sscanf at the last token
			if (token != NULL) {
				sscanf(token, " %d", &arrValues[length]);
			//	printf("  %d\n", arrValues[length]);
				length++;
			}
		}

		command_set(create_entry(tailEntry), arrValues, length, keyHolder);


		}
			else if (strncasecmp(line, "PUSH", 4) == 0){
			printf("hello");

		}
			else if (strncasecmp(line, "APPEND", 6) == 0){
			command_help();
		}
			else if (strncasecmp(line, "PICK", 4) == 0){
			command_help();
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
			command_help();
		}
			else if (strncasecmp(line, "MAX", 3) == 0){
			command_help();
		}
			else if (strncasecmp(line, "SUM", 3) == 0){
			command_help();
		}
			else if (strncasecmp(line, "LEN", 3) == 0){
			command_help();
		}
			else if (strncasecmp(line, "REV", 3) == 0){
			command_help();
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
