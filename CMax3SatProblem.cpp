//
// Created by keimi on 14.01.2022.
//

#include "CMax3SatProblem.h"

double CMax3SatProblem::Compute(std::vector<bool> solution) {
    std::map<int, bool> var_to_solution;
    for (int i = 0; i < solution.size(); ++i) {
        var_to_solution.insert({variables[i], solution[i]});
    }
    int fulfilled = 0;
    bool first, second, third;
    for (auto & clause : clauses) {
        first = var_to_solution.at(abs(std::get<0>(clause)));
        second = var_to_solution.at(abs(std::get<1>(clause)));
        third = var_to_solution.at(abs(std::get<2>(clause)));

        if(std::get<0>(clause) < 0){first = !first;}
        if(std::get<1>(clause) < 0){second = !second;}
        if(std::get<2>(clause) < 0){third = !third;}

        if(first || second || third){fulfilled++;}
    }


    return (double)solution.size() / (double)fulfilled;
}


void CMax3SatProblem::retrieve_variables() {
    std::vector<std::tuple<int, int, int>> copy = clauses;
    std::set<int> vars;
    int a,b,c;
    for (auto & i : copy) {
        std::tie(a,b,c) = i;
        vars.insert(abs(a));
        vars.insert(abs(b));
        vars.insert(abs(c));
    }
    variables.assign(vars.begin(), vars.end());
}

void CMax3SatProblem::Load(const std::string& address) {
    std::ifstream source_file;
    source_file.open(address);

    int first, second, third;
    char bracket;

    while(source_file){
        source_file >> bracket >> first >> second >> third >> bracket;
        clauses.emplace_back(first, second, third);
    }

    source_file.close();
    retrieve_variables();
}

void CMax3SatProblem::print_clauses() {
    for (auto & clause : clauses) {
        std::cout<<std::get<0>(clause)<<
                "\t"<<std::get<1>(clause)<<
                        "\t"<<std::get<2>(clause)<<"\n";
    }
}

void CMax3SatProblem::print_variables() {
    for (auto & var : variables) {
        std::cout<<var<<"\n";
    }
}

int CMax3SatProblem::size() {
    return variables.size();
}

