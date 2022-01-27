//
// Created by keimi on 24.01.2022.
//

#ifndef MINI_PROJECT_PROBLEM_H
#define MINI_PROJECT_PROBLEM_H

#include <iostream>
#include <vector>

class Problem {
public:
    virtual bool Load(const std::string& address) = 0;
    virtual double Compute(std::vector<bool> solution) = 0;
    virtual int size() = 0;
};


#endif //MINI_PROJECT_PROBLEM_H
