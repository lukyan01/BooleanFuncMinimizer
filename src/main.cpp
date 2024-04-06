#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#include "BooleanMinimizer.h"
#include "strategies/QuineMcCluskeyStrategy.h"



std::vector<int> parseStringToVector(const std::string& str) {
    std::vector<int> vec;
    std::istringstream iss(str);
    int num;

    while (iss >> num) {
        vec.push_back(num);
    }

    return vec;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <minterms> <dontCares>\n";
        return 1;
    }
    std::cout << "Running Minimizer" << std::endl;

    std::vector<int> minterms = parseStringToVector(argv[1]);
    std::vector<int> dontCares = parseStringToVector(argv[2]);

    std::cout << "Parsed minterms: ";
    for (const auto& term : minterms) {
        std::cout << term << ' ';
    }
    std::cout << std::endl;

    std::cout << "Parsed don't cares: ";
    for (const auto& term : dontCares) {
        std::cout << term << ' ';
    }
    std::cout << std::endl;

    std::cout << "Outpt File: " << argv[3] << std::endl;

    std::unique_ptr<MinimizationStrategy> qmStrategy = std::make_unique<QuineMcCluskeyStrategy>();
    BooleanMinimizer minimizer(std::move(qmStrategy));

    std::vector<std::string> result = minimizer.minimizeFunction(minterms, dontCares, 4);

    std::ofstream outFile(argv[3]);
    if (!outFile) {
        std::cerr << "Failed to open output file.\n";
        return 1;
    }

    for (const auto& term : result) {
        outFile << term << '\n';
    }

    return 0;
}