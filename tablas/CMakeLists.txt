cmake_minimum_required(VERSION 3.17)
project(tablas C)

set(CMAKE_C_STANDARD 11)

add_executable(tabla_encadenamiento main_encadenamiento.c
        vars.h
        utils.c utils.h
        lista.h lista.c
        tabla_hash_encadenamiento.h tabla_hash_encadenamiento.c)

add_executable(tablas_recolocacion main_recolocacion.c
        vars.h
        utils.c utils.h
        tablas_hash_recolocacion.h tablas_hash_recolocacion.c)