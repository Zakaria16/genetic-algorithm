#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H
#include <iostream>
#include <vector>

/// Class representing individual in population
template <typename T=int>
class Individual {
public:
    Individual();

    Individual(std::vector<T> chromosome, std::vector<T> target);

    std::vector<T> getChromosome();

    void setChromosome(const std::vector<T> &chromosome);

    int getFitness() const;

    virtual int calculateFitness();
    
    virtual ~Individual()=default;

    /// Overloading < operator

    bool operator<(const Individual &rhs) const;

    bool operator>(const Individual &rhs) const;

    bool operator<=(const Individual &rhs) const;

    bool operator>=(const Individual &rhs) const;

    bool operator==(const Individual &rhs) const;

    bool operator!=(const Individual &rhs) const;

    //friend std::ostream &operator<<(std::ostream &os, const Individual &individual);

private:
    // int random_num(int start, int end);
    std::vector<T> mChromosome{};
    std::vector<T> target{};
    int fitness{};

};

template<typename T>
Individual<T>::Individual()
= default;

template<typename T>
Individual<T>::Individual(std::vector<T> chromosome, std::vector<T> target): mChromosome(chromosome), target(target), fitness(this->calculateFitness())
{}

/// Calculate fittness score, it is the number of
/// characters in std::string which differ from target
/// std::string.
template<typename T>
int Individual<T>::calculateFitness()
{
    int len = target.size();
    int fitness_ = 0;
    for (int i = 0; i < len; i++)
    {
        if (mChromosome[i] != target[i])
            fitness_++;
    }
    return fitness_;
};

// // Function to generate random numbers in given range
// int Individual::random_num(int start, int end)
// {
// 	int range = (end-start)+1;
// 	int random_int = start+(rand()%range);
// 	return random_int;
// }
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
    return !(rhs < *this);
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

//template<typename T>
//std::ostream &operator<<(std::ostream &os, const Individual<T> &individual) {
//    os << "mChromosome: " << individual.mChromosome << " target: " << individual.target << " fitness: "
//       << individual.fitness;
//    return os;
//}


#endif