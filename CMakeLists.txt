cmake_minimum_required(VERSION 3.16)
project(omp-example)
set(CMAKE_CXX_STANDARD 11)

find_package(OpenMP)
add_compile_options(-Wunknown-pragmas)

add_executable(hello src/hello.cpp)
target_link_libraries(hello OpenMP::OpenMP_CXX)

add_executable(hello_for src/hello_for.cpp)
target_link_libraries(hello_for OpenMP::OpenMP_CXX)

add_executable(data_clause src/data_clause.cpp)
target_link_libraries(data_clause OpenMP::OpenMP_CXX)

add_executable(matrix_vector src/matrix_vector.cpp)
target_link_libraries(matrix_vector OpenMP::OpenMP_CXX)

add_executable(vector_norm src/vector_norm.cpp)
target_link_libraries(vector_norm OpenMP::OpenMP_CXX)

add_executable(inner_product src/inner_product.cpp)
target_link_libraries(inner_product OpenMP::OpenMP_CXX)
