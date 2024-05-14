#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "builtins.h"


// function for "cd" command
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

// function for "exit" command
int exit_command(char **args) {
	return 0; // exit shell
}
