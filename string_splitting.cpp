#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>

// FROM: https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/

namespace jly_tutorials
{
	// show the results
	void print_splitstring(std::string splittype, std::string text, std::vector<std::string> results) {
		std::cout << "using " << splittype << std::endl;
		std::cout << '[' << text << ']' << std::endl;
		for (auto& r : results) {
			std::cout << r << " | ";
		}
		std::cout << std::endl;
	}

	// 1.2 - subclasss string to override >> operator to split by char
	class WordDelimitedByComma : public std::string	{};
	std::istream& operator>>(std::istream& is, jly_tutorials::WordDelimitedByComma& output)
	{
		std::getline(is, output, ',');
		return is;
	}

	// 1.3 - non-iterator string splitting usings a function (obvious solution)
	std::vector<std::string> split_string3(const std::string& s, char delimiter)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, delimiter))
		{
			tokens.push_back(token);
		}
		return tokens;
	}

	int main_splitstring1() {
		int type = 3;
		if (type==1) {
			// default string splitting (using spaces)
			std::string text = "Let me split this into words";
			
			std::istringstream iss(text);

			// The extra parentheses in the first parameter are made to disambiguate from a function call
			/* std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
				std::istream_iterator<std::string>());
				*/
			std::vector<std::string> results(std::istream_iterator<std::string>{iss}, // <== NOTE THE BRACES
				std::istream_iterator<std::string>());

			print_splitstring("1.1 default string splitting", text, results);
		} 
		else if(type==2) 
		{
			// modified string splitting (using commas)
			std::string text = "Let,me,split,this,into,words";
			
			std::istringstream iss(text);
			
			std::vector<std::string> results((std::istream_iterator<WordDelimitedByComma>(iss)),
				std::istream_iterator<WordDelimitedByComma>());
			
			print_splitstring("1.2 overloaded operator>>", text, results);
		}
		else if (type==3)
		{
			// modified string splitting (using commas)
			std::string text = "Let,me,split,this,into,words";
			std::vector<std::string> results = split_string3(text, ',');
			print_splitstring("1.3 custom function", text, results);

		}
		return 0;
	}
}