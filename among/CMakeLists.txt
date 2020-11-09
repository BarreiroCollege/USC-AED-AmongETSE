cmake_minimum_required(VERSION 3.17)
project(among C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(among
        abb.c
        abb.h
        cola.c
        cola.h
        ConstantesAmongETSE.h
        FuncionesAmongETSE.c
        FuncionesAmongETSE.h
        main.c)
