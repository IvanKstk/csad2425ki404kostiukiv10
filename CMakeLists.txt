# Мінімальна версія CMake
cmake_minimum_required(VERSION 3.10)

# Назва проекту
project(ClientServerProject)

# Встановлюємо стандарт C++
set(CMAKE_CXX_STANDARD 17)



# Вказуємо директорії з заголовочними файлами
include_directories(${CMAKE_SOURCE_DIR}/client/include)

# Додаємо виконуваний файл для клієнта
add_executable(client
    ${CMAKE_SOURCE_DIR}/client/src/main.cpp
    ${CMAKE_SOURCE_DIR}/client/src/serial.cpp
)

add_definitions(-DUNICODE -D_UNICODE)

# Вказуємо, що потрібно використовувати бібліотеку Windows
if(WIN32)
    target_link_libraries(client PRIVATE ws2_32)
endif()


