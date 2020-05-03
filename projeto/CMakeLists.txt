cmake_minimum_required(VERSION 3.15)
project(projeto C)

set(CMAKE_C_STANDARD 99)

add_executable(projeto main.c dados.c dados.h interface.c interface.h logica.c logica.h listas.c listas.h)

target_link_libraries(projeto m)