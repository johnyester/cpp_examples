// https://www.fluentcpp.com/2017/10/17/stdaccumulate-your-knowledge-on-algorithms/

/*
* std::accumulate
templane<class InputIt, class T, class BinaryOperation>
T accumulate(InputIt first, InputIt last, T init,
	BinaryOperation op)
	{
		for(; first != last; ++first)
		{
			init = op(init, *first);
		}
		return init;
	}

sig of op: Type1 fun(const Type1 &a, const Type2 &b);  // i.e. type of passed args can differ

https://en.cppreference.com/w/cpp/algorithm/accumulate
Parameters
	first, last	-	the range of elements to sum
	init		-	initial value of the sum
	op			-	binary operation function object that will be applied. 
		The binary operator takes the current accumulation value a (initialized to init) 
		and the value of the current element b.

		The signature of the function should be equivalent to the following:
			Ret fun(const Type1 &a, const Type2 &b);

		The signature does not need to have const &.

		The type Type1 must be such that an object of type T can be implicitly converted to Type1. 
		The type Type2 must be such that an object of type InputIt can be dereferenced and then implicitly converted to Type2. 
		The type Ret must be such that an object of type T can be assigned a value of type Ret.​

Type requirements
	-InputIt must meet the requirements of LegacyInputIterator.
	-T must meet the requirements of CopyAssignable and CopyConstructible.

Return value
	1) The sum of the given value and elements in the given range.
	2) The result of left fold of the given range over op

Notes
std::accumulate performs a left fold. 

In order to perform a right fold, 
	one must reverse the order of the arguments to the binary operator, 
	and use reverse iterators.
*/

// monoids
// https://en.wikipedia.org/wiki/Monoid
//A Monoid can be defined as a tuple(M, op, e) where:
//  M is a set of element
//	op is an associative binary operation on two elements of M, returning a new element of M
//	e is an element of M, neutral for op on both left and right side
//Integers form a Monoid under addition with the neutral element zero
//Integers form a Monoid under multiplication with the neutral element one
//Sequential containers form a Monoid under concatenation(strings, vectors…)
//Associative containers form a Monoid under union (maps, sets…)
//  addition, multiplication on integers
//	concatenation on strings
//	union on sets
//	merging objects of all kinds
//	min, max, oad, or, ...
//	parsing
//	etc.

/* https://deque.blog/2017/09/13/monoids-what-they-are-why-they-are-useful-and-what-they-teach-us-about-software/
template<class Coordinate>
using Shape = std::function<bool (Coordinate const&)>;
using Coord2D = std::pair<double, double>;
using Shape2D = Shape<Coord2D>;
template<class Coordinate>
Shape<Coordinate> outside(Shape<Coordinate> const& s) {
	return [=](Coordinate const& coord) {
		return not s(coord);
	};
}
*/

/*
std::reduce
template<class Inputit, class T, class BinaryOp>
T reduce(InputIt first, InputIt last,
	T init, BinaryOp op);
*/
#include <vector>
#include <numeric>
#include <functional>
#include <iostream>
#include <iterator>

template < typename It, typename Compare,
	typename T = typename std::iterator_traits<It>::value_type>
	T min_element(It first, It last, Compare cmp)
{
	auto init = *first;
	return std::accumulate(
		++first, last, init,
		[&](const T& a, const T& b) {
		return cmp(b, a) ? b : a;
	});
}

namespace jly_tutorials
{
	void main_accumulate()
	{
		std::vector<int> v = { 7, 1,2,3,4,5 };
		int sum = std::accumulate(v.cbegin(), v.cend(), 0, std::plus<>());
		std::cout << sum << '\n';

		int product = std::accumulate(v.cbegin(), v.cend(), 1, std::multiplies<>());
		std::cout << product << std::endl;

		int max_val = std::accumulate(v.cbegin(), v.cend(), 0, [](int a, int b) {return a > b ? a : b; });
		std::cout << max_val << std::endl;

		int min_val = min_element(v.cbegin(), v.cend(), [](int a, int b) {return a < b ? 1 : 0; });
		std::cout << min_val << std::endl;

		bool results[] = { true, false, true, true, false };

		bool all_true = std::accumulate(std::cbegin(results), std::cend(results), true, std::logical_and<>());
		std::cout << (all_true ? "all true" : "not all true") << '\n';

		bool some_true = std::accumulate(std::cbegin(results), std::cend(results), false, std::logical_or<>());
		std::cout << (some_true ? "some true" : "none_true") << '\n';

		bool none_true = !std::accumulate(std::cbegin(results), std::cend(results), false, std::logical_or<>());
		std::cout << (none_true ? "none true" : "some true") << '\n';

		std::string strs[] = { "Hello ","World","!" };
		std::cout << std::accumulate(strs, strs + 3, std::string()) << std::endl;

		// std::accumulate O(n) for strings by supplying a custom functor :
		// https://stackoverflow.com/questions/15347123/how-to-construct-a-stdstring-from-a-stdvectorstring/18703743#18703743
		std::vector<std::string> strsv = { "Hello ","World","!" };
		std::string s = std::accumulate(strsv.cbegin(), strsv.cend(), std::string{},
			[](std::string& s, const std::string& piece) -> decltype(auto) { return s += piece; });
		// Note that s must be a reference to non - const, the lambda return type must be a reference(hence decltype(auto)), and the body must use += not + .
		std::cout << s << std::endl;


	}

	// 
	/* https://accu.org/index.php/articles/2182
	Folding is a highly generic operation available through std::accumulate.
	Paul Keir goes beyond reduction, with the help of C++14’s polymorphic lambdas.

	fold: an elementary reduction operator from functional programming
	*/
	template <typename F>
	auto flip(const F& f) { return std::bind(f, std::placeholders::_2, std::placeholders::_1); }


	template <typename F, typename T, typename C>
	T foldr(const F& f, const T& z, const C& c) {
		return accumulate(crbegin(c), crend(c), z,
			flip(f));
	}

	void main_accumulate_fold()
	{
		// right fold - reverse traverse of container - right minus
		auto ans = foldr(std::minus<>{}, 0, std::vector<int>{1, 2, 3});
		std::cout << ans << std::endl;

		// concatenation
		auto cons = [=](auto x, auto xs) {
			decltype(xs) ys{ x };
			copy(begin(xs), end(xs), back_inserter(ys));
			return ys;
		};
		auto ans_cons = foldr(cons, std::vector<int>{}, std::vector<int>{1, 2, 3});
		std::cout << ans_cons.size() << std::endl;

		// concatenation using lambda to automate type creation
		auto id = [=](auto xs) {
			return foldr(cons, decltype(xs){}, xs);
		};
		auto ans_cons6 = id(std::vector<int>{1, 2, 3});
		std::cout << "ans_cons6 " << ans_cons6.size() << std::endl;

		// append
		auto append = [=](auto xs, auto ys) {
			return foldr(cons, ys, xs);
		};
		auto ans7 = append(std::vector<int>{1, 2, 3}, std::vector<int>{4, 5, 6});
		std::cout << "ans7 " << ans7.size() << std::endl;

		// length
		auto length = [=](auto xs) {
			return foldr(
				[=](auto, auto n) { return 1 + n; },
				0,
				xs);
		};
		std::cout << "length = " << length(ans7) << std::endl;

		// reverse
		auto reverse = [=](auto xs) {
			return foldr(
				[=](auto y, auto ys)
			{ return append(ys, decltype(xs){y}); },
				decltype(xs){},
				xs);
		};

		// map
		auto map = [=](auto f, auto xs) {
			return foldr(
				[=](auto y, auto ys) { return cons(f(y), ys); },
				vector<decltype(f(*xs.begin()))>{},
				xs);
		};

		// sum & length 
		auto sumlength = [=](auto xs) {
			return foldr(
				[=](auto n, auto p) {
				return std::make_pair(n + p.first, 1 + p.second);},
				std::make_pair(0, 0), xs);
		};

		//f(g(x))
		auto compose = [=](auto fs) {
			using fn_t = typename decltype(fs)::value_type;
			return foldr(
				[=](auto f, auto g)
			{ return [=](auto x) { return f(g(x)); }; },
				fn_t([=](auto x) { return x; }),
				fs);
		};

		// left fold, aka accumulate, using a right fold
		auto foldl = [=](auto f, auto z, auto xs) {
			using z_t = decltype(z);
			using fn_t = std::function<z_t(z_t)>;
			return foldr(
				[=](auto x, auto g) {
				return [=](auto a) { return g(f(a, x)); };
			},
				fn_t([=](auto x) { return x; }), xs)(z);
		};
	}
}