cmake_minimum_required(VERSION 3.10) # Проверка версии CMake.
                                     # Если версия установленой программы
                                     # старее указаной, произайдёт аварийный выход.

project(include) # Название проекта

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

set(SOURCE_LIB cache_funcs.cpp LFU.cpp tester.cpp) # Установка переменной со списком исходников

add_library(include STATIC ${SOURCE_LIB}) # Создание статической библиотеки
