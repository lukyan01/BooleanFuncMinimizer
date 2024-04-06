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
    std::vector<std::string> minimizeFunction(const std::vector<int>& on, const std::vector<int>& dc, int minLength);

private:
    std::unique_ptr<MinimizationStrategy> strategy;
};


#endif //BOOLEANFUNCMINIMIZER_BOOLEANMINIMIZER_H
