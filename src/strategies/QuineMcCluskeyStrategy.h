//
// Created by Lukyan on 4/1/2024.
//

#ifndef BOOLEANFUNCMINIMIZER_QUINEMCCLUSKEYSTRATEGY_H
#define BOOLEANFUNCMINIMIZER_QUINEMCCLUSKEYSTRATEGY_H

#include "MinimizationStrategy.h"
#include <vector>

// Concrete class implementing MinimizationStrategy for the Quine-McCluskey algorithm
class QuineMcCluskeyStrategy : public MinimizationStrategy {
public:
    // Overrides the minimize function in the MinimizationStrategy interface
    void minimize(const std::vector<int>& minterms) override;
};


#endif //BOOLEANFUNCMINIMIZER_QUINEMCCLUSKEYSTRATEGY_H
