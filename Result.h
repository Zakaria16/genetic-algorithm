#ifndef RESULT_HPP
#define RESULT_HPP

#include "Individual.h"

template<typename T>
class Result {
public:
    Result(int generation, const Individual<T> &solution, double duration);

    Individual<T> getSolution();

    int getGeneration();

    int getDuration();

private:
    Individual<T> solution;
    int generation;
    double duration;
};


template<typename T>
Individual<T> Result<T>::getSolution() {
    return this->solution;
}


template<typename T>
Result<T>::Result(int generation, const Individual<T> &solution, double duration):solution(solution), generation(generation),
duration(duration) {
}


template<typename T>
inline int Result<T>::getGeneration() {
    return this->generation;
}

template<typename T>
inline int Result<T>::getDuration() {
    return this->duration;
}

#endif