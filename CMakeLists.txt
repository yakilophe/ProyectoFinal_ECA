cmake_minimum_required(VERSION 3.10)
project(ProyectoFinal_ECA CXX) 

# Compila el ejecutable principal (BFS)
add_executable(grafo_ejecutable src/Algoritmo_BFS.cpp) 

# Agrega el subdirectorio 'tests' para que se ejecute su propio CMakeLists.txt
add_subdirectory(tests)
