// genetic_algorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Individual.h"
#include "GeneticAlgorithm.h"
#include "Result.h"

using namespace std;

const string GENES = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890, .-;:_!\"#%&/()=?@${[]}";
//const string GENES = "lvjhalkdsufiowhfoewiahfnchzfiodafjiodfjiodsfiosjfsonvh ifhdjklahfisd aihfsdjhsdkljhf dhfuheihcdjs";

int main() {
    std::vector<char> s(GENES.begin(),GENES.end());
    std::vector<char> targ={'M','A','Z','I','T','E','K'};
    std::vector<int> hello = {1, 2, 4, 5, 6, 7, 8, 9, 0};
    std::vector<int> t = {9, 8, 7};
    GeneticAlgorithm<char> ga(targ, s, 100);
    ga.set_iterations(200);
    auto res = ga.optimize();
    auto idv = res.getSolution();

    cout << "Iteration: " << res.getGeneration() << "\t";
    //cout<< "String: "<< idv.getChromosome()<<"\t";
    cout << "Fitness: " << idv.getFitness() << "\t";
    cout << "Time: " << res.getDuration() << "s" << "\n";
}
