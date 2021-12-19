#pragma once
#include "Individual.h"
template<class T = Individual>
class Result
{
public:
	Result(int generation, T solution, double duration);
	
	T getSolution();
	int getGeneration();
	int getDuration();
	
private:
	T solution;
	int generation;
	double duration;
};

template<class T>
T Result<T>::getSolution() {
	return this->solution;
}


template<class T>
Result<T>::Result(int generation, T solution, double duration)
{
	this->solution = solution;
	this->generation = generation;
	this->duration = duration;

}




template<class T>
inline int Result<T>::getGeneration()
{
	return this->generation;
}

template<class T>
inline int Result<T>::getDuration()
{
	return this->duration;
}

