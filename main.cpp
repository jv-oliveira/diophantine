#include <iostream>
#include <chrono>
#include "linear_diophantine_eq.hpp"

using namespace diophantine;
using namespace std::chrono;

int main() {
    int a, b, c;
    std::cout << "Please input values a, b and c separated by spaces:\n";
    std::cin >> a >> b >> c;
    std::cout << "Do you want to solve for:\n"
                 "[0] Non Negative numbers\n"
                 "[1] Positive numbers\n"
                 "[2] Negative numbers\n"
                 "[3] Non Positive numbers\n";
    int solve_for;
    std::cin >> solve_for;
    auto start = steady_clock::now();
    linear_diophantine_eq equation(a, b, c, SOLVE_FOR(solve_for));
    auto solutions = equation.get_solutions();
    auto end = steady_clock::now();
    std::cout << "It took " << duration_cast<nanoseconds>(end - start).count() << " ns\n";
    if (solutions.empty()) {
        std::cout << "There are no solutions!\n";
    } else {
        std::cout << "The positive solutions are:\n";
        for (const auto& solution : solutions) {
            std::cout << solution << "\n";
        }
    }
    return EXIT_SUCCESS;
}