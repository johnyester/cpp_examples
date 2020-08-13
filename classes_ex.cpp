#include <iostream>
#include <vector>

// https://web.archive.org/web/20160316174223/https://blogs.oracle.com/pcarlini/entry/c_11_tidbits_non_static
namespace jly_tutorials
{

    int main_classes_ex() {
        // Non-static Data Member Initializers
        struct A
        {
            int m;
            A() : m(7) { }
        };

        struct B
        {
            int m = 7;   // non-static data member initializer
        };
        //thus the code :
        A a;
        B b;
        std::cout << a.m << '\n';
        std::cout << b.m << std::endl;
        // prints '7' followed by '7', because both the 'm' member of 'a' and the 'm' member of 'b' are initialized to 7.

        // A non - static data member initializer can be always overridden, thus:
        struct C
        {
            int m = 7;
            C() : m(14) { }
        };
        C c;
        std::cout << c.m << std::endl;

        struct D
        {
            std::vector<int> m{ 4, 5, 6 };
            D() : m({ 2,4,6 }) {}
        };
        // The code :
        D d;
        std::cout << d.m[0] << '\n';
        std::cout << d.m[1] << '\n';
        std::cout << d.m[2] << std::endl;

        return 0;
    }
}