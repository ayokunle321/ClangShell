#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mode_manager.h"

#define MAX_MODE_LENGTH 20

static char current_mode[MAX_MODE_LENGTH] = "";

// checks if a command exists in the system
int is_tool_available(const char *tool) {
	char command[100];
	snprintf(command, sizeof(command), "command -v %s > /dev/null 2>&1", tool);
	return system(command) == 0;
}

// sets program mode
int set_mode(const char*mode) {
	// supported modes and their tools
	struct {
		const char *name;
		const char *tool;
	} modes[] = {
		{"python", "python3"},
		{"c", "gcc"}
		};

	for (size_t i = 0; i < sizeof(modes) / sizeof(modes[0]); ++i) {
		if (strcmp(mode, modes[i].name) == 0) {
			// check if required tool is available
			if (is_tool_available(modes[i].tool)){
				strncpy(current_mode, mode,	MAX_MODE_LENGTH - 1);
				current_mode[MAX_MODE_LENGTH - 1] = '\0'; // ensure its null terminated
				printf("Mode set to '%s'.\n", mode);
				return 0;
			}
		} else {
			printf("ERROR: '%s' is not installed. Please install '%s' to use this mode.\n",
				modes[i].tool, modes[i].tool);
			return -2; // tool not available
		}
	}

	printf("ERROR: Unsupported mode %s. Available modes are 'python' and 'c'.\n", mode);
	return -1; // unsupported mode
}

// function to get the current mode
char* get_current_mode () {
	return current_mode;
}
