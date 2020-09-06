#include <tuple>
#include <string>
#include <istream>

namespace jly_tutorials
{
	void main_structured_bindings()
	{
		auto [a, i, b] = std::tuple('a', 123, true);    // With no types needed for the tuple!


		//// ex put stream in loop since that's where it's used:
		// https://www.fluentcpp.com/2018/06/19/3-simple-c17-features-that-will-make-your-code-simpler/
		//{
		//	std::istringstream iss(head);
		//	for (std::string name; std::getline(iss, name); )
		//		// Process name
		//}
		//for (auto [iss, name] = pair(istringstream(head), string{}); getline(iss, name); ) {

	}
}