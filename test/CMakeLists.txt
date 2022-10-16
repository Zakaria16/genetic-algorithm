add_executable(test test.cpp
        IndividualTest.cpp
        GeneticAlgorithmTest.cpp
        )

target_link_libraries(test ${GTEST_LIBRARIES} gcov)
target_include_directories(test PRIVATE ${GTEST_INCLUDE_DIR})
target_compile_options(test PRIVATE --coverage)