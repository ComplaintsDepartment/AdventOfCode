/*
--- Part Two ---

Based on your calculations, the planned course doesn't seem to make any sense. You find the submarine manual and discover that the process is actually slightly more complicated.

In addition to horizontal position and depth, you'll also need to track a third value, aim, which also starts at 0. The commands also mean something entirely different than you first thought:

    down X increases your aim by X units.
    up X decreases your aim by X units.
    forward X does two things:
        It increases your horizontal position by X units.
        It increases your depth by your aim multiplied by X.

Again note that since you're on a submarine, down and up do the opposite of what you might expect: "down" means aiming in the positive direction.

Now, the above example does something different:

    forward 5 adds 5 to your horizontal position, a total of 5. Because your aim is 0, your depth does not change.
    down 5 adds 5 to your aim, resulting in a value of 5.
    forward 8 adds 8 to your horizontal position, a total of 13. Because your aim is 5, your depth increases by 8*5=40.
    up 3 decreases your aim by 3, resulting in a value of 2.
    down 8 adds 8 to your aim, resulting in a value of 10.
    forward 2 adds 2 to your horizontal position, a total of 15. Because your aim is 10, your depth increases by 2*10=20 to a total of 60.

After following these new instructions, you would have a horizontal position of 15 and a depth of 60. (Multiplying these produces 900.)

Using this new interpretation of the commands, calculate the horizontal position and depth you would have after following the planned course. What do you get if you multiply your final horizontal position by your final depth?

*/

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

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


int main() 
{

    std::string curLine;
    std::vector<std::string> inputData;
    std::vector<std::string>::iterator iter;
    std::ifstream inputFile("InputFile.txt", std::ifstream::in); // Open for reading only with ifstream
    int distance(0);
    int depth(0);
    int aim(0);
    std::string Direction;
    int Magnitude;
   
    enum Dirs {
        DirUndef,
        DirFor,
        DirUp,
        DirDown
    };

    // Map the string values we want to an enumation we can switch/case
    std::map<std::string, Dirs> mapDirs;
    mapDirs["forward"] = DirFor;
    mapDirs["up"] = DirUp;
    mapDirs["down"] = DirDown;

    // inputFile.open("InputFile.txt"); // Open is unnecessary as we opened it above in the declaration
    inputData = getInputData (inputFile);
    
    for (int i=0; i < inputData.size() ; i++)
    {   
        // Substring will work for C++ string types here.  It will return a start to end
        // use built in string::find with our delimiter to split to find the end of the
        // first word.  Similar for second.  Use the size of the string and start
        // at the first delimiter.
        Direction=inputData.at(i).substr(0, inputData.at(i).find(" ")); // We know the input is only 2 values long.  We'll make a real tokenizer if we need it later.
        Magnitude=std::stoi(inputData.at(i).substr(inputData.at(i).find(" "), inputData.at(i).size())); // Don't forget to turn our strings into integers

        // C++ does not out of the box support switch/case statements with the string type
        // If we declare enumerations and then map the strings we want to them, we can
        // then apply strings as the cases with ease.
        switch(mapDirs[Direction])
        {
            case DirFor:
                distance += Magnitude; 
                depth    += aim * Magnitude;
                break;
            case DirUp:
                aim   -= Magnitude;
                break;
            case DirDown:
                aim   += Magnitude;
                break;
            default:
                std::cout << "Unexpected direction." << std::endl;
                break;
        }
    }

    int answer = depth * distance; 

    std::cout << "Final value: " << answer << std::endl;

    return 0;
}
