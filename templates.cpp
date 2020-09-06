#include <iostream>

/*
For naming template parameters, typename and class are equivalent. §14.1.2:
    There is no semantic difference between class and typename in a template-parameter.
*/
namespace jly_tutorials
{
    // https://www.learncpp.com/cpp-tutorial/132-function-template-instances/

    // function template
    template <typename T> // this is the template parameter declaration
    const T& max(const T& x, const T& y)
    {
        return (x > y) ? x : y;
    }

    // function template
    template <class T>
    T average(T* array, int length)
    {
        T sum(0);

        for (int count{ 0 }; count < length; ++count)
            sum += array[count];

        sum /= length;
        return sum;
    }

    // class to use function templates, overload operators are used to make things work.
    class Cents
    {
    private:
        int m_cents;
    public:
        Cents(int cents)
            : m_cents{ cents }
        {
        }

        friend bool operator>(const Cents& c1, const Cents& c2)
        {
            return (c1.m_cents > c2.m_cents);
        }

        friend std::ostream& operator<< (std::ostream& out, const Cents& cents)
        {
            out << cents.m_cents << " cents ";
            return out;
        }
        

        Cents operator+(const Cents& cents)
        {
            Cents ans{ 0 };
            ans.m_cents =  m_cents + cents.m_cents;
            return ans;
        }

        Cents& operator+=(const Cents& cents)
        {
            m_cents += cents.m_cents;
            return *this;
        }

        Cents& operator/=(int value)
        {
            m_cents /= value;
            return *this;
        }

        friend Cents operator+(const Cents& cents1, const Cents& cents2)
        {
            return cents1.m_cents + cents2.m_cents;
        }

    };



    int main_templates()
    {
        double d{ max(6.34, 18.523) }; // calls max(double, double)

        Cents nickle{ 5 };
        Cents dime{ 10 };

        Cents bigger{ max(nickle, dime) };

        int array1[]{ 5, 3, 2, 1, 4 };
        std::cout << average(array1, 5) << '\n';

        double array2[]{ 3.12, 3.45, 9.23, 6.34 };
        std::cout << average(array2, 4) << '\n';

        Cents array3[]{ Cents(5), Cents(10), Cents(15), Cents(14) };
        std::cout << average(array3, 4) << '\n';
        
        Cents nd = nickle + dime;
        std::cout << "nd = nickle+dime " << nd << std::endl;

        std::cout << "nickle+dime " << nickle + dime << std::endl;


        return 0;
    }

    // Class template with two parameters 
    template<typename T1, typename T2>
    class Test
    {
        T1 a;
        T2 b;
    public:
        Test(T1 x, T2 y)
        {
            a = x;
            b = y;
        }
        void show()
        {
            std::cout << a << " and " << b << std::endl;
        }
    };

    // Main Function 
    int main_template_multiparam()
    {
        // instantiation with float and int type 
        Test <float, int> test1(1.23f, 123);  // 1.23f because 1.23 is a double.

        // instantiation with float and char type 
        Test <int, char> test2(100, 'W');

        /*
        1.23 and 123
        100 and W
        */
        test1.show();
        test2.show();

        return 0;
    }
}