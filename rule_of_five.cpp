#include <iostream>
#include <cstring> 
using namespace std;

// http://coreyjames.me/2020/03/22/rule-of-five-c/

// this has a nice structure, but some of the methods are wrong/fragile - JLY
// see rule_of_five2 - JLY
namespace jly_tutorials
{
	template < class T >
	class RuleOfFiveTemplated {
		size_t size = 0;
		T* data = nullptr;
	public:
		// Default Constructor
		RuleOfFiveTemplated() {
			std::cout << (void*)this << ": RuleOfFiveTemplated constructor()\n";
		}

		// Constructor Overload
		RuleOfFiveTemplated(size_t size) : size(size), data(new T[size]) {
			cout << (void*)this << ": RuleOfFiveTemplated (" << size << ") constructor\n";
		}

		// One - Assignment Operator - looks bad, see raii1 - JLY
		RuleOfFiveTemplated& operator = (const RuleOfFiveTemplated& rhs) {
			cout << (void*)this << ": RuleOfFiveTemplated assignment operator, size = " << size << ", rhs.size = " << rhs.size << endl;
			if (this != &rhs) {
				delete[] data;
				data = nullptr;
				size = 0;

				if (rhs.data) {
					size = rhs.size;
					try {
						data = new T[size];
						memcpy(data, rhs.data, size * sizeof(T));
					}
					catch (const std::bad_alloc& err) {
						cout << (void*)this << ": RuleOfFiveTemplated Failed to copy value inside data: " << err.what() << endl;
					}
				}
			}
			else {
				cout << (void*)this << ": RuleOfFiveTemplated copy assignment operator called on itself" << endl;
			}
			return *this;
		}

		// Two - Copy Constructor - looks bad, see raii1 - JLY
		RuleOfFiveTemplated(const RuleOfFiveTemplated& rhs) {
			cout << (void*)this << ": RuleOfFiveTemplated copy constructor, size = " << size << ", rhs.size = " << rhs.size << endl;
			data = nullptr;
			*this = rhs;
		}

		// three - Move Assignment Operator
		RuleOfFiveTemplated&& operator = (RuleOfFiveTemplated&& rhs) noexcept {
			cout << (void*)this << ": RuleOfFiveTemplated move assignment operator, size = " << size << ", rhs.size = " << rhs.size << endl;
			if (this != &rhs) {
				delete[] data;

				size = rhs.size;
				data = rhs.data;

				rhs.size = 0;
				rhs.data = nullptr;
			}
			else {
				cout << (void*)this << ": RuleOfFiveTemplated move assignment operator called on itself\n";
			}
			return std::move(*this);
		}

		// Four - Move Constructor
		RuleOfFiveTemplated(RuleOfFiveTemplated&& rhs) noexcept {
			cout << (void*)this << ": RuleOfFiveTemplated move constructor, size = " << size << ", rhs.size = " << rhs.size << endl;
			data = nullptr;
			*this = std::move(rhs);
		}

		// Five - De-Constructor
		~RuleOfFiveTemplated() {
			cout << (void*)this << ": RuleOfFiveTemplated destructor, size=" << size << "\n";
			delete[] data;
		}

		// Print
		void print() {
			cout << (void*)this << ": size=" << size << " (" << size * sizeof(T) << " BYTES)\n";
		}
	};
	// Non - Templated Rule Of Five
	class RuleOfFive {
		size_t size = 0;
		double* data = nullptr;
	public:
		RuleOfFive() {
			cout << (void*)this << ": RuleOfFive default constructor" << endl;
		}

		RuleOfFive(size_t size) : size(size), data(new double[size]) {
			cout << (void*)this << ": RuleOfFive constructor overload." << endl;
		}

		// One - Copy assignment operator
		RuleOfFive& operator=(RuleOfFive& rhs) {
			cout << (void*)this << ": RuleOfFive copy assignment operator, size = " << size << ", rhs.size = " << rhs.size << endl;
			if (this != &rhs) {
				delete[] data;
				data = nullptr;
				size = 0;

				if (rhs.data) {
					size = rhs.size;
					try
					{
						data = new double[size];
						memcpy(data, rhs.data, size * sizeof(double));
					}
					catch (const std::bad_alloc&)
					{
						cout << (void*)this << ": RuleOfFive Failed to copy value inside data" << endl;
					}
				}
			}
			else {
				cout << (void*)this << ": RuleOfFive copy assignment operator called on itself" << endl;
			}

			return *this;
		}

		// Two - Copy Constructor
		RuleOfFive(RuleOfFive& rhs) {
			cout << (void*)this << ": RuleOfFive copy constructor, size = " << size << ", rhs.size = " << rhs.size << endl;
			data = nullptr;
			*this = rhs;
		}

		// Three - Move Assignment operator
		RuleOfFive&& operator=(RuleOfFive&& rhs) noexcept {
			cout << (void*)this << ": RuleOfFive move assignment operator, size = " << size << ", rhs.size = " << rhs.size << endl;
			if (this != &rhs) {
				delete[] data;

				size = rhs.size;
				data = rhs.data;

				rhs.size = 0;
				rhs.data = nullptr;
			}
			else {
				cout << (void*)this << ": RuleOfFive move assignment operator called on itself" << endl;
			}

			return std::move(*this);
		}

		// Four - Move constructor
		RuleOfFive(RuleOfFive&& rhs) noexcept {
			cout << (void*)this << ": RuleOfFive move constructor, size = " << size << ", rhs.size = " << rhs.size << endl;
			data = nullptr;
			*this = std::move(rhs);
		}

		// Five - Deconstuctor
		~RuleOfFive() {
			cout << (void*)this << ": RuleOfFive deconstuctor" << endl;
		}

		// Print
		void print()
		{
			cout << (void*)this << ": size=" << size << " (" << size * sizeof(double) << " BYTES)" << endl;
		}
	};
	// Main Function
	void main_rule_of_five()
	{
		cout << "Rule Of Five" << endl << endl;

		// Test Default Constructors
		cout << endl << "Testing Default Constructor" << endl << "=========================================" << endl;

		RuleOfFive x;
		cout << "x created : ";
		x.print();

		RuleOfFiveTemplated<double> tx;
		cout << "tx created : ";
		tx.print();

		// Test Constructor Overloads
		cout << endl << "Testing Constructor Overloads" << endl << "=========================================" << endl;

		RuleOfFive y(1000);
		cout << "y created : ";
		y.print();

		RuleOfFiveTemplated<double> ty(1000);
		cout << "ty created : ";
		ty.print();

		// Test Copy Assignment operator
		cout << endl << "Test Rule One - Copy Assignment operator" << endl << "=========================================" << endl;

		x = y;
		cout << "x : lhs : ";
		x.print();
		cout << "y : rhs : ";
		y.print();

		tx = ty;
		cout << "tx : lhs : ";
		tx.print();
		cout << "ty : rhs : ";
		ty.print();

		// Test Copy Constructor
		cout << endl << "Test Rule Two - Copy Constructor" << endl << "=========================================" << endl;

		RuleOfFive z(x);
		cout << "z created : lhs : ";
		z.print();
		cout << "x : rhs : ";
		x.print();

		RuleOfFiveTemplated<double> tz(tx);
		cout << "tz created : lhs : ";
		tz.print();
		cout << "tx : rhs : ";
		tx.print();

		// Test Move Assignment operator
		cout << endl << "Test Rule Three - Move Assignment operator" << endl << "=========================================" << endl;

		y = std::move(x);
		cout << "y : lhs : ";
		y.print();
		cout << "x : rhs : ";
		x.print();

		ty = std::move(tx);
		cout << "ty : lhs : ";
		ty.print();
		cout << "tx : rhs : ";
		tx.print();

		// Test Move Constructor
		cout << endl << "Test Rule Four - Move Constructor" << endl << "=========================================" << endl;

		RuleOfFive a(std::move(y));
		cout << "a created : lhs : ";
		a.print();
		cout << "y : rhs : ";
		y.print();

		RuleOfFiveTemplated<double> ta(std::move(ty));
		cout << "ta created : lhs : ";
		ta.print();
		cout << "ty : rhs : ";
		ty.print();

		// Test Deconstructors
		cout << endl << "Test Rule Five - Deconstructors" << endl << "=========================================" << endl;
	}
}
/*
Rule Of Five


Testing Default Constructor
=========================================
00FDFA34: RuleOfFive default constructor
x created : 00FDFA34: size=0 (0 BYTES)
00FDFA24: RuleOfFiveTemplated constructor()
tx created : 00FDFA24: size=0 (0 BYTES)

Testing Constructor Overloads
=========================================
00FDFA14: RuleOfFive constructor overload.
y created : 00FDFA14: size=1000 (8000 BYTES)
00FDFA04: RuleOfFiveTemplated (1000) constructor
ty created : 00FDFA04: size=1000 (8000 BYTES)

Test Rule One - Copy Assignment operator
=========================================
00FDFA34: RuleOfFive copy assignment operator, size = 0, rhs.size = 1000
x : lhs : 00FDFA34: size=1000 (8000 BYTES)
y : rhs : 00FDFA14: size=1000 (8000 BYTES)
00FDFA24: RuleOfFiveTemplated assignment operator, size = 0, rhs.size = 1000
tx : lhs : 00FDFA24: size=1000 (8000 BYTES)
ty : rhs : 00FDFA04: size=1000 (8000 BYTES)

Test Rule Two - Copy Constructor
=========================================
00FDF9F4: RuleOfFive copy constructor, size = 0, rhs.size = 1000
00FDF9F4: RuleOfFive copy assignment operator, size = 0, rhs.size = 1000
z created : lhs : 00FDF9F4: size=1000 (8000 BYTES)
x : rhs : 00FDFA34: size=1000 (8000 BYTES)
00FDF9E4: RuleOfFiveTemplated copy constructor, size = 0, rhs.size = 1000
00FDF9E4: RuleOfFiveTemplated assignment operator, size = 0, rhs.size = 1000
tz created : lhs : 00FDF9E4: size=1000 (8000 BYTES)
tx : rhs : 00FDFA24: size=1000 (8000 BYTES)

Test Rule Three - Move Assignment operator
=========================================
00FDFA14: RuleOfFive move assignment operator, size = 1000, rhs.size = 1000
y : lhs : 00FDFA14: size=1000 (8000 BYTES)
x : rhs : 00FDFA34: size=0 (0 BYTES)
00FDFA04: RuleOfFiveTemplated move assignment operator, size = 1000, rhs.size = 1000
ty : lhs : 00FDFA04: size=1000 (8000 BYTES)
tx : rhs : 00FDFA24: size=0 (0 BYTES)

Test Rule Four - Move Constructor
=========================================
00FDF9D4: RuleOfFive move constructor, size = 0, rhs.size = 1000
00FDF9D4: RuleOfFive move assignment operator, size = 0, rhs.size = 1000
a created : lhs : 00FDF9D4: size=1000 (8000 BYTES)
y : rhs : 00FDFA14: size=0 (0 BYTES)
00FDF9C4: RuleOfFiveTemplated move constructor, size = 0, rhs.size = 1000
00FDF9C4: RuleOfFiveTemplated move assignment operator, size = 0, rhs.size = 1000
ta created : lhs : 00FDF9C4: size=1000 (8000 BYTES)
ty : rhs : 00FDFA04: size=0 (0 BYTES)

Test Rule Five - Deconstructors
=========================================
00FDF9C4: RuleOfFiveTemplated destructor, size=1000
00FDF9D4: RuleOfFive deconstuctor
00FDF9E4: RuleOfFiveTemplated destructor, size=1000
00FDF9F4: RuleOfFive deconstuctor
00FDFA04: RuleOfFiveTemplated destructor, size=0
00FDFA14: RuleOfFive deconstuctor
00FDFA24: RuleOfFiveTemplated destructor, size=0
00FDFA34: RuleOfFive deconstuctor
*/