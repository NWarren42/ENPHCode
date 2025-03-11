cmake_minimum_required(VERSION 3.19)

project(global-Week_6-String_Functions_4)

set(CMAKE_CXX_STANDARD 14)

# Files from `./src` directory
set(SRC
        src/main.cpp "../String Functions 4/src/password6.cpp" "../String Functions 4/src/password6.h")


# Running learner side code
# Use PROJECT_NAME dependent names of targets for the plugin support to work correctly.
add_executable(${PROJECT_NAME}-run ${SRC})