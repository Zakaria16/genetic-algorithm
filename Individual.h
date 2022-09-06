#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <iostream>
#include <vector>

/// Class representing individual in population
template<typename T=int>
class Individual {
public:
    Individual();

    ///
    /// \param chromosome
    /// \param target
    Individual(std::vector<T> chromosome, std::vector<T> target);

    std::vector<T> getChromosome();

    void setChromosome(const std::vector<T> &chromosome);

    /// retrieve the fitness
    /// \return the fitness
    [[nodiscard]] int getFitness() const;

    /// Calculate fitness score of the chromosome
    /// \return int the number of characters in chromosome which differ from target
    virtual int calculateFitness();

    virtual ~Individual() = default;

    bool operator<(const Individual &rhs) const;

    bool operator>(const Individual &rhs) const;

    bool operator<=(const Individual &rhs) const;

    bool operator>=(const Individual &rhs) const;

    bool operator==(const Individual &rhs) const;

    bool operator!=(const Individual &rhs) const;

private:
    // int random_num(int start, int end);
    std::vector<T> mChromosome{};
    std::vector<T> target{};
    int fitness{};

};

template<typename T>
Individual<T>::Individual() = default;

template<typename T>
Individual<T>::Individual(std::vector<T> chromosome, std::vector<T> target): mChromosome(chromosome), target(target),
                                                                             fitness(this->calculateFitness()) {}

template<typename T>
int Individual<T>::calculateFitness() {
    int len = target.size();
    int fitness_ = 0;
    for (int i = 0; i < len; i++) {
        if (mChromosome[i] != target[i])
            fitness_++;
    }
    return fitness_;
};

template<typename T>
std::vector<T> Individual<T>::getChromosome() {
    return mChromosome;
}

template<typename T>
void Individual<T>::setChromosome(const std::vector<T> &chromosome) {
    this->mChromosome = chromosome;
}

template<typename T>
int Individual<T>::getFitness() const {
    return fitness;
}

template<typename T>
bool Individual<T>::operator<(const Individual &rhs) const {
    return fitness < rhs.fitness;
}

template<typename T>
bool Individual<T>::operator>(const Individual &rhs) const {
    return rhs < *this;
}

template<typename T>
bool Individual<T>::operator<=(const Individual &rhs) const {
    return rhs >= *this;
}

template<typename T>
bool Individual<T>::operator>=(const Individual &rhs) const {
    return !(*this < rhs);
}

template<typename T>
bool Individual<T>::operator==(const Individual &rhs) const {
    return mChromosome == rhs.mChromosome &&
           target == rhs.target &&
           fitness == rhs.fitness;
}

template<typename T>
bool Individual<T>::operator!=(const Individual &rhs) const {
    return !(rhs == *this);
}
#endif