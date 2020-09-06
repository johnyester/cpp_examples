#include <array>
#include <iostream>
#include <algorithm> // for std::sort

/*
std::array<int, 3> myArray; // declare an integer array with length 3

std::array<int, 5> myArray = { 9, 7, 5, 3, 1 }; // initializer list
std::array<int, 5> myArray2 { 9, 7, 5, 3, 1 }; // uniform initialization

std::array myArray { 9, 7, 5, 3, 1 }; // The type is deduced to std::array<int, 5> C++17
std::array myArray { 9.7, 7.31 }; // The type is deduced to std::array<double, 2> C++17

std::array<int, 5> myArray;
myArray = { 0, 1, 2, 3, 4 }; // okay
myArray = { 9, 8, 7 }; // okay, elements 3 and 4 are set to zero!
myArray = { 0, 1, 2, 3, 4, 5 }; // not allowed, too many elements in initializer list!

Accessing std::array values using the subscript operator works just like you would expect:
std::cout << myArray[1] << '\n';
myArray[2] = 6;

std::array supports a second form of array element access (the at() function) that does bounds checking:
std::array myArray { 9, 7, 5, 3, 1 };
myArray.at(1) = 6; // array element 1 is valid, sets array element 1 to value 6
myArray.at(9) = 10; // array element 9 is invalid, will throw an error

The size() function can be used to retrieve the length of the std::array:
std::array myArray { 9.0, 7.2, 5.4, 3.6, 1.8 };
std::cout << "length: " << myArray.size() << '\n';

Because std::array doesn’t decay to a pointer when passed to a function, 
i.e., the size() function will work even if you call it from within a function
*/
namespace jly_tutorials
{
    struct House
    {
        int number{};
        int stories{};
        int roomsPerStory{};
    };

    struct Array
    {
        House value[3]{};
    };

    int main_arrays()
    {
        // With braces, this works.
        Array houses{
            { { 13, 4, 30 }, { 14, 3, 10 }, { 15, 3, 40 } }  // note extra set of braces to ID House eles
        };
        
        std::cout << houses.value[0].number << std::endl;
        std::cout << houses.value[1].stories << std::endl;
        std::cout << houses.value[2].roomsPerStory << std::endl;

        for (const auto& house : houses.value) // note that 'house' is each houses.value - neat way to access
        {
            std::cout << "House number " << house.number
                << " has " << (house.stories * house.roomsPerStory)
                << " rooms\n";
        }

        std::cout << "myArray2{ 7, 3, 1, 9, 5 } sort forward.\n";
        std::array myArray2{ 7, 3, 1, 9, 5 };
        std::sort(myArray2.begin(), myArray2.end()); // sort the array forwards

        for (int element : myArray2)
            std::cout << element << ' ';

        std::cout << '\n';

        std::cout << "myArray2{ 7, 3, 1, 9, 5 } sort reverse\n";

        std::sort(myArray2.rbegin(), myArray2.rend()); // sort the array backwards
        for (int element : myArray2)
            std::cout << element << ' ';

        std::cout << '\n';

        std::cout << "output array, myArray{ 7, 3, 1, 9, 5 }, in reverse order\n";

        std::array myArray{ 7, 3, 1, 9, 5 };

        // Print the array in reverse order.
        for (auto i{ myArray.size() }; i-- > 0; )  // does print [0], test 5, dec, print, test 4, dec, print, ...
            std::cout << myArray[i] << ' ';

        std::cout << '\n';

        for (std::size_t i{ 0 }; i < myArray.size(); ++i)  // array index parameter is std::size_t, not uint/etc.
            std::cout << myArray[i] << ' ';

        std::cout << '\n';

        return 0;
    }
}