#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

int main() 
{
    
    std::ifstream inputfile; // Open for reading only with ifstream
    inputfile.open("InputFile.txt");

    std::string lastLine;
    std::string curLine;
    int count(0);

    if (inputfile.is_open())
    {
        std::getline ( inputfile, lastLine );
        while ( std::getline ( inputfile, curLine ) )
        {
            if( std::stoi(curLine) > std::stoi(lastLine) )
            {
                count++;
            }
            lastLine = curLine;
        }
    }
    else 
    {
        std::cout << "File not found." << std::endl;
    }

    std::cout << "Final Count is: " << count << std::endl;

return 0;
}
