#pragma once

// load snippet
int load_snippet(const char* name, char* content_buffer);

// save a snippet
void save_snippet(char* name, char* content);

// list all saved snippets
void list_snippets();

// delete a snippet
void delete_snippet(char* name);
