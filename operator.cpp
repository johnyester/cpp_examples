/*
* https://en.cppreference.com/w/cpp/language/operators
Overloaded operators
When an operator appears in an expression, and at least one of its operands has a class type or an enumeration type, then overload resolution is used to determine the user-defined function to be called among all the functions whose signatures match the following:

Expression	As member function		As non-member function	Example
@a			(a).operator@ ( )		operator@ (a)			!std::cin calls std::cin.operator!()
a@b			(a).operator@ (b)		operator@ (a, b)		std::cout << 42 calls std::cout.operator<<(42)
a=b			(a).operator= (b)		cannot be non-member	Given std::string s;, s = "abc"; calls s.operator=("abc")
a(b...)		(a).operator()(b...)	cannot be non-member	Given std::random_device r;, auto n = r(); calls r.operator()()
a[b]		(a).operator[](b)		cannot be non-member	Given std::map<int, int> m;, m[1] = 2; calls m.operator[](1)
a->			(a).operator-> ( )		cannot be non-member	Given std::unique_ptr<S> p;, p->bar() calls p.operator->()
a@			(a).operator@ (0)		operator@ (a, 0)		Given std::vector<int>::iterator i;, i++ calls i.operator++(0)
in this table, @ is a placeholder representing all matching operators: all prefix operators in @a, all postfix operators other than -> in a@, all infix operators other than = in a@b

In addition, for comparison operators ==, !=, <, >, <=, >=, <=>, overload resolution also considers the rewritten candidates generated from operator== or operator<=>.

(since C++20)
Note: for overloading co_await, (since C++20)user-defined conversion functions, user-defined literals, allocation and deallocation see their respective articles.
*/

#include<iostream> 
using namespace std;

namespace jly_tutorials
{
    class Complex {
    private:
        int real, imag;
    public:
        Complex(int r = 0, int i = 0) { real = r;   imag = i; std::cout << "Constructor called." << std::endl; }

        // This is automatically called when '+' is used with 
        // between two Complex objects 
        Complex operator + (Complex const& obj) {
            Complex res;
            std::cout << "member function operator+ called." << std::endl;
            res.real = real + obj.real;
            res.imag = imag + obj.imag;
            return res;
        }
        void print(std::string msg = "??") { cout << msg << ' ' << real << " + i" << imag << endl; }

        // the below is not a member of the class and 
        // -> could be declared here as a friend function and defined outside of class def.
        // Since the below is not part of the class def,
        // -> friend is used to give the operator+ access to the private members of Complex
        friend Complex operator+(const Complex& c1, const Complex& c2)
        {
            Complex res;
            std::cout << "global function operator+ called." << std::endl;
            res.real = c1.real + c2.real;
            res.imag = c1.imag + c2.imag;
            return res;

        }

        /*
        Move Assignment operator
        Syntax
        class_name & class_name :: operator= ( class_name && ) [=default;, =delete;]
        The move assignment operator is called whenever it is selected by overload resolution, 
        e.g. when an object appears on the left-hand side of an assignment expression, 
        where the right-hand side is an rvalue of the same or implicitly convertible type.

        https://en.cppreference.com/w/cpp/language/move_assignment
        Implicitly - declared move assignment operator
        If no user - defined move assignment operators are provided for a class type(struct, class, or union), 
        and all of the following is true :
            there are no user - declared copy constructors;
            there are no user - declared move constructors;
            there are no user - declared copy assignment operators;
            there are no user - declared destructors,
        then the compiler will declare a move assignment operator as an inline public member 
        of its class with the signature T& T::operator=(T&&).

         A class can have multiple move assignment operators,
         e.g.both T& T::operator=(const T&&) and T& T::operator=(T&&).
         If some user - defined move assignment operators are present,
         the user may still force the generation of the implicitly declared 
         move assignment operator with the keyword default.

         for an outline of a move constructor and move assignement see: https://docs.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=vs-2019
        T& T::operator=(const T&&) = default;
        T& T::operator=(T&&) = default;

        struct V
        {
            V& operator=(V&& other) {
                // this may be called once or twice
                // if called twice, 'other' is the just-moved-from V subobject
                return *this;
            }
        };
        struct A : virtual V { }; // operator= calls V::operator=
        struct B : virtual V { }; // operator= calls V::operator=
        struct C : B, A { };      // operator= calls B::operator=, then A::operator=
                                  // but they may only call V::operator= once

        int main()
        {
          C c1, c2;
          c2 = std::move(c1);
        }
        */

        /*
        * Syntax
        class_name & class_name :: operator= ( class_name )
        The copy assignment operator is called whenever selected by overload resolution, 
        e.g. when an object appears on the left side of an assignment expression.

         https://en.cppreference.com/w/cpp/language/copy_assignment
        Implicitly - declared copy assignment operator
        If no user - defined copy assignment operators are provided for a class type(struct, class, or union), 
        the compiler will always declare one as an inline public member of the class.
        This implicitly - declared copy assignment operator has the form T & T::operator=(const T&) 
        if all of the following is true :
            each direct base B of T has a copy assignment operator whose parameters are B or const B & or const volatile B&;
            each non - static data member M of T of class type or array of class type has a copy assignment operator whose parameters are M or const M & or const volatile M & .
        Otherwise the implicitly - declared copy assignment operator is declared as T & T::operator=(T&). 
        (Note that due to these rules, the implicitly - declared copy assignment operator cannot bind 
        to a volatile lvalue argument.)
        
         A class can have multiple copy assignment operators, 
        e.g. both T& T::operator=(const T&) and T& T::operator=(T). 
        If some user-defined copy assignment operators are present, 
        the user may still force the generation of the implicitly declared copy assignment operator with the keyword default. 
        */

    };

    void main_operator()
    {

        Complex c1(10, 5), c2(2, 4);
        Complex c3 = c1 + c2; // An example call to "operator+" 
        c3.print("c3");
        Complex c4{ 9 };
        c4.print("c4");
        Complex c5 = c4 + 1;
        c5 = 1 + c4;
        c5.print("c5");
        Complex c6 = c1;
        c4 = Complex(3, 2);
        c6.print("c6");
        Complex c7(c6);
        c6 = c4;
        c6.print("c6");
        c7.print("c7");
    }
}