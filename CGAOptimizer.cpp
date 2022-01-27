//
// Created by keimi on 27.01.2022.
//

#include "CGAOptimizer.h"


CGAOptimizer::CGAOptimizer(int newSize_of_population, double newProbability_of_crossing, double newProbability_of_mutation, int newTournamentSize, Problem *newProblem) {
    size_of_population = newSize_of_population;
    probability_of_crossing = newProbability_of_crossing;
    probability_of_mutation = newProbability_of_mutation;
    tournament_size = newTournamentSize;
    problem = newProblem;
}

CGAOptimizer::~CGAOptimizer() {
    for (int i = 0; i < individuals.size(); ++i) {
        delete individuals[i];
    }
}

void CGAOptimizer::Initialize() {
    if(individuals.empty()){
        for (int i = 0; i < size_of_population; ++i) {
            individuals.push_back(new CGAIndividual(problem->size(), problem)); //creates random solutions
        }
    }
}

void CGAOptimizer::RunIteration() {
    std::vector<CGAIndividual*> new_population;
    CGAIndividual *parent1, *parent2, *child1, *child2;
    std::chrono::duration<double> elapsed[4];
    elapsed[0] = std::chrono::duration<double>::zero();
    elapsed[1] = std::chrono::duration<double>::zero();
    elapsed[2] = std::chrono::duration<double>::zero();
    elapsed[3] = std::chrono::duration<double>::zero();


    auto start = std::chrono::high_resolution_clock::now();
    while(new_population.size() < individuals.size()){

        auto startInside = std::chrono::high_resolution_clock::now();
        parent1 = pickParent(individuals, tournament_size);
        parent2 = pickParent(individuals, tournament_size);
        auto finishInside = std::chrono::high_resolution_clock::now();
        elapsed[0] += finishInside - startInside;

        startInside = std::chrono::high_resolution_clock::now();
        child1 = parent1->Crossover(parent2, probability_of_crossing);
        child2 = parent2->Crossover(parent1, probability_of_crossing);
        finishInside = std::chrono::high_resolution_clock::now();
        elapsed[1] += finishInside - startInside;

        startInside = std::chrono::high_resolution_clock::now();
        child1->Mutation(probability_of_mutation);
        child2->Mutation(probability_of_mutation);
        finishInside = std::chrono::high_resolution_clock::now();
        elapsed[2] = finishInside - startInside;

        startInside = std::chrono::high_resolution_clock::now();
        new_population.push_back(child1);
        new_population.push_back(child2);
        finishInside = std::chrono::high_resolution_clock::now();
        elapsed[3] += finishInside - startInside;
    }
    std::cout <<"\n(pick parent 2x) Elapsed time: " << elapsed[0].count() << " s\n";
    std::cout <<"\n(Crossover 2x) Elapsed time: " << elapsed[1].count() << " s\n";
    std::cout <<"\n(Mutation 2x) Elapsed time: " << elapsed[2].count() << " s\n";
    std::cout <<"\n(pushback 2x) Elapsed time: " << elapsed[3].count() << " s\n";

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedWhile = finish - start;
    std::cout <<"\n(while) Elapsed time: " << elapsedWhile.count() << " s\n";


    std::cout<<"\n\n";
    for (int i = 0; i < individuals.size(); ++i) {
        delete individuals[i];
    }
    individuals = new_population;
    std::cout<<"Average: "<<averageFitness()<<" Max: "<<maxFitness();
    std::cout<<"\n\n";

}

double CGAOptimizer::averageFitness() {
    double average = 0;
    for (int i = 0; i < individuals.size(); ++i) {
        average += individuals[i]->getFitnessValue();
    }
    average /= size_of_population;
    return average;
}

double CGAOptimizer::maxFitness() {
    double max = 0;
    for (int i = 0; i < individuals.size(); ++i) {
        if(max < individuals[i]->getFitnessValue())
            max = individuals[i]->getFitnessValue();
    }
    return max;
}


