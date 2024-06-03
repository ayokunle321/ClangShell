cmake_minimum_required(VERSION 3.29)
project(PolyShell C)

set(CMAKE_C_STANDARD 11)

# add the include directory
include_directories(include)

# executable folder
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

# executable target
add_executable(polyshell
        src/shell.c
        src/builtins.c
        src/input_manager.c
        src/mode_manager.c
        src/execution_manager.c
        src/snippet_manager.c
)
