#include <iostream>

namespace jly_tutorials
{
	template <typename N>
		void change(N n) {
		//if n is std::reference_wrapper<int>, 
		// it implicitly converts to int& here.
		n += 1;
	}

	void main_references() {
		int x = 10;

		int& xref = x;
		change(xref); //Passed by value 
		//x is still 10
		std::cout << x << "\n"; //10

		//Be explicit to pass by reference
		change<int&>(x);
		//x is 11 now
		std::cout << x << "\n"; //11

		//Or use std::ref
		change(std::ref(x)); //Passed by reference
		//x is 12 now
		std::cout << x << "\n"; //12

		/*
		the following will not compile
		int& xref1;
		change(xref);

		int* xp;
		change(xp);
		*/

		///////////////////////////////////
		
		//Error! must initialize.//
		// std::reference_wrapper<int> nr; 

		std::string str1{ "Hello" };
		std::string str2{ "World" };

		auto r1 = std::ref(str1); //OK
		auto r2 = std::ref(str2); //OK

		//Assignment rebinds the reference_wrapper  
		r2 = r1;  //r2 also refers to str1 now 

		//Implicit conversion to std::string&
		std::string cstr = r2; //cstr is "Hello"

		//Possible to create an array of reference_wrapper
		std::reference_wrapper<std::string> arr[] = { str1, str2 };

		//Error! no temporary (rvalue) allowed.
		// auto r2 = std::ref(std::string("Hello")); 

		/////////////////////////////////////
		// The only downside is that to access the members of an object(T), 
		// we have to use the 'std::reference_wrapper<T>::get' method:
		std::string str{ "Hello" };

		auto sref = std::ref(str);
		//Print length of str
		std::cout << sref.get().length() << "\n"; //5

		// Also, to assign to the referred object use 'get()':
		sref.get() = "World"; //str is changed to "World"
		std::cout << str << "\n"; //World
	}
}