#include <iostream>
#include "CMax3SatProblem.h"
#include "CGAOptimizer.h"


int main() {
    CMax3SatProblem *testObject = new CMax3SatProblem();
    std::string file_address = "C://Users//keimi//CLionProjects//Mini_Project//m3s_350_45.txt";
    testObject->Load(file_address);
    testObject->print_clauses();
    testObject->print_variables();
    std::vector<bool> test_solution;
    for (int i = 0; i < 50; ++i) {
        if(i%2 == 0){
            test_solution.push_back(true);
        }else{
            test_solution.push_back(false);
        }
    }
    std::cout << testObject->Compute(test_solution);

    auto *test_optimizer = new CGAOptimizer<CMax3SatProblem>(1000, 0.75, 0.2, testObject);
    test_optimizer->Initialize();
    for (int i = 0; i < 100; ++i) {
        test_optimizer->RunIteration();
    }

    delete testObject;
    delete test_optimizer;

    return 0;
}
