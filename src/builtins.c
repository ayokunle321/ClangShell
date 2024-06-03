#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "builtins.h"


// command to change directory
int cd_command(char **args) {
	if (args[1] == NULL) {
		fprintf(stderr, "cd: expected argument to \"cd\"\n");
	} else {
		if (chdir(args[1]) != 0) {
			perror("cd");
		}
	}
	return 1; // continue shell loop
}

// command to exit polyshell
int exit_command() {
	return 0; // exit shell
}
