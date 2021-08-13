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
	GeneticAlgorithm ga("MaziTek GH", GENES,100);
	// Get starting timepoint 
	clock_t begin = clock();
	Individual idv = ga.optimize();
	// Get ending timepoint 
	clock_t end = clock();


	// Get duration. Substart timepoints to  

	double time_spent = (end - begin) / CLOCKS_PER_SEC;
	//cout << "Iteration: " << idv.getGeneration() << "\t";
 	cout<< "String: "<< idv.getChromosome()<<"\t"; 
    cout<< "Fitness: "<< idv.getFitness() << "\t";
	cout << "Time: " << time_spent <<"s" << "\n";

	Result<> result(1, idv, time_spent);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
