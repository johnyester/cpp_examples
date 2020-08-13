#include <array>
#include <tuple>
#include <iostream>
#include <vector>
#include <map>
#include <typeinfo>
#include <typeindex>
#include <boost/optional.hpp>

namespace jly_tutorials
{
    template<class T>
    struct generator_iterator {
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T;
        using iterator_category = std::input_iterator_tag;
        boost::optional<T> state;
        std::function< boost::optional<T>() > operation;
        // we store the current element in "state" if we have one:
        T operator*() const {
            return *state;
        }
        // to advance, we invoke our operation.  If it returns a nullopt
        // we have reached the end:
        generator_iterator& operator++() {
            state = operation();
            return *this;
        }
        generator_iterator operator++(int) {
            auto r = *this;
            ++(*this);
            return r;
        }

        // generator iterators are only equal if they are both in the "end" state:
        friend bool operator==(generator_iterator const& lhs, generator_iterator const& rhs) {
            if (!lhs.state && !rhs.state) return true;
            return false;
        }
        friend bool operator!=(generator_iterator const& lhs, generator_iterator const& rhs) {
            return !(lhs == rhs);
        }

        // We implicitly construct from a std::function with the right signature:
        generator_iterator(std::function< boost::optional<T>() > f) :operation(std::move(f))
        {
            if (operation)
                state = operation();
        }
        // default all special member functions:
        generator_iterator(generator_iterator&&) = default;
        generator_iterator(generator_iterator const&) = default;
        generator_iterator& operator=(generator_iterator&&) = default;
        generator_iterator& operator=(generator_iterator const&) = default;
        generator_iterator() = default;
    };

    template<class It>
    struct range_t {
        It b, e;
        It begin() const { return b; }
        It end() const { return e; }
    };
    template<class It>
    range_t<It> range(It b, It e) {
        return { std::move(b), std::move(e) };
    }
    template<class It>
    range_t<It> range(It b) {
        return range(std::move(b), It{});
    }

    template< class F >
    auto generator(F f)
    {
        using V = std::decay_t< decltype(*f()) >;
        return range(generator_iterator<V>(std::move(f)));
    }
    int main_generator_iterator() {
        auto from_1_to_10 = [i = 0]() mutable->boost::optional<int>
        {
            auto r = ++i;
            std::cout << "from_1_to_10()" << std::endl;
            if (r > 10) return {};
            return r;
        };
        for (int i : generator(from_1_to_10))
            std::cout << i << '\n';
        return 0;
    }
}