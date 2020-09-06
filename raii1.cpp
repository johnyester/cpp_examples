#include <algorithm>
#include <iostream>

// https://cpppatterns.com/patterns/copy-and-swap.html
// https://cpppatterns.com/patterns/rule-of-five.html
// https://en.cppreference.com/w/cpp/language/rule_of_three
// https://www.fluentcpp.com/2019/04/19/compiler-generated-functions-rule-of-three-and-rule-of-five/
/*
a default constructor: X()
a copy constructor: X(const X&)
a copy assignment: operator=(const X&)
a move constructor: X(X&&)
a move assignment: operator=(X&&)
a destructor: ~X()
*/

/*
the rule of three specifies that if a 
class implements any of the following functions, 
it should implement all of them:
	copy constructor
	copy assignment operator
	destructor
These functions are usually required only when a 
class is manually managing a dynamically allocated resource, 
and so all of them must be implemented to manage the resource safely.

the rule of five identifies that it usually appropriate 
to also provide the following functions to 
allow for optimized copies from temporary objects:
	move constructor
	move assignment operator

C.20: If you can avoid defining any default operations, do
This rule is also known as "the rule of zero". 
That means, if your class needs no default operations because 
all its members have the six special functions, you are done.

C.21: If you define or =delete any default operation, define or =delete them all

*/

namespace jly_tutorials
{
	// building this class based on reading to learn to implement rule of five.
	// need to fix copy and implement move & delete
	// see rule_of_five2.cpp for a good example
	class NaiveVector {
	public:
		int* ptr_;
		size_t size_;

		// default constructor: X()
		NaiveVector() : ptr_(nullptr), size_(0) {}

		// destructor: ~X()
		~NaiveVector() { delete[] ptr_; }

		// copy constructor: X(const X&)
		NaiveVector(const NaiveVector& rhs) {
			ptr_ = new int[rhs.size_];
			size_ = rhs.size_;
			std::copy(rhs.ptr_, rhs.ptr_ + size_, ptr_);
		}

		// https://www.geeksforgeeks.org/copy-swap-idiom-c/
		friend void swap(NaiveVector& obj1, NaiveVector& obj2) {
			std::swap(obj1.size_, obj2.size_);
			std::swap(obj1.ptr_, obj2.ptr_);
		}

		// copy assignment: operator=(const X&)
		NaiveVector& operator=(const NaiveVector& rhs) {
			NaiveVector copy = rhs;
			swap(*this, copy);
			return *this;
		}
	};

	void show_container(NaiveVector rhs) {
		std::cout << "size: " << rhs.size_ << std::endl;
		if (rhs.size_ < 1) {
			std::cout << "error: container is empty." << std::endl;
			return;
		}
		for (size_t i = 0; i < rhs.size_; i++) {
			std::cout << rhs.ptr_[i] << std::endl;
		}

	}

	void main_raii1() {
		NaiveVector nvec;
		show_container(nvec);

		NaiveVector nvec1 = nvec;
		show_container(nvec1);
	}

	// https://www.modernescpp.com/index.php/c-core-guidelines-constructors-assignments-and-desctructors
	// does have poor copy behavior on shallow copy. See next example for fix.
	struct Strange {

		Strange() : p(new int(2011)) {}

		// deep copy 
		Strange(const Strange& a) : p(new int(*(a.p))) {}    // (1)

		// shallow copy - this can cause problems if one of the copies gets deleted before the other.
		Strange& operator=(const Strange& a) {               // (2)
			p = a.p;
			return *this;
		}

		int* p;

	};

	/*
		Deep copy - Strange s2(s1)
		s1.p: 01768A98; *(s1.p): 2011
		s2.p: 01768BB0; *(s2.p): 2011
		*(s2.p) = 2017
		s1.p: 01768A98; *(s1.p): 2011
		s2.p: 01768BB0; *(s2.p): 2017

		Shallow copy - Strange s3 = s1
		s1.p: 01768A98; *(s1.p): 2011
		s3.p: 0176A7C8; *(s3.p): 2011
		*(s3.p) = 2017
		s1.p: 01768A98; *(s1.p): 2011
		s3.p: 0176A7C8; *(s3.p): 2017

		delete s1.p
		s2.p: 01768BB0; *(s2.p): 2017
		s3.p: 0176A7C8; *(s3.p): 2017
	*/
	int main_ruleof6() {

		std::cout << std::endl;

		std::cout << "Deep copy - Strange s2(s1)" << std::endl;

		Strange s1;
		Strange s2(s1);                                     // (3)

		std::cout << "s1.p: " << s1.p << "; *(s1.p): " << *(s1.p) << std::endl;
		std::cout << "s2.p: " << s2.p << "; *(s2.p): " << *(s2.p) << std::endl;

		std::cout << "*(s2.p) = 2017" << std::endl;
		*(s2.p) = 2017;                                     // (4)

		std::cout << "s1.p: " << s1.p << "; *(s1.p): " << *(s1.p) << std::endl;
		std::cout << "s2.p: " << s2.p << "; *(s2.p): " << *(s2.p) << std::endl;

		std::cout << std::endl;

		std::cout << "Shallow copy - Strange s3 = s1" << std::endl;

		Strange s3 = s1;                                            // (5)

		std::cout << "s1.p: " << s1.p << "; *(s1.p): " << *(s1.p) << std::endl;
		std::cout << "s3.p: " << s3.p << "; *(s3.p): " << *(s3.p) << std::endl;


		std::cout << "*(s3.p) = 2017" << std::endl;
		*(s3.p) = 2017;                                     // (6)

		std::cout << "s1.p: " << s1.p << "; *(s1.p): " << *(s1.p) << std::endl;
		std::cout << "s3.p: " << s3.p << "; *(s3.p): " << *(s3.p) << std::endl;

		std::cout << std::endl;

		std::cout << "delete s1.p" << std::endl;
		delete s1.p;                                        // (7)

		std::cout << "s2.p: " << s2.p << "; *(s2.p): " << *(s2.p) << std::endl;
		std::cout << "s3.p: " << s3.p << "; *(s3.p): " << *(s3.p) << std::endl;

		std::cout << std::endl;

		return 0;
	}

	////////////////////////////////
	// https://medium.com/@prafullkumar77/the-rule-of-three-and-five-c-9f31645e38ac
	class CPPR5Class
	{
	public:
		// Default constructor 
		CPPR5Class() :
			data(new char[14])
		{
#pragma warning(suppress : 4996)
			std::strcpy(data, "Hello, World!");
		}

		// Copy constructor 
		CPPR5Class(const CPPR5Class& original) :
			data(new char[std::strlen(original.data) + 1])
		{
#pragma warning(suppress : 4996)
			std::strcpy(data, original.data);
		}

		// Move constructor 
		CPPR5Class(CPPR5Class&& original) noexcept : /* noexcept needed to enable optimizations in containers */
			data(original.data)
		{
			original.data = nullptr;
		}

		// Destructor 
		~CPPR5Class() noexcept /* explicitly specified destructors should be annotated noexcept as best-practice */
		{
			delete[] data;
		}

		// Copy assignment operator 
		CPPR5Class& operator= (const CPPR5Class& original)
		{
			CPPR5Class tmp(original);         // re-use copy-constructor
			*this = std::move(tmp); // re-use move-assignment
			return *this;
		}

		// Move assignment operator 
		CPPR5Class& operator= (CPPR5Class&& original) noexcept
		{
			if (this == &original)
			{
				// take precautions against `CPPR5Class = std::move(CPPR5Class)`
				return *this;
			}
			delete[] data;
			data = original.data;
			original.data = nullptr;
			return *this;
		}

	private:
		friend std::ostream& operator<< (std::ostream& os, const CPPR5Class& cPPR5Class)
		{
			os << cPPR5Class.data;
			return os;
		}

		char* data;
	};

	int main_medium_ruleof5()
	{
		const CPPR5Class cPPR5Class;
		std::cout << cPPR5Class << std::endl;

		return 0;
	}
};
