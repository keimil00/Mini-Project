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
    CGAOptimizer(int newSize_of_population, double newProbability_of_crossing, double newProbability_of_mutation, T *newProblem);

    virtual ~CGAOptimizer();

    void Initialize();
    void RunIteration();
    double averageFitness();
private:
    int size_of_population;
    double probability_of_crossing;
    double probability_of_mutation;
    T *problem;
    std::vector<CGAIndividual<T>*> individuals;
};

template <typename T>
CGAOptimizer<T>::CGAOptimizer(int newSize_of_population, double newProbability_of_crossing, double newProbability_of_mutation, T *newProblem) {
    size_of_population = newSize_of_population;
    probability_of_crossing = newProbability_of_crossing;
    probability_of_mutation = newProbability_of_mutation;
    problem = newProblem;
}

template<typename T>
CGAOptimizer<T>::~CGAOptimizer() {
}

template<typename T>
void CGAOptimizer<T>::Initialize() {
    if(individuals.empty()){
        for (int i = 0; i < size_of_population; ++i) {
            individuals.push_back(new CGAIndividual<T>(problem->size(), problem)); //creates random solutions
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
        child1 = parent1->Crossover(parent2, probability_of_crossing);
        child2 = parent2->Crossover(parent1, probability_of_crossing);
        child1->Mutation(probability_of_mutation);
        child2->Mutation(probability_of_mutation);
        new_population.push_back(child1);
        new_population.push_back(child2);
    }
    std::cout<<"\n\n";

    std::cout<<averageFitness();
    std::cout<<"\n\n";

    individuals = new_population;

    std::cout<<averageFitness();

}

template<typename T>
double CGAOptimizer<T>::averageFitness() {
    double average = 0;
    for (int i = 0; i < individuals.size(); ++i) {
        average += individuals[i]->Fitness();
    }
    average /= size_of_population;
    return average;
}






#endif //UNTITLED8_CGAOPTIMIZER_H
