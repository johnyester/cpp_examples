#include <string>
#include <iostream>
#include <iomanip>
#include <utility>

// https://en.cppreference.com/w/cpp/language/move_constructor
// the above has links to:
//See also
//converting constructor
//copy assignment
//copy constructor
//copy elision
//default constructor
//destructor
//explicit
//initialization
//aggregate initialization
//constant initialization
//copy initialization
//default initialization
//direct initialization
//initializer list
//list initialization
//reference initialization
//value initialization
//zero initialization
//move assignment
//new

// might want to follow up with: https://en.cppreference.com/w/cpp/language/copy_elision
namespace jly_tutorials
{
	struct A
	{
		std::string s;
		int k;
		A() : s("test"), k(-1) {
			std::cout << "constructor called." << std::endl;
		}
		A(const A& o) : s(o.s), k(o.k) {
			std::cout << "copying, move failed!\n";
		}
		A(A&& o) noexcept :
			s(std::move(o.s)),       // explicit move of a member of class type
			k(std::exchange(o.k, 0)) // explicit move of a member of non-class type
		{
			std::cout << "moving." << std::endl;
		}
	};

	A f(A a)
	{
		std::cout << "f() called." << std::endl;
		return a;
	}

	struct B : A
	{
		std::string s2;
		int n;
		// implicit move constructor B::(B&&)
		// calls A's move constructor
		// calls s2's move constructor
		// and makes a bitwise copy of n
	};

	struct C : B
	{
		~C() { } // destructor prevents implicit move constructor C::(C&&)
	};

	struct D : B
	{
		D() { }
		~D() { }          // destructor would prevent implicit move constructor D::(D&&)
		D(D&&) = default; // forces a move constructor anyway
	};

	/*
	Trying to move A
	constructor called.
	f() called.
	moving.
	Before move, a1.s = "test" a1.k = -1
	moving.
	After move, a1.s = "" a1.k = 0
	Trying to move B
	constructor called.
	Before move, b1.s = "test"
	moving.
	After move, b1.s = ""
	Trying to move C
	constructor called.
	copying, move failed!
	Trying to move D
	constructor called.
	moving.
	*/
	void main_move_constructors()
	{
		std::cout << "Trying to move A\n";
		A a1 = f(A()); // return by value move-constructs the target from the function parameter
		std::cout << "Before move, a1.s = " << std::quoted(a1.s) << " a1.k = " << a1.k << '\n';
		A a2 = std::move(a1); // move-constructs from xvalue
		std::cout << "After move, a1.s = " << std::quoted(a1.s) << " a1.k = " << a1.k << '\n';

		std::cout << "Trying to move B\n";
		B b1;
		std::cout << "Before move, b1.s = " << std::quoted(b1.s) << "\n";
		B b2 = std::move(b1); // calls implicit move constructor
		std::cout << "After move, b1.s = " << std::quoted(b1.s) << "\n";

		std::cout << "Trying to move C\n";
		C c1;
		C c2 = std::move(c1); // calls copy constructor

		std::cout << "Trying to move D\n";
		D d1;
		D d2 = std::move(d1);
	}
}