#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 100

void shell_loop() {
	char input[MAX_INPUT_SIZE];		// user input
    char *args[MAX_ARGS];			// command arguments
	pid_t pid;						// process id
	int status;						// status for child process

	// main loop listening for shell
	while (1) {
		printf("clang-shell> ");
		fgets(input, MAX_INPUT_SIZE, stdin);	// read user input

		// remove new line from input
		int input_len = strlen(input);
		input[input_len] = '\0';

		// split input into command and args
		char *token = strtok(input, " ");
		int i = 0;

		while (token != NULL ) {
			args[i++] = token;
			token = strtok(NULL, " ");	// split remaining tokens
		}

		args[i] = NULL; // null terminate array

		pid = fork(); // making a new process to execute the command

		// child process
		if (pid == 0) {
			if (execvp(args[0], args ) == -1) {
				perror("ERROR: command could not be executed");	// display error if command fails
			}
			exit(EXIT_FAILURE);
		}

		if (pid < 0) {
			perror("ERROR: a new process could not be created"); // display error if forking failed

		}

		// parent process
		else {
			waitpid(pid, &status, 0); // wait for child process to complete
		}

	}
}

int main()
{
	// call shell loop
	shell_loop();
}


