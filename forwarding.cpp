// forward example
#include <utility>      // std::forward
#include <iostream>     // std::cout

/*
* https://medium.com/pranayaggarwal25/universal-reference-perfect-forwarding-5664514cacf9
How to work with Universal References?
A type in independent of lvalueness and rvalueness
There are lvalues of type int (e.g., variables declared to be ints), 
and there are rvalues of type int (e.g., literals like 10)

Widget&& var1 = makeWidget()   // var1 is an lvalue, but
// its type is rvalue reference (to Widget)

As with Rvalue references, we use std::move, 
with Universal references we should always use std::forward<T> present in <utility> header
which takes care of copy in case of Lvalue Ref and move in case of Rvalue Ref.

std::forward keeps the reference type of x. So:
If x is an rvalue reference then std::forward is = std::move,
If x is an lvalue reference then std::forward doesn’t do anything.

So for the previous example of ‘wrapper’ function on func(E1 E2, ... En)-
template <typename T1, typename T2>
void wrapper(T1&& e1, T2&& e2) {
	func(std::forward<T1>(e1), std::forward<T2>(e2));
}
// Awesome!!

std::forward is a conditional cast but std::move is an unconditional cast.

Applications of perfect forwarding are std::make_shared , std::make_unique , vector::emplace_back etc.
*/
namespace jly_tutorials
{
	// function with lvalue and rvalue reference overloads:
	void overloaded(const int& x) { std::cout << "[lvalue]"; }
	void overloaded(int&& x) { std::cout << "[rvalue]"; }

	// function template taking rvalue reference to deduced type:
	template <class T> void fn(T&& x) {
		overloaded(x);                   // always an lvalue
		overloaded(std::forward<T>(x));  // rvalue if argument is rvalue
	}

	/*
	* http://www.cplusplus.com/reference/utility/forward/
	calling fn with lvalue: [lvalue][lvalue]
	calling fn with rvalue: [lvalue][rvalue]
	*/
	int main_forwarding() {
		int a;

		std::cout << "calling fn with lvalue: ";
		fn(a);
		std::cout << '\n';

		std::cout << "calling fn with rvalue: ";
		fn(0);
		std::cout << '\n';

		int&& i = 10;
		std::cout << "int&& " << i << std::endl;

		return 0;
	}
}