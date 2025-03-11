cmake_minimum_required(VERSION 3.19)

project(global-Week_6-String_Functions_3)

set(CMAKE_CXX_STANDARD 14)

# Files from `./src` directory
set(SRC
        src/password6.cpp
        src/password6.h
        src/main.cpp)


# Running learner side code
# Use PROJECT_NAME dependent names of targets for the plugin support to work correctly.
add_executable(${PROJECT_NAME}-run ${SRC})