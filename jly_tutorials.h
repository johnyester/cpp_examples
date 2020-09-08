#pragma once
#ifndef __jly_tutorials__
#define __jly_tutorials__
/**
namespaces
namespace Shorter = Some::Impossibly::Annoyingly::Long:Name::For::Namespace::Finally;
Shorter::TheClassName foo;


The interface principle: 
C++ consider a function taking a type as an argument as being part of the interface for that type, 
so no need to specify the namespace because the parameter already implied the namespace.
namespace ns {
	class A {};
	void print(A a){}
}
If you wanted to print an A object, the code would be this one:
ns::A a;
print(a);
*/
#include <string>
#include <sstream>      // std::stringstream
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <map>
#include <vector>
#include <deque>
#include <tuple>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <random>
#include <stdlib.h>
#include <fstream>
#include <utility> // std::pair
#include <direct.h> // _getcwd()
#include <filesystem> // std::filesystem::current_path()
#include <cassert>


namespace jly_tutorials 
{
	///////////////////////////////////////////
	// constants
	constexpr double pi = 3.14159265358979323846;

	///////////////////////////////////////////
	// functions in jly_tutorials.cpp
	std::string get_cwd();

	///////////////////////////////////////////
	// lambdas
	// prints: arg1, arg2, arg3
	const auto print_args = [](auto first, auto... args) {
		std::cout << first;
		((std::cout << ", " << args), ...);
		std::cout << '\n';
	};

	///////////////////////////////////////////
	// templates
	template<typename P, typename VT>
	void print_container(P p, VT data)
	{
		std::cout << p << std::endl;
		for (const auto& d : data)
		{
			std::cout << d << std::endl;
		}
	}

	template<typename ContainerType>
	int write_container2csv(ContainerType container, std::string fileName, std::string colnames = "", std::string delimiter = ",")
	{
		std::fstream file;
		int linesCount = 0;
		file.open(fileName, std::ios::out | std::ios::trunc);
		if (colnames.length())
		{
			file << colnames << '\n';
		}
		for (auto& v : container)
		{
			using T = typename std::decay<decltype(*v.begin())>::type;
			std::copy(v.begin(), v.end(), std::ostream_iterator<T>(file, delimiter.c_str()));
			file << "\n";
			linesCount++;
		}
		file.close();
		std::cout << __func__ << "(): wrote " << linesCount << " rows to csvfile " << std::filesystem::current_path() << "\\\\" << fileName << std::endl;
		return linesCount;
	}

	template<typename ContainerType>
	int write_vec_pair2csv(ContainerType container, std::string fileName, std::string delimiter = ",")
	{
		std::fstream file;
		int linesCount = 0;
		file.open(fileName, std::ios::out | std::ios::trunc);
		for (auto& d : container)
		{
			file << d.first << ",\t" << d.second << std::endl;
			linesCount++;
		}
		file.close();
		std::cout << __func__ << "(): wrote " << linesCount << " rows to csvfile " << std::filesystem::current_path() << "\\\\" << fileName << std::endl;
		return linesCount;
	}

	////////////////////////////////////////////////////////
	int main_adjacent_find();                   // ./jly_cpp/std_algorithm.cpp:
	int main_all_of();                   // ./jly_cpp/std_algorithm.cpp:
	int main_any_of();                   // ./jly_cpp/std_algorithm.cpp:
	int main_arrays();                   // ./jly_cpp/std_array.cpp:
	int main_bidirectional_iterators();                   // ./jly_cpp/std_iterator.cpp:
	int main_binary_search();                   // ./jly_cpp/std_algorithm.cpp:
	int main_c2string();                   // ./jly_cpp/class2string.cpp:
	int main_classes();                   // ./jly_cpp/classes.cpp:
	int main_classes_ex();                   // ./jly_cpp/classes_ex.cpp:
	int main_const_iterators();                   // ./jly_cpp/std_iterator.cpp:
	int main_constexpr_usage();                   // ./jly_cpp/constexpr_usage.cpp:
	int main_copy();                   // ./jly_cpp/std_algorithm.cpp:
	int main_copy_backward();                   // ./jly_cpp/std_algorithm.cpp:
	int main_copy_if();                   // ./jly_cpp/std_algorithm.cpp:
	int main_example_iterators();                   // ./jly_cpp/std_iterator.cpp:
	int main_forward_iterators();                   // ./jly_cpp/std_iterator.cpp:
	int main_forwarding();                   // ./jly_cpp/forwarding.cpp:
	int main_generator_iterator();                   // ./jly_cpp/generator_iterator_ex.cpp:
	int main_iterator_copy();                   // ./jly_cpp/std_iterator.cpp:
	int main_iterators();                   // ./jly_cpp/std_iterator.cpp:
	int main_medium_ruleof5();                   // ./jly_cpp/raii1.cpp:
	int main_new_operator();                   // ./jly_cpp/new_operator.cpp:
	int main_new_placement();                   // ./jly_cpp/new_operator.cpp:
	int main_oneway_iterators();                   // ./jly_cpp/std_iterator.cpp:
	int main_optionals_value_or();                   // ./jly_cpp/optionals.cpp:
	int main_reversing_iterator();                   // ./jly_cpp/std_iterator.cpp:
	int main_ruleof6();                   // ./jly_cpp/raii1.cpp:
	int main_rvo();                   // ./jly_cpp/return_value_opt.cpp:
	int main_set_sorting();                   // ./jly_cpp/containers.cpp:
	int main_sets();                   // ./jly_cpp/containers.cpp:
	int main_splitstring1();                   // ./jly_cpp/string_splitting.cpp:
	int main_templates();                   // ./jly_cpp/templates.cpp:
	void main_algorithm_generate();                   // ./jly_cpp/std_algorithm.cpp:
	void main_codesmells1();                   // ./jly_cpp/CodeSmells1.cpp:
	void main_file_reader_c();                   // ./jly_cpp/ex_file_reader.cpp:
	void main_file_reader_cpp();                   // ./jly_cpp/ex_file_reader.cpp:
	void main_lambda_c14();                   // ./jly_cpp/lambdas.cpp:
	void main_lambdas();                   // ./jly_cpp/lambdas.cpp:
	void main_llaxyz();                   // ./jly_cpp/llaxyz.cpp:
	void main_maps();                   // ./jly_cpp/maps.cpp:
	void main_move_constructors();                   // ./jly_cpp/move_constructors.cpp:
	void main_pairs();                   // ./jly_cpp/pairs.cpp:
	void main_raii1();                   // ./jly_cpp/raii1.cpp:
	void main_references();                   // ./jly_cpp/references.cpp:
	void main_rule_of_five();                   // ./jly_cpp/rule_of_five.cpp:
	void main_rule_of_five2();                   // ./jly_cpp/rule_of_five2.cpp:
	void main_scratch();                   // ./jly_cpp/_scratch.cpp:
	void main_simple_fold();                   // ./jly_cpp/fold_expressions.cpp:
	void main_structured_bindings();                   // ./jly_cpp/structured_bindings.cpp:
	void main_userdefinedLiteralsConstexpr();                   // ./jly_cpp/userdefinedLiteralsConstexpr.cpp:
	void main_variadic_templates();                   // ./jly_cpp/variadic_templates.cpp:
	void main_vector();                   // ./jly_cpp/std_vector.cpp:
	void main_vectors();                   // ./jly_cpp/vectors.cpp:
	int main_template_multiparam();
	void main_operator();
	void main_functors();
	int main_transform();
	void main_accumulate();
	void main_accumulate_fold();
	//
	int main_writecsv();
	int main_readcsv();
	int main_copy_vec2csv();
	int main_csvwriter();  // CSVWriter()
	void main_get_cwd();
	//
	void main_containers();
}
#endif