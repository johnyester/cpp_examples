#include "jly_tutorials.h"

namespace jly_tutorials
{
	// the c++ alternative is std::filesystem::current_path().string()
	std::string get_cwd() {
		char buff[FILENAME_MAX]; //create string buffer to hold path
		_getcwd(buff, FILENAME_MAX);
		std::string current_working_dir(buff);
		return current_working_dir;
	}
}
