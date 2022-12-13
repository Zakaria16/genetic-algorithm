#include <gtest/gtest.h>
#include "Individual.h"

namespace genetic_algorithm::test {
    class IndividualTest : public ::testing::Test {

    protected:
        void SetUp() override {
        }
    };


    TEST_F(IndividualTest, ZeroFitnessTest) {
        std::vector<std::string> target = {"why", "me"};
        Individual<std::string> individual{{"Hello", "world"}, target};
        auto x = individual.getFitness();
        ASSERT_EQ(x, target.size());
    }

    TEST_F(IndividualTest, FullFitnessTest) {
        Individual<int> individual{{4, 5, 6, 7},
                                   {4, 5, 6, 7}};

        auto x = individual.getFitness();
        ASSERT_EQ(x, 0);
    }

    TEST_F(IndividualTest, PartFitnessTest) {
        Individual<int> individual{{1, 5, 0, 7},
                                   {4, 5, 6, 7}};

        auto x = individual.getFitness();
        ASSERT_EQ(x, 2);
    }
}
