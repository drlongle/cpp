/*
 * Write a class that checks whether a number is prime at compile time
 * Write a class that checks whether all numbers in a sequence are prime
 */

#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

template <int A> struct is_prime {
    static consteval bool func() noexcept {
        if (A <= 1)
            return false;
        for (int i = 2; i <= A / 2; i++) {
            if (A % i == 0)
                return false;
        }
        return true;
    }
    static constexpr bool value = func();
};

template <typename T, T... I>
consteval auto sum(std::integer_sequence<T, I...>) {
    return (I + ... + 0);
}

template <typename T, T... I>
consteval auto is_prime_sequence(std::integer_sequence<T, I...>) {
    return (is_prime<I>::value && ...);
}

template <typename T> struct find {
    static constexpr int value = is_prime_sequence(T{});
};

int main() {
    std::cout << is_prime<0>::value << std::endl;
    std::cout << is_prime<1>::value << std::endl;
    std::cout << is_prime<2>::value << std::endl;
    std::cout << is_prime<3>::value << std::endl;
    std::cout << is_prime<4>::value << std::endl;
    std::cout << is_prime<100>::value << std::endl;

    std::cout << find<std::integer_sequence<int, 0>>::value << std::endl;
    std::cout << find<std::integer_sequence<int, 1>>::value << std::endl;
    std::cout << find<std::integer_sequence<int, 2>>::value << std::endl;
    std::cout << find<std::integer_sequence<int, 3>>::value << std::endl;
    std::cout << find<std::integer_sequence<int, 4>>::value << std::endl;
    std::cout << find<std::integer_sequence<int, 5>>::value << std::endl;
    std::cout << find<std::integer_sequence<int, 6>>::value << std::endl;

    std::cout << find<std::integer_sequence<int, 0, 1>>::value << std::endl;
    std::cout << find<std::integer_sequence<int, 0, 1, 2>>::value << std::endl;
    std::cout << find<std::integer_sequence<int, 0, 1, 2, 3>>::value
              << std::endl;
    std::cout << find<std::integer_sequence<int, 0, 1, 2, 3, 4>>::value
              << std::endl;
    std::cout << find<std::integer_sequence<int, 0, 1, 2, 3, 4, 5>>::value
              << std::endl;
    std::cout << find<std::integer_sequence<int, 0, 1, 2, 3, 4, 5, 6>>::value
              << std::endl;

    std::cout << find<std::integer_sequence<int, 4, 8, 15, 16, 23, 42>>::value
              << std::endl;

    std::cout << find<std::integer_sequence<
                     int, 198, 4, 667, 917, 74, 468, 817, 705, 908, 517, 88,
                     353, 975, 903, 326, 25, 170, 629, 992, 724, 587, 411, 536,
                     250, 268, 727, 643, 547, 181>>::value
              << std::endl;
    std::cout
        << find<std::integer_sequence<int, 559, 917, 917, 198, 670, 522, 184,
                                      521, 364, 227, 6, 294, 295>>::value
        << std::endl;
    std::cout
        << find<std::integer_sequence<
               int, 590, 765, 522, 825, 722, 927, 646, 422, 453, 186, 673, 897,
               690, 408, 217, 841, 259, 274, 254, 523, 758, 325, 350, 353, 561,
               384, 40, 981, 623, 35, 0, 461, 446, 0, 394>>::value
        << std::endl;
    std::cout
        << find<std::integer_sequence<
               int, 590, 765, 522, 825, 722, 927, 646, 422, 453, -2, 673, 897,
               690, 408, 217, 841, 259, 274, 254, 523, 758, 325, 350, 353, 561,
               384, 40, 981, 623, 35, 0, 461, 446, 0, 394>>::value
        << std::endl;

    return 0;
}
