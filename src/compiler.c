#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"

// function to compile C files using clang
int compile_and_run(char *source_file) {
	char command[1024];
	char executable[256];

	// generate the name of the executable
	snprintf(executable, sizeof(executable), "./%.*s", (int)strlen(source_file) - 2, source_file);

	// compile the C program
	snprintf(command, sizeof(command), "clang %s -o %s", source_file, executable);
	int result = system(command);

	if (result == 0) {
		// execute program after compiling
		printf("Compilation successful, running %s...\n", executable);
		system(executable);
	} else {
		fprintf(stderr, "ERROR: Compilation failed\n");
		return 1; // error occurred
	}

	return 0; // success
}