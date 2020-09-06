/*
Functions
Iterator operations:
advance - Advance iterator (function template )
distance - Return distance between iterators (function template )
begin - Iterator to beginning (function template )
end - Iterator to end (function template )
prev - Get iterator to previous element (function template )
next - Get iterator to next element (function template )

Iterator generators:
back_inserter - Construct back insert iterator (function template )
front_inserter - Constructs front insert iterator (function template )
inserter - Construct insert iterator (function template )
make_move_iterator - Construct move iterator (function template )

Classes
iterator - Iterator base class (class template )
iterator_traits - Iterator traits (class template )

Predefined iterators
reverse_iterator - Reverse iterator (class template )
move_iterator - Move iterator (class template )
back_insert_iterator - Back insert iterator (class template )
front_insert_iterator - Front insert iterator (class template )
insert_iterator - Insert iterator (class template )
istream_iterator - Istream iterator (class template )
ostream_iterator - Ostream iterator (class template )
istreambuf_iterator - Input stream buffer iterator (class template )
ostreambuf_iterator - Output stream buffer iterator (class template )

Category tags
input_iterator_tag - Input iterator category (class )
output_iterator_tag - Output iterator category (class )
forward_iterator_tag - Forward iterator category (class )
bidirectional_iterator_tag - Bidirectional iterator category (class )
random_access_iterator_tag - Random-access iterator category (class )
*/
// inserter example

#include <iostream>     // std::cout
#include <iterator>     // std::front_inserter
#include <list>         // std::list
#include <algorithm>    // std::copy
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <string>
#include <iostream>
#include <iostream>
#include <fstream>
#include <numeric>  // for accumulate()
#include <iterator>  

using namespace std;

namespace jly_tutorials
{
	int main_iterator_copy() {
		std::list<int> foo, bar;
		for (int i = 1; i <= 5; i++)
		{
			foo.push_back(i); bar.push_back(i * 10);
		}

		std::list<int>::iterator it = foo.begin();
		advance(it, 3);

		// std:inserter
		// template <class Container, class Iterator>
		// insert_iterator<Container> inserter(Container & x, Iterator it);
		std::copy(bar.begin(), bar.end(), std::inserter(foo, it));

		std::cout << "foo contains:";
		for (std::list<int>::iterator it = foo.begin(); it != foo.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';

		return 0;
	}

	/*
Types of iterators:
	Based upon the functionality of the iterators, they can be classified into five major categories:
Input Iterators:
	They are the weakest of all the iterators and have very limited functionality.
	They can only be used in a single-pass algorithms, i.e., those algorithms which
	process the container sequentially, such that no element is accessed more than once.
Output Iterators:
	Just like input iterators, they are also very limited in their functionality
	and can only be used in single-pass algorithm, but not for accessing elements,
	but for being assigned elements.
Forward Iterator:
	They are higher in the hierarachy than input and output iterators,
	and contain all the features present in these two iterators.
	But, as the name suggests, they also can only move in a forward direction and that too one step at a time.
Bidirectional Iterators:
	They have all the features of forward iterators along with the fact that
	they overcome the drawback of forward iterators, as they can move in both
	the directions, that is why their name is bidirectional.
Random-Access Iterators:
	They are the most powerful iterators. They are not limited to moving sequentially,
	as their name suggests, they can randomly access any element inside the container.
	They are the ones whose functionality are same as pointers.
*/


	int main_iterators()
	{
		vector<int> myIntVector;
		vector<int>::iterator myIntVectorIterator;

		// Add some elements to myIntVector
		myIntVector.push_back(1);
		myIntVector.push_back(4);
		myIntVector.push_back(8);
		cout << "old way ...\n";
		for (myIntVectorIterator = myIntVector.begin();
			myIntVectorIterator != myIntVector.end();
			myIntVectorIterator++)
		{
			cout << *myIntVectorIterator << " ";
			//Should output 1 4 8
		}
		cout << endl;
		for (auto& i : myIntVector) {
			cout << i << " ";
		}
		cout << endl;
		return 0;
	}

	// examples below are from https://www.bogotobogo.com/cplusplus/stl3_iterators.php
	int main_oneway_iterators()
	{
		/*
		The data file:
		1 2 3 4 5 6 7 8 9 10
		Output:
		Sum of the data is 55
		*/
		ifstream myInt("data");
		istream_iterator<int> iter(myInt); // initialization constructor - constructs iterator associated with stream.
		istream_iterator<int> eos;  // default constructor - constructs an end of stream iterator

		cout << "Sum of the data is "
			<< accumulate(iter, eos, 0)  // accumulate(input_iter, input_iter, value)
			<< endl;
		return 0;
	}

	/*
	Forward Iterators
		Forward iterators use only the ++ operators for navigating through a container.
		So a forward iterator can only go forward through a container one element at a time.
		Unlike input and output iterators, however, it necessarily goes through a sequence
		of values in the same order each time we use it.
	*/
	template<typename ForwardIterator>
	void square(ForwardIterator first, ForwardIterator last)
	{
		cout << "Squares:  ";
		for (; first != last; first++) {
			*first = (*first) * (*first);
			cout << *first << " ";
		}
		cout << endl;
	}
	int main_forward_iterators()
	{
		int arr[] = { 1, 2, 3, 4, 5 };

		vector<int> v(arr, arr + sizeof(arr) / sizeof(arr[0]));

		cout << "Elements: ";
		for (auto it : v) {
			cout << it << " ";
		}
		cout << endl;

		square(v.begin(), v.end());

		return 0;
	}

	template<typename Bidirectional>
	bool isPalindrome(Bidirectional first, Bidirectional last)
	{
		while (true)
		{
			last--;

			// when a character is a space, skip it
			if (*last == ' ') last--;
			if (*first == ' ') first++;
			if (first == last)
				break;

			// case insensitive comparison
			if (tolower(*first) != tolower(*last))
				return false;

			first++;

			if (first == last)
				break;
		}
		return true;
	}

	int main_bidirectional_iterators()
	{
		string s[] = { "Never odd or even",
					  "No lemon, no melon",
					  "telnet",
					  "reviver" };

		for (int i = 0; i < 4; i++) {
			cout << s[i] << " - is a palidrome:"
				<< isPalindrome(s[i].begin(), s[i].end()) << endl;
		}
		return 0;
	}

	int main_const_iterators()
	{
		vector<int> v(10, 0);

		// iterator
		vector<int>::iterator it;
		it = v.begin(); //ok
		*it = 911; // ok
		it++; //ok

		// const_iterator
		vector<int>::const_iterator cit;
		cit = v.begin();
		// *cit = 911; // Error: cannot assign to a variable that is const
		cit++; // ok

		// iterator that is constant
		const vector<int>::iterator itc = v.begin();
		// itc = v.begin();  // Can't assign a new value
		*itc = 911;  // ok: itc can change its underlying element
		// itc++; // Error: can't change the value of itc

		return 0;
	}

	int main_example_iterators()
	{
		/*
		The output is:
			sets in ascending order 1 2 3 4 5 6
			sets in descending order 6 5 4 3 2 1
			multi sets in ascending order
			1 1 2 3 4 5 6
			multi maps in ascending order
			(1,this)(1,is)(2,a)(3,map)(4,of)(5,tagged)(6,strings)
			Associate Array: an array in which the index
			may be of an arbitrary type
			string-float map
			key: "Null" value: 0
			key: "PI" value: 3.1415
			key: "an arbitrary number" value: 4983.22
			vector, list & deque1 2 3 4 5 6
			6.6 5.5 4.4 3.3 2.2 1.1
			 using constant iterator
			a b c d e f g h i j k l m n o p q r s t u v w x y z
			 using non_constant iterator
			A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
			 list output using while
			A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
		*/
		set<int> col_set;
		set<int, greater<int> > col_set2;
		multiset<int> col_mset;
		multimap<int, string> col_mmap;
		map<string, float> col_sfmap;
		vector<int> col_vec;
		deque<float> col_deque;
		list<char> col_list;

		col_set.insert(3);
		col_set.insert(1);
		col_set.insert(5);
		col_set.insert(4);
		col_set.insert(1);
		col_set.insert(6);
		col_set.insert(2);

		set<int>::const_iterator pos_set;
		cout << "sets in ascending order ";
		for (pos_set = col_set.begin(); pos_set != col_set.end(); ++pos_set) {
			cout << *pos_set << ' ';
		}
		cout << endl;

		col_set2.insert(3);
		col_set2.insert(1);
		col_set2.insert(5);
		col_set2.insert(4);
		col_set2.insert(1);
		col_set2.insert(6);
		col_set2.insert(2);

		set<int, greater<int> >::const_iterator pos_set2;
		cout << "sets in descending order ";
		for (pos_set2 = col_set2.begin(); pos_set2 != col_set2.end(); ++pos_set2) {
			cout << *pos_set2 << ' ';
		}
		cout << endl;

		col_mset.insert(3);
		col_mset.insert(1);
		col_mset.insert(5);
		col_mset.insert(4);
		col_mset.insert(1);
		col_mset.insert(6);
		col_mset.insert(2);

		multiset<int>::const_iterator pos_mset;
		cout << "multi sets in ascending order " << endl;
		for (pos_mset = col_mset.begin(); pos_mset != col_mset.end(); ++pos_mset) {
			cout << *pos_mset << ' ';
		}
		cout << endl;

		col_mmap.insert(make_pair(5, "tagged"));
		col_mmap.insert(make_pair(2, "a"));
		col_mmap.insert(make_pair(1, "this"));
		col_mmap.insert(make_pair(4, "of"));
		col_mmap.insert(make_pair(6, "strings"));
		col_mmap.insert(make_pair(1, "is"));
		col_mmap.insert(make_pair(3, "map"));

		multimap<int, string>::const_iterator pos_mmap;
		cout << "multi maps in ascending order " << endl;
		for (pos_mmap = col_mmap.begin(); pos_mmap != col_mmap.end(); ++pos_mmap) {
			cout << "(" << pos_mmap->first << "," << pos_mmap->second << ")";
		}
		cout << endl;

		cout << "Associate Array: an array in which the index \n" <<
			"may be of an arbitrary type \n" <<
			"string-float map" << endl;
		col_sfmap["PI"] = 3.1415f;
		col_sfmap["an arbitrary number"] = 4983.223f;
		col_sfmap["Null"] = 0;

		map<string, float>::iterator pos_sfmap;
		for (pos_sfmap = col_sfmap.begin(); pos_sfmap != col_sfmap.end(); ++pos_sfmap) {
			cout << "key: \"" << pos_sfmap->first << "\" "
				<< "value: " << pos_sfmap->second << endl;
		}

		cout << "vector, list & deque";
		for (int i = 1; i <= 6; i++) {
			col_vec.push_back(i);
			col_deque.push_front(float(static_cast<double>(i) * 1.1));
		}

		for (char c = 'a'; c <= 'z'; ++c) {
			col_list.push_back(c);
		}

		for (auto& i : col_vec) {
			cout << i << ' ';
		}
		cout << endl;
		for (auto& i : col_deque) {
			cout << i << ' ';
		}
		cout << endl;

		//constant version iterator (read only)
		cout << " using constant iterator \n";
		list<char>::const_iterator pos;
		for (pos = col_list.begin(); pos != col_list.end(); pos++) {
			cout << *pos << ' ';
		}
		cout << endl;

		//non-constant version iterator (read and write)
		cout << " using non_constant iterator \n";
		list<char>::iterator ncpos;
		// note that the preincrement operator(prefix ++) is used here.
		// postincrement(++) is slower because it should return
		// the old position.
		for (ncpos = col_list.begin(); ncpos != col_list.end(); ++ncpos) {
			*ncpos = toupper(*ncpos);
			cout << *ncpos << ' ';
		}
		cout << endl;

		cout << " list output using while \n";
		while (!col_list.empty()) {
			cout << col_list.front() << ' ';
			col_list.pop_front();
		}
		cout << endl;

		return 0;
	}

	template<class BidirIt>
	void my_reverse(BidirIt first, BidirIt last)
	{
		typename std::iterator_traits<BidirIt>::difference_type n = std::distance(first, last);
		--n;
		while (n > 0) {
			typename std::iterator_traits<BidirIt>::value_type tmp = *first;
			*first++ = *--last;
			*last = tmp;
			n -= 2;
		}
	}

	int main_reversing_iterator()
	{
		std::vector<int> v{ 1, 2, 3, 4, 5 };
		my_reverse(v.begin(), v.end());
		for (int n : v) {
			std::cout << n << ' ';
		}
		std::cout << '\n';

		std::list<int> l{ 1, 2, 3, 4, 5, 6 };
		my_reverse(l.begin(), l.end());
		for (auto n : l) {
			std::cout << n << ' ';
		}
		std::cout << '\n';

		int a[] = { 1, 2, 3, 4, 5 };
		my_reverse(a, a + 5);
		for (int i = 0; i < 5; ++i) {
			std::cout << a[i] << ' ';
		}
		std::cout << '\n';

		//    std::istreambuf_iterator<char> i1(std::cin), i2;
		//    my_reverse(i1, i2); // compilation error
		return 0;
	}

}