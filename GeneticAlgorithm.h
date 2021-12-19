#pragma once

// #include <vector>
// #include <algorithm> 
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

#include "Individual.h"
#include "Result.h"

using namespace std;

class GeneticAlgorithm
{
private:
	int target_size=0;
	int genes_size = 0;
	int population_size;
	int iterations = 1000;
	string target;
	string genes;
	string create_gnome();
	static int random_num(int start, int end);
	//long _population_size=100;
public:
	GeneticAlgorithm(string target, string genes,int populationSize);
	//GeneticAlgorithm(string target, string genes);
	vector<Individual> create_population();
	Result<> optimize();
	Individual mate(Individual parent1, Individual parent2);
	void set_target(string target);
	void set_genes(string genes);
	void set_iterations(int iterations);

};
