#include <iostream>
#include "CMax3SatProblem.h"
#include "CGAOptimizer.h"


int main() {
    CMax3SatProblem testObject;
    std::string file_address = "C://Users//keimi//CLionProjects//Mini_Project//m3s_50_0.txt";
    testObject.Load(file_address);
    testObject.print_clauses();
    testObject.print_variables();
    std::vector<bool> test_solution;
    for (int i = 0; i < 50; ++i) {
        if(i%2 == 0){
            test_solution.push_back(true);
        }else{
            test_solution.push_back(false);
        }
    }
    std::cout << testObject.Compute(test_solution);

    CGAOptimizer<CMax3SatProblem*> *test_optimizer = new CGAOptimizer<CMax3SatProblem*>(100, 0.3, 0.1);
    test_optimizer->Initialize();
    test_optimizer->RunIteration();

    return 0;
}
