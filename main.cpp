// genetic_algorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Individual.h"
#include "GeneticAlgorithm.h"
#include "Result.h"

using namespace std;

const string GENES = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890, .-;:_!\"#%&/()=?@${[]}";
//const string GENES = "lvjhalkdsufiowhfoewiahfnchzfiodafjiodfjiodsfiosjfsonvh ifhdjklahfisd aihfsdjhsdkljhf dhfuheihcdjs";

int main()
{
	GeneticAlgorithm ga("i love MaziTek GH", GENES,100);
	ga.set_iterations(200);
	Result<> res = ga.optimize();
	Individual idv = res.getSolution();
	
	cout << "Iteration: " << res.getGeneration() << "\t";
 	cout<< "String: "<< idv.getChromosome()<<"\t"; 
    cout<< "Fitness: "<< idv.getFitness() << "\t";
	cout << "Time: " << res.getDuration() << "s" << "\n";
}
