cmake_minimum_required(VERSION 3.10) # Проверка версии CMake.
                                     # Если версия установленой программы
                                     # старее указаной, произайдёт аварийный выход.

project(include) # Название проекта

set(SOURCE_LIB cache_funcs.cpp LRU.cpp) # Установка переменной со списком исходников

add_library(include STATIC ${SOURCE_LIB}) # Создание статической библиотеки
