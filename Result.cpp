#include "Result.h"

template<class T>
Result<T>::Result(int generation,T solution,int duration)
{
	this->solution = solution;
	this->generation = generation;
	this->duration = duration;
	
}

template<class T>
Result<T>::~Result()
{
	delete this->solution;


}

