#include <iostream>

#include "BooleanMinimizer.h"
#include "strategies/QuineMcCluskeyStrategy.h"



int main() {
    // Create an instance of the strategy wrapped in a unique_ptr
    std::unique_ptr<MinimizationStrategy> qmStrategy = std::make_unique<QuineMcCluskeyStrategy>();

    // Create the minimizer and set the strategy
    BooleanMinimizer minimizer(std::move(qmStrategy));

    // Alternatively, if you want to set the strategy after construction
    // BooleanMinimizer minimizer;
    // minimizer.setStrategy(std::make_unique<QuineMcCluskeyStrategy>());

    std::vector<int> minterms = {1, 2, 5, 7, 8, 11, 14, 15};
    std::vector<int> dontCares = {0, 3, 4, 9, 10};

    // Minimize the Boolean function represented by the given minterms
    minimizer.minimizeFunction(minterms);

    return 0;
}
