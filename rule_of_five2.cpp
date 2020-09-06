#include <string>
#include <cstdio>
#include <iostream>

using namespace std;

namespace jly_tutorials
{
    // https://en.cppreference.com/w/cpp/language/rule_of_three

    class rule_of_five
    {
        char* cstring; // raw pointer used as a handle to a dynamically-allocated memory block
    public:
        rule_of_five(const char* s = "")
            : cstring(nullptr)
        {
            if (s) {
                std::size_t n = std::strlen(s) + 1;
                cstring = new char[n];      // allocate
                std::memcpy(cstring, s, n); // populate 
            }
        }

        ~rule_of_five()
        {
            delete[] cstring;  // deallocate
        }

        rule_of_five(const rule_of_five& other) // copy constructor
            : rule_of_five(other.cstring)
        {}

        rule_of_five(rule_of_five&& other) noexcept // move constructor
            : cstring(std::exchange(other.cstring, nullptr))
        {}

        rule_of_five& operator=(const rule_of_five& other) // copy assignment
        {
            return *this = rule_of_five(other);
        }

        rule_of_five& operator=(rule_of_five&& other) noexcept // move assignment
        {
            std::swap(cstring, other.cstring);
            return *this;
        }

        // alternatively, replace both assignment operators with 
        //  rule_of_five& operator=(rule_of_five other) noexcept
        //  {
        //      std::swap(cstring, other.cstring);
        //      return *this;
        //  }
    };

    class rule_of_zero
    {
        std::string cppstring;
    public:
        rule_of_zero(const std::string& arg) : cppstring(arg) {}
    };

    class base_of_five_defaults
    {
    public:
        base_of_five_defaults(const base_of_five_defaults&) = default;
        base_of_five_defaults(base_of_five_defaults&&) = default;
        base_of_five_defaults& operator=(const base_of_five_defaults&) = default;
        base_of_five_defaults& operator=(base_of_five_defaults&&) = default;
        virtual ~base_of_five_defaults() = default;
    };


    // another reasonable example of the rule of five
    // https://cpppatterns.com/patterns/rule-of-five.html
    /*
    The copy and move assignment operators in the example code provide only basic exception safety.
    They may alternatively be implemented with the copy-and-swap idiom, https://cpppatterns.com/patterns/copy-and-swap.html
    which provides strong exception safety at an optimisation cost.
    */
    class resource {
    public:
        resource() : x(-1) {}
        resource(int v) : x(v) {}
        int x;
    };
    class rule_of_five2
    {
    public:
        rule_of_five2()
            : p{ new resource{} }
        { }

        rule_of_five2(int v)
            : p{ new resource(v)}
        { }
        // copy constructor
        rule_of_five2(const rule_of_five2& other)
            : p{ new resource{*(other.p)} }
        { }

        // move constructor
        rule_of_five2(rule_of_five2&& other) noexcept
            : p{ other.p } 
        {
            other.p = nullptr;
        }

        /* copy-and-swap alternative for copy & move assignment
        * foo& operator=(foo other) // takes its argument by value
        {
          swap(*this, other);
          return *this;
        }
        friend void swap(foo& first, foo& second)
        {
          using std::swap;
          swap(first.p, second.p);
        }
        */
        // copy assignment operator - by reference, 
        rule_of_five2& operator=(const rule_of_five2& other)
        {
            if (&other != this) {
                delete p;
                p = nullptr;
                p = new resource{ *(other.p) };
            }
            return *this;
        }

        // move assignment operator - by value?/rhs?
        rule_of_five2& operator=(rule_of_five2&& other) noexcept
        {
            if (&other != this) {
                delete p;
                p = other.p;
                other.p = nullptr;
            }
            return *this;
        }

        void print() {
            std::cout << p << std::endl;
        }
        // destructor 
        ~rule_of_five2()
        {
            std::cout << "destructor called" << std::endl;
            delete p;
        }
        resource* p;
    };

    void main_rule_of_five2()
    {
        cout << "Rule Of Five" << endl << endl;

        // Test Default Constructors
        cout << endl << "Testing Default Constructor" << endl << "=========================================" << endl;

        rule_of_five2 x;
        cout << "x created : ";
        x.print();

        // Test Constructor Overloads
        cout << endl << "Testing Constructor Overloads" << endl << "=========================================" << endl;

        rule_of_five2 y(1000);
        cout << "y created : ";
        y.print();

        // Test Copy Assignment operator
        cout << endl << "Test Rule One - Copy Assignment operator" << endl << "=========================================" << endl;

        x = y;
        cout << "x : lhs : ";
        x.print();
        cout << "y : rhs : ";
        y.print();

        // Test Copy Constructor
        cout << endl << "Test Rule Two - Copy Constructor" << endl << "=========================================" << endl;

        rule_of_five2 z(x);
        cout << "z created : lhs : ";
        z.print();
        cout << "x : rhs : ";
        x.print();


        // Test Move Assignment operator
        cout << endl << "Test Rule Three - Move Assignment operator" << endl << "=========================================" << endl;

        y = std::move(x);
        cout << "y : lhs : ";
        y.print();
        cout << "x : rhs : ";
        x.print();

        // Test Move Constructor
        cout << endl << "Test Rule Four - Move Constructor" << endl << "=========================================" << endl;

        rule_of_five2 a(std::move(y));
        cout << "a created : lhs : ";
        a.print();
        cout << "y : rhs : ";
        y.print();

        // Test Deconstructors
        cout << endl << "Test Rule Five - Deconstructors" << endl << "=========================================" << endl;
    }
}