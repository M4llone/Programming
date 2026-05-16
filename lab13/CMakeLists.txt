# Я комментарий
# Задаем планку версии. Если у разработчика CMake старее — он увидит ошибку
cmake_minimum_required(VERSION 3.10)

# Инициализирует проект и создает полезные переменные типа ${CMAKE_CURRENT_SOURCE_DIR},
# что означает текущий каталог с исходниками
    project(lab13)

# Создание переменных APP_DIR и SOURCE_DIR
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/smarthome.c
)

# Аналог опции -I
include_directories(include)

# Главная цель: что собрать и из чего.
# Формат: add_executable(ИМЯ_ПРОГРАММЫ ИСХОДНИКИ)
add_executable(sorted src/main.c src/smarthome.c    )

add_library(shared SHARED src/smarthome.c)  

add_library(static STATIC src/smarthome.c)

option(BUILD_SHARED_LIBS OFF)


if(BUILD_SHARED_LIBS)
    add_executable(program_with_lib src/main.c)
    target_link_libraries(program_with_lib shared)
else()
    add_executable(program_with_lib src/main.c)
    target_link_libraries(program_with_lib static)
endif()
