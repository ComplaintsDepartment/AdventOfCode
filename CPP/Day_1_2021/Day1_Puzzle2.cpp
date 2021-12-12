#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main() 
{
    
    std::ifstream inputfile; // Open for reading only with ifstream
    inputfile.open("InputFile.txt");

    std::string curLine;
    int count(0);
    int curVal(0);
    int lastVal(0);
    std::vector<int> inputData; // Smallish file and not real time critical.  Vector is a suitable and simple solution



    if (inputfile.is_open())
    {
        while ( std::getline ( inputfile, curLine ) ) 
        {
            inputData.push_back(std::stoi(curLine)); // Put the entire file into int vectors
        }

        lastVal = inputData[0] + inputData[1] + inputData[2]; // Hard code off the first set so we don't count i
        for ( int i = 1; i < inputData.size(); i++ )
        {
            curVal = inputData[i] + inputData[i+1] + inputData[i+2]; 
            if ( curVal > lastVal )
            {
                count++;
            }
            lastVal=curVal;
       } 
    }
    else 
    {
        std::cout << "File not found." << std::endl;
    }

    std::cout << "Final Count is: " << count << std::endl;

    return 0;
}
