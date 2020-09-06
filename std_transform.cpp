/*
single range prototype:
template<typename InputIterator, typename OutputIterator, typename UnaryOperation>
OutputIterator transform(InputIterator first1, InputIterator last1,
                         OutputIterator result,
                         UnaryOperation op);

For example, to obtain the keys that a map contains, you can use std::transform the following way:
    map<int, string> m = { {1,"foo"}, {42, "bar"}, {7, "baz"} };
    vector<int> keys;
    std::transform(m.begin(), m.end(), std::back_inserter(keys), getFirst);
- where getFirst is a (non-standard) function that takes a pair and returns its first element. And std::back_inserter used above is an output iterator that does a push_back into the container it is passed, every time it is assigned to.

two range prototype:
    template<typename InputIterator1, typename InputIterator2, typename OutputIterator, typename BinaryOperation>
    OutputIterator transform(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2,
                             OutputIterator result,
                             BinaryOperation op);
add two ranges of ints by summing together their respective elements:
    vector<int> numbers1 = {1, 5, 42, 7, 8};
    vector<int> numbers2 = {10, 7, 4, 2, 2};
    vector<int> results;
    std::transform(numbers1.begin(), numbers1.end(),
                   numbers2.begin(),
                   std::back_inserter(results),
                   [](int i, int j) {return i+j;});

std::transform in place
The output range can be either of the 2 input ranges. In that case the range is transformed “in place”.


** The Difference between for_each and transform
* https://www.drdobbs.com/effective-standard-c-library-foreach-vs/184403769
The algorithms for_each and transform are often understood as very similar in that 
they apply an operation (supplied as a function object) to each element in an input range. 
The difference is that for_each discards the operation's return value, 
while transform copies the return value to an element in the output range. 
This kind of understanding is a fairly common oversimplification. 
According to the Standard, however, the difference between both algorithms is more fundamental. 

    FOR_EACH. The for_each algorithm is specified in the Standard in the section of non-modifying sequence operations.
        template<class InputIterator, class Function>
        Function for_each(InputIterator first, InputIterator last, Function f);
        Effects: 
            Applies f to the result of dereferencing every iterator in the range [first, last), 
            starting from first and proceeding to last - 1.

            Returns: f
            Complexity: Applies f exactly last - first times.
            Notes: If f returns a result, the result is ignored.

    TRANSFORM. The transform algorithm is specified in the Standard in the section of mutating sequence operations. 
    It comes in two flavors, one version (unary transform) works on one input sequence, 
    the other version (binary transform) takes two input sequences. 
    - Since we want to compare for_each and transform, we only consider the unary transform.
        template<class InputIterator, class OutputIterator, class UnaryOperation>
        OutputIterator transform(InputIterator first, InputIterator last,
                                 OutputIterator result, UnaryOperation op);
        Effects: 
            Assigns through every iterator i in the range [result, result + (last - first)) 
            a new corresponding value equal to op(*(first + (i - result)).
            Requires: op shall not have any side effects [2].
            Returns: result + (last - first)
            Complexity: Exactly last - first applications of op.
            Notes: result may be equal to first.

* Alternate description of differences between transform and for_each:
There are actually 2 main differences, one is technical and relatively not important in practice,
and the other one is more important:
    the not important, technical one: from a standard point of view,
    for_each offers more guarantees than transform, namely:
        the range is traversed in order from the first element to the last,
        the function (or function object) is not copied during the traversal.

        As a consequence, you could theoretically control state in your function object with for_each.
        But in general you don’t really want state in your functors anyway.

    the important one: for_each and transform just don’t do the same thing on a given element:
        for_each applies a function on the element,
        transform applies a function on the element, *and* assigns the result back to the element.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

namespace jly_tutorials
{
    /*
    Hello World!
    2
    4
    6
    8
    10
    11
    22
    33
    44
    55
    11.100000
    22.200001
    33.299999
    44.400002
    55.500000
    */
    int main_transform() {

        auto values = std::vector<int>{ 1,2,3,4,5 };
        auto doubleValues = std::vector<int>{};

        //std::back_inserter returns std::back_insert_iterator that uses Container::push_back().
        std::transform(values.begin(), values.end(), std::back_inserter(doubleValues), [](int number) {return 2 * number; });

        std::for_each(doubleValues.begin(), doubleValues.end(), [](int number) { std::cout << number << "\n"; });

        // binary transform
        auto otherValues = std::vector<int>{ 10,20,30,40,50 };
        auto results = std::vector<int>{};
        std::transform(values.begin(), values.end(), otherValues.begin(), std::back_inserter(results), [](int number, int otherNumber) { return number + otherNumber; });

        std::for_each(results.begin(), results.end(), [](int number) { std::cout << number << "\n"; });

        // binary transform using different data types
        auto otherValuesf = std::vector<float>{ 10.1f,20.2f,30.3f,40.4f,50.5f };
        auto resultss = std::vector<std::string>{};
        std::transform(
            values.begin(), values.end(), 
            otherValuesf.begin(), 
            std::back_inserter(resultss), 
            [](int number, float otherNumber) {return std::to_string(number + otherNumber); });

        std::for_each(resultss.begin(), resultss.end(), [](const std::string& number) { std::cout << number << "\n"; });

        return 0;
    }
}