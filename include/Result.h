#ifndef GA_RESULT_HPP
#define GA_RESULT_HPP

#include "Individual.h"
namespace genetic_algorithm {
    template<typename T>
    class Result {
    public:
        Result(int generation, const Individual<T> &solution, double duration);

        auto getSolution();

        auto getGeneration();

        auto getDuration();

    private:
        Individual<T> solution;
        int generation;
        double duration;
    };


    template<typename T>
    auto Result<T>::getSolution() {
        return this->solution;
    }


    template<typename T>
    Result<T>::Result(int generation, const Individual<T> &solution, double duration):solution(solution),
                                                                                      generation(generation),
                                                                                      duration(duration) {
    }


    template<typename T>
    inline auto Result<T>::getGeneration() {
        return this->generation;
    }

    template<typename T>
    inline auto Result<T>::getDuration() {
        return this->duration;
    }
}
#endif