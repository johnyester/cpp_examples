#include <vector>
#include <iostream>

namespace jly_tutorials
{
    struct President
    {
        std::string name;
        std::string country;
        int year;

        President(std::string p_name, std::string p_country, int p_year)
            : name(std::move(p_name)), country(std::move(p_country)), year(p_year)
        {
            std::cout << name <<" I am being constructed.\n";
        }
        President(President&& other)
            : name(std::move(other.name)), country(std::move(other.country)), year(other.year)
        {
            std::cout << name << " I am being moved.\n";
        }
        President& operator=(const President& other) = default;
    };

    /*
    emplace_back:
    1
    Nelson Mandela I am being constructed.
    2
    2 Nelson Mandela I am being constructed.
    3
    3 Nelson Mandela I am being constructed.

    4
    4 Nelson Mandela I am being constructed.
    Nelson Mandela I am being moved.
    2 Nelson Mandela I am being moved.
    3 Nelson Mandela I am being moved.

    push_back:
    1
    Franklin Delano Roosevelt I am being constructed.
    Franklin Delano Roosevelt I am being moved.
    2
    2 Franklin Delano Roosevelt I am being constructed.
    2 Franklin Delano Roosevelt I am being moved.
    3
    3 Franklin Delano Roosevelt I am being constructed.
    3 Franklin Delano Roosevelt I am being moved.
    4
    4 Franklin Delano Roosevelt I am being constructed.
    4 Franklin Delano Roosevelt I am being moved.
    Franklin Delano Roosevelt I am being moved.
    2 Franklin Delano Roosevelt I am being moved.
    3 Franklin Delano Roosevelt I am being moved.
    */
	void main_vectors()
	{
		std::vector<int> vi = { 1,2,3 };
		vi.push_back(4);

		std::vector<std::pair<int, double>> vp = { {1,1.1}, {2, 2.2} };
		vp.push_back({ 3,3.3 });
		
		std::vector<std::tuple<int, double, char>> vt = { {1,1.1,'a'} };
		vt.push_back({ 2,2.2,'b' });

        // emplace_back forwards parameters to the President constructor and 
        // avoids the extra copy or move operation required when using push_back
        std::vector<President> elections;
        elections.reserve(3);
        std::cout << "emplace_back:\n";
        std::cout << "1\n";
        elections.emplace_back("Nelson Mandela", "South Africa", 1994);
        std::cout << "2\n";
        elections.emplace_back("2 Nelson Mandela", "South Africa", 1994);
        std::cout << "3\n";
        elections.emplace_back("3 Nelson Mandela", "South Africa", 1994);
        std::cout << "4\n";
        elections.emplace_back("4 Nelson Mandela", "South Africa", 1994);

        std::vector<President> reElections;
        reElections.reserve(3);
        std::cout << "\npush_back:\n";
        std::cout << "1\n";
        reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));
        std::cout << "2\n";
        reElections.push_back(President("2 Franklin Delano Roosevelt", "the USA", 1936));
        std::cout << "3\n";
        reElections.push_back({ "3 Franklin Delano Roosevelt", "the USA", 1936 });
        std::cout << "4\n";
        reElections.push_back({ "4 Franklin Delano Roosevelt", "the USA", 1936 });

        std::cout << "\nContents:\n";
        for (President const& president : elections) {
            std::cout << president.name << " was elected president of "
                << president.country << " in " << president.year << ".\n";
        }
        for (President const& president : reElections) {
            std::cout << president.name << " was re-elected president of "
                << president.country << " in " << president.year << ".\n";
        }

	}
}