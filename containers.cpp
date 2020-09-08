#include "jly_tutorials.h"



namespace jly_tutorials
{
	struct custom_compare final
	{
		bool operator() (const std::string& left, const std::string& right) const
		{
			int nLeft = atoi(left.c_str());
			int nRight = atoi(right.c_str());
			return nLeft < nRight;
		}
	};

	int main_set_sorting()
	{
		std::set<std::string> sut({ "1", "2", "5", "23", "6", "290" });

		// default sort
		std::cout << "### Default sort on std::set<std::string> :" << std::endl;
		for (auto&& data : sut)
			std::cout << data << std::endl;

		// sort string2num
		std::set<std::string, custom_compare> sut_custom({ "1", "2", "5", "23", "6", "290" },
			custom_compare{}); //< Compare object optional as its default constructible.

		std::cout << std::endl << "### Custom sort on set :" << std::endl;
		for (auto&& data : sut_custom)
			std::cout << data << std::endl;

		// reverse sort using lambda
		auto compare_via_lambda = [](auto&& lhs, auto&& rhs) {/* std::cerr << lhs << ' ' << rhs << endl; */ return lhs > rhs; };
		using set_via_lambda = std::set<std::string, decltype(compare_via_lambda)>;
		set_via_lambda sut_reverse_via_lambda({ "1", "2", "5", "23", "6", "290" },
			compare_via_lambda);

		std::cout << std::endl << "### Lambda sort on set :" << std::endl;
		for (auto&& data : sut_reverse_via_lambda)
			std::cout << data << std::endl;

		return 0;
	}

	int main_sets()
	{
		std::set<int> col_set;

		col_set.insert(3);
		col_set.insert(1);
		col_set.insert(5);
		col_set.insert(4);
		col_set.insert(1);
		col_set.insert(6);
		col_set.insert(2);
		std::cout << "regular set:\n";
		for (auto& i : col_set) {
			std::cout << i << ' ';
		}
		std::cout << std::endl;

		std::set<int, std::greater<int> > col_set2;
		col_set2.insert(3);
		col_set2.insert(1);
		col_set2.insert(5);
		col_set2.insert(4);
		col_set2.insert(1);
		col_set2.insert(6);
		col_set2.insert(2);
		std::cout << "set/greater:\n";
		for (auto& i : col_set2) {
			std::cout << i << ' ';
		}
		std::cout << std::endl;

		return 0;
	}

	template<typename LabelT, typename ContainerT>
	void show_container(const LabelT& msg, const ContainerT& c)
	{
		std::cout << msg << ' ';
		std::copy(c.begin(), c.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << "\n";

	}

	template<typename T>
	void show_msg(T msg)
	{
		std::cout << msg << std::endl;
	}
	void main_containers()
	{
		// create a vector using brace initialization - might change to a generator, add a random step/increment
		std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		show_container("Original vector:", v);

		// constructor copy original vector into a vector we will shuffle ...
		auto shuffledv = v;
		// use shuffle to re-order the vector elements ...
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(shuffledv.begin(), shuffledv.end(), g);
		show_container("shuffledv:", shuffledv);

		// create a set to copy the shuffled vector into to see sorting effect ...
		std::set<int> setdata;
		// could have used the set constructor initialization to copy the shuffled vector: 
		std::set<int> setdata_alt(shuffledv.begin(), shuffledv.end());

		// explicit copy vector elements to set ...
		// set does not have push_back defined so we can't use a back_inserter/back_insert_iterator
		// std::copy(shuffledv.cbegin(), shuffledv.cend(), std::back_inserter(setdata));  // error - only list, deque, string, & vector have push_back defined.
		show_msg("copying shuffledv to setdata");
		std::copy(shuffledv.cbegin(), shuffledv.cend(), std::inserter(setdata, setdata.end()));
		show_container("setdata:", setdata);

		// Iterator Operations
		print_args("iterator ops");
		// advance
		auto advancev = v.begin();
		std::advance(advancev, 2);
		print_args("advancev (2)", *advancev);
		//*advancev = 99; // push_front() called
		//show_container("v after *advancev = 99",v);
		// next
		auto it = v.begin();
		auto nextv = std::next(it, 2);
		print_args("nextv (2)", "*it", *it, "*nextv", *nextv);
		// distance
		print_args("distance", std::distance(v.begin(), nextv), "between begin and nextv");
		print_args("distance", std::distance(nextv, v.begin()), "between nextv and begin");

		// Iterator Generators
		// back_inserter - returns a back_insert_iterator 
		auto backv = std::back_inserter(v);
		*backv = -1;
		*backv = -1;
		*backv = -1;
		print_args("back_inserter for v, called 3 times");
		show_container("v", v);

		// deque
		print_args("deque ops");
		// Create a deque containing integers
		std::deque<int> d = { 7, 5, 16, 8 };
		// Add an integer to the beginning and end of the deque
		d.push_front(13);
		d.push_back(25);
		// iterator assignment
		auto advanced = d.begin();
		*advanced = 98;
		*advanced = 99;
		show_container("deque after *advanced=98/99 called", d);
		// inserter assignment
		auto frontd = std::front_inserter(d);
		*frontd = -2;
		*frontd = -3;
		show_container("front inserter {-2,-3} called on d", d);

	}

}