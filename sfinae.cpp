#include "jly_tutorials.h"

namespace jly_tutorials
{
	struct Test {
		typedef int foo;
	};

	template <typename T>
	void f(typename T::foo) {}  // Definition #1

	template <typename T>
	void f(T) {}  // Definition #2

	void main_sfinae()
	{

		f<Test>(10);  // Call #1.
		f<int>(10);   // Call #2. Without error (even though there is no int::foo)
					  // thanks to SFINAE.
	}
}