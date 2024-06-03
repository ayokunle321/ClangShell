#pragma once

// function to set language mode
void set_mode(const char* mode);

// function to get the current language mode
char* get_current_mode();

// function to check if a tool is available in the system
int is_tool_available(const char *tool);