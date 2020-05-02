cmake_minimum_required(VERSION 3.15)
project(bot C)

set(CMAKE_C_STANDARD 99)

add_executable(bot main.c bot.c bot.h)