/*
--- Part Two ---

Considering every single measurement isn't as useful as you expected: there's just too much noise in the data.

Instead, consider sums of a three-measurement sliding window. Again considering the above example:

199  A      
200  A B    
208  A B C  
210    B C D
200  E   C D
207  E F   D
240  E F G  
269    F G H
260      G H
263        H

Start by comparing the first and second three-measurement windows. The measurements in the first window are marked A (199, 200, 208); their sum is 199 + 200 + 208 = 607. The second window is marked B (200, 208, 210); its sum is 618. The sum of measurements in the second window is larger than the sum of the first, so this first comparison increased.

Your goal now is to count the number of times the sum of measurements in this sliding window increases from the previous sum. So, compare A with B, then compare B with C, then C with D, and so on. Stop when there aren't enough measurements left to create a new three-measurement sum.

In the above example, the sum of each three-measurement window is as follows:

A: 607 (N/A - no previous sum)
B: 618 (increased)
C: 618 (no change)
D: 617 (decreased)
E: 647 (increased)
F: 716 (increased)
G: 769 (increased)
H: 792 (increased)

In this example, there are 5 sums that are larger than the previous sum.

Consider sums of a three-measurement sliding window. How many sums are larger than the previous sum?
*/

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

        lastVal = inputData.at(0) + inputData.at(1) + inputData.at(2); // Hard code off the first set so we don't count i
        for ( int i = 1; i < inputData.size()-2; i++ )
        {
            curVal = inputData.at(i) + inputData.at(i+1) + inputData.at(i+2); 
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
