/*
--- Day 3: Binary Diagnostic ---

The submarine has been making some odd creaking noises, so you ask it to produce a diagnostic report just in case.

The diagnostic report (your puzzle input) consists of a list of binary numbers which, when decoded properly, can tell you many useful things about the conditions of the submarine. The first parameter to check is the power consumption.  
You need to use the binary numbers in the diagnostic report to generate two new binary numbers (called the gamma rate and the epsilon rate). The power consumption can then be found by multiplying the gamma rate by the epsilon rate.

Each bit in the gamma rate can be determined by finding the most common bit in the corresponding position of all numbers in the diagnostic report. For example, given the following diagnostic report:

00100
11110
10110
10111
10101
01111
00111
11100
10000
11001
00010
01010

Considering only the first bit of each number, there are five 0 bits and seven 1 bits. Since the most common bit is 1, the first bit of the gamma rate is 1.

The most common second bit of the numbers in the diagnostic report is 0, so the second bit of the gamma rate is 0.

The most common value of the third, fourth, and fifth bits are 1, 1, and 0, respectively, and so the final three bits of the gamma rate are 110.

So, the gamma rate is the binary number 10110, or 22 in decimal.

The epsilon rate is calculated in a similar way; rather than use the most common bit, the least common bit from each position is used. So, the epsilon rate is 01001, or 9 in decimal. Multiplying the gamma rate (22) by the epsilon rate (9) produces the power consumption, 198.

Use the binary numbers in your diagnostic report to calculate the gamma rate and epsilon rate, then multiply them together. What is the power consumption of the submarine? (Be sure to represent your answer in decimal, not binary.)

*/

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "getInputData.h"

int main() 
{

    std::vector<std::string> inputData;
    std::ifstream inputFile("InputFile.txt", std::ifstream::in); // Open for reading only with ifstream
   
    uint Decimal(0);
    uint lineCount(0);
    
    inputData = getInputData (inputFile);
    int inputSize = inputData.size();
    std::vector<int> storeHighs(12);
    std::vector<int> storeState(12);
    int gamma(0);
    int epsilon(0); 

    for ( int i=0 ; i < inputSize ; i++ )
    {  
        std::string curString = inputData.at(i);
        for ( int j=0 ; j < storeHighs.size() ; j++ ) {
            // Because ASCII numerals begin at 0, subtract the decimal
            // value of ASCII 0 from the implicit cast to get back to 
            // decimal integer.  Alternative method would be subtract
            // ASCII character '0'
            if ( (int)( curString.at(j) ) - 48 ) { 
                storeHighs.at(j)++;
            }
        }
    }
   
    // Now that we've incremented all the ones, develop a State Vector
    // that will keep track of if it had a larger than mean High bit
    // value, or Low
    for ( int i=0 ; i < storeState.size() ; i++ ) {
        if ( storeHighs.at(i) > inputSize/2 ) {
            storeState.at(i) = 1;
        }
    }
    
    // Develop the decimal value now
    // We've stored the high state if the high bit was observed in the majority
    // of the cases. Since we're been keeping it as an integer flag, we can
    // develop the decimal by bit shifting that value to the appropriate position.
    // Since we we working with a string, which was LSB left as we read the string,
    // the store values have to be pushed forward from the LSB from lowest number
    // manner in which we stored them.
    for ( int i=0 ; i < storeState.size() ; i++ ) {
        gamma += storeState.at(i) << ((storeState.size()-1) - i);
    }

    // If the field had the larger value, it was applicable in each bit
    // location for gamma.  If it was not, it means it was applicable for
    // epsilon.  Making epsilon a direct complement of gamma.
    epsilon = ~gamma & 0x0FFF;
    std::cout << "Gamma: " << gamma << " Epsilon: " << epsilon << std::endl;
    std::cout << "Result: " << gamma * epsilon << std::endl;

    
        
    return 0;
}
