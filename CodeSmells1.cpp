#include <iostream>
#include <array>
#include <vector>
#include <functional>
#include <random>
#include <numeric>

#define M_PI (3.14159265358979323846)

namespace jly_tutorials
{
	/*
		Rand_double rd{0,0.5};
		// print 10 random number between 0 and 0.5
		for (int i=0;i<10;++i){
			std::cout << rd() << ' ';
		}
	*/
	class Rand_double
	{
	public:
		Rand_double(double low, double high)
			:r(std::bind(std::uniform_real_distribution<>(low, high), std::default_random_engine())) {}

		double operator()() { return r(); }

	private:
		std::function<double()> r;
	};


	void show_container(std::vector<double>& data)
	{
		for (auto& d : data)
		{
			std::cout << d << " ";
		}
		std::cout << std::endl;
	}

	std::vector<double> gen_seq_vec(const int len, double first_val, const double step_size = 1.0)
	{
		std::vector<double> vec;
		vec.reserve(len);
		for (int i = 0; i < len; i++)
		{
			vec.emplace_back(first_val);
			first_val += step_size;
		}
		return vec;
	}
	std::vector<double> gen_rand_vec(const int len, double low_val=0.0, double high_val=100.0)
	{
		Rand_double rd{ low_val, high_val };
		std::vector<double> vec;
		vec.reserve(len);
		for (int i = 0; i < len; i++) {
			vec.emplace_back(rd());
		}
		return vec;
	}

	constexpr double area(const double r) { return r * r * M_PI; }
	double total_area(const std::vector<double>& rand_vec, const std::vector<double>& seq_vec)
	{

		const auto accumulate_area = [](const auto lhs, const auto rhs) {
			return lhs + area(rhs);
		};
		const auto total_area = [&](const auto& container) {
			return std::accumulate(begin(container), end(container), 0.0, accumulate_area);
		};

		return total_area(rand_vec) + total_area(seq_vec);
	}

	void main_codesmells1()
	{
		std::cout << "main_codesmells1()" << std::endl;
		auto rand_vec = gen_rand_vec(10, 1., 2.);
		std::cout << rand_vec.size() << " elements." << std::endl;
		show_container(rand_vec);

		auto seq_vec = gen_seq_vec(10, 1.0, .1);
		show_container(seq_vec);

		std::cout << total_area(rand_vec, seq_vec) << std::endl;
	}
}