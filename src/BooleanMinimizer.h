//
// Created by Lukyan on 4/1/2024.
//

#ifndef BOOLEANFUNCMINIMIZER_BOOLEANMINIMIZER_H
#define BOOLEANFUNCMINIMIZER_BOOLEANMINIMIZER_H

#include <vector>
#include <memory>
#include "strategies/MinimizationStrategy.h"

// Context class for minimizing boolean functions using different strategies
class BooleanMinimizer {
public:
    explicit BooleanMinimizer(std::unique_ptr<MinimizationStrategy> strategy = nullptr);
    void setStrategy(std::unique_ptr<MinimizationStrategy> strategy);
    void minimizeFunction(const std::vector<int>& minterms);

private:
    std::unique_ptr<MinimizationStrategy> strategy;
};


#endif //BOOLEANFUNCMINIMIZER_BOOLEANMINIMIZER_H
