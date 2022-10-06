#ifndef GA_GENETIC_ALGORITHM_H
#define GA_GENETIC_ALGORITHM_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <random>
#include <thread>

#include "Individual.h"
#include "Result.h"

namespace genetic_algorithm {
    template<typename T>
    class GeneticAlgorithm {

    public:
        /// create a genetic algorithm object
        /// \param target vector of type T the target
        /// \param genes
        /// \param populationSize
        GeneticAlgorithm(const std::vector<T> &target, const std::vector<T> &genes, int populationSize);

        ///
        /// \param target
        /// \param genes
        /// \param populationSize
        GeneticAlgorithm(const std::string &target, const std::string &genes, int populationSize);

        std::vector<Individual<T>> createPopulation();

        ///
        /// \return optime the genetic algorithm
        Result<T> optimize();

        /// Mate two offspring
        /// \param parent1 parents 1
        /// \param parent2 parent 2
        /// \return Individual new offspring
        Individual<T> mate(Individual<T> parent1, Individual<T> parent2);

        void set_target(const std::vector<T> &target) {
            this->mTarget = target;
        }

        void set_genes(const std::vector<T> &genes) {
            this->mGenes = genes;
        }

        void setIterations(int iterations) {
            this->mIterations = iterations;
        }

        /// show print of each step of the optimizations
        /// \param value bool true to enable, false otherwise
        [[maybe_unused]] auto enableDebug(bool value);

    private:
        int mPopulationSize;
        int mIterations = 1000;
        std::vector<T> mTarget;
        std::vector<T> mGenes;

        std::vector<T> createGnome();

        static int randomNumber(int start, int end);

        bool isDebug{false};
    };


    template<typename T>
    GeneticAlgorithm<T>::GeneticAlgorithm(const std::vector<T> &target, const std::vector<T> &genes, int populationSize)
            :mTarget(target), mGenes(genes), mPopulationSize(populationSize) {}

    template<typename T>
    std::vector<Individual<T>> GeneticAlgorithm<T>::createPopulation() {
        // create initial population
        static std::vector<Individual<T>> population;
        for (int i = 0; i < mPopulationSize; i++) {
            std::vector<T> gnome = createGnome();
            population.emplace_back(gnome, mTarget);
        }
        return population;
    }

    template<typename T>
    Result<T> GeneticAlgorithm<T>::optimize() {
        std::vector<Individual<T>> population = createPopulation();
        int generation = 0;
        /// 14/08/2022 use chrono duration
        //clock_t begin_time = clock();
        auto start = std::chrono::steady_clock::now();
        Individual<T> bestIndividual = population[0];
        while (generation < mIterations) {
            // sort the population in increasing order of fitness score
            sort(population.begin(), population.end());

            //debug
            if (isDebug) {
                std::cout << "Generation: " << generation << "\t";
                std::stringstream ss;
                ss << "data: {";
                for (const auto &d: bestIndividual.getChromosome()) {
                    ss << d << ",";
                }
                ss << "}\t";
                std::cout << ss.str();
                std::cout << "Fitness: " << bestIndividual.getFitness() << "\n";
            }

            // if the individual having the lowest fitness score i.e
            // 0 then we know that we have reached to the target
            // and break the loop
            if (bestIndividual.getFitness() <= 0) {
                break;
            }

            // Otherwise generate new offsprings for new generation
            std::vector<Individual<T>> new_generation;

            // Perform Elitism, that mean 10% of the fittest population
            // goes to the next generation
            auto sampleSize = static_cast<int> (0.1 * mPopulationSize);
            new_generation.reserve(sampleSize);
            for (int i = 0; i < sampleSize; ++i)
                new_generation.push_back(population[i]);

            // From 90% of the fittest population, Individuals
            // will mate to produce offspring
            sampleSize = static_cast<int>(0.9 * mPopulationSize);
            for (int i = 0; i < sampleSize; ++i) {
                const auto len = population.size() / 2;
                auto r = randomNumber(0, len);
                Individual<T> parent1 = population[r];
                r = randomNumber(0, len);
                Individual<T> parent2 = population[r];
                Individual<T> offspring = mate(parent1, parent2);
                new_generation.push_back(offspring);
            }
            population = std::move(new_generation);
            bestIndividual = population[0];
            generation++;
        }
        /// 13/05/2022 use duration
        //const auto timeSpent = (clock() - begin_time) / (double )CLOCKS_PER_SEC;
        std::chrono::duration<double> elapsed{std::chrono::steady_clock::now() -
                                              start};
        const Result<T> res(generation, population[0], elapsed.count());
        return res;
    }

    template<typename T>
    Individual<T> GeneticAlgorithm<T>::mate(Individual<T> parent1, Individual<T> parent2) {
        // chromosome for offspring
        std::vector<T> child_chromosome;

        int len = parent1.getChromosome().size();
        child_chromosome.reserve(len);
        for (int i = 0; i < len; i++) {
            // random probability
            double prob = randomNumber(0, 100) / 100.0;
            std::string hj;

            // if prob is less than 0.45, insert gene
            // from parent 1
            if (prob < 0.45) {
                const auto res = (parent1.getChromosome())[i];
                child_chromosome.push_back(res);
            }

                // if prob is between 0.45 and 0.90, insert
                // gene from parent 2
            else if (prob < 0.90) {
                const auto res = (parent2.getChromosome())[i];
                child_chromosome.push_back(res);
            }

                // otherwise insert random gene(mutate),
                // for maintaining diversity
            else {
                child_chromosome.push_back(mGenes[randomNumber(0, mGenes.size() - 1)]);
            }
        }
        // create new Individual<T>(offspring) using
        // generated chromosome for offspring
        return Individual<T>(child_chromosome, mTarget);
    }

    template<typename T>
    std::vector<T> GeneticAlgorithm<T>::createGnome() {
        // create chromosome or string of genes
        std::vector<T> gnome;
        for (int i = 0; i < mTarget.size(); i++) {
            //mutated gene
            gnome.push_back(mGenes[randomNumber(0, mGenes.size() - 1)]);
        }
        return gnome;
    }

/// Function to generate random numbers in given range
/// \tparam T
/// \param start range begin
/// \param end range end
/// \return int
    template<typename T>
    int GeneticAlgorithm<T>::randomNumber(int start, int end) {
        static std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(start, end);
        return static_cast<int>(dist(mt));
    }

    template<>
    GeneticAlgorithm<char>::GeneticAlgorithm(const std::string &target, const std::string &genes, int populationSize)
            :mPopulationSize(populationSize) {
        mTarget = std::vector<char>(target.begin(), target.end());
        mGenes = std::vector<char>(genes.begin(), genes.end());
    }

    template<typename T>
    [[maybe_unused]] auto GeneticAlgorithm<T>::enableDebug(bool value) {
        isDebug = value;
    }
}
#endif