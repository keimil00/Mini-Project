//
// Created by keimi on 14.01.2022.
//

#ifndef UNTITLED8_CGAOPTIMIZER_H
#define UNTITLED8_CGAOPTIMIZER_H


#include <vector>
#include "CGAIndividual.h"

template <typename T>
class CGAOptimizer {
public:
    CGAOptimizer(int size_of_population, double probability_of_crossing, double probability_of_mutation);
    void Initialize();
    void RunIteration();

private:
    int size_of_population;
    double probability_of_crossing;
    double probability_of_mutation;
    T problem;
    std::vector<CGAIndividual<T>*> individuals;
};

template <typename T>
CGAOptimizer<T>::CGAOptimizer(int size_of_population, double probability_of_crossing, double probability_of_mutation) {
    this->size_of_population = size_of_population;
    this->probability_of_crossing = probability_of_crossing;
    this->probability_of_mutation = probability_of_mutation;
    static_assert(problem.size(), "Class of the problem need to implement method size() in order to pass number of variables");
}

template<typename T>
void CGAOptimizer<T>::Initialize() {
    if(individuals.empty()){
        for (int i = 0; i < size_of_population; ++i) {
            individuals.push_back(new CGAIndividual<T>(problem.size(), problem)); //creates random solutions
        }
    }
}

template<typename T>
void CGAOptimizer<T>::RunIteration() {
    std::vector<CGAIndividual<T>*> new_population;
    CGAIndividual<T> *parent1, *parent2, *child1, *child2;

    while(new_population.size() < individuals.size()){
        parent1 = pickParent(individuals);
        parent2 = pickParent(individuals);
        child1 = parent1->Crossover(parent2);
        child2 = parent2->Crossover(parent1);
        child1 = child1->Mutation();
        child2 = child2->Mutation();
        addIndividual(new_population, child1, child2);
    }

}




#endif //UNTITLED8_CGAOPTIMIZER_H
