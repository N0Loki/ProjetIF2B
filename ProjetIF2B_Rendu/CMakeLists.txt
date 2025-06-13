cmake_minimum_required(VERSION 3.30)
project(ProjetIF2B_Rendu C)

set(CMAKE_C_STANDARD 99)

add_executable(ProjetIF2B_Rendu main.c
        main.c
        main.h
        Game.c
        Game.h
        saves.c
        saves.h
        setup.c
        setup.h
        pose.c
        pose.h
        capture.c
        capture.h
)