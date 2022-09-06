cmake_minimum_required(VERSION 3.1)
project(genetic_algorithm)
SET(CMAKE_CXX_STANDARD 20)

include_directories(
    ${CMAKE_SOURCE_DIR}
)

add_library(genetic_algorithm GeneticAlgorithm.cpp Individual.cpp)

add_executable(main main.cpp)
target_link_libraries(main genetic_algorithm)



