cmake_minimum_required(VERSION 3.10)
project(ServerTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_server
    TestServer/test_determineResult.cpp
    TestServer/test_generateServerChoice.cpp
    TestServer/test_generateStrategicChoice.cpp
    TestServer/test_resetServer.cpp
    new_server/Source Files/Server.cpp
)

include_directories(include)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_compile_definitions(TestServer PRIVATE TEST_ENVIRONMENT)

target_link_libraries(TestServer PRIVATE ${GTEST_LIBRARIES} pthread)

add_executable(server_main
    src/main.cpp
    src/Server.cpp
)

target_include_directories(server_main PRIVATE include)
