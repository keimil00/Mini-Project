//
// Created by keimi on 14.01.2022.
//

#ifndef UNTITLED8_CGAINDIVIDUAL_H
#define UNTITLED8_CGAINDIVIDUAL_H

#include <utility>
#include <ctime>
#include <vector>
#include "CGAOptimizer.h"
#include "Problem.h"



class CGAIndividual;
class CGAOptimizer;
CGAIndividual* pickParent(std::vector<CGAIndividual*> const &population);


class CGAIndividual {
public:
    CGAIndividual(int size, Problem *problem);
    CGAIndividual(std::vector<bool> genes, Problem *problem);
    static int random(int min, int max);
    CGAIndividual* Crossover(CGAIndividual const *mate, double probability_of_crossing);
    void Mutation(double probability_of_mutation);
    double Fitness();
    double getFitnessValue() const;
    friend CGAIndividual* pickParent(std::vector<CGAIndividual*> const &population, int tournamentSize);
private:
    Problem *problem;
    int genotype_length;
    std::vector<bool> genotype;
    double fitness;
};



#endif //UNTITLED8_CGAINDIVIDUAL_H
