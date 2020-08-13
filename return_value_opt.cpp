#include <iostream>

namespace jly_tutorials {
	struct P {
		constexpr P() : x{ 0 } {}
		constexpr P(P&&) : x{ 1 } {}
		int x;
	};

	constexpr auto will_this_rvo() {
		P p;
		//std::cout << "in will_this_rvo() " << p.x << std::endl;
		return p;
	}

	struct P1 {
		P1() : x{ 0 } { std::cout << "P1()\n"; }
		//P1(P1&&) : x{ 1 } { std::cout << "P1(P1&&)\n"; }
		int x;
	};

	auto will_this_rvo1() {
		P1 p;
		std::cout << "in will_this_rvo1() " << p.x << std::endl;  // 0
		p.x = 2;
		return p;
	}

	struct my_type
	{
		my_type() { std::cout << "my_type: default constructor called.\n"; };
		my_type(const my_type&) { std::cout << "Copying\n"; }
		my_type(my_type&&) { std::cout << "Moving\n"; }
	};

	my_type func()
	{
		return my_type();
	}

	int main_rvo() {
		const auto p = will_this_rvo();
		std::cout << p.x << std::endl;  // 1
		const auto p1 = will_this_rvo1();
		std::cout << p1.x << std::endl;  // 1
		struct my_type mt = my_type();
		return 0;
	}


}