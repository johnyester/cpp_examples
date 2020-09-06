#include <array>
#include <iostream>

// check out 
// http://www.vishalchovatiya.com/variadic-template-cpp-implementing-unsophisticated-tuple/
// https://www.ibm.com/support/knowledgecenter/SSLTBW_2.4.0/com.ibm.zos.v2r4.cbclx01/variadic_templates.htm

namespace jly_tutorials
{
	template<typename VT, typename ... Params>
	std::array<VT, sizeof...(Params) + 1> init_array_with_list(const VT& v1, const Params& ... params)
	{
		std::cout << v1 << std::endl;
		return { v1, params... };
	}

	////////////////////
	template<typename VT>
	VT getdata1(VT v1)
	{
		return v1;
	}
	template<typename VT, typename ... P>  // variadic template
	std::array<VT, sizeof...(P)> init_array_with_type_and_list(const P& ... params) // param expansion
	{
		return { params... }; // pack expansion
	}


	/// ////////////////////////////
	template <typename... Ts>  // (1)
	void ignore(Ts... ts) {}   // (2)


	template <typename... Args>
	void print_list(Args... args) {
		(void(std::cout << args << std::endl), ...);
	}

	template<typename P, typename VT>
	void print_array(P p, VT data)
	{
		std::cout << p << std::endl;
		for (const auto& d : data)
		{
			std::cout << d << std::endl;
		}
	}

	void main_variadic_templates()
	{
		// std::array<double, 3>
		auto data = init_array_with_list(1., 2., 3.);
		for (const auto& d : data)
		{
			std::cout << d << std::endl;
		}
		print_array("data using init_array_with_list()",data);

		auto data1 = init_array_with_type_and_list<double>(1., 2., 3.);
		print_array("data1 using init_array_with_type_and_list()", data1);

	}
}