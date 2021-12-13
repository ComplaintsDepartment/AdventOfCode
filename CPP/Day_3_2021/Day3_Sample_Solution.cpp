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

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "getInputData.h"

int main() 
{

    std::string curLine;
    std::vector<std::string> inputData;
//    std::ifstream inputFile("InputFile.txt", std::ifstream::in); // Open for reading only with ifstream
    std::ifstream inputFile("SampleData.txt", std::ifstream::in); // Open for reading only with ifstream
   
    uint Decimal(0);
    uint lineCount(0);
    uint Cnt1(0);
    uint Cnt2(0);
    uint Cnt3(0);
    uint Cnt4(0);
    uint Cnt5(0);
    uint isOneHigh(0);
    uint isOneLow(0);
    uint isTwoHigh(0);
    uint isTwoLow(0);
    uint isThreeHigh(0);
    uint isThreeLow(0);
    uint isFourHigh(0);
    uint isFourLow(0);
    uint isFiveHigh(0);
    uint isFiveLow(0);
    
    inputData = getInputData (inputFile);

    const uint MASK1 = 1ULL;
    const uint MASK2 = 2ULL;
    const uint MASK3 = 4ULL;
    const uint MASK4 = 8ULL;
    const uint MASK5 = 16ULL;

    
    char * refChar = NULL;

    for (int i=0; i < inputData.size(); i++)
    {   
        lineCount++;

        // Convert string to unsigned long long, of base 2.
        // No need for a reference to the endptr, so set NULL
        Decimal = std::strtoull(inputData.at(i).c_str(), &refChar, 2 ); // .c_str() returns a const char* to the const of the string object
//        std::cout << "Dec: " << Decimal << std::endl; 
        // I understand it's not the preferred style to not include the {} 
        // but I really only need a single line here
        if ( Decimal & MASK1 )
            Cnt1++;
//            std::cout << "Mask1 " << (Decimal & MASK1) << std::endl;
        if ( Decimal & MASK2 )
            Cnt2++;
        if ( Decimal & MASK3 )
            Cnt3++;
        if ( Decimal & MASK4 )
            Cnt4++;
        if ( Decimal & MASK5 )
            Cnt5++;
    
    }

    std::cout << "Cnts: " << Cnt5 << " " << Cnt4 << " " << Cnt3 << " " << Cnt2 << " " << Cnt1 << " " << lineCount << std::endl;
    
    if ( Cnt1 > lineCount/2)
        isOneHigh = 1;
    else
        isOneLow = 1;
    if ( Cnt2 > lineCount/2)
        isTwoHigh = 1;
    else
        isTwoLow = 1;
    if ( Cnt3 > lineCount/2)
        isThreeHigh = 1;
    else
        isThreeLow = 1;
    if ( Cnt4 > lineCount/2)
        isFourHigh = 1;
    else
        isFourLow = 1;
    if ( Cnt5 > lineCount/2)
        isFiveHigh = 1;
    else
        isFiveLow = 1;

    std::cout << "Highs " << isFiveHigh  << " Lows " << isFiveLow << std::endl;
    std::cout << "Highs " << isFourHigh  << " Lows " << isFourLow << std::endl;
    std::cout << "Highs " << isThreeHigh << " Lows " << isThreeLow << std::endl;
    std::cout << "Highs " << isTwoHigh   << " Lows " << isTwoLow << std::endl;
    std::cout << "Highs " << isOneHigh   << " Lows " << isOneLow << std::endl;

    uint gamma   = ( isFiveHigh << 4 ) + ( isFourHigh << 3 ) + ( isThreeHigh << 2 ) + ( isTwoHigh << 1 ) + ( isOneHigh );  
    uint epsilon = ( isFiveLow  << 4 ) + ( isFourLow  << 3 ) + ( isThreeLow  << 2 ) + ( isTwoLow  << 1 ) + ( isOneLow );   

    std::cout << "Gamma " << gamma << " Epsilon " << epsilon << std::endl;
    std::cout << "Gamma times Epsilon is: " << gamma * epsilon << std::endl;

    return 0;
}
