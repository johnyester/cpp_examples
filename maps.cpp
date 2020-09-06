#include <map>

namespace jly_tutorials
{
    void main_maps()
    {
        std::map<char, int> mymap;
        auto mapret = mymap.insert(std::pair('a', 100));

        if (auto [itelem, success] = mymap.insert(std::pair('a', 100)); success) {
            // Insert success
        }
    }
}