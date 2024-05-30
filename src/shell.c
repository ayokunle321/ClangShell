#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "builtins.h"
#include "snippet_manager.h"


#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 100
#define CODE_BUFFER_SIZE 4096

char current_mode[10] = "";	// no default mode on startup
char code_buffer[CODE_BUFFER_SIZE]; // buffer to hold code during multi-line input


void load_snippet(char *snippet_name) {
	char snippet[MAX_INPUT_SIZE * 100]; // buffer to hold loaded snippet

	if (retrieve_snippet(snippet_name, snippet)) {
		printf("Loaded snippet '%s'. You can edit it before running. \n", snippet_name);
		printf("%s\n", snippet); // display snippet

		strcpy(code_buffer, snippet); // load snippet in code buffer
		collect_multiline_input() // allow user to edit and run
	} else {
		printf("Snippet '%s' not found.\n", snippet_name);
	}
}

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

// function to execute built-in commands
int execute_builtin(char **args){
	if (strcmp(args[0], "cd") == 0) {
		return cd_command(args);
	}

	if (strcmp(args[0], "exit") == 0) {
		return exit_command(args);
	}

	if (strcmp(args[0], "mode") == 0) {
		set_mode(args[1]); // set the language mode
		return 1; // success
	}

	return -1; // not a built-in command
}

void shell_loop() {
	char input[MAX_INPUT_SIZE];		// user input
    char *args[MAX_ARGS];			// command arguments
	pid_t pid;						// process id
	int status;						// status for child process

	// main loop listening for shell
	while (1) {
		printf("%s-shell> ", current_mode);		// show current mode in prompt
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

		// check if command is built-in
		int builtin_status = execute_builtin(args);
		if (builtin_status == 0) {
			break; // exit shell
		} if (builtin_status == 1) {
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


