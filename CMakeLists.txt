cmake_minimum_required(VERSION 2.81)
project("genetic algorithm")


include_directories(
    ${CMAKE_SOURCE_DIR}
)

add_library(genetic_algorithm GeneticAlgorithm.cpp Individual.cpp)

add_executable(main main.cpp)
target_link_libraries(main genetic_algorithm)

