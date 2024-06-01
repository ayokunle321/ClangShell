#pragma once

// function to save a snippet
void save_snippet(char* name, char* content);

// function to retrieve a snippet by name
int retrieve_snippet(char* name, char* content_buffer);

// function to list all saved snippets
void list_snippets();

// function to delete a snippet by name
void delete_snippet(char* name);
