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

void command_bye() {
	printf("bye\n");
}

void command_help() {
	printf("%s\n", HELP);
}

void command_set(entry* entry, int *array) {
	entry->values =
}

entry* create_entry(){
	entry* list = (entry *) malloc(sizeof(entry));
	return list;
}

int main(void) {

	char line[MAX_LINE];
	int arrValues[MAX_LINE];
	char* token;
	int i;

	while (true) {
		printf("> ");

		if (fgets(line, MAX_LINE, stdin) == NULL) {
			printf("\n");
			command_bye();
			return 0;
		}

		i = 0;

		//Get the first token (Command)
		token = strtok(line, " \n");

		//Walk through other tokens (Values)
		while (token != NULL) {
			token = strtok(NULL, " \n");

			//Stop sscanf at the last token
			if (token != NULL) {
				sscanf(token, " %d", &arrValues[i]);
				printf("  %d\n", arrValues[i]);
				i++;
			}
		}

		if (strncasecmp(line, "BYE", 3) == 0){
			command_bye();
			return 0;
		}
		else if (strncasecmp(line, "HELP", 4) == 0){
			command_help();
		}
		else if (strncasecmp(line, "LIST KEYS", 9) == 0){
			command_help();
		}
		else if (strncasecmp(line, "LIST ENTRIES", 12) == 0){
			command_help();
		}
			else if (strncasecmp(line, "LIST SNAPSHOTS", 14) == 0){
			command_help();
		}
			else if (strncasecmp(line, "GET", 3) == 0){
			command_help();
		}
			else if (strncasecmp(line, "DEL", 3) == 0){
			command_help();
		}
			else if (strncasecmp(line, "PURGE", 5) == 0){
			command_help();
		}
			else if (strncasecmp(line, "SET", 3) == 0){
			command_set(create_entry(), arrValues);
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
