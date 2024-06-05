#include <stdio.h>
#include <string.h>
#include "input_manager.h"

#include <sys/resource.h>

// buffer to hold code during multi-line input
static char code_buffer[CODE_BUFFER_SIZE];

// function to collect multi-line input for code
void collect_multiline_input() {
	char input[MAX_INPUT_SIZE];
	printf("Multi-line mode. Type your code. Type 'run' to execute\n");

	while(1) {
		printf("... ");
		if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
			printf("ERROR: Failed to read input.\n");
			break;
		}

		size_t input_len = strlen(input);

		if (input[input_len -1] == '\n') {
			input[input_len -1] = '\0';
		}

		// remove new line from input
		input[strlen(input) - 1] = '\0';

		if (strcmp(input, "run") == 0) {
			break;
		}

		if (strlen(code_buffer) + strlen(input) + 1 >= CODE_BUFFER_SIZE) {
			printf("ERROR: Code buffer full cannot add more input.\n");
			break;
		}

		strcat(code_buffer, input); // append input to the code buffer
		strcat(code_buffer, "\n"); // add newline between code lines
	}
}

// function to display what is in the code buffer
void display_code_buffer() {
	char temp_buffer[CODE_BUFFER_SIZE];
	strncpy(temp_buffer, code_buffer, CODE_BUFFER_SIZE);

	char* line = strtok(temp_buffer, "\n");
	while (line != NULL) {
		printf("... %s\n", line);
		line = strtok(NULL, "\n");
	}
}

// function to retrieve current code buffer for execution
char* get_code_buffer() {
	return code_buffer;
}