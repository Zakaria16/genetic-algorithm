#include "Individual.h"



Individual::Individual()
{
	this->chromosome = "";
	this->target = "";
	this->fitness = calculateFitness();
}

Individual::Individual(string chromosome, string target)
{
	this->chromosome = chromosome;
	this->target = target;
	this->fitness = calculateFitness();
};



// Calculate fittness score, it is the number of 
// characters in string which differ from target 
// string. 
int Individual::calculateFitness()
{
	int len = target.size();
	int fitness = 0;
	for (int i = 0; i < len; i++)
	{
		if (chromosome[i] != target[i])
			fitness++;
	}
	return fitness;
};

// // Function to generate random numbers in given range 
// int Individual::random_num(int start, int end) 
// { 
// 	int range = (end-start)+1; 
// 	int random_int = start+(rand()%range); 
// 	return random_int; 
// } 

string Individual::getChromosome() {
	return chromosome;
}

void Individual::setChromosome(string chromosome) {
	this->chromosome = chromosome;
}

int Individual::getFitness() {
	return fitness;
}

void Individual::setFitness(int fitness) {
	this->fitness = fitness;
}

bool operator<(const Individual& ind1, const Individual& ind2)
{
	return ind1.fitness < ind2.fitness;
}

bool operator>(const Individual& ind1, const Individual& ind2)
{

	return ind1.fitness>ind2.fitness;
}

bool operator==(const Individual& ind1, const Individual& ind2)
{
	return ind1.fitness==ind2.fitness;
}

