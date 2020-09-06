/*
* https://www.fluentcpp.com/2017/02/23/predicates-on-ranges-with-the-stl/
The *_of series
The STL provides 3 algorithms that indicates whether all, some, or none of the elements of a range satisfy a given condition. The condition is itself expressed by a predicate, that is to say a function pointer (or object) that take an element of the range and returns a bool.
These 3 algorithms are:
	std::all_of: checks whether all of the elements in the range satisfy the given condition. It returns true if the range is empty, so its semantic is more precisely checking if no element does not satisfy the condition.
	std::any_of: checks whether any one of the elements in the range satisfies the given condition. It returns false if the range is empty.
	std::none_of: checks whether no element in the range satisfy the given condition. It returns true if the range is empty.

This is it for the STL, but Boost goes a bit further and proposes the following algorithm:
	boost::algorithm::one_of: checks whether exactly one element in the range satisfies the given condition. It (quite expectably) returns false if the range is empty.

Boost also provides “*_equal” versions of each of the above algorithms, that accept a range and a value, and have the same behaviour as their native counterpart, with the condition being that the element is equal to the passed value. The comparison is done with operator== and cannot be customised.
	boost::algorithm::all_of_equal: takes a range and a value, and checks if all elements of the range are equal to the value.
	boost::algorithm::any_of_equal: takes a range and a value, and checks if any one element of the range is equal to the value.
	boost::algorithm::none_of_equal: takes a range and a value, and checks if any no element of the range is equal to the value.
	boost::algorithm::one_of_equal: takes a range and a value, and checks if any exactly one element of the range is equal to the value.
And in the case of an empty range, they behave the same way as their native counterparts.

std::equal can be used to compare 2 ranges, checking if elements are respectively equal 
(comparison is done with operator== or with a custom comparator). 
Note that std::equal takes a 1.5-Range, meaning that the first range is indicated by a begin and an end iterator, 
while the second range misses the end iterator:
	template<template InputIterator1, template InputIterator2 >
	bool equal(InputIterator1 first1, InputIterator1 last1,
			   InputIterator2 first2);
- Starting from C++14 this is corrected, with new overloads of std::equal taking 2 complete ranges with both begins and ends.

std::is_permutation
Before C++14, std::is_permutation had an 1.5-Range interface, that is to say that it accepted a begin and end for the first range, and only a begin iterator for the second one:
	std::is_permutation(v1.begin(), v1.end(),
						v2.begin());
std::is_permutation compares elements with operator==, and provides an overload that accepts custom comparators.

std::mismatch and std::lexicographical_compare
std::mismatch compares respective elements of its 2 input ranges starting from their beginning, 
and returns the first place where they differ, in the form of an std::pair of iterators: 
the first element of the pair is an iterator to the first mismatching element in the 1st range, 
and second element of the pair is an iterator to the first mismatching element in the 2nd range.
It performs comparisons with operator== (or a custom comparator).
template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
	std::pair<InputIt1,InputIt2>
		mismatch(InputIt1 first1, InputIt1 last1,
				 InputIt2 first2,
				 BinaryPredicate p);
- just as for std::equal, the 1.5-Range problem is solved for std::mismatch starting from C++14

std::lexicographical_compare actually provides an order on ranges, and operates the same way as a dictionary would provide an order on strings, hence its name. It compares elements two by two with operator< (or a custom comparator).

template<typename InputIt1, typename InputIt2, typename Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
							 InputIt2 first2, InputIt2 last2,
							 Compare comp );
- std::lexicographical_compare takes 2 full ranges so it does not have the 1.5-Range problem.

*/