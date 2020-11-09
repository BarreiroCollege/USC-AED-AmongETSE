cmake_minimum_required(VERSION 3.17)
project(mapa C)

set(CMAKE_C_STANDARD 11)

add_executable(mapa ConstantesAEMapa.h grafo.h grafo.c funciones.h funciones.c main.c)