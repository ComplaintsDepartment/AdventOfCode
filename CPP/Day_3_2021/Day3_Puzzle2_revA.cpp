/*
--- Part Two ---

Next, you should verify the life support rating, which can be determined by multiplying the oxygen generator rating by the CO2 scrubber rating.

Both the oxygen generator rating and the CO2 scrubber rating are values that can be found in your diagnostic report - finding them is the tricky part. Both values are located using a similar process that involves filtering out values until only one remains. Before searching for either rating value, start with the full list of binary numbers from your diagnostic report and consider just the first bit of those numbers. Then:

    Keep only numbers selected by the bit criteria for the type of rating value for which you are searching. Discard numbers which do not match the bit criteria.
    If you only have one number left, stop; this is the rating value for which you are searching.
    Otherwise, repeat the process, considering the next bit to the right.

The bit criteria depends on which type of rating value you want to find:

    To find oxygen generator rating, determine the most common value (0 or 1) in the current bit position, and keep only numbers with that bit in that position. If 0 and 1 are equally common, keep values with a 1 in the position being considered.
    To find CO2 scrubber rating, determine the least common value (0 or 1) in the current bit position, and keep only numbers with that bit in that position. If 0 and 1 are equally common, keep values with a 0 in the position being considered.

For example, to determine the oxygen generator rating value using the same example diagnostic report from above:

    Start with all 12 numbers and consider only the first bit of each number. There are more 1 bits (7) than 0 bits (5), so keep only the 7 numbers with a 1 in the first position: 11110, 10110, 10111, 10101, 11100, 10000, and 11001.  Then, consider the second bit of the 7 remaining numbers: there are more 0 bits (4) than 1 bits (3), so keep only the 4 numbers with a 0 in the second position: 10110, 10111, 10101, and 10000.
    In the third position, three of the four numbers have a 1, so keep those three: 10110, 10111, and 10101.
    In the fourth position, two of the three numbers have a 1, so keep those two: 10110 and 10111.
    In the fifth position, there are an equal number of 0 bits and 1 bits (one each). So, to find the oxygen generator rating, keep the number with a 1 in that position: 10111.
    As there is only one number left, stop; the oxygen generator rating is 10111, or 23 in decimal.

Then, to determine the CO2 scrubber rating value from the same example above:

    Start again with all 12 numbers and consider only the first bit of each number. There are fewer 0 bits (5) than 1 bits (7), so keep only the 5 numbers with a 0 in the first position: 00100, 01111, 00111, 00010, and 01010.
    Then, consider the second bit of the 5 remaining numbers: there are fewer 1 bits (2) than 0 bits (3), so keep only the 2 numbers with a 1 in the second position: 01111 and 01010.
    In the third position, there are an equal number of 0 bits and 1 bits (one each). So, to find the CO2 scrubber rating, keep the number with a 0 in that position: 01010.
    As there is only one number left, stop; the CO2 scrubber rating is 01010, or 10 in decimal.

Finally, to find the life support rating, multiply the oxygen generator rating (23) by the CO2 scrubber rating (10) to get 230.

Use the binary numbers in your diagnostic report to calculate the oxygen generator rating and CO2 scrubber rating, then multiply them together. What is the life support rating of the submarine? (Be sure to represent your answer in decimal, not binary.)

*/

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "stdio.h"
#include <algorithm>
#include "getInputData.h"


// Find if high or low states are more predominant
int findState( std::vector<std::string> inputVec, int charNum, int isHigh ) {
    int countHighs(0);
    for ( int i=0 ; i < inputVec.size() ; i++ ) {
        std::string curString = inputVec.at(i); 
            if ( (int)( curString.at(charNum) ) - 48 ) { 
                countHighs++;
            }
    }
    bool state(countHighs >= inputVec.size()/2);
    return ( isHigh ? state : !state );
}

/* Work through the string bit by bit.  First take the entire
vector, and determine which value is most predominant with
findState.  Accept it for Oxy, negate it for CO2.
From there, make a waterfall of smaller sized vectors while
keeping the original inputData value.
The check is against each specific Bit being an ASCII 0 or 1
and subtracting the ASCII represented value as applicable.
Once we've generated the smaller vector value, erase the holding
vector and start the next iteration. */
std::vector<std::string> smallifier( std::vector<std::string> preFilter, int iteration, int isHigh )
{
    std::vector<std::string> postFilter;
    int curState = findState( preFilter, iteration, isHigh );
    for( int j=0 ; j < preFilter.size() ; j++ ) {
        std::string curString = preFilter.at(j); 
        if ( (int)( curString.at(iteration) ) - 48 == curState ) { 
            postFilter.push_back(preFilter.at(j));
        }
    }
    return postFilter;
}

int main() 
{

    std::vector<std::string> inputData;
    std::vector<std::string> curOxyVec;
    std::vector<std::string> curCO2Vec;
    std::vector<std::string> foundOxy(1);
    std::vector<std::string> foundCO2(1);

    std::ifstream inputFile("InputFile.txt", std::ifstream::in); // Open for reading only with ifstream
   
    inputData = getInputData (inputFile);
    int inputSize = inputData.size();
    int stringLength = inputData.at(0).size(); 
    
    int oxy(0);
    int co2(0);
    curOxyVec = inputData;
    curCO2Vec = inputData;

    for ( int i=0 ; i < stringLength ; i++) {
        
        if (curOxyVec.size() != 1) {
            curOxyVec = smallifier(curOxyVec, i, 1);
        } 
        else {
            foundOxy.at(0) = curOxyVec.at(0);
        }

        if (curCO2Vec.size() != 1) {
            curCO2Vec = smallifier(curCO2Vec, i, 0);
        }
        else {
            foundCO2.at(0) = curCO2Vec.at(0);
        }
//        std::cout << "Next Size: " << curOxyVec.size() << std::endl;
//        std::cout << "Next Size: " << curCO2Vec.size() << std::endl;
    }

    oxy = std::stoi(foundOxy.at(0), 0, 2);
    co2 = std::stoi(foundCO2.at(0), 0, 2);
    std::cout << "Oxygen: " << oxy << std::endl;
    std::cout << "CO2: " << co2 << std::endl;
    
    std::cout << "Total: " << oxy * co2 << std::endl;

    return 0;
}
