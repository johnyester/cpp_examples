#include <vector>
#include <iostream>

/*
vector <type> variable (elements)
Iterators
	begin() – Returns an iterator pointing to the first element in the vector
	end() – Returns an iterator pointing to the theoretical element that follows the last element in the vector
	rbegin() – Returns a reverse iterator pointing to the last element in the vector (reverse beginning). It moves from last to first element
	rend() – Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector (considered as reverse end)
	cbegin() – Returns a constant iterator pointing to the first element in the vector.
	cend() – Returns a constant iterator pointing to the theoretical element that follows the last element in the vector.
	crbegin() – Returns a constant reverse iterator pointing to the last element in the vector (reverse beginning). It moves from last to first element
	crend() – Returns a constant reverse iterator pointing to the theoretical element preceding the first element in the vector (considered as reverse end)
Modifiers:
	assign() – It assigns new value to the vector elements by replacing old ones
	    v.assign(5, 10);  // fill the array with 10 five times 
	push_back() – It push the elements into a vector from the back
	pop_back() – It is used to pop or remove elements from a vector from the back.
	insert() – It inserts new elements before the element at the specified position
		v.insert(v.begin(), 5); 
	erase() – It is used to remove elements from a container from the specified position or range.
		v.erase(v.begin()); // removes the first element
	swap() – It is used to swap the contents of one vector with another vector of same type. Sizes may differ.
	clear() – It is used to remove all the elements of the vector container
	emplace() – It extends the container by inserting new element at position
		v.emplace(v.begin(), 5); // inserts at the beginning
	emplace_back() – It is used to insert a new element into the vector container, the new element is added to the end of the vector
		v.emplace_back(20); // Inserts 20 at the end
Capacity
	size() – Returns the number of elements in the vector.
	max_size() – Returns the maximum number of elements that the vector can hold.
	capacity() – Returns the size of the storage space currently allocated to the vector expressed as number of elements.
	resize(n) – Resizes the container so that it contains ‘n’ elements.
	empty() – Returns whether the container is empty.
	shrink_to_fit() – Reduces the capacity of the container to fit its size and destroys all elements beyond the capacity.
	reserve() – Requests that the vector capacity be at least enough to contain n elements.
Element access:
	reference operator [g] – Returns a reference to the element at position ‘g’ in the vector
	at(g) – Returns a reference to the element at position ‘g’ in the vector
	front() – Returns a reference to the first element in the vector
	back() – Returns a reference to the last element in the vector
	data() – Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
All Vector Functions :
	vector::begin() and vector::end()
	vector rbegin() and rend()
	vector::cbegin() and vector::cend()
	vector::crend() and vector::crbegin()
	vector::assign() - void assign( size_type count, const T& value ); (until C++20)
	vector::at()
	vector::back()
	vector::capacity()
	vector::clear()
	vector::push_back()
	vector::pop_back()
	vector::empty()
	vector::erase()
	vector::size()
	vector::swap() - Exchanges the contents of the container with those of other. Does not invoke any move, copy, or swap operations on individual elements.
	vector::reserve()
	vector::resize()
	vector::shrink_to_fit()
	vector::operator=
	vector::operator[]
	vector::front()
	vector::data() - Returns pointer to the underlying array serving as element storage. 
	vector::emplace_back()
	vector::emplace() - Inserts a new element into the container directly before pos.
		template< class... Args > iterator emplace( const_iterator pos, Args&&... args );
	vector::max_size()
	vector::insert()
*/
namespace jly_tutorials
{
	void printStack(const std::vector<int>& stack)
	{
		for (auto element : stack)
			std::cout << element << ' ';
		std::cout << "(cap " << stack.capacity() << " length " << stack.size() << ")\n";
	}


	void main_vector()
	{

		// C++03
		// no need to specify length at the declaration
		std::vector<int> array;  // empty vector
		std::vector<int> array2 = { 9, 7, 5, 3, 1 }; // use initializer list to initialize array (Before C++11)
		std::vector<int> array3{ 9, 7, 5, 3, 1 }; // use uniform initialization to initialize array
		std::vector<int> vect(7, 10); // len 7, vals 10
		
		int arr[] = { 10, 20, 30 };
		int n = sizeof(arr) / sizeof(arr[0]);
		std::vector<int> vect2(arr, arr + n); // initialize from an array

		std::vector<int> vect1{ 10, 20, 30 };
		std::vector<int> vect3(vect1.begin(), vect1.end()); // initialize from another vector
		
		vect2 = vect1; // Using assignment operator to copy one vector to other 

		std::vector<int> vect2a(vect1); // Deep copy 

		std::copy(vect1.begin(), vect1.end(), back_inserter(vect2)); // Copying vector by copy function 
			
		vect2.assign(vect1.begin(), vect1.end()); // Deep copying vector by assign function 

		// as with std::array, the type can be omitted since C++17
		std::vector array4{ 9, 7, 5, 3, 1 }; // deduced to std::vector<int>

		array[6] = 2; // no bounds checking
		array.at(7) = 3; // does bounds checking

		// C++11
		array = { 0, 1, 2, 3, 4 }; // okay, array length is now 5
		array = { 9, 8, 7 }; // okay, array length is now 3

		// resize - can enlarge or reduce
		array.resize(5); // set size to 5

		// vector with default eles
		// Using direct initialization, we can create a vector with 5 elements,
		// each element is a 0. If we use brace initialization, the vector would
		// have 1 element, a 5.
		std::vector<int> array5(5);

		// size/length v capacity
		// Array subscripts and at() are based on length, not capacity
		// 	stack.reserve(5); // Set the capacity to (at least) 5
		std::vector<int> array6{};
		array2 = { 0, 1, 2, 3, 4 }; // okay, array2 length = 5
		std::cout << "length: " << array2.size() << "  capacity: " << array2.capacity() << '\n';

		array2 = { 9, 8, 7 }; // okay, array2 length is now 3!
		std::cout << "length: " << array2.size() << "  capacity: " << array2.capacity() << '\n';


		/*
		Stack behavior with std::vector
			- push_back() pushes an element on the stack.
			- back() returns the value of the top element on the stack.
			- pop_back() pops an element off the stack.

		*/

		////////////////////////////
		// Vector with 5 integers
		// Default value of integers will be 0.
		std::vector < int >	vecOfInts(5);
		for (int x : vecOfInts)
			std::cout << x << std::endl;

		// str array to vec
		//std::string arr[] = {"first","sec","third","fourth"};
		//std::vector < std::string > vecOfStr(arr, arr + sizeof(arr) / sizeof(std::string));

		// list to vec
		// std::vector < std::string > vecOfStr(listOfStr.begin(), listOfStr.end());

		// copy a vector
		//std::vector < std::string > vecOfStr;
		//vecOfStr.push_back("first");
		//vecOfStr.push_back("sec");
		//vecOfStr.push_back("third");
		//// Vector with other string object
		//std::vector < std::string > vecOfStr3(vecOfStr);


	}
}