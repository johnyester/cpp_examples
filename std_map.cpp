#include "jly_tutorials.h"

/*
Member functions
	(constructor) - constructs the map
	(destructor) - destructs the map
	operator= - assigns values to the container
	get_allocator - returns the associated allocator

Element access
	at - access specified element with bounds checking
	operator[] - access or insert specified element

Iterators
	begin, cbegin - returns an iterator to the beginning
	end, cend - returns an iterator to the end
	rbegin, crbegin - returns a reverse iterator to the beginning
	rend, crend - returns a reverse iterator to the end

Capacity
	empty - checks whether the container is empty
	size - returns the number of elements
	max_size - returns the maximum possible number of elements

Modifiers
	clear - clears the contents
	emplace vs insert vs operator[]/at() in C++ STL
		In C++, all containers (vector, stack, queue, set, map, etc) support both insert and emplace operations.
		The advantage of emplace is, it does in-place insertion and avoids an unnecessary copy of object.
		For primitive data types, it does not matter which one we use.
		But for objects, use of emplace() is preferred for efficiency reasons.
		operator[] needs to be able to construct a default initialized value, and it is thus unusable for value types that can not be defalut initialized
		operator[] will overwrite an existing key/value pair.
	insert - returns std::pair<iterator,bool> - inserts elements or nodes, if the container doesn't already contain an element with an equivalent key. (since C++17)
	insert_or_assign - inserts an element or assigns to the current element if the key already exists
	emplace - Inserts a new element into the container constructed in-place with the given args if there is no element with the key in the container.
	emplace_hint - constructs elements in-place using a hint
	try_emplace - inserts in-place if the key does not exist, does nothing if the key exists
	operator[]
		is a find-or-add operator.
		It will try to find an element with the given key inside the map,
		and if it exists it will return a reference to the stored value.
		If it does not, it will create a new element inserted in place with default initialization and return a reference to it.
	erase - erases elements
	swap - Exchanges the contents of the container with those of other. Does not invoke any move, copy, or swap operations on individual elements.
	extract
		1) Unlinks the node that contains the element pointed to by position and returns a node handle that owns it
		2) If the container has an element with key equivalent to x, unlinks the node that contains that element from the container and returns a node handle that owns it. Otherwise, returns an empty node handle.
		In either case, no elements are copied or moved, only the internal pointers of the container nodes are repointed (rebalancing may occur, as with erase())
		Extracting a node invalidates the iterators to the extracted element. Pointers and references to the extracted element remain valid, but cannot be used while element is owned by a node handle: they become usable if the element is inserted into a container.
	merge - splices nodes from another container

Lookup
	count - Returns the number of elements with key that compares equivalent to the specified argument, which is either 1 or 0 since this container does not allow duplicates.
	find - finds element with specific key
	contains - checks if the container contains element with specific key
	equal_range - returns range of elements matching a specific key
	lower_bound - returns an iterator to the first element not less than the given key
	upper_bound - returns an iterator to the first element greater than the given key

Observers
	key_comp - returns the function that compares keys
	value_comp - returns the function that compares keys in objects of type value_type
*/
//http://www.vishalchovatiya.com/using-std-map-wisely-with-modern-cpp/

/*
std::map
std::multimap
std::unordered_map/multimap

/////////////////
map.find()
std::map::find
	  iterator find (const key_type& k);
const_iterator find (const key_type& k) const;

Get iterator to element
	Searches the container for an element with a key equivalent to k and returns an iterator to it if found,
	otherwise it returns an iterator to map::end.

	Two keys are considered equivalent if the container's comparison object returns false reflexively
	(i.e., no matter the order in which the elements are passed as arguments).

Parameters
	k
		Key to be searched for.
		Member type key_type is the type of the keys for the elements in the container, defined in map as an alias of its first template parameter (Key).

Return value
	An iterator to the element, if an element with specified key is found, or map::end otherwise.
		map.end().second = 0
		If the map object is const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator.
NOTES:
1. Member types iterator and const_iterator are bidirectional iterator types pointing to elements (of type value_type).
2. value_type in map containers is an alias of pair<const key_type, mapped_type>.
3. Another member function, map::count, can be used to just check whether a particular key exists.
/////////
map.count
//////////////////////////////
map.erase
//////////////
map.emplace
map.try_emplace C++17

*/
namespace jly_tutorials
{

	// std::map::contains c++20
	bool map_contains(std::map<int, int> src, int val)
	{
		if (auto search = src.find(val); search != src.end()) { // c+20: if (freq_of.contains(val))
			return true;
		}
		return false;
	}

	void main_maps()
	{
		std::map<char, int> mymap;
		auto mapret = mymap.insert(std::pair('a', 100));

		if (auto [itelem, success] = mymap.insert(std::pair('a', 100)); success) {
			// Insert success
		}

		auto src = std::map<int, int>{ {3, 1}, {1, 1}, {2, 1} };
		if (map_contains(src, 7))
		{
			// do something ...

		}
	}
	void main_map_emplace()
	{
		// use map to build histogram via emplace/try_emplace
		std::vector v{ 3, 4, 5, 8, 7, 3, 5, 2, 4 };
		std::map<uint32_t, uint32_t> freq_of;
		for (const auto& n : v) {
			// count occurances of the keys
			if (false)
			{
				// will try to create item, may fail
				if (const auto& [it, inserted] = freq_of.emplace(n, 1); !inserted) {
					it->second++;  // Exists already
				}
			}
			else {
				// will only create if doesn't exist.
				if (const auto& [it, inserted] = freq_of.try_emplace(n, 1); !inserted) {
					it->second++;
				}
			}
		}
	}
	int main_map_insert() {
		std::map<uint32_t, std::string> m{ {2, ""}, {3, ""} };
		// set best guess for next insertion
		auto where(end(m));
		for (const auto& n : { 8, 7, 6, 5, 4, 3, 2, 1 }) { // Items in non-incremental order
			if (true) {
				// use best guess for searching for next insertion point
				where = m.insert(where, { n, "" });  // update guess for next insertion
			}
			else {
				// How it is not done!
				// m.insert(end(m), {0, ""});
			}
		}
		for (const auto& [key, value] : m) {
			std::cout << key << " : " << value << std::endl;
		}
		return EXIT_SUCCESS;
	}

	int main_map_merge() {
		/*
		The duplicated elements are not transferred. They’re left behind in the right-hand-side map.
		*/
		std::map<uint32_t, std::string> fruits{ {5, "grapes"}, {2, "tomoto"} };
		std::map<uint32_t, std::string> person{ {2, "mickel"}, {10, "shree"} };
		std::map<uint32_t, std::string> fruits_and_persons;
		fruits_and_persons.merge(fruits);
		assert(fruits.size() == 0);
		fruits_and_persons.merge(person);
		assert(person.size() == 1);
		assert(person.at(2) == "mickel"); // Won't overwrite value at 2 i.e.`mickel`
		assert((fruits_and_persons == decltype(fruits){
			{2, "tomoto"},
			{ 5, "grapes" },
			{ 10, "shree" },
		}));
		return EXIT_SUCCESS;
	}

	// https://dzone.com/articles/using-stdmap-wisely-with-modern-c
	//remove & reinsert std::map nodes without any reallocation of memory
	int main_map_change_keys() {
		std::map<int, std::string> race_scoreboard{ {1, "Mickel"}, {2, "Shree"}, {3, "Jenti"} };
		using Pair = std::map<int, std::string>::value_type;
		{
			auto Jenti(race_scoreboard.extract(3));
			auto Mickel(race_scoreboard.extract(1));
			std::swap(Jenti.key(), Mickel.key());
			auto [it, is_inserted, nh] = race_scoreboard.insert(move(Jenti)); // nh = node handle
			assert(*it == Pair(1, "Jenti") && is_inserted == true && nh.empty());
			race_scoreboard.insert(move(Mickel));
		}
		assert((race_scoreboard == decltype(race_scoreboard){
			{1, "Jenti"},
			{ 2, "Shree" },
			{ 3, "Mickel" },
		}));
		return EXIT_SUCCESS;
	}
}