#include <iostream>
#include <string>


// using struct
struct Map_Value_Printer {
    Map_Value_Printer(const std::string& key_desc,
        const std::string& value_desc) /// Capture
        : m_key_desc(key_desc), m_value_desc(value_desc)
    {
        std::cout << "ctor\n";
    }

    template<typename Value>
    void operator()(const Value& value) { /// Callable
        std::cout << m_key_desc << ": '" << value.first << "' "
            << m_value_desc << ": '" << value.second << "'\n";
    }

    const std::string& m_key_desc;   /// captured values
    const std::string& m_value_desc;
};

template<typename Map>
void print_map_struct(const Map& map, const std::string key_desc = "key",
    const std::string value_desc = "value")
{
    for_each(map.begin(), map.end(), Map_Value_Printer(key_desc, value_desc));
}

////////////
// using foreach/lambdas
template<typename Map>
void print_map_lambda(const Map& map, const std::string key_desc = "key",
    const std::string value_desc = "value")
{
    for_each(begin(map), end(map),
        [&](const auto& data) // auto == "typename Map::value_type"
    { /// lambda!
        std::cout << key_desc << ": '" << data.first << "' "
            << value_desc << ": '" << data.second << "'\n";
    }
    );
}

#include <iostream>
#include <map>
#include <string>
// using explicit for loop
void print_map_foreach(const std::map<int, std::string>& map,
    const std::string& key_desc = "key",
    const std::string& value_desc = "value")
{
    for (auto data_itr = map.begin(); // auto == "std::map<int, std::string>::const_iterator"
        data_itr != map.end();
        ++data_itr)
    {
        std::cout << key_desc << ": '" << data_itr->first << "' "
            << value_desc << ": '" << data_itr->second << "'\n";
    }
}

#include <iostream>
#include <string>
// range based for loop with structured bindings
template<typename Map>
void print_map_structured_bindings(const Map& map, const std::string& key_desc = "key",
    const std::string& value_desc = "value")
{
    for (const auto& [key, value] : map) /// structured binding
    {
        std::cout << key_desc << ": '" << key << "' "
            << value_desc << ": '" << value << "'\n";
    }
}


/* foreach build up/break down
Each iterator will point to a std::pair<const T,S> where T and S are the same types you specified on your map.
Here this would be:

for (std::map<int, MyClass>::iterator it = Map.begin(); it != Map.end(); ++it)
{
  it->second.Method();
}


If you still want to use std::for_each, pass a function that takes a std::pair<const int, MyClass>& as an argument instead.
Example:

void CallMyMethod(std::pair<const int, MyClass>& pair) // could be a class static method as well
{
  pair.second.Method();
}

And pass it to std::for_each:

std::for_each(Map.begin(), Map.end(), CallMyMethod);

///////////////
C++11 allows you to do:

for (const auto& kv : myMap) {
    std::cout << kv.first << " has value " << kv.second << std::endl;
}

C++17 allows you to do:

for (const auto& [key, value] : myMap) {
    std::cout << key << " has value " << value << std::endl;
}
*/

