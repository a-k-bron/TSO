cmake_minimum_required(VERSION 3.6)
project(Administracion_de_memoria)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Clases/Nodo.cpp Clases/Nodo.h Clases/Lista.cpp Clases/Lista.h)
add_executable(Administracion_de_memoria ${SOURCE_FILES})