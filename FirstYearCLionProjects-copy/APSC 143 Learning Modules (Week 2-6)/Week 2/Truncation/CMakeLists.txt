cmake_minimum_required(VERSION 3.19)

project(global-Week_2-Truncation)

set(CMAKE_CXX_STANDARD 14)

# Files from `./src` directory
set(SRC
        src/main.cpp src/password2.h src/password2.cpp)


# Running learner side code
# Use PROJECT_NAME dependent names of targets for the plugin support to work correctly.
add_executable(${PROJECT_NAME}-run ${SRC})