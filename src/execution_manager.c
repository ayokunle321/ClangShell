#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "execution_manager.h"
#include "input_manager.h"
#include "mode_manager.h"

// function to execute code based on the current mode
void execute_mode() {
	char* mode = get_current_mode();	// get the current language mode
	char* code = get_code_buffer();		// get the collected code from input

	if (strcmp(mode, "python") == 0) {
		// save the python code to a temp file
		FILE *file = fopen("temp_code.py", "w");
		if (file) {
			fputs(code, file);
			fclose(file);
			system("python3 temp_code.py");
		}
	} else if (strcmp(mode, "c") == 0) {
		// save the C code to a temporary file, compile and run
		FILE *file = fopen("temp_code.c", "w");
		if (file) {
			fputs(code, file);
			fclose(file);
			system("gcc temp_code.c -o temp_program && ./temp_program");
		} else {
			printf("ERROR: Could not write to temp_code.c\n");
		}

	} else {
		printf("No valid mode set.");
	}

}
