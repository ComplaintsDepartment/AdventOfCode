#include <string>
#include <iostream>
#include <fstream>
#include <vector>

/******************************************************************************
Function: getInputData

Portable function to support Advent of Code projects.  Input types change,
so here, on Day 2, importing files as strings makes sense, as we will parse
them appropriately as we need to.

Usage:  Declare, define, and open an ifstream class and send the reference
to it.

Arguments: Reference to ifstream input file

Returns: Vector of strings from input file
******************************************************************************/
std::vector<std::string> getInputData( std::ifstream &inputFile )
{
    std::string curLine;
    std::vector<std::string> inputData2;
    if (inputFile.is_open())
    {
        while ( std::getline ( inputFile, curLine ) ) 
        {
            // I can push whatever I want onto the vector as long as I
            // accurately declare it properly, then keep track of the types
            // I'm trying to shove there.
            inputData2.push_back(curLine);
        }
    }
    else 
    {
        std::cout << "File not found." << std::endl;
    }
    return inputData2;
}

