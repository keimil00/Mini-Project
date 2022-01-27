//
// Created by keimi on 14.01.2022.
//

#ifndef UNTITLED8_CGAOPTIMIZER_H
#define UNTITLED8_CGAOPTIMIZER_H


#include <vector>
#include "CGAIndividual.h"
#include <chrono>
#include "Problem.h"

class CGAIndividual;

class CGAOptimizer {
public:
    CGAOptimizer(int newSize_of_population, double newProbability_of_crossing, double newProbability_of_mutation, Problem *newProblem);
    ~CGAOptimizer();
    void Initialize();
    void RunIteration();
    double averageFitness();
    double maxFitness();
private:
    int size_of_population;
    double probability_of_crossing;
    double probability_of_mutation;
    Problem *problem;
    std::vector<CGAIndividual*> individuals;
};





#endif //UNTITLED8_CGAOPTIMIZER_H
