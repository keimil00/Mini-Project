//
// Created by keimi on 14.01.2022.
//

#ifndef UNTITLED8_CGAINDIVIDUAL_H
#define UNTITLED8_CGAINDIVIDUAL_H

#include <utility>
#include <ctime>
#include <vector>



template <typename T>
class CGAIndividual {
public:
    CGAIndividual(int size, T problem);
    CGAIndividual(std::vector<bool> genes, T problem);
    CGAIndividual* Crossover(CGAIndividual *mate, double probability_of_crossing);
    void Mutation(double probability_of_mutation);
    double Fitness();
    friend CGAIndividual* pickParent(std::vector<CGAIndividual*> population);
private:
    T problem;
    int genotype_length;
    std::vector<bool> genotype;
    double fitness;
    int tournament_size = 2;
    int random(int min, int max);
};


template<typename T>
CGAIndividual<T>::CGAIndividual(int size, T problem) {
    static_assert(problem.Compute(), "Class of the problem need to implement method Compute() in order to pass number of variables");
    genotype_length = size;
    for (int i = 0; i < genotype_length; ++i) {
        i = random(0,1);
    }
    this->problem = problem;
}

template<typename T>
CGAIndividual<T>::CGAIndividual(std::vector<bool> genes, T problem) {
    static_assert(problem.Compute(), "Class of the problem need to implement method Compute() in order to pass number of variables");
    genotype = std::move(genes);
    this->problem = problem;
    Fitness();
}
template<typename T>
CGAIndividual<T>* CGAIndividual<T>::Crossover(CGAIndividual *mate, double probability_of_crossing) {
    if(random(0,1) > probability_of_crossing){
        return *this;
    }

    int len = genotype.size();
    std::vector<bool> child_genotype(len);
    for (int i = 0; i < len; ++i) {
        float chances = random(0, 100)/100;

        if(chances < 0.5)
            child_genotype[i] = genotype[i];
        else if(chances >= 0.5)
            child_genotype[i] = mate->genotype[i];
    }
    return new CGAIndividual(child_genotype);
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
int CGAIndividual<T>::random(int min, int max) {
    static bool first = true;
    if (first)
    {
        srand( time(NULL) ); //seeding for the first time only!
        first = false;
    }
    return min + rand() % (( max + 1 ) - min);
}

template<typename T>
CGAIndividual<T> *pickParent(std::vector<CGAIndividual<T> *> population) {
    std::vector<CGAIndividual<T> *> candidates;
    double best_result = 0;
    int best_candidate_index;
    for (int i = 0; i < CGAIndividual<T>::tournament_size; ++i) {
        candidates.push_back(population[random(0, population.size())]);
        if(candidates[i]->Fitness() > best_result){
            best_result = candidates[i].fitness;
            best_candidate_index = i;
        }
    }
    return candidates[best_candidate_index];
}

template<typename T>
double CGAIndividual<T>::Fitness() {
    fitness = problem.Compute(genotype);
    return fitness;
}



#endif //UNTITLED8_CGAINDIVIDUAL_H
