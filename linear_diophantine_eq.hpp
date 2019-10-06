//
// Created by joao on 8/24/19.
//

#ifndef DIOPHANTINE_LINEAR_DIOPHANTINE_EQ_HPP
#define DIOPHANTINE_LINEAR_DIOPHANTINE_EQ_HPP

#include <vector>
#include <numeric>
#include <ostream>

#include <algorithm>

namespace diophantine {

namespace {
/**
 * xgcd auxiliary functions
 */
constexpr void calculate_x(int& x0, int& x1, int q) {
    auto tmp = x1;
    x1 = x0 - q * x1;
    x0 = tmp;
}

constexpr void calculate_y(int& y0, int& y1, int q) {
    int tmp = y1;
    y1 = y0 - q * y1;
    y0 = tmp;
}

constexpr void update_params(int& a, int& b) {
    int tmp = a;
    a = b % a;
    b = tmp;
}
}

/**
 * Extended Euclidean Algorithm
 * \see https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
 * \param a first input
 * \param b second input
 * \param x0 first bezout coefficient
 * \param y0 second bezout coefficient
 * \return gcd of a and b
 */
constexpr int xgcd(int a, int b, int& x0, int& y0) {
    int x1 = 1, y1 = 0;
    x0 = y1 = 0;
    x1 = y0 = 1;
    while (a != 0) {
        int q = b / a;
        update_params(a, b);
        calculate_y(y0, y1, q);
        calculate_x(x0, x1, q);
    }
    return b;
}

/**
 * Data structure for one simple solution for the simplest linear diophantine equation
 */
struct solution {
    int x;
    int y;
    
    constexpr bool is_negative() const {
        return x < 0 && y < 0;
    }
    
    constexpr bool is_non_negative() const {
        return x >= 0 && y >= 0;
    }
    
    constexpr bool is_positive() const {
        return x > 0 && y > 0;
    }
    
    constexpr bool is_non_positive() const {
        return x <= 0 && y <= 0;
    }
    
    constexpr bool is_null() const {
        return x == 0 && y == 0;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const solution& solution) {
        os << "x: " << solution.x << " y: " << solution.y;
        return os;
    }
};

enum SOLVE_FOR : uint8_t {
    NON_NEGATIVE,
    POSITIVE,
    NEGATIVE,
    NON_POSITIVE,
};

/**
 * simplest linear diophantine equation solver
 * ax + by = c
 */
class linear_diophantine_eq {
    int _a, _b, _c;
    int _x0, _y0;
    int _gcd;
    SOLVE_FOR _sf;
    
    using result_flags_t = union { struct{bool bits[4];}; uint8_t value;};
public:
    constexpr linear_diophantine_eq(int a, int b, int c, SOLVE_FOR sf = NON_NEGATIVE)
    :   _a(a), _b(b), _c(c),
        _x0(0), _y0(1),
        _gcd(xgcd(_a, _b, _x0, _y0)),
        _sf(sf)
    {}
    
    std::vector<solution> get_solutions() const {
        if (_c % _gcd)
            return {};
        std::vector<solution> solutions;
        const solution& first = bezout_identity_solution();
        if (is_a_valid_solution(first))
            solutions.emplace_back(first);
        find_solutions(first.x, first.y, -1, [](int& r) { --r; }, solutions);
        find_solutions(first.x, first.y, 1, [](int& r) { ++r; }, solutions);
        return solutions;
    }
    
private:
    
    constexpr solution bezout_identity_solution() const {
        auto x = _x0;
        auto y = _y0;
        auto z = _c / _gcd;
        x *= z;
        y *= z;
        return get_solution_r(0, x, y);
    }
    
    constexpr solution get_solution_r(int r, int x, int y) const {
        return solution {x - (r * _b) / _gcd, y + (r * _a) / _gcd};
    }
    
    constexpr bool is_a_valid_solution(const solution& sol) const {
        switch (_sf) {
            case NON_NEGATIVE:
                return sol.is_non_negative();
            case POSITIVE:
                return sol.is_positive();
            case NEGATIVE:
                return sol.is_negative();
            case NON_POSITIVE:
                return sol.is_non_positive();
        }
        return false;
    }
    
    constexpr bool gotta_stop_to_find_solutions(int r, const solution& sol) const {
        bool check_ascending = _sf == NEGATIVE || _sf == NON_POSITIVE;
        std::pair<int, int> cmp = {sol.x, sol.y};
        if (r < 0)
            std::swap(cmp.first, cmp.second);
        
        if (check_ascending) {
            std::swap(cmp.first, cmp.second);
            return cmp.first > 0;
        } else {
            return cmp.first < 0;
        }
    }
    
    template <typename Unary>
    constexpr void find_solutions(int x, int y,
                                  int r0,
                                  Unary r_step,
                                  std::vector<solution>& solutions) const {
        auto r = r0;
        do {
            auto sol = get_solution_r(r, x, y);
            if (gotta_stop_to_find_solutions(r, sol))
                break;
            if (is_a_valid_solution(sol))
                solutions.emplace_back(sol);
            r_step(r);
        } while (true);
    }
};

}

#endif //DIOPHANTINE_LINEAR_DIOPHANTINE_EQ_HPP
