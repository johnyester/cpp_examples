//http://www.cplusplus.com/reference/algorithm/

#include <iostream>     // std::cout
#include <algorithm>    // std::adjacent_find
#include <vector>       // std::vector
#include <array>        // std::array



namespace jly_tutorials
{
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
    //copy_n
    //count
    //count_if
    //equal
    //equal_range
    //fill
    //fill_n
    //find
    //find_end
    //find_first_of
    //find_if
    //find_if_not
    //for_each
    //generate
    //generate_n
    //includes
    //inplace_merge
    //is_heap
    //is_heap_until
    //is_partitioned
    //is_permutation
    //is_sorted
    //is_sorted_until
    //iter_swap
    //lexicographical_compare
    //lower_bound
    //make_heap
    //max
    //max_element
    //merge
    //min
    //minmax
    //minmax_element
    //min_element
    //mismatch
    //move
    //move_backward
    //next_permutation
    //none_of
    //nth_element
    //partial_sort
    //partial_sort_copy
    //partition
    //partition_copy
    //partition_point
    //pop_heap
    //prev_permutation
    //push_heap
    //random_shuffle
    //remove
    //remove_copy
    //remove_copy_if
    //remove_if
    //replace
    //replace_copy
    //replace_copy_if
    //replace_if
    //reverse
    //reverse_copy
    //rotate
    //rotate_copy
    //search
    //search_n
    //set_difference
    //set_intersection
    //set_symmetric_difference
    //set_union
    //shuffle
    //sort
    //sort_heap
    //stable_partition
    //stable_sort
    //swap
    //swap_ranges
    //transform
    //unique
    //unique_copy
    //upper_bound
}
