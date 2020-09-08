#include "jly_tutorials.h"

namespace jly_tutorials
{
	void main_structured_bindings()
	{
		auto [a, i, b] = std::tuple('a', 123, true);    // With no types needed for the tuple!


		//// ex put stream in loop since that's where it's used:
		// https://www.fluentcpp.com/2018/06/19/3-simple-c17-features-that-will-make-your-code-simpler/
		//{
		//	std::istringstream iss(head);
		//	for (std::string name; std::getline(iss, name); )
		//		// Process name
		//}
		//for (auto [iss, name] = pair(istringstream(head), string{}); getline(iss, name); ) {


		/////////////////////////
		std::map<std::string, int> m;

		// insert an element into the map and check if insertion succeeded
		auto [iterator, success] = m.insert({ "Hello", 42 });

		if (success) {
			// your code goes here
		}

		// iterate over all elements without having to use the cryptic 'first' and 'second' names
		for (auto const& [key, value] : m) {
			std::cout << "The value for " << key << " is " << value << '\n';
		}
		///////////////////////////////

		//////////////////////
		// Structured bindings can be used by default with std::pair, std::tuple, and any type 
		// whose non - static data members are all either public direct members or members of an unambiguous base class :
		struct A { int x; };
		struct B : A { int y; };
		B foo();

		// with structured bindings - doesn't compile 
		// cannot decompose type with non - static data - members in both 'jly_tutorials::main_structured_bindings::B' and 'jly_tutorials::main_structured_bindings::A'	jly_cpp	H : \cpp_repo\jly_cpp\structured_bindings.cpp	43
		// auto [x, y] = foo();

		// equivalent code without structured bindings
		const auto result = foo();
		auto& x1 = result.x;
		auto& y1 = result.y;
		////////////////////////////////////
	}
}