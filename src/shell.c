#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <builtins.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 100

// tokenizes the input and skips extra spaces
void parse_input(char* input, char** args){
	int i = 0;
	char* token = strtok(input, " ");

	while (token != NULL) {
		// skip empty tokens
		if (strlen(token) > 0) {
			args[i++] = token;
		}

		token = strtok(NULL, " ");
	}

	args[i] = NULL; // null terminate args array
}

int execute_builtin(char **args){
	if (strcmp(args[0], "cd") == 0) {
		return cd_command(args);
	}

	if (strcmp(args[0], "exit") == 0) {
		return exit_command(args);
	}

	return -1; // else not a built-in command
}

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
		int input_len = strlen(input)-1;
		input[input_len] = '\0';

		// skip empty input
		if (input_len == 0 || isspace(input[0])) {
			continue;
		}

		// split input into args
		parse_input(input, args);

		// check if command is built in
		int builtin_status = execute_builtin(args);
		if (builtin_status == 0) {
			break; // exit shell
		}

		if (builtin_status == 1) {
			continue; // command executed now continue loop
		}

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


