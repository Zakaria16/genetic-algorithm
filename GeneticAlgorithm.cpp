#include "GeneticAlgorithm.h"

//#include "individual.h"

using namespace std;


GeneticAlgorithm::GeneticAlgorithm(string target, string genes,int population_size) {
	this->target = target;
	this->genes = genes;
	this->population_size = population_size;
	this->genes_size = genes.size();
	this->target_size = target.size();
	srand((unsigned)(time(0)));
}



vector<Individual> GeneticAlgorithm::create_population()
{
	// create initial population
	static vector<Individual> population;
	for (int i = 0; i < population_size; i++)
	{
		string gnome = create_gnome();
		population.push_back(Individual(gnome, target));
	}
	return population;
}


Result<> GeneticAlgorithm::optimize()
{
	vector<Individual> population = create_population();
	bool found = false;
	int generation = 0;
	clock_t begin_time = clock();
	
	while (!found && generation<iterations)
	{
		// sort the population in increasing order of fitness score
		sort(population.begin(), population.end());

		//debug
		cout << "Generation: " << generation << "\t";
		cout << "String: " << population[0].getChromosome() << "\t";
		cout << "Fitness: " << population[0].getFitness() << "\n";

		// if the individual having lowest fitness score ie.
		// 0 then we know that we have reached to the target
		// and break the loop
		if (population[0].getFitness() <= 0)
		{
			found = true;
			break;
		}

		// Otherwise generate new offsprings for new generation
		vector<Individual> new_generation;

		// Perform Elitism, that mean 10% of fittest population
		// goes to the next generation
		int s = (int)(0.1 * population_size);
		for (int i = 0; i < s; i++)
			new_generation.push_back(population[i]);

		// From 90% of fittest population, Individuals
		// will mate to produce offspring
		s = (int)(0.9 * population_size);
		for (int i = 0; i < s; i++)
		{
			int len = population.size();
			int r = random_num(0, (int)len/2);
			Individual parent1 = population[r];
			r = random_num(0, (int)len/2);
			Individual parent2 = population[r];
			Individual offspring = mate(parent1, parent2);
			new_generation.push_back(offspring);
		}
		population = new_generation;


		generation++;
	}
	double time_spent = (double)((clock()- begin_time) / CLOCKS_PER_SEC);
	Result<> res(generation, population[0], time_spent);
	return res;
}


Individual GeneticAlgorithm::mate(Individual p1, Individual p2)
{
	// chromosome for offspring
	string child_chromosome = "";

	int len = p1.getChromosome().size();
	for (int i = 0; i < len; i++)
	{
		// random probability
		double prob = random_num(0, 100)/100.0;

		// if prob is less than 0.45, insert gene
		// from parent 1
		if (prob < 0.45)
			child_chromosome += (p1.getChromosome())[i];

		// if prob is between 0.45 and 0.90, insert
		// gene from parent 2
		else if (prob < 0.90)
			child_chromosome += (p2.getChromosome())[i];

		// otherwise insert random gene(mutate),
		// for maintaining diversity
		else
		{
			child_chromosome += genes[random_num(0, genes_size - 1)];
		}
	}
	// create new Individual(offspring) using 
	// generated chromosome for offspring 
	return Individual(child_chromosome, target);
}

void GeneticAlgorithm::set_iterations(int iterations)
{
	this->iterations = iterations;
}



string GeneticAlgorithm::create_gnome()
{
	// create chromosome or string of genes
	string gnome = "";
	for (int i = 0; i < target_size; i++)
	{
		//mutated gene
		gnome += genes[random_num(0, genes_size - 1)];
	}
	return gnome;
}


// Function to generate random numbers in given range

int GeneticAlgorithm::random_num(int start, int end)
{
	int range = (end - start) + 1;
	int random_int = start + (rand() % range);
	return random_int;
}
