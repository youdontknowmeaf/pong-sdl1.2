cmake_minimum_required(VERSION 3.13)
project(Pong_3DS_Edition C)

find_package(SDL REQUIRED)

add_executable(Pong_3DS_Edition main.c)

target_link_libraries(Pong_3DS_Edition PRIVATE ${SDL_LIBRARY} citro3d ctru)
target_include_directories(Pong_3DS_Edition PRIVATE ${SDL_INCLUDE_DIR})

include(ProcessorCount)
