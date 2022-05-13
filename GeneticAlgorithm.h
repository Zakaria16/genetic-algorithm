#pragma once

// #include <vector>
// #include <algorithm> 
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>

#include "Individual.h"
#include "Result.h"

template<typename T>
class GeneticAlgorithm
{
private:
	int target_size=0;
	int genes_size = 0;
	int population_size;
	int iterations_ = 1000;
	T target_;
	T genes_;
	T create_gnome();
	static int random_num(int start, int end);
	//long _population_size=100;
public:
	GeneticAlgorithm(const T& target, const T& genes,int populationSize);
	//GeneticAlgorithm(string target, string genes);
	std::vector<Individual<T>> create_population();
	Result<T> optimize();
	Individual<T> mate(Individual<T> parent1, Individual<T> parent2);
	void set_target(const T& target) {
       this->target_ =target;
    }

    void set_genes(const T& genes) {
        this->genes_ = genes;
    }

    void set_iterations(int iterations){
        this->iterations_ = iterations;
    }

};



template<typename T>
GeneticAlgorithm<T>::GeneticAlgorithm(const T &target, const T &genes, int population_size):population_size(population_size) {
    this->target_ = target;
    this->genes_ = genes;

    this->genes_size = genes.size();
    this->target_size = target.size();
    //todo replace
    std::srand((unsigned) (time(0)));
}

template<typename T>
std::vector<Individual<T>> GeneticAlgorithm<T>::create_population() {
    // create initial population
    static std::vector<Individual<T>> population;
    for (int i = 0; i < population_size; i++) {
        T gnome = create_gnome();
        population.emplace_back(gnome, target_);
    }
    return population;
}

template<typename T>
Result<T> GeneticAlgorithm<T>::optimize() {
    std::vector<Individual<T>> population = create_population();
    int generation = 0;
    clock_t begin_time = clock();
    Individual<T> bestIndividual = population[0];
    while (generation < iterations_) {
        // sort the population in increasing order of fitness score
        sort(population.begin(), population.end());

        //debug
        std::cout << "Generation: " << generation << "\t";
        std::stringstream ss;
        ss<<"data: {";
        for(const auto &d:bestIndividual.getChromosome() ) {
            ss <<d<<",";
        }
        ss<<"}\n";
        std::cout<<ss.str();
        std::cout << "Fitness: " << bestIndividual.getFitness() << "\n";

        // if the individual having lowest fitness score ie.
        // 0 then we know that we have reached to the target
        // and break the loop
        if (bestIndividual.getFitness() <= 0) {
            break;
        }

        // Otherwise generate new offsprings for new generation
        std::vector<Individual<T>> new_generation;

        // Perform Elitism, that mean 10% of fittest population
        // goes to the next generation
        int s = (int) (0.1 * population_size);
        new_generation.reserve(s);
        for (int i = 0; i < s; i++)
            new_generation.push_back(population[i]);

        // From 90% of fittest population, Individuals
        // will mate to produce offspring
        s = (int) (0.9 * population_size);
        for (int i = 0; i < s; i++) {
            int len = population.size();
            int r = random_num(0, (int) len / 2);
            Individual<T> parent1 = population[r];
            r = random_num(0, (int) len / 2);
            Individual<T> parent2 = population[r];
            Individual<T> offspring = mate(parent1, parent2);
            new_generation.push_back(offspring);
        }
        population = std::move(new_generation);
        bestIndividual  = population[0];
        generation++;
    }

    auto time_spent =  (double )((clock() - begin_time) / CLOCKS_PER_SEC);

    auto ind = population[0];
    Result<T>  res(generation,ind, time_spent);
    return res;
}

template<typename T>
Individual<T> GeneticAlgorithm<T>::mate(Individual<T> parent1, Individual<T> parent2) {
    // chromosome for offspring
    T child_chromosome;

    int len = parent1.getChromosome().size();
    child_chromosome.reserve(len);
    for (int i = 0; i < len; i++) {
        // random probability
        double prob = random_num(0, 100) / 100.0;std::string hj;

        // if prob is less than 0.45, insert gene
        // from parent 1
        if (prob < 0.45) {
            const auto res = (parent1.getChromosome())[i];
            child_chromosome.push_back(res); //todo
        }

            // if prob is between 0.45 and 0.90, insert
            // gene from parent 2
        else if (prob < 0.90) {
            const auto res = (parent2.getChromosome())[i];
            child_chromosome.push_back(res); //todo
        }

            // otherwise insert random gene(mutate),
            // for maintaining diversity
        else {
            child_chromosome.push_back(genes_[random_num(0, genes_size - 1)]);
        }
    }
    // create new Individual<T>(offspring) using
    // generated chromosome for offspring
    return Individual<T>(child_chromosome, target_);
}


template<typename T>
T GeneticAlgorithm<T>::create_gnome() {
    // create chromosome or string of genes
    T gnome;
    for (int i = 0; i < target_size; i++) {
        //mutated gene
        gnome.push_back(genes_[random_num(0, genes_size - 1)]);
    }
    return gnome;
}


/// Function to generate random numbers in given range
/// \tparam T
/// \param start range begin
/// \param end range end
/// \return int
template<typename T>
int GeneticAlgorithm<T>::random_num(int start, int end) {
    int range = (end - start) + 1;
    int random_int = start + (std::rand() % range);
    return random_int;
}
