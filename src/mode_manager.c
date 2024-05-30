#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mode_manager.h"

static char current_mode[10] = "";

// function to check if a command exists in the system
int is_tool_available(const char *tool) {
	char command[100];
	snprintf(command, sizeof(command), "command -v %s > /dev/null 2>&1", tool);
	return system(command) == 0;
}

// function to change the mode
void set_mode(const char*mode) {
	if (strcmp(mode, "python") == 0) {
		if (is_tool_available("python3")) {
			strcpy(current_mode, mode);
			printf("Mode switched to python\n");
		} else {
			printf("python3 is not installed. Please install python3 to use this mode.\n");
		}

	} else if (strcmp(mode, "c") == 0) {
		if (is_tool_available("gcc")) {
			strcpy(current_mode, mode);
		} else {
			printf("gcc is not installed. Please install gcc to use this mode.\n");
		}

	} else {
		printf("Unsupported mode: %s\n", mode);
	}
}

// function to get the current mode
char* get_current_mode () {
	return current_mode;
}
