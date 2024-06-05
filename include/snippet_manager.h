#pragma once

// load snippet
int load_snippet(const char* name, char* content_buffer);

// save a snippet
int save_snippet(const char* name, const char* content);

// list all saved snippets
void list_snippets();

// delete a snippet
int delete_snippet(const char* name);
