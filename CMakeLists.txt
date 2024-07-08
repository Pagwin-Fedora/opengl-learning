# This is a template I intend to use to create C++ cmake projects going forwards
# the structure takes heavily after https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html
# This file takes heavily from https://gitlab.com/CLIUtils/modern-cmake/-/blob/master/examples/extended-project/CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

project(project_name_here
    VERSION 0.1
    LANGUAGES CXX)

# setting this so compile_commands.json is generated for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# for convenience if they're needed
#find_package(Boost REQUIRED)
#find_package(fmt REQUIRED)

# adding glfw from source
add_subdirectory(glfw)

# lib src code
add_subdirectory(src)

# app source code
add_subdirectory(apps)

