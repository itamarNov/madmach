# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Define the project and specify it uses C
project(MyCProject LANGUAGES C)

# Add an executable target with source files
add_executable(MyExecutable main.c utils.c)
