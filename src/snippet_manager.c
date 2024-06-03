#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "snippet_manager.h"

#define MAX_SNIPPETS 100
#define MAX_SNIPPET_SIZE 1024

typedef struct {
	char name[50];
	char content[MAX_SNIPPET_SIZE];
} Snippet;

Snippet snippet_storage[MAX_SNIPPETS];	//array to hold saved snippets
int snippet_count = 0;

void save_snippet(char* name, char* content) {
	if (snippet_count < MAX_SNIPPETS) {
		strcpy(snippet_storage[snippet_count].name, name);
		strcpy(snippet_storage[snippet_count].content, content);
		snippet_count++;
		printf("Snippet '%s' saved successfully.\n", name);
	} else {
		printf("Error: Maximum snippet storage limit reached.\n");
	}
}

// function to load a snippet by name
int load_snippet(const char* name, char* content_buffer) {
	for (int i = 0; i < snippet_count; i++) {
		if (strcmp(snippet_storage[i].name, name) == 0) {
			strcpy(content_buffer, snippet_storage[i].content);
			return 1; // snippet found
		}
	}
	return 0; // snippet not found
}

// function to list all saved snippets
void list_snippets(){
	if (snippet_count == 0) {
		printf("No snippets saved.\n");
	} else {
		printf("Saved snippets: \n");
		for (int i = 0; i < snippet_count; i++) {
			printf(" -%s\n", snippet_storage[i].name);
		}
	}
}

// function to delete snippet
void delete_snippet(char* name)
{
	for (int i = 0; i < snippet_count; i++) {
		if (strcmp(snippet_storage[i].name, name) == 0) {
			for (int j = i; j < snippet_count - 1; j++) {
				snippet_storage[j] = snippet_storage[j + 1];
			}
			snippet_count--;

			printf("Snippet '%s' deleted successfully.\n", name);
			return;
		}
	}

	printf("Snippet '%s' not found.\n", name);
}

