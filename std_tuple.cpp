// https://riptutorial.com/cplusplus/example/1601/using-std--tuple
#include "jly_tutorials.h"

namespace jly_tutorials
{
	std::tuple<int, int, int, int> foo14(int a, int b) { // or auto (C++14)
		return std::make_tuple(a + b, a - b, a * b, a / b);
	}

	std::tuple<int, int, int, int> foo17(int a, int b) {
		return { a + b, a - b, a * b, a / b };
	}

	/////////////////////
	// return a tuple of lvalue references instead of a tuple of values
	std::tuple<int&, int&> minmax(int& a, int& b) {
		if (b < a)
			return std::tie(b, a);
		else
			return std::tie(a, b);
	}

	// minmax tuple usage
	void increase_least(int& a, int& b) {
		std::get<0>(minmax(a, b))++;
	}
	////////////////////////
	
	void main_tuple()
	{

		////////////////
		auto mrvs = foo14(5, 12);
		auto add = std::get<0>(mrvs);
		auto sub = std::get<1>(mrvs);
		auto mul = std::get<2>(mrvs);
		auto div = std::get<3>(mrvs);

		int add1, sub1, mul1, div1;
		std::tie(add1, sub1, mul1, div1) = foo14(5, 12); // 14
		// std::ignore
		std::tie(add1, sub1, std::ignore, div1) = foo14(5, 12);

		auto [add2, sub2, mul2, div2] = foo17(5, 12);
		////////////////

		////////////////
		auto t = std::make_tuple(1, "Foo", 3.14);
		// index-based access
		std::cout << "(" << std::get<0>(t) << ", " << std::get<1>(t)
			<< ", " << std::get<2>(t) << ")\n";
		// type-based access (C++14 or later)
		std::cout << "(" << std::get<int>(t) << ", " << std::get<const char*>(t)
			<< ", " << std::get<double>(t) << ")\n";
		// Note: std::tie and structured binding may also be used to decompose a tuple
		////////////////
	}
}