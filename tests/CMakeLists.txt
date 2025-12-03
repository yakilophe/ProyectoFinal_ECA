# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
# Nombre del proyecto basado en tu repositorio
project(ProyectoFinal_ECA CXX) 

# Compila el ejecutable principal (BFS)
# La ruta del archivo fuente: src/Algoritmo_BFS.cpp
add_executable(grafo_ejecutable src/Algoritmo_BFS.cpp) 

# Agrega el subdirectorio 'tests' para que se ejecute su propio CMakeLists.txt
add_subdirectory(tests)
