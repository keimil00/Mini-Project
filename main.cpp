#include <iostream>
#include "CMax3SatProblem.h"

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
    std::cout<< "Hello";
    return 0;
}
