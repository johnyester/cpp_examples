#include <ostream>
#include <iostream>

using namespace std;

namespace jly_tutorials
{

    // override << operator
    // compile with: /EHsc

    class Date
    {
        int mo, da, yr;
    public:
        Date(int m, int d, int y)
        {
            mo = m; da = d; yr = y;
        }
        friend ostream& operator<<(ostream& os, const Date& dt);
    };

    ostream& operator<<(ostream& os, const Date& dt)
    {
        os << dt.mo << '/' << dt.da << '/' << dt.yr;
        return os;
    }

    int main_c2string()
    {
        Date dt(5, 6, 92);
        cout << dt;
        return 0;
    }
}