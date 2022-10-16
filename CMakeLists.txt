cmake_minimum_required(VERSION 3.1)

project(genetic_algorithm
        VERSION 1.0.0
        DESCRIPTION "A C++ Genetic Algorithm library"
        )

SET(CMAKE_CXX_STANDARD 20)

include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
)


add_library(genetic_algorithm src/GeneticAlgorithm.cpp)
target_include_directories(genetic_algorithm INTERFACE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE: ${CMAKE_INSTALL_INCLUDEDIR}>)


add_executable(main main.cpp)
target_link_libraries(main genetic_algorithm)

#INSTALLATION
include(GNUInstallDirs)

install(TARGETS genetic_algorithm
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/.." COMPONENT dev)

configure_file(libgenetic_algorithm.pc.in libgenetic_algorithm.pc @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libgenetic_algorithm.pc" DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")




