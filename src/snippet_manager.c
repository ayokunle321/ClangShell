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

Snippet snippet_storage[MAX_SNIPPETS];  // array to hold saved snippets
int snippet_count = 0;

// saves a snippet
int save_snippet(const char* name, const char* content) {
    if (name == NULL || strlen(name) == 0) {
        printf("ERROR: Snippet name cannot be empty.\n");
        return -1; // invalid name
    }

    if (content == NULL || strlen(content) == 0) {
        printf("ERROR: Snippet content cannot be empty.\n");
        return -2; // invalid content
    }

    // check if the snippet already exists
    for (int i = 0; i < snippet_count; i++) {
        if (strcmp(snippet_storage[i].name, name) == 0) {
            printf("ERROR: A snippet with the name '%s' already exists.\n", name);
            return -3; // duplicate name
        }
    }

    if (snippet_count < MAX_SNIPPETS) {
        strncpy(snippet_storage[snippet_count].name, name, sizeof(snippet_storage[snippet_count].name) - 1);
        snippet_storage[snippet_count].name[sizeof(snippet_storage[snippet_count].name) - 1] = '\0'; // ensure null-termination

        strncpy(snippet_storage[snippet_count].content, content, sizeof(snippet_storage[snippet_count].content) - 1);
        snippet_storage[snippet_count].content[sizeof(snippet_storage[snippet_count].content) - 1] = '\0'; // ensure null-termination

        snippet_count++;
        printf("Snippet '%s' saved successfully.\n", name);
        return 0; // succes
    } else {
        printf("ERROR: Maximum snippet storage limit reached.\n");
        return -4; //storage limit reached
    }
}

// loads a snippet
int load_snippet(const char* name, char* content_buffer) {
    for (int i = 0; i < snippet_count; i++) {
        if (strcmp(snippet_storage[i].name, name) == 0) {
            strncpy(content_buffer, snippet_storage[i].content, MAX_SNIPPET_SIZE - 1);
            content_buffer[MAX_SNIPPET_SIZE - 1] = '\0'; // ensure null-termination
            return 1; // snippet found
        }
    }
    return 0; // snippet not found
}

// list all saved snippets
void list_snippets() {
    if (snippet_count == 0) {
        printf("No snippets saved.\n");
    } else {
        printf("Saved snippets:\n");
        for (int i = 0; i < snippet_count; i++) {
            printf(" - %s\n", snippet_storage[i].name);
        }
    }
}

// delete a snippet
int delete_snippet(const char* name) {
    for (int i = 0; i < snippet_count; i++) {
        if (strcmp(snippet_storage[i].name, name) == 0) {
            // shift the remaining snippets to fill the gap
            for (int j = i; j < snippet_count - 1; j++) {
                snippet_storage[j] = snippet_storage[j + 1];
            }
            snippet_count--;
            printf("Snippet '%s' deleted successfully.\n", name);
            return 1; //
        }
    }
    printf("ERROR: Snippet '%s' not found.\n", name);
    return 0; // snippet not found
}
