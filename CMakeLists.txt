# Minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(ClientServerProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Specify directories with header files
include_directories(${CMAKE_SOURCE_DIR})

# Add an executable file for the client with all the necessary files
add_executable(client
    ${CMAKE_SOURCE_DIR}/client/main.cpp
    ${CMAKE_SOURCE_DIR}/client/game.cpp
    ${CMAKE_SOURCE_DIR}/client/game_logic.cpp
    ${CMAKE_SOURCE_DIR}/client/menu.cpp
    ${CMAKE_SOURCE_DIR}/client/serial.cpp
)

# Adding definitions for Unicode support
add_definitions(-DUNICODE -D_UNICODE)

# Specify that the Windows library should be used
if(WIN32)
    target_link_libraries(client PRIVATE ws2_32)
endif()
