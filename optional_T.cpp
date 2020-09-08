// https://www.fluentcpp.com/2016/11/24/clearer-interfaces-with-optionalt/
/*
*
* optional<T> allows the detection of a valid ref or empty value, like smart pointers do.
*
* For instance, let’s consider the following legacy function:

int oldF(); // by convention, oldF returns -1 as a no-value

You would rewrite it so that it benefits from optional to express the no-value, the following way:

boost::optional<int> newF();

And to limit the amount of code modified at the same time you can still keep the old function,
and make it call the new one:

int oldF()
{
	return newF().get_value_or(-1);
}

It helps with STL that would return an iterator:

 interface for finding an element in a vector:

boost::optional<std::vector<int>::iterator> find(const std::vector<int>& v, int target)
{
	std::vector<int>::const_iterator targetPosition = std:find(begin(v), end(v), target);
	if(targetPosition != end(v))
	{
		return targetPosition;
	}
	else
	{
		return boost::none;
	}
}
Here the function cannot guarantee to actually find the target value in the collection. With optional as a return type, it expresses that it may or may not return an actual position in the collection.

It would be used this way:

auto targetPosition = find(v, target);
if (targetPosition)
{
	// use *targetPosition
}
*/
#include <boost/optional.hpp>

namespace jly_tutorials
{
	boost::optional<int> f(int) { return 0; }
	boost::optional<int> g(int&, int&) { return 0; }
	boost::optional<int> h(int) { return 0; }

	// see https://www.fluentcpp.com/2017/07/04/multiple-error-handling-with-the-optional-monad-in-c/
	// to see how to use monads to simplify the below

	
	//class f1 {
	//	f1(int) {}
	//	auto operator=(int) {}
	//	template<typename T, typename TtoOptionalU>
	//	auto operator>>=(boost::optional<T> const& t, TtoOptionalU f) -> decltype(f(*t));
	//};
	
	void main_optional_t()
	{
		boost::optional<int> result;

		boost::optional<int> b = f(3);
		if (b)
		{
			boost::optional<int> c = f(4);
			if (c)
			{
				boost::optional<int> d = g(*b, *c);
				if (d)
				{
					boost::optional<int> e = h(*d);
					if (e)
					{
						result = h(*e);
					}
				}
			}
		}

		if (result)
		{
			// we can use *result
		}
		else
		{
			// we know that something went wrong
		}

		/*
		boost::optional<int> result = f(3) >>= [=](int b)     // b is the result of f(3) if it succeeds
		{ return f(4) >>= [=](int c)     // c is the result of f(4) if it succeeds
		{ return g2(b, c) >>= [=](int d) // and so on
		{ return h(d) >>= [=](int e)
		{ return h(e);
		}; }; }; };

		boost::optional<int> result3 = f(3) >>= [=](int b) { return
			f(4) >>= [=](int c) { return
			g2(b, c) >>= [=](int d) { return
			h(d) >>= [=](int e) { return
			h(e);
		}; }; }; };
		*/

	}
}