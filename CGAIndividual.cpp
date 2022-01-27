//
// Created by keimi on 27.01.2022.
//

#include "CGAIndividual.h"



CGAIndividual::CGAIndividual(int size, Problem *new_problem) {
    genotype_length = size;
    genotype = std::vector<bool>(genotype_length);
    for (int i = 0; i < genotype_length; ++i) {
        genotype[i] = random(0,1);
    }
    problem = new_problem;
    Fitness();
}

CGAIndividual::CGAIndividual(std::vector<bool> genes, Problem *new_problem) {
    genotype = genes;
    problem = new_problem;
    Fitness();
}

int CGAIndividual::random(int min, int max) {
    static bool first = true;
    if (first)
    {
        srand( time(nullptr) ); //seeding for the first time only!
        first = false;
    }
    return min + rand() % (( max + 1 ) - min);
}

CGAIndividual* CGAIndividual::Crossover(CGAIndividual const *mate, double probability_of_crossing) {
    if(random(0,1) > probability_of_crossing){
        return new CGAIndividual(genotype, problem);
    }

    int len = (int) genotype.size();
    std::vector<bool> child_genotype(len);
    for (int i = 0; i < len; ++i) {
        bool chances = (bool) random(0, 1);

        if (chances) { child_genotype[i] = genotype[i]; }
        else { child_genotype[i] = mate->genotype[i]; }
    }
    return (new CGAIndividual(child_genotype, problem));
}

void CGAIndividual::Mutation(double probability_of_mutation) {
    for (int i = 0; i < genotype_length; ++i) {
        if(random(0, 1) < probability_of_mutation){
            genotype[i] = !genotype[i];
        }
    }
}

double CGAIndividual::Fitness() {
    fitness = problem->Compute(genotype);
    return fitness;
}

CGAIndividual *pickParent(std::vector<CGAIndividual *> const &population, int tournamentSize) {
double best_result = 0;
int best_candidate_index;
for (int i = 0; i < tournamentSize; ++i) {
int r = CGAIndividual::random(0, population.size() - 1);
if(population[r]->fitness > best_result){
best_result = population[r]->fitness;
best_candidate_index = r;
}
}
return population[best_candidate_index];
}

double CGAIndividual::getFitnessValue() {
    return fitness;
}


