#pragma once

#define MAX_INPUT_SIZE 1024
#define CODE_BUFFER_SIZE 4096

// function to collect multi-line input
void collect_multiline_input();

// display code buffer's content
void display_code_buffer();

//function to retrieve the current code buffer
char* get_code_buffer();