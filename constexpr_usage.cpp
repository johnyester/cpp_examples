#include <iostream>

namespace jly_tutorials
{
    // constexpr specifies that the value of an object or a function can be evaluated at compile time and the expression can be used in other constant expressions.For example, in below code product() is evaluated at compile time.

    // constexpr function for product of two numbers. 
    // By specifying constexpr, we suggest compiler to  
    // to evaluate value at compile time 
    constexpr int product(int x, int y)
    {
        return (x * y);
    }

    constexpr long int fib(int n)
    {
        return (n <= 1) ? n : fib(n - 1) + fib(n - 2);
    }

    // A class with constexpr constructor and function
    class Rectangle
    {
        int _h, _w;
    public:
        // A constexpr constructor 
        constexpr Rectangle(int h, int w) : _h(h), _w(w) {}

        constexpr int getArea() { return _h * _w; }
    };

    constexpr unsigned int factorial(unsigned int n)
    {
        return (n <= 1) ? 1 : (n * factorial(n - 1));
    }

    // https://www.modernescpp.com/index.php/constexpr-functions
    constexpr auto gcd_while(int a, int b) {
        while (b != 0) {
            auto t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    constexpr int gcd_recursive(int a, int b) {
        return (b == 0) ? a : gcd_recursive(b, a % b);
    }


    int main_constexpr_usage()
    {
        const int x = product(10, 20);
        std::cout << x;

        const long int res = fib(30);  // done at compile time. - w/o const it become run time
        std::cout << res;

        /*
        //constexpr does not work for:
        constexpr Rectangle obj(10, 20);

        //Error	C2662	'int jly_tutorials::Rectangle::getArea(void)': 
        // cannot convert 'this' pointer from 'const jly_tutorials::Rectangle' to 
        // 'jly_tutorials::Rectangle &'	
        std::cout << obj.getArea();
        */

        static constexpr auto magic_value = factorial(5);

        return 0;
    }
}