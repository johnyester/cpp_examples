#include "jly_tutorials.h"

namespace jly_tutorials
{

	// the c++ alternative is std::filesystem::current_path() - returns std::filesystem:path object NOT STRING
	std::string get_current_dir() {
			char buff[FILENAME_MAX]; //create string buffer to hold path
			_getcwd(buff, FILENAME_MAX);
			std::string current_working_dir(buff);
			return current_working_dir;
	}

	void main_get_cwd() {
		std::cout << get_current_dir() << std::endl;
	}
}