cmake_minimum_required(VERSION 3.10) # Проверка версии CMake.
                                     # Если версия установленой программы
                                     # старее указаной, произайдёт аварийный выход.

project(Hash) # Название проекта

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

set(SOURCE_EXE ./src/main.cpp) # Установка переменной со списком исходников

include_directories(include) # Расположение заголовочных файлов

add_executable(main ${SOURCE_EXE}) # Создает исполняемый файл с именем main

add_subdirectory(include) # Добавление подпроекта, указывается имя дирректории

target_link_libraries(main include) # Линковка программы с библиотекой
