#include <utility>
namespace jly_tutorials
{
	void main_pairs()
	{
		std::pair<int, double> p(2, 4.5);
		// Here, p is an instance of the class pair and is initialized with values of 2 and 4.5.
		// Or the other method of achieving this would be :

		auto p1 = std::make_pair(2, 4.5);
		// Both methods have their drawbacks.Creating “make functions” like std::make_pair is confusing, artificialand inconsistent with how non - template classes are constructed.std::make_pair, std::make_tuple etc are available in the standard library, but for user - defined types it is worse : you have to write your own make_… functions.Doh!

		// Specifying template arguments, as in :
		auto p2 = std::pair<int, double>(2, 4.5);
		// should be unnecessary since they can be inferred from the type of the arguments – as is usual with template functions.

		// In C++17, this requirement for specifying the types for a templated class constructor has been abolished.
		// This means that we can now write :
		auto p3 = std::pair(2, 4.5);
		// or
		std::pair p4(2, 4.5);
		// which is the logical way you would expect to be able to define p!
	}
}