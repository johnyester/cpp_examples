/*
* https://www.fluentcpp.com/2017/03/23/filling-algorithms-stl/
** std::fill and std::uninitialized_fill

* std::fill takes a range and a value, and sets all elements of the range as equal to this value.

    vector<int> v = {1, 2, 3, 4, 5};
    fill(v.begin(), v.end(), 3);
    // v contains {3, 3, 3, 3, 3};

=> std::fill calls operator= on each element.

* std::uninitialized_fill does essentially the same thing, 
but it takes a range of memory that has been allocated but not initialized 
(for instance with operator new, malloc, or a custom memory allocator).

This algorithm performs the initialization of each element with the passed value,
which means that it calls its constructor taking a value of this type. 
=> So std::uninitialized_fill does not call operator=.

The following example illustrates how std::uninitialized_fill can be used:
    class MyClass
    {
    public:
        explicit MyClass(int i);
    private:
        int i_;
    };

    // Allocate a buffer that can contain 5 objects of MyClass
    MyClass* myObjects = static_cast<MyClass*>(malloc(5 * sizeof(MyClass)));

    // Call constructor on each object, with value 3
    std::uninitialized_fill(myObjects, myObjects + 5, 3);

    // Use myObjects...

    // Call destructor on each object
    std::for_each(myObjects, myObjects + 5, [](const MyClass& object){object.~MyClass();});

    // Deallocate the buffer
    free(myObjects);
    myObjects = nullptr;

This is conceptually very similar to an placement new in an array, 
but without the drawbacks associated to the unknown size allocated 
in arrays by the compiler for bookkeeping.

** std::generate and std::iota
* std::generate takes a range and a function (or function object) callable with no parameter, 
and assigns to each element of the range the value returned by a call to the function.

Its canonical example of usage is filling a range with random values :
    int getRandomNumber();

    vector<int> v = {1, 2, 3, 4, 5};
    generate(v.begin(), v.end(), getRandomNumber);
    // v may contain {7, 257, -3, 18, -44};

* std::iota fills a range with incremental values obtained with prefix operator++, starting from a given value:
    vector<int> = {1, 2, 3, 4, 5};
    iota(v.begin(), v.end(), 10);
    // v now contains {10, 11, 12, 13, 14}

** _n algorithms
std::fill, std::uninitialized_fill and std::generate have *_n couterparts, 
namely std::fill_n, std::uninitialized_n and std::generate_n, 
that take an output iterator, along with a size.

    template <typename OutputIterator, class Size, class T>
    OutputIterator fill_n(OutputIterator first, Size count, const T& value);

These algorithms are useful if you need to fill the first n elements of your collection:
    std::vector<char> v = {'h', 'e', 'l', 'l', 'o', '!'};
    std::fill_n(begin(v), 3, 'a');
    // v contains {'a', 'a', 'a', 'l', 'o', '!'};

They can also be used to append several identical values to a collection. For instance std::generate_n can typically be used to fill out a empty collection with random numbers:
    int randomNumberGenerator()
    {
        static std::random_device random_device;
        static std::mt19937 engine{random_device()};
        static std::uniform_int_distribution<> distribution(1,6);
        return distribution(engine);
    }

    std::vector<int> numbers;
    std::generate_n(std::back_inserter(numbers), 10, randomNumberGenerator);
    // numbers may now contain {4, 1, 1, 6, 6, 3, 2, 5, 4, 1}

** Containers methods
vector, deque, list and string have methods that can fill them with values: their constructor, and their assign method.
The constructor can be used that way:
    vector<string> v(3, "hello");
    // vector now contains {“hello”, “hello”, “hello”},
Here, the vector constructs one string from the passed value (“hello”), 
and then creates the other elements by copy-constructing from that string

The assign method constructs one object from the passed value, 
then calls operator= on each element to assign it with this constructed object:
    vector<string> v;
    v.assign(3, “hello”);
    // vector now contains {“hello”, “hello”, “hello”},
*/