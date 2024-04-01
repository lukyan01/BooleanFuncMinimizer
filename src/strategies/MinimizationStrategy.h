//
// Created by Lukyan on 4/1/2024.
//

#ifndef BOOLEANFUNCMINIMIZER_MINIMIZATIONSTRATEGY_H
#define BOOLEANFUNCMINIMIZER_MINIMIZATIONSTRATEGY_H

#include <vector>

// Interface for minimization strategies
class MinimizationStrategy {
public:
    virtual ~MinimizationStrategy() = default;

    // Pure virtual function to be implemented by concrete strategies
    // Takes a list of minterms as input and performs minimization
    virtual void minimize(const std::vector<int>& minterms) = 0;
};


#endif //BOOLEANFUNCMINIMIZER_MINIMIZATIONSTRATEGY_H
