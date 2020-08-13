#include <iostream>

// https://www.bfilipek.com/2020/08/lambda-capturing.html

namespace jly_tutorials
{


	void main_c14() {
		// capture with initializer
		// const auto foo = [z = x + y]() { std::cout << z << '\n'; };
		// auto
		// const auto foo = [](auto x, auto y) { /*...*/ };
		int x = 30;
		int y = 12;
		const auto foo = [z = x + y]() { std::cout << z << '\n'; };
		x = 0;
		y = 0;
		foo();
	}


	void main_lambdas()
	{
		//  syntax: [] () specifiers exception attr->ret{ /*code; */ }
		//	[] - introduces the lambda expression, capture clause
		//	() - the list of arguments, like in a regular function, optional if specifiers / exception list is empty
		//	specifiers / exception / attr - mutable, noexcept - additional specifiers
		//	ret - trailing return type, in most cases not needed as the compiler can deduce the type
		//	/* code; */ - the body of the lambda

		//// 1. the simplest lambda:
		//[] {};

		//// 2. with two params:
		//[](float f, int a) { return a * f; };
		//[](int a, int b) { return a < b; };

		//// 3. trailing return type:
		//[](MyClass t) -> int { auto a = t.compute(); print(a); return a; };

		//// 4. additional specifiers:
		//[x](int a, int b) mutable { ++x; return a < b; };
		//[](float param) noexcept { return param * param; };
		//[x](int a, int b) mutable noexcept { ++x; return a < b; };

		//// 5. optional ()
		//[x] { std::cout << x; }; // no () needed

		//[x] mutable { ++x; };    // won't compile!
		//[x]() mutable { ++x; };  // fine - () required before mutable

		//[] noexcept {};        // won't compile!
		//[]() noexcept {};      // fine

		//The syntax for captures:

		//  [&] - capture by reference all automatic storage duration variables declared in the reaching scope.
		//	[=] - capture by value(create a copy) all automatic storage duration variables declared in the reaching scope.
		//	[x, &y] - capture x by value and y by a reference explicitly.
		//	[x = expr] - a capture with an initialiser(C++14)
		//	[args...] - capture a template argument pack, all by value.
		//	[&args...] - capture a template argument pack, all by reference.
		//	[...capturedArgs = std::move(args)](){} - capture pack by move(C++20)
		//	Some examples :

		//int x = 2, y = 3;

		//const auto l1 = []() { return 1; };          // No capture
		//const auto l2 = [=]() { return x; };         // All by value (copy)
		//const auto l3 = [&]() { return y; };         // All by ref
		//const auto l4 = [x]() { return x; };         // Only x by value (copy)
		//// const auto lx = [=x]() { return x; };     // wrong syntax, no need for
		//											   // = to copy x explicitly

		//const auto l5 = [&y]() { return y; };        // Only y by ref
		//const auto l6 = [x, &y]() { return x * y; }; // x by value and y by ref
		//const auto l7 = [=, &x]() { return x + y; }; // All by value except x 
		//											   // which is by ref
		//const auto l8 = [&, y]() { return x - y; };  // All by ref except y which 
		//											   // is by value
		//const auto l9 = [this]() {}                  // capture this pointer
		//	const auto la = [*this]() { }              // capture a copy of *this - since C++17

		/*
		main_lambdas() starting ...
		1, 2, 3, hello, 10.5,
		1, 2, 3, hello, 10.5,
		1, 2, 3, hello, 10.5
		*/
		std::cout << "main_lambdas() showing lambda/fold examples ..." << std::endl;
		// https://www.bfilipek.com/2020/08/c-lambda-week-some-tricks.html
		const auto printer = [](auto... args) {
			const auto printElem = [](auto elem) {
				std::cout << elem << ", ";
			};
			(printElem(args), ...);
			std::cout << '\n';
		};

		printer(1, 2, 3, "hello", 10.5f);

		const auto printer2 = [](auto... args) {
			((std::cout << args << ", "), ...);
			std::cout << '\n';
		};

		printer2(1, 2, 3, "hello", 10.5f);

		const auto printer3 = [](auto first, auto... args) {
			std::cout << first;
			((std::cout << ", " << args), ...);
			std::cout << '\n';
		};

		printer3(1, 2, 3, "hello", 10.5f);

	}
}