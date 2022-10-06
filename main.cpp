#include <iostream>
#include <vector>

#include "Individual.h"
#include "GeneticAlgorithm.h"
#include "Result.h"

const std::string GENES = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890, .-;:_!\"#%&/()=?@${[]}";
//const string GENES = "lvjhalkdsufiowhfoewiahfnchzfiodafjiodfjiodsfiosjfsonvh ifhdjklahfisd aihfsdjhsdkljhf dhfuheihcdjs";

int main() {
    std::vector<char> s(GENES.begin(),GENES.end());
    std::vector<char> targ={'M','A','Z','I','T','E','K'};
    //std::vector<int> hello = {1, 2, 4, 5, 6, 7, 8, 9, 0};
    //std::vector<int> t = {9, 8, 7};
    genetic_algorithm::GeneticAlgorithm<char> ga(targ, s, 100);
    ga.setIterations(200);
  //  ga.enableDebug(true);
    auto res = ga.optimize();
    auto idv = res.getSolution();
    std::cout<<"chromosome: [";
    for (const auto &i:idv.getChromosome()) {
         std::cout<<i<<",";
    }
    std::cout<<"]\t";

    std::cout << "Iteration: " << res.getGeneration() << "\t";
    std::cout << "Fitness: " << idv.getFitness() << "\t";
    std::cout << "Time: " << res.getDuration() << "s" << "\n";
}
