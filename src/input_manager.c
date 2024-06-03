#include <stdio.h>
#include <string.h>
#include "input_manager.h"

// buffer to hold code during multi-line input
static char code_buffer[CODE_BUFFER_SIZE];

// function to collect multi-line input for code
void collect_multiline_input() {
	char input[MAX_INPUT_SIZE];
	printf("Multi-line mode. Type your code. Type 'run' to execute");

	while(1) {
		printf("... ");
		fgets(input, MAX_INPUT_SIZE, stdin);

		// remove new line from input
		input[strlen(input) - 1] = '\0';

		if (strcmp(input, "run") == 0) {
			break;
		}

		strcat(code_buffer, input); // append input to the code buffer
		strcat(code_buffer, "\n"); // add newline between code lines
	}
	memset(code_buffer, 0, sizeof(code_buffer)); // clear the buffer
}

// function to display what is in the code buffer
void display_code_buffer() {
	char* line = strtok(get_code_buffer(), "\n");
	while (line != NULL) {
		printf("... %s\n", line);
		line = strtok(NULL, "\n");
	}

}

// function to retrieve current code buffer for execution
char* get_code_buffer() {
	return code_buffer;
}