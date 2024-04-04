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

void BooleanMinimizer::minimizeFunction(const std::vector<int>& on, const std::vector<int>& dc, int minLength) {
    if (strategy) {
        strategy->minimize(on, dc, minLength);
    } else {
        throw std::logic_error("Minimization strategy not set.");
    }
}