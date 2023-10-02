cmake_minimum_required(VERSION 3.10) # Проверка версии CMake.
                                     # Если версия установленой программы
                                     # старее указаной, произайдёт аварийный выход.

project(Hash) # Название проекта

set(SOURCE_EXE ./src/main.cpp) # Установка переменной со списком исходников

include_directories(include) # Расположение заголовочных файлов

add_executable(main ${SOURCE_EXE}) # Создает исполняемый файл с именем main

add_subdirectory(include) # Добавление подпроекта, указывается имя дирректории

target_link_libraries(main include) # Линковка программы с библиотекой
