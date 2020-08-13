#pragma once

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

namespace jly_tutorials {
	int main();

	int main_adjacent_find();  // algorithms.cpp:
	int main_all_of();  // algorithms.cpp:
	int main_any_of();  // algorithms.cpp:
	int main_bidirectional_iterators();  // iterators.cpp:
	int main_binary_search();  // algorithms.cpp:
	int main_c2string();  // class2string.cpp:
	int main_classes(void);  // classes.cpp:
	int main_classes_ex();  // classes_ex.cpp:
	int main_const_iterators();  // iterators.cpp:
	int main_containers();  // containers.cpp:
	int main_copy();  // algorithms.cpp:
	int main_copy_backward();  // algorithms.cpp:
	int main_copy_if();  // algorithms.cpp:
	int main_example_iterators();  // iterators.cpp:
	int main_forward_iterators();  // iterators.cpp:
	int main_iterators();  // iterators.cpp:
	int main_oneway_iterators();  // iterators.cpp:
	int main_reversing_iterator();
	int main_optionals_value_or();  // optionals.cpp:
	int main_set_sorting();  // containers.cpp:
	int main_sets();  // containers.cpp:
	int main_splitstring1();  // string_splitting.cpp:
	int main_rvo();
	int main_generator_iterator(); // generator_iterator.cpp
	void main_references();  // references
	void main_llaxyz();
	void main_unary_fold();
	void main_binary_fold();
	void main_lambdas();
	int main_new_operator();
	int main_new_placement();
	void main_variadic_templates();

}