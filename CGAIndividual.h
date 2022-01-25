//
// Created by keimi on 14.01.2022.
//

#ifndef UNTITLED8_CGAINDIVIDUAL_H
#define UNTITLED8_CGAINDIVIDUAL_H

#include <utility>
#include <ctime>
#include <vector>
#include "CGAOptimizer.h"

#define     TOURNAMENT_SIZE 2

template <typename T> class CGAIndividual;
template <typename T> class CGAOptimizer;
template <typename T> CGAIndividual<T>* pickParent(std::vector<CGAIndividual<T>*> const &population);

template <typename T>
class CGAIndividual {
public:
    CGAIndividual(int size, T *problem);
    CGAIndividual(std::vector<bool> genes, T *problem);
    static int random(int min, int max);
    CGAIndividual* Crossover(CGAIndividual const *mate, double probability_of_crossing);
    void Mutation(double probability_of_mutation);
    double Fitness();
    friend CGAIndividual* pickParent<T>(std::vector<CGAIndividual<T>*> const &population);
private:
    T *problem;
    int genotype_length;
    std::vector<bool> genotype;
    double fitness;
};


template<typename T>
CGAIndividual<T>::CGAIndividual(int size, T *new_problem) {
    genotype_length = size;
    genotype = std::vector<bool>(genotype_length);
    for (int i = 0; i < genotype_length; ++i) {
        genotype[i] = random(0,1);
    }
    problem = new_problem;
}

template<typename T>
CGAIndividual<T>::CGAIndividual(std::vector<bool> genes, T *new_problem) {
    genotype = std::move(genes);
    problem = new_problem;
    Fitness();
}

template<typename T>
int CGAIndividual<T>::random(int min, int max) {
    static bool first = true;
    if (first)
    {
        srand( time(nullptr) ); //seeding for the first time only!
        first = false;
    }
    return min + rand() % (( max + 1 ) - min);
} //TODO correct random selection;

template<typename T>
CGAIndividual<T>* CGAIndividual<T>::Crossover(CGAIndividual<T> const *mate, double probability_of_crossing) {
    if(random(0,1) > probability_of_crossing){
        return this;
    }

    int len = genotype.size();
    std::vector<bool> child_genotype(len);
    for (int i = 0; i < len; ++i) {
        float chances = ((float)random(0, 100))/100.0;

        if(chances < 0.5)
            child_genotype[i] = genotype[i];
        else if(chances >= 0.5)
            child_genotype[i] = mate->genotype[i];
    }
    return (new CGAIndividual<T>(child_genotype, problem));
}

template<typename T>
void CGAIndividual<T>::Mutation(double probability_of_mutation) {
    for (int i = 0; i < genotype_length; ++i) {
        if(random(0, 1) < probability_of_mutation){
            genotype[i] = !genotype[i];
        }
    }
}

template<typename T>
double CGAIndividual<T>::Fitness() {
    fitness = problem->Compute(genotype);
    return fitness;
}

template<typename T>
CGAIndividual<T> *pickParent(std::vector<CGAIndividual<T> *> const &population) {
    double best_result = 0;
    int best_candidate_index;
    for (int i = 0; i < TOURNAMENT_SIZE; ++i) {
        int r = CGAIndividual<T>::random(0, population.size() - 1);
        if(population[r]->Fitness() > best_result){
            best_result = population[r]->fitness;
            best_candidate_index = r;
        }
    }
    return population[best_candidate_index];
}




#endif //UNTITLED8_CGAINDIVIDUAL_H
