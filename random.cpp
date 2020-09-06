#include <random>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>

namespace jly_tutorials
{
    void main_random()
    {
        std::mt19937 rng; // default constructed, seeded with fixed seed
        std::generate_n(std::ostream_iterator<std::mt19937::result_type>(std::cout, " "),
            5, std::ref(rng));
        std::cout << '\n';
    }
}