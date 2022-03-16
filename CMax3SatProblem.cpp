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

bool CMax3SatProblem::Load(const std::string& address) {
    std::ifstream source_file;
    source_file.open(address);
    if(!source_file.is_open()){ return false; }

    int first, second, third;

    std::string line;
    std::stringstream ss;
    std::string temp;

    while(!source_file.eof()){
        getline(source_file, line);
        if(line.empty()) {
            source_file.close();
            retrieve_variables();
            return true;
        }
        line.erase(std::remove(line.begin(), line.end(), '('), line.end());
        line.erase(std::remove(line.begin(), line.end(), ')'), line.end());

        ss << line;

        if(!ss.eof()){ ss >> temp; }
        else { return false; }

        if(!(std::istringstream(temp) >> first)){ return false; }

        if(!ss.eof()){ ss >> temp; }
        else { return false; }

        if(!(std::istringstream(temp) >> second)){ return false; }
        if(!ss.eof()){ ss >> temp; }

        else { return false; }
        if(!(std::istringstream(temp) >> third)){ return false; }

        ss.str(std::string());
        clauses.emplace_back(first, second, third);
    }

    source_file.close();
    retrieve_variables();
    return true;
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

