//
// Created by Lukyan on 4/1/2024.
//

#include "BooleanMinimizer.h"
#include <stdexcept>

BooleanMinimizer::BooleanMinimizer(std::unique_ptr<MinimizationStrategy> strategy)
        : strategy(std::move(strategy)) {}

void BooleanMinimizer::setStrategy(std::unique_ptr<MinimizationStrategy> newStrategy) {
    strategy = std::move(newStrategy);
}

void BooleanMinimizer::minimizeFunction(const std::vector<int> &minterms) {
    if (strategy) {
        strategy->minimize(minterms);
    } else {
        throw std::logic_error("Minimization strategy not set.");
    }
}