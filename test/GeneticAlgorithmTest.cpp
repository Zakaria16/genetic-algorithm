#include <gtest/gtest.h>
#include "GeneticAlgorithm.h"

namespace genetic_algorithm::test {
    class GeneticAlgorithmTest : public testing::Test {

    protected:
        virtual void SetUp() {

        }
    };

    TEST(GeneticAlgorithmTest, GATest) {
        std::vector<int> genes = {1, 2, 4, 5, 6, 7, 8, 9, 0};
        std::vector<int> t{9, 8, 7};
        genetic_algorithm::GeneticAlgorithm<int> ga(t, genes, 100);
        ga.setIterations(200);
        ga.enableDebug(true);
        auto res = ga.optimize();
        auto idv = res.getSolution();
        ASSERT_EQ(t, idv.getChromosome());
    }
}