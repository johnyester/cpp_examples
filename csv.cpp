#include "jly_tutorials.h"

//https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/

namespace jly_tutorials
{
    ////////////////////////////////////////////////
    // int main_csvwriter()
    /*
     * A class to create and write data in a csv file.
     */
    class CSVWriter
    {
        std::string fileName;
        std::string delimiter;
        int linesCount;
    public:
        CSVWriter(std::string filename, std::string delm = ",") :
            fileName(filename), delimiter(delm), linesCount(0)
        {}
        /*
         * Member function to store a range as comma seperated value
         */
        template<typename T>
        void addDatainRow(T first, T last);
        template<typename T>
        void write_container(T container);
    };

    /*
     * This Function accepts a range and appends all the elements in the range
     * to the last row, seperated by delimeter (Default is comma)
     */
    template<typename T>
    void CSVWriter::addDatainRow(T first, T last)
    {
        std::fstream file;
        // Open the file in truncate mode if first line else in Append Mode
        file.open(fileName, std::ios::out | (linesCount ? std::ios::app : std::ios::trunc));
        // Iterate over the range and add each lement to file seperated by delimeter.
        for (; first != last; )
        {
            file << *first;
            if (++first != last)
                file << delimiter;
        }
        file << "\n";
        linesCount++;
        // Close the file
        file.close();
    }

    template<typename ContainerType>
    void CSVWriter::write_container(ContainerType container)
    {
        std::fstream file;
        // Open the file in truncate mode if first line else in Append Mode
        file.open(fileName, std::ios::out | std::ios::trunc);
        for (auto& v : container)
        {
            //using var_type = typename ContainerType::value_type; // typename decltype(v)::value_type;
            //std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
            //std::copy(v.begin(), v.end(), std::ostream_iterator<double>(std::cout, delimiter.c_str()));
            std::copy(v.begin(), v.end(), std::ostream_iterator<double>(file, delimiter.c_str()));
            file << "\n";
            linesCount++;
        }
        // Close the file
        file.close();

    }
    ///////////////////////////////////////////////////////


    // main_writecsv()
    void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<int>>> dataset) {
        // Make a CSV file with one or more columns of integer values
        // Each column of data is represented by the pair <column name, column data>
        //   as std::pair<std::string, std::vector<int>>
        // The dataset is represented as a vector of these columns
        // Note that all columns should be the same size

        // Create an output filestream object
        std::ofstream myFile(filename);

        // Send column names to the stream
        for (unsigned int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).first;
            if (j != dataset.size() - 1) myFile << ","; // No comma at end of line
        }
        myFile << "\n";

        // Send data to the stream
        for (unsigned int i = 0; i < dataset.at(0).second.size(); ++i)
        {
            for (unsigned int j = 0; j < dataset.size(); ++j)
            {
                myFile << dataset.at(j).second.at(i);
                if (j != dataset.size() - 1) myFile << ","; // No comma at end of line
            }
            myFile << "\n";
        }

        // Close the file
        myFile.close();
    }

    // main_readcsv
    std::vector<std::pair<std::string, std::vector<int>>> read_csv(std::string filename) {
        // Reads a CSV file into a vector of <string, vector<int>> pairs where
        // each pair represents <column name, column values>

        // Create a vector of <string, int vector> pairs to store the result
        std::vector<std::pair<std::string, std::vector<int>>> result;

        // Create an input filestream
        std::ifstream myFile(filename);

        // Make sure the file is open
        if (!myFile.is_open()) throw std::runtime_error("Could not open file");

        // Helper vars
        std::string line, colname;
        int val;

        // Read the column names
        if (myFile.good())
        {
            // Extract the first line in the file
            std::getline(myFile, line);

            // Create a stringstream from line
            std::stringstream ss(line);

            // Extract each column name
            while (std::getline(ss, colname, ',')) {

                // Initialize and add <colname, int vector> pairs to result
                result.push_back({ colname, std::vector<int> {} });
            }
        }
        // Create a stringstream of the current line
        std::stringstream ss;
        // Read data, line by line
        while (std::getline(myFile, line))
        {
            ss << line;

            // Keep track of the current column index
            int colIdx = 0;

            // Extract each integer
            while (ss >> val) {

                // Add the current integer to the 'colIdx' column's values vector
                result.at(colIdx).second.push_back(val);

                // If the next token is a comma, ignore it and move on
                if (ss.peek() == ',') ss.ignore();

                // Increment the column index
                colIdx++;
            }
        }

        // Close file
        myFile.close();

        return result;
    }


    /*
    20,hi,99
    3,4,5
    a,b,c
    3,4,1
    */
    double randMToN(double M, double N)
    {
        return M + (rand() / (RAND_MAX / (N - M)));
    }

    int main_csvwriter()
    {
        if (0) 
        {
            // Creating an object of CSVWriter
            CSVWriter writer("example.csv");  // H:\cpp_repo\jly_cpp
            std::vector<std::string> dataList_1 = { "20", "hi", "99" };
            // Adding vector to CSV File
            writer.addDatainRow(dataList_1.begin(), dataList_1.end());
            // Create a set of integers
            std::set<int> dataList_2 = { 3, 4, 5 };
            // Adding Set to CSV File
            writer.addDatainRow(dataList_2.begin(), dataList_2.end());
            std::string str = "abc";
            // Adding characters in a string in csv file.
            writer.addDatainRow(str.begin(), str.end());
            // An array of int
            int arr[] = { 3,4,1 };
            // Wrote an elements in array to csv file.
            writer.addDatainRow(arr, arr + sizeof(arr) / sizeof(int));
        }

        CSVWriter writer2("vec.csv");
        //std::vector<double> row(10);
        //std::generate(row.begin(), row.end(), [] {return randMToN(-100., 100.); });
        std::vector<std::vector<double>> data;
        std::generate_n(std::back_inserter(data), 10, [] {
            std::vector<double> row(10);
            std::generate(row.begin(), row.end(), [] {return randMToN(-100., 100.); });
            return row; 
        });
        writer2.write_container(data);

        std::string filename{ "newvec.csv" };
        auto lines = write_container2csv(data, filename, ",");
        std::cout << "wrote " << lines << " row to file " << filename << std::endl;
        return 0;
    }


    int main_copy_vec2csv() {

        std::vector<std::string> v;
        v.push_back("a");
        v.push_back("b");
        v.push_back("c");

        std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "\n"));


        return 0;
    }

    void main_writedata2csv(std::string filename = "data.csv")
    {
        std::ofstream myfile(filename);
        myfile << "This is the first cell in the first column.\n";
        myfile << "a,b,c,\n";
        myfile << "c,s,v,\n";
        myfile << "1,2,3.456\n";
        myfile << "semi;colon";
        myfile.close();
    }

    int main_readcsv() {
        // Read three_cols.csv and ones.csv
        std::vector<std::pair<std::string, std::vector<int>>> three_cols = read_csv("three_cols.csv");
        std::vector<std::pair<std::string, std::vector<int>>> ones = read_csv("ones.csv");

        // Write to another file to check that this was successful
        write_csv("three_cols_copy.csv", three_cols);
        write_csv("ones_copy.csv", ones);

        return 0;
    }
    int main_writecsv() {
        // Make three vectors, each of length 100 filled with 1s, 2s, and 3s
        std::vector<int> vec1(100, 1);
        std::vector<int> vec2(100, 2);
        std::vector<int> vec3(100, 3);

        // Wrap into a vector
        std::vector<std::pair<std::string, std::vector<int>>> vals = { {"One", vec1}, {"Two", vec2}, {"Three", vec3} };

        // Write the vector to CSV
        write_csv("three_cols.csv", vals);

        return 0;
    }
}