//
// Created by keimi on 14.01.2022.
//

#ifndef UNTITLED8_CMAX3SATPROBLEM_H
#define UNTITLED8_CMAX3SATPROBLEM_H


#include <string>
#include <vector>
#include <iostream>
#include <tuple>
#include <set>
#include <map>
#include <cstdlib>
#include <fstream>
#include "Problem.h"

class CMax3SatProblem: public virtual Problem {
public:
    void Load(const std::string& address) override;
    double Compute(std::vector<bool> solution) override;
    void print_clauses();
    void print_variables();
    int size() override;
private:
    std::vector<std::tuple<int, int, int>> clauses;
    std::vector<int> variables;
    void retrieve_variables();
};


#endif //UNTITLED8_CMAX3SATPROBLEM_H
