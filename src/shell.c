#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "builtins.h"
#include "input_manager.h"
#include "mode_manager.h"
#include "execution_manager.h"
#include "snippet_manager.h"

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 100

// tokenizes the input and skips extra spaces
void parse_input(char* input, char** args) {
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

// executes built-in commands
int execute_builtin(char **args) {
    if (strcmp(args[0], "cd") == 0) {
        return cd_command(args);
    }

    if (strcmp(args[0], "exit") == 0) {
        return exit_command();
    }

    if (strcmp(args[0], "mode") == 0) {
        if (args[1] != NULL) {
            return set_mode(args[1]); // set the language mode
        } else {
            printf("ERROR: 'mode' command requires an argument.\n");
            return -1;
        }
    }

    return -1; // not a built-in command
}

// executes external commands using fork-exec
int execute_external_command(char **args) {
    pid_t pid = fork();
    int status;

    if (pid == 0) { // child process
        if (execvp(args[0], args) == -1) {
            perror("ERROR: Command execution failed");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) { // fork failed
        perror("ERROR: Failed to create new process");
        return -1;
    } else { // parent process
        waitpid(pid, &status, 0); // wait for the child process to complete
    }

    return status;
}

void shell_loop() {
    char input[MAX_INPUT_SIZE];     // user input
    char *args[MAX_ARGS];           // command arguments

    // main loop listening for shell input
    while (1) {
        // Display the shell prompt
        printf("%s-shell> ", get_current_mode());   // show current mode in prompt
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            printf("ERROR: Failed to read input.\n");
            continue;
        }

        // remove the new line from input
        int input_len = strlen(input) - 1;
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
        } else if (builtin_status == 1) {
            continue; // command executed successfully, continue the loop
        }

        // handle custom commands
        if (strcmp(args[0], "start") == 0) {
            collect_multiline_input(); // collect code input
            if (strlen(get_code_buffer()) > 0) {
                if (execute_code() != 0) {
                    printf("ERROR: Code execution failed.\n");
                }
            }
            continue;
        }

        if (strcmp(args[0], "load_snippet") == 0) {
            if (args[1] != NULL) {
                memset(get_code_buffer(), 0, CODE_BUFFER_SIZE);
                if (load_snippet(args[1], get_code_buffer())) {
                    printf("Snippet '%s' loaded successfully.\n", args[1]);
                    display_code_buffer();
                    collect_multiline_input();
                } else {
                    printf("ERROR: Snippet '%s' not found.\n", args[1]);
                }
            } else {
                printf("ERROR: 'load_snippet' requires an argument.\n");
            }
            continue;
        }

        // execute external command
        execute_external_command(args);
    }
}

int main() {
    // start the shell loop
    shell_loop();
}
