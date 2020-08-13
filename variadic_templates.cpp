#include <array>
#include <iostream>

// check out 
// http://www.vishalchovatiya.com/variadic-template-cpp-implementing-unsophisticated-tuple/
// https://www.ibm.com/support/knowledgecenter/SSLTBW_2.4.0/com.ibm.zos.v2r4.cbclx01/variadic_templates.htm

namespace jly_tutorials
{
	template<typename VT, typename ... Params>
	std::array<VT, sizeof...(Params) + 1> get_data(const VT& v1, const Params& ... params)
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
	std::array<VT, sizeof...(P)> get_data1(const P& ... params) // param expansion
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
		std::array<double, 3> data = get_data(1., 2., 3.);
		for (const auto& d : data)
		{
			std::cout << d << std::endl;
		}
		print_array("data",data);

		std::array<double,3> data1{ 1., 2., 3. };

		//TODO Doesn't work for some reason the template is not identified 
		/*double d = get_data1(3.);
		std::array<double, 3> data = get_data1(1., 2., 3.);*/

	}
}