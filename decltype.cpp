#include "jly_tutorials.h"

/*
examples of using decltype
*/

// => get element type from vec in vec
template<typename ContainerType>
int decay_decltype_example(ContainerType container, std::string fileName, std::string delimiter = ",")
{
	std::fstream file;
	int linesCount = 0;
	file.open(fileName, std::ios::out | std::ios::trunc);
	for (auto& v : container)
	{
		using T = typename std::decay<decltype(*v.begin())>::type;  // <= gets the inner element type
		std::copy(v.begin(), v.end(), std::ostream_iterator<T>(file, delimiter.c_str()));
		file << "\n";
		linesCount++;
	}
	file.close();
	return linesCount;
}
