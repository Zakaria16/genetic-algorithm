#pragma once
#include <iostream>
using namespace std;
// Class representing individual in population
class Individual
{
public:
	Individual();
	Individual(string chromosome, string target);
	//Individual mate(Individual parent2,string genes);
	string getChromosome();
	void setChromosome(string chromosome);
	virtual int getFitness();
	virtual void setFitness(int fitness);
	virtual int calculateFitness();
	
	// Overloading < operator 
	friend bool operator< (const Individual& ind1, const Individual& ind2);
	friend bool operator> (const Individual& ind1, const Individual& ind2);
	friend bool operator== (const Individual& ind1, const Individual& ind2);


private:
	// int random_num(int start, int end);
	string chromosome;
	string target;
	int fitness;
	
};
