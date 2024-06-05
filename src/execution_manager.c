#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "execution_manager.h"
#include "input_manager.h"
#include "mode_manager.h"

// function to execute code based on the current mode
int execute_code() {
	char* mode = get_current_mode();	// get the current language mode
	char* code = get_code_buffer();		// get the collected code from input

	if (strlen(code) == 0){
		printf("ERROR: No code to execute. Please enter code first");
		return -1;
	}

	char temp_filename[32];
	int result = 0;

	if (strcmp(mode, "python") == 0) {
		// create a temp file for python code
		snprintf(temp_filename, sizeof(temp_filename), "tempcodeXXXXXX.py");
		int temp_fd = mkstemps(temp_filename, 3);
		if (temp_fd == -1) {
			printf("ERROR: Could not create a temporary file for python code.");
			return -1;
		}

		// write code to the temporary file
		FILE *file = fdopen(temp_fd, "w");
		if (file) {
			fputs(code, file);
			fclose(file);

			// execute code using python3
			char command[128];
			snprintf(command, sizeof(command), "python3 %s", temp_filename);
			result = system(command);

			remove(temp_filename); // remove temporary file

		} else {
			printf("ERROR: Could not write to temporary file.\n");
			close(temp_fd);
			return -1;
		}
	} else if (strcmp(mode, "c") == 0) {
		// create a temp file for c code
		snprintf(temp_filename, sizeof(temp_filename), "tempcodeXXXXXX.c");
		int temp_fd = mkstemps(temp_filename, 2);
		if (temp_fd == -1) {
			printf("ERROR: Could not create a temporary file for C code.");
			return -1;
		}

		// save the C code to a temporary file, compile and run
		FILE *file = fdopen(temp_filename, "w");
		if (file) {
			fputs(code, file);
			fclose(file);

			// compile and run C program
			char command[128];
			snprintf(command, sizeof(command), "gcc %s -o temp_program && ./temp_program", temp_filename);
			system("gcc temp_code.c -o temp_program && ./temp_program");

			// clean up file and program
			remove(temp_filename);
			remove("temp_program");
		} else {
			printf("ERROR: Could not write to temporary file for C code\n");
			close(temp_fd);
			return -1;
		}

	} else {
		printf("No valid mode set. Please set the mode to 'python' or 'c'.\n");
		return -1;
	}

	// check if code executed
	if (result != 0) {
		printf("ERROR: Code execution failed.\n");
		return -1;
	}

	return 0;
}
