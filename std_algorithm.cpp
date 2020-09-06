#include <algorithm>
#include <vector>
#include <iostream>
#include <iostream>     // std::cout
#include <algorithm>    // std::adjacent_find
#include <vector>       // std::vector
#include <array>        // std::array

/* copy from container to container
   template <typename InputIterator, typename OutputIterator>
   OutputIterator copy(InputIterator first, InputIterator last, OutputIterator out);

   * explicit loop - BAD
for (std::vector<company::salesForce::Employee>::const_iterator it = employees.begin(); it != employees.end(); ++it)
{
    employeeRegister.push_back(*it);
}
// back_inserter is a convenience function template that
// constructs a std::back_insert_iterator for the container c with the type deduced from the type of the argument.
//
// back_insert_iterator - iterator adaptor for insertion at the end of a container
// front_inserter - creates a std::front_insert_iterator of type inferred from the argument
// inserter - creates a std::insert_iterator of type inferred from the argument
//

    * STL algorithm - GOOD
std::copy(employees.begin(), employees.end(), std::back_inserter(employeeRegister));
*/

/* for_each successively applies a function (or functor or lambda) to all the elements of a collection:
* template <typename InputIterator, typename Function>
    Function for_each(InputIterator first, InputIterator last, Function f);

there is mainly one specific case where for_each is effectively adapted: when performing side effects.

for_each should be used to modify the elements of the collection it is applied on,
or to perform side effects on a more general sense,
like sending information to a logger or to an external service.

*/

/*
Functions in <algorithm>
Non-modifying sequence operations:
all_of - Test condition on all elements in range (function template )
    template<class InputIterator, class UnaryPredicate>
      bool all_of (InputIterator first, InputIterator last, UnaryPredicate pred)
    {
      while (first!=last) {
        if (!pred(*first)) return false;
        ++first;
      }
      return true;
    }
any_of - Test if any element in range fulfills condition (function template )
    template <class InputIterator, class UnaryPredicate>
      bool any_of (InputIterator first, InputIterator last, UnaryPredicate pred);
none_of - Test if no elements fulfill condition (function template )

for_each - Apply function to range (function template )

find - Find value in range (function template )
    template<class InputIterator, class T>
      InputIterator find (InputIterator first, InputIterator last, const T& val)
    {
      while (first!=last) {
        if (*first==val) return first;
        ++first;
      }
      return last;
    }

find_if - Find element in range (function template )
    template <class InputIterator, class UnaryPredicate>
       InputIterator find_if (InputIterator first, InputIterator last, UnaryPredicate pred);
find_if_not - Find element in range (negative condition) (function template )
find_end - Find last subsequence in range (function template )
find_first_of - Find element from set in range (function template )
adjacent_find - Find equal adjacent elements in range (function template )

count - Count appearances of value in range (function template )
count_if - Return number of elements in range satisfying condition (function template )

mismatch - Return first position where two ranges differ (function template )
equal - Test whether the elements in two ranges are equal (function template )
is_permutation - Test whether range is permutation of another (function template )

search - Search range for subsequence (function template )
search_n - Search range for elements (function template )

Modifying sequence operations:
copy - Copy range of elements (function template )
copy_n - Copy elements (function template )
copy_if - Copy certain elements of range (function template )
copy_backward - Copy range of elements backward (function template )

move - Move range of elements (function template )
move_backward - Move range of elements backward (function template )

swap - Exchange values of two objects (function template )
swap_ranges - Exchange values of two ranges (function template )
iter_swap - Exchange values of objects pointed to by two iterators (function template )

transform - Transform range (function template )
    template <class InputIterator, class OutputIterator, class UnaryOperator>
      OutputIterator transform (InputIterator first1, InputIterator last1,
                                OutputIterator result, UnaryOperator op)
    {
      while (first1 != last1) {
        *result = op(*first1);  // or: *result=binary_op(*first1,*first2++);
        ++result; ++first1;
      }
      return result;
    }

replace - Replace value in range (function template )
replace_if - Replace values in range (function template )
replace_copy - Copy range replacing value (function template )
replace_copy_if - Copy range replacing value (function template )

fill - Fill range with value (function template )
fill_n - Fill sequence with value (function template )

generate - Generate values for range with function (function template )
    template <class ForwardIterator, class Generator>
      void generate ( ForwardIterator first, ForwardIterator last, Generator gen )
    {
      while (first != last) {
        *first = gen();
        ++first;
      }
    }
    ex:
        std::vector<int> v(5);
        // Equivalent to std::iota(v.begin(), v.end(), 0);
        std::generate(v.begin(), v.end(), [n = 0] () mutable { return n++; });

generate_n - Generate values for sequence with function (function template )

remove - Remove value from range (function template )
remove_if - Remove elements from range (function template )
remove_copy - Copy range removing value (function template )
remove_copy_if - Copy range removing values (function template )

unique - Remove consecutive duplicates in range (function template )
unique_copy - Copy range removing duplicates (function template )

reverse - Reverse range (function template )
reverse_copy - Copy range reversed (function template )

rotate - Rotate left the elements in range (function template )
rotate_copy - Copy range rotated left (function template )

random_shuffle - Randomly rearrange elements in range (function template )
shuffle - Randomly rearrange elements in range using generator (function template )

Partitions:
is_partitioned - Test whether range is partitioned (function template )
partition - Partition range in two (function template )
stable_partition - Partition range in two - stable ordering (function template )
partition_copy - Partition range into two (function template )
partition_point - Get partition point (function template )

Sorting:
sort - Sort elements in range (function template )
stable_sort - Sort elements preserving order of equivalents (function template )
partial_sort - Partially sort elements in range (function template )
partial_sort_copy - Copy and partially sort range (function template )
is_sorted - Check whether range is sorted (function template )
is_sorted_until - Find first unsorted element in range (function template )
nth_element - Sort element in range (function template )

Binary search (operating on partitioned/sorted ranges):
lower_bound - Return iterator to lower bound (function template )
upper_bound - Return iterator to upper bound (function template )
equal_range - Get subrange of equal elements (function template )
binary_search - Test if value exists in sorted sequence (function template )

Merge (operating on sorted ranges):
merge - Merge sorted ranges (function template )
inplace_merge - Merge consecutive sorted ranges (function template )

includes - Test whether sorted range includes another sorted range (function template )

set_union - Union of two sorted ranges (function template )
set_intersection - Intersection of two sorted ranges (function template )
set_difference - Difference of two sorted ranges (function template )
set_symmetric_difference - Symmetric difference of two sorted ranges (function template )

Heap:
push_heap - Push element into heap range (function template )
pop_heap - Pop element from heap range (function template )
make_heap - Make heap from range (function template )

sort_heap - Sort elements of heap (function template )

is_heap - Test if range is heap (function template )
is_heap_until - Find first element not in heap order (function template )

Min/max:
min - Return the smallest (function template )
max - Return the largest (function template )
minmax - Return smallest and largest elements (function template )
min_element - Return smallest element in range (function template )
max_element - Return largest element in range (function template )
minmax_element - Return smallest and largest elements in range (function template )

Other:
lexicographical_compare - Lexicographical less-than comparison (function template )
next_permutation - Transform range to next permutation (function template )
prev_permutation - Transform range to previous permutation (function template )
*/

namespace jly_tutorials
{
    void main_algorithm_generate()
    {
        std::vector<int> v(5);
        // Equivalent to std::iota(v.begin(), v.end(), 0);
        std::generate(v.begin(), v.end(), [n = 0]() mutable { return n++; });
        for (auto d : v)
            std::cout << d << " ";
        std::cout << std::endl;
    }

    //<algorithm>
    //adjacent_find
    bool my_adjacent_find(int i, int j) {
        return (i == j);
    }

    int main_adjacent_find() {
        int myints[] = { 5,20,5,30,30,20,10,10,20 };
        std::vector<int> myvector(myints, myints + 8);
        std::vector<int>::iterator it;

        // using default comparison:
        it = std::adjacent_find(myvector.begin(), myvector.end());

        if (it != myvector.end())
            std::cout << "the first pair of repeated elements are: " << *it << '\n';

        //using predicate comparison:
        it = std::adjacent_find(++it, myvector.end(), my_adjacent_find);

        if (it != myvector.end())
            std::cout << "the second pair of repeated elements are: " << *it << '\n';

        return 0;
    }
    //all_of
    // all_of example
    int main_all_of() {
        std::array<int, 8> foo = { 3,5,7,11,13,17,19,23 };

        if (std::all_of(foo.begin(), foo.end(), [](int i) {return i % 2; }))
            std::cout << "All the elements are odd numbers.\n";

        return 0;
    }
    //any_of
    // any_of example
    bool my_any_of(int i)
    {
        return i < 0 ? true : false;
    }
    int main_any_of() {
        std::array<int, 7> foo = { 0,1,-1,3,-3,5,-5 };

        if (std::any_of(foo.begin(), foo.end(), [](int i) {return i < 0; }))
            std::cout << "There are negative elements in the range.\n";

        return 0;
    }
    //binary_search
    // binary_search example
    bool my_binary_search(int i, int j) { return (i < j); }

    int main_binary_search() {
        int myints[] = { 1,2,3,4,5,4,3,2,1 };
        std::vector<int> v(myints, myints + 9);                         // 1 2 3 4 5 4 3 2 1

        // using default comparison:
        std::sort(v.begin(), v.end());

        std::cout << "looking for a 3... ";  // looking for a 3... found!
        if (std::binary_search(v.begin(), v.end(), 3))
            std::cout << "found!\n"; else std::cout << "not found.\n";

        // using myfunction as comp:
        std::sort(v.begin(), v.end(), my_binary_search);

        std::cout << "looking for a 6... "; //         looking for a 6... not found.
        if (std::binary_search(v.begin(), v.end(), 6, my_binary_search))
            std::cout << "found!\n"; else std::cout << "not found.\n";

        return 0;
    }
    //copy
    // copy algorithm example
    int main_copy() {
        int myints[] = { 10,20,30,40,50,60,70 };
        std::vector<int> myvector(7);

        std::copy(myints, myints + 7, myvector.begin());

        std::cout << "myvector contains:";  // myvector contains: 10 20 30 40 50 60 70
        for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
            std::cout << ' ' << *it;

        std::cout << '\n';

        return 0;
    }
    //copy_backward
    int main_copy_backward() {
        std::vector<int> myvector;

        // set some values:
        for (int i = 1; i <= 5; i++)
            myvector.push_back(i * 10);          // myvector: 10 20 30 40 50

        myvector.resize(myvector.size() + 3);  // allocate space for 3 more elements

        std::copy_backward(myvector.begin(), myvector.begin() + 5, myvector.end());

        std::cout << "myvector contains:"; // myvector contains: 10 20 30 10 20 30 40 50
        for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';

        return 0;
    }
    //copy_if
    int main_copy_if() {
        std::vector<int> foo = { 25,15,5,-5,-15 };
        std::vector<int> bar(foo.size());

        // copy only positive numbers:
        auto it = std::copy_if(foo.begin(), foo.end(), bar.begin(), [](int i) {return !(i < 0); });
        bar.resize(std::distance(bar.begin(), it));  // shrink container to new size

        std::cout << "bar contains:";  // bar contains: 25 15 5
        for (int& x : bar) std::cout << ' ' << x;
        std::cout << '\n';

        return 0;
    }
}