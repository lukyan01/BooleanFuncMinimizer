//
// Created by Lukyan on 4/1/2024.
//

#include "QuineMcCluskeyStrategy.h"


void QuineMcCluskeyStrategy::minimize(const std::vector<int>& minterms_on, const std::vector<int>& minterms_dc, int mintermLength) {

    auto Nbits = static_cast<size_t>(mintermLength);

    // Runtime dispatch mechanism
    switch (Nbits) {
        case 4:
        case 8:
            minimize_template<uint8_t>(minterms_on, minterms_dc);
            break;
        case 16:
            minimize_template<uint16_t>(minterms_on, minterms_dc);
            break;
        case 32:
            minimize_template<uint32_t>(minterms_on, minterms_dc);
            break;
        case 64:
            minimize_template<uint64_t>(minterms_on, minterms_dc);
            break;
        default:
            throw std::runtime_error("Unsupported minterm length");
    }
}

template <typename IntTypeN>
void QuineMcCluskeyStrategy::minimize_template(const std::vector<int>& minterms_on, const std::vector<int>& minterms_dc) {

    using namespace minbool;

    // Convert vectors of int to vectors of IntTypeN
    std::vector<IntTypeN> minterms_on_uint(minterms_on.begin(), minterms_on.end());
    std::vector<IntTypeN> minterms_dc_uint(minterms_dc.begin(), minterms_dc.end());

    // Convert vectors of IntTypeN to vectors of MinTerm<Nbits>
    std::vector<MinTerm<sizeof(IntTypeN) * 8>> minterms;
    minterms.reserve(minterms_on_uint.size() + minterms_dc_uint.size());
    for (IntTypeN minterm : minterms_on_uint) {
        minterms.emplace_back(minterm);
    }
    for (IntTypeN minterm : minterms_dc_uint) {
        minterms.emplace_back(minterm);
    }

    // Get the solution
    auto solution = get_minimized_func_terms<sizeof(IntTypeN) * 8>(minterms_on_uint, minterms_dc_uint);


    // Print the solution
    for (const auto& term : solution) {
        std::cout << term << std::endl;
    }
}
