#include <optional>
#include <iostream>
#include <cstdlib>


/*
Severity	Code	Description	Project	File	Line	Suppression State
Error	C4996	'getenv': This function or variable may be unsafe. 
Consider using _dupenv_s instead. To disable deprecation, 
use _CRT_SECURE_NO_WARNINGS. See online help for details.	jly_cpp	H:\cpp_repo\jly_cpp\optionals.cpp	9
*/
#pragma warning(disable : 4996)

namespace jly_tutorials
{
    std::optional<const char*> maybe_getenv(const char* n)
    {
        const char* p = "not found";
        if (const char* x = std::getenv(n))
            return x;
        else
            return p; // was {} - empty.
    }
    int main_optionals_value_or()
    {
        std::cout << maybe_getenv("MYPWD").value_or("(none)") << '\n';
        return 0;
    }
}