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

std::vector<std::string> BooleanMinimizer::minimizeFunction(const std::vector<int>& on, const std::vector<int>& dc, int minLength) {
    if (strategy) {
        return strategy->minimize(on, dc, minLength);
    } else {
        throw std::logic_error("Minimization strategy not set.");
    }
}