cmake_minimum_required(VERSION 3.29)
project(ClangShell C)

set(CMAKE_C_STANDARD 11)

# add the include directory
include_directories(include)

# target
add_executable(clangshell
        src/shell.c)
