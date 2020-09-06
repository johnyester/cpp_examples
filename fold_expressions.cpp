#include <iostream>
#include <iomanip>
#include <vector>

namespace jly_tutorials
{
	// https://baptiste-wicht.com/posts/2015/05/cpp17-fold-expressions.html
	////// Note the syntax style for ..., op, and arg
	template<typename... T>
	auto fold_sum_1(T... s) {
		return (... + s);
	}

	/*
	Fold expressions over a parameter pack.
	EXPRESSION							EXPANSION
	(... op pack)						((pack1 op pack2) op ...) op packN
	(init op ... op pack)				(((init op pack1) op pack2) op ...) op packN
	(pack op ...)						pack1 op (... op (packN-1 op packN))
	(pack op ... op init)				pack1 op (... op (packN-1 op (packN op init)))
	*/

	////// The syntax style below maynot be the most accepted, see above
	template<typename ...Args> auto sum(Args ...args)
	{
		std::cout << "summing fold args with constant" << std::endl;
		return (args + ... + 0);
	}

	template<typename ...Args> auto sum2(Args ...args)
	{
		std::cout << "summing fold args" << std::endl;
		return (args + ...);
	}

	template<typename ...Args>
	void FoldPrint(Args&&... args)
	{
		std::cout << "printing fold args using forward<>():" << std::endl;
		(std::cout << ... << std::forward<Args>(args)) << '\n';
	}

	template<typename ...Args>
	void FoldPrint2(Args&&... args)
	{
		std::cout << "printing fold args:" << std::endl;
		(std::cout << ... << args) << '\n';
	}
	
	template<typename T, typename... Args>
	void push_back_vec(std::vector<T>& v, Args&&... args)
	{
		(v.push_back(args), ...);
	}

	template<typename P, typename VT>
	void print_container(P p, VT data)
	{
		std::cout << p << std::endl;
		for (const auto& d : data)
		{
			std::cout << d << std::endl;
		}
	}

	void main_simple_fold()
	{
		std::cout << sum(1, 2, 3, 4, 5, 6, 7) << "\n";
		std::cout << sum2(1, 2, 3, 4, 5, 6, 7) << "\n";

		FoldPrint("hello", ", ", 10, ", ", 90.0);
		FoldPrint2("hello", ", ", 10, ", ", 90.0);

		std::vector<int> v;
		push_back_vec(v, 1, 2, 3, 4);
		print_container("the vector:", v);

	}

	///////////////////
	// http://cpptruths.blogspot.com/2016/12/understanding-fold-expressions.html
	// check out: http://cpptruths.blogspot.com/2014/03/fun-with-lambdas-c14-style-part-1.html
	/* C17 fold examples:
	defined over a 32 operators: + - * / % ^ & | = < > << >> += -= *= /= %= ^= &= |= <<= >>= == != <= >= && || , .* ->*.
	*/


}