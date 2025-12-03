# tests/CMakeLists.txt

# El comando de prueba es el script de shell
add_test(
    NAME test_bfs_system
    COMMAND ${CMAKE_SOURCE_DIR}/tests/test_bfs.sh
)
