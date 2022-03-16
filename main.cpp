#include <iostream>
#include "CMax3SatProblem.h"
#include "CGAOptimizer.h"

#define ITERATIONS_NUMBER 200
#define POPULATION_SIZE 200
#define PROBABILITY_OF_CROSSING 0.5
#define PROBABILITY_OF_MUTATION 0.3
#define TOURNAMENT_SIZE 2


int main(int argc, char** argv) {
    if(argc < 1) {std:: cout<<"Provide file name.";}
    else {
        auto *testObject = new CMax3SatProblem();
        std::string file_address = argv[1];
        if (testObject->Load(file_address)) {
            auto *test_optimizer = new CGAOptimizer(POPULATION_SIZE,
                                                    PROBABILITY_OF_CROSSING,
                                                    PROBABILITY_OF_MUTATION,
                                                    TOURNAMENT_SIZE,
                                                    testObject);
            test_optimizer->Initialize();

            for (int i = 0; i < ITERATIONS_NUMBER; ++i) {
                test_optimizer->RunIteration();
            }

            delete testObject;
            delete test_optimizer;
        } else {
            std::cout << "Wrong name or file structure.";
        }
    }


    return 0;
}
