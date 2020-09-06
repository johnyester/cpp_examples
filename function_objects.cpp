/*
* https://www.fluentcpp.com/2017/01/23/stl-function-objects-stateless-is-stressless/
*
* A function object is an object that can be used in a function call syntax:
	myFunctionObject(x);

even though it is declared with a class (or a struct). 
This syntax is allowed by the declaration of an operator():
	class MyFunctionObject
	{
	public:
		void operator()(int x)
		{
			....
		}
	}
	
The advantage of function objects over simple functions is that function objects can embark data:
	class MyFunctionObject
	{
	public:
		explicit MyFunctionObject(Data data) : data_(data) {}
		void operator()(int x)
		{
			....usage of data_....
		}
	private:
		Data data_;
	}

And at call site:
	MyFunctionObject myFunctionObject(data);
	myFunctionObject(42);

This way the function call will use both 42 and data to execute. 
This type of object is called a functor.


In C++11, lambdas fill the same need with a lighter syntax:
	Data data;
	auto myFunctionObject = [data](int x){....usage of data....};

	myFunctionObject(42);


Functions, functors and lambdas can be used with the same function-call syntax. 
For this reason they are all callables.

Callables are used profusely with the STL because algorithms have generic behaviours that are customized by callables. Take the example of for_each. for_each iterates over the elements of a collection and does something with each of them. This something is described by a callable. The following examples bump up every number of a collection by adding 2 to them, and show how to achieve this with a function, a functor and a lambda:

- with a function the value 2 has to be hardcoded:
	void bump2(double& number)
	{
		number += 2;
	}

	std::vector<double> numbers = {1, 2, 3, 4, 5};

	std::for_each(numbers.begin(), numbers.end(), bump2);

- with a functor, the bump value can be a passed as a parameter, which allows greater flexibility but with a heavier syntax:
	class Bump
	{
	public:
		explicit Bump(double bumpValue) : bumpValue_(bumpValue) {}
		void operator()(double& number) const
		{
			number += bumpValue_;
		}
	private:
		double bumpValue_;
	};

	std::vector<double> numbers = {1, 2, 3, 4, 5};

	std::for_each(numbers.begin(), numbers.end(), Bump(2));

- and the lambda allows the same flexibility, but with a lighter syntax:
	std::vector<double> numbers = {1, 2, 3, 4, 5};

	double bumpValue = 2;
	std::for_each(numbers.begin(), numbers.end(),
				  [bumpValue](double& number){number += bumpValue;});
*/

/* Notes:
Here are some advantages of function object listed in "The C++ Standard Library" by Nicolai M. Josuttis.
1. Function object are "smart functions."
	Objects that behave like pointers are smart pointers. 
	This is similarly true for objects that behave like functions: 
	They can be "smart functions" because they may have abilities beyond operator (). 
	Function objects may have other member functions and attributes. 
	This means that function objects have a state. ....
2. Each function object has its own type.
	Ordinary functions have different types only when their signatures differ.
	However, function objects can have different types when their signatures are the same.
	In fact, each functional behavior defined by a function object has its own type. 
	This is a significant improvement for generic programming using templates because 
	you can pass functional behavior as a template parameter. ...
3. Function objects are usually faster than ordinary functions.
	The concept of templates usually allows better optimization because 
	more details are defined at compile time. 
	Thus, passing function objects instead of ordinary functions often results in better performance.

*/
/*
Other resources to review in future
	https://www.cprogramming.com/tutorial/functors-function-objects-in-c++.html
	- ideas on equivalent use of functors and functions using templates
	- no complete examples - would be a good exercise to build the examples!
	- does compare functors to virtual functions, a consideration.

	https://www.bogotobogo.com/cplusplus/functors.php
	- some examples of functors
	- discusses predicates, function adapters (bind2nd, bind1st)
*/

#include <vector>
#include <algorithm>
#include <iostream>

namespace jly_tutorials
{
	class Count7
	{
	public:
		Count7() : counter_(0) {}
		void operator()(int number)
		{
			if (number == 7) ++counter_;
		}
		int getCounter() const { return counter_; }
	private:
		int counter_;
	};


	/* the focus of these examples is to examine the issue with using states in callables */
	void main_functors()
	{
		std::vector<int> numbers = { 1, 7, 4, 7, 7, 2, 3, 4 };

		// states in callables
		// works
		int count = std::for_each(numbers.begin(), numbers.end(), Count7()).getCounter();
		std::cout << count << " 7's found." << std::endl;

		// doesn't work because count7 is a copy - The reason is that, surprising at it sounds, count7 has never reached the inside of for_each. Indeed for_each takes its callable by value, so it is a copy of count7 that was used by for_each and that had its state modified.
		Count7 count7;
		std::for_each(numbers.begin(), numbers.end(), count7);
		count = count7.getCounter();

		/* for_each does use the same copy for each loop, unlike transform */

		// lambda - still too complex, use std::count instead
		std::for_each(numbers.begin(), numbers.end(),
			[&count](int number) { if (number == 7) ++count; });
		
		// better way
		count = std::count(numbers.begin(), numbers.end(), 7);

		/* http://www.cplusplus.com/reference/algorithm/count/
			template <class InputIterator, class T>
			  typename iterator_traits<InputIterator>::difference_type
				count (InputIterator first, InputIterator last, const T& val);

		The behavior of this function template is equivalent to:
			template <class InputIterator, class T>
			  typename iterator_traits<InputIterator>::difference_type
				count (InputIterator first, InputIterator last, const T& val)
			{
			  typename iterator_traits<InputIterator>::difference_type ret = 0;
			  while (first!=last) {
				if (*first == val) ++ret;
				++first;
			  }
			  return ret;
			}
		*/
		std::cout << count << std::endl;

		// another classical example of state within a callable: sentinels

	}
}