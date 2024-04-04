//
// Created by Lukyan on 4/1/2024.
//

#ifndef BOOLEANFUNCMINIMIZER_QUINEMCCLUSKEYSTRATEGY_H
#define BOOLEANFUNCMINIMIZER_QUINEMCCLUSKEYSTRATEGY_H

#include "MinimizationStrategy.h"
#include "third-party/minbool.h"
#include <vector>


class QuineMcCluskeyStrategy : public MinimizationStrategy {
public:
    // Overrides the minimize function in the MinimizationStrategy interface
    void minimize(const std::vector<int>& on, const std::vector<int>& dc, int minLength) override;
private:
    template <typename IntTypeN>
    void minimize_template(const std::vector<int>& minterms_on, const std::vector<int>& minterms_dc);
};


#endif //BOOLEANFUNCMINIMIZER_QUINEMCCLUSKEYSTRATEGY_H
