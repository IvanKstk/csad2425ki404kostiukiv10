cmake_minimum_required(VERSION 3.10)

# Назва проекту
project(ClientTests)

# Використовуємо стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Вказуємо директорії для заголовних файлів
include_directories(D:/csad/client/include)

# Виконуваний файл для клієнта
add_executable(client_main
    D:/csad/client/src/main.cpp
    D:/csad/client/src/game.cpp
    D:/csad/client/src/game_logic.cpp
    D:/csad/client/src/menu.cpp
    D:/csad/client/src/serial.cpp
)

# Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Виконуваний файл для тестів, називається TestProject
add_executable(TestProject
    D:/csad/client/tests/test_game.cpp
    D:/csad/client/tests/test_game_logic.cpp
    D:/csad/client/tests/test_menu.cpp
    D:/csad/client/tests/test_serial.cpp
    D:/csad/client/src/game.cpp
    D:/csad/client/src/game_logic.cpp
    D:/csad/client/src/menu.cpp
    D:/csad/client/src/serial.cpp
)

# Лінкуємо Google Test до TestProject
target_link_libraries(TestProject PRIVATE ${GTEST_LIBRARIES} pthread)

# Додаємо підтримку CTest
enable_testing()
add_test(NAME ClientTests COMMAND TestProject)