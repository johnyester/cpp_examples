#include <set>
#include <iostream>
#include <stdlib.h> 

using namespace std;


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
		set<int> col_set;

		col_set.insert(3);
		col_set.insert(1);
		col_set.insert(5);
		col_set.insert(4);
		col_set.insert(1);
		col_set.insert(6);
		col_set.insert(2);
		cout << "regular set:\n";
		for (auto& i : col_set) {
			cout << i << ' ';
		}
		cout << endl;

		set<int, greater<int> > col_set2;
		col_set2.insert(3);
		col_set2.insert(1);
		col_set2.insert(5);
		col_set2.insert(4);
		col_set2.insert(1);
		col_set2.insert(6);
		col_set2.insert(2);
		cout << "set/greater:\n";
		for (auto& i : col_set2) {
			cout << i << ' ';
		}
		cout << endl;

		return 0;
	}

	int main_containers()
	{
		main_sets();
		main_set_sorting();
		return 0;
	}
}