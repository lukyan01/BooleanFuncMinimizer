//
// Created by Lukyan on 4/1/2024.
//

#ifndef BOOLEANFUNCMINIMIZER_MINIMIZATIONSTRATEGY_H
#define BOOLEANFUNCMINIMIZER_MINIMIZATIONSTRATEGY_H

#include <vector>
#include <string>

// Interface for minimization strategies
class MinimizationStrategy {
public:
    virtual ~MinimizationStrategy() = default;

    // Pure virtual function to be implemented by concrete strategies
    // Takes a list of minterms as input and performs minimization
    virtual std::vector<std::string> minimize(const std::vector<int>& on, const std::vector<int>& dc, int minLength) = 0;
};


#endif //BOOLEANFUNCMINIMIZER_MINIMIZATIONSTRATEGY_H
