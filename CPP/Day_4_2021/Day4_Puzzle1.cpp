/* 
--- Day 4: Giant Squid ---

You're already almost 1.5km (almost a mile) below the surface of the ocean, already so deep that you can't see any sunlight. What you can see, however, is a giant squid that has attached itself to the outside of your submarine.

Maybe it wants to play bingo?

Bingo is played on a set of boards each consisting of a 5x5 grid of numbers. Numbers are chosen at random, and the chosen number is marked on all boards on which it appears. (Numbers may not appear on all boards.) If all numbers in any row or any column of a board are marked, that board wins. (Diagonals don't count.)

The submarine has a bingo subsystem to help passengers (currently, you and the giant squid) pass the time. It automatically generates a random order in which to draw numbers and a random set of boards (your puzzle input). For example:

7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1

22 13 17 11  0
 8  2 23  4 24
21  9 14 16  7
 6 10  3 18  5
 1 12 20 15 19

 3 15  0  2 22
 9 18 13 17  5
19  8  7 25 23
20 11 10 24  4
14 21 16 12  6

14 21 17 24  4
10 16 15  9 19
18  8 23 26 20
22 11 13  6  5
 2  0 12  3  7

After the first five numbers are drawn (7, 4, 9, 5, and 11), there are no winners, but the boards are marked as follows (shown here adjacent to each other to save space):

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 1 12 20 15 19        14 21 16 12  6         2  0 12  3  7

After the next six numbers are drawn (17, 23, 2, 0, 14, and 21), there are still no winners:

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 1 12 20 15 19        14 21 16 12  6         2  0 12  3  7

Finally, 24 is drawn:

22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 1 12 20 15 19        14 21 16 12  6         2  0 12  3  7

At this point, the third board wins because it has at least one complete row or column of marked numbers (in this case, the entire top row is marked: 14 21 17 24 4).

The score of the winning board can now be calculated. Start by finding the sum of all unmarked numbers on that board; in this case, the sum is 188. Then, multiply that sum by the number that was just called when the board won, 24, to get the final score, 188 * 24 = 4512.

To guarantee victory against the giant squid, figure out which board will win first. What will your final score be if you choose that board?
*/

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "stdio.h"
#include <algorithm>
#include "getInputData.h"


struct trackWinner {
    int isWinner=0;
    int cardNum=0;
};

std::vector<int> splitStringToIntISS ( std::string curLine, std::string delimiter ) {
    
    std::vector<int> splitInts;
    std::istringstream stoSplits(curLine, std::istringstream::in);
    std::string s;   
    
    for(std::string s; stoSplits >> s;)
       splitInts.push_back(std::stoi(s));
    return splitInts;
}

std::vector<int> splitStringToIntCommas ( std::string curLine ) {
    
    std::vector<int> splitInts;
    std::istringstream stoSplits(curLine, std::istringstream::in);
    std::string s;   
    
    while(std::getline(stoSplits, s, ',')) 
       splitInts.push_back(std::stoi(s));
    return splitInts;
}    

trackWinner checkWinner ( std::vector< std::vector< std::vector<int> > > markedCards, int j, int k) {
       
        trackWinner tw;
        int sumRows(0); 
        int sumColumns(0);
        int sumDiags(0);

        for (int m=0 ; m < markedCards[0][0].size() ; m++ ) {
            sumRows += markedCards[1][j][m];
            sumColumns += markedCards[1][j/5*5+m][k];
            // Push the value to a card boundary, then bring the row back down
            // to the appropriate card.
            if ( ( j - j/5*5 ) == k ) { 
                 
                sumDiags += markedCards[1][ j/5*5 + m][ m ];
            }

//         if (sumRows == 5 )
//             std::cout << "ROW WINNER! " << "CARD: " << j/5 << std::endl;
//         if (sumColumns == 5 )
//             std::cout << "COLUMN WINNER! " << "CARD: " << j/5 << std::endl;
//         if (sumDiags == 5 )
//             std::cout << "DIAG WINNER! " << "CARD: " << j/5 << std::endl;
        }
        if (sumRows == 5 || sumColumns == 5 || sumDiags == 5) {
            tw.isWinner = 1;   
            tw.cardNum = j/5; 
//            std::cout << "Card Number: "  << tw.cardNum << std::endl;
        }
        return ( tw );
}

int countUnmarked ( std::vector< std::vector< std::vector<int> > > markedCards, int cardNum ) {

    int unmarkedSum(0);
    for (int m=0 ; m < markedCards[0][0].size() ; m++ ) {
        for (int n=0 ; n < markedCards[0][0].size() ; n++ ) {
//            std::cout << markedCards[1][cardNum*5+m][n] << std::endl; 
            if ( ! (markedCards[1][cardNum*5+m][n] ) ) {
                unmarkedSum += markedCards[0][cardNum*5+m][n];            
            }
        }
    }
    return unmarkedSum;
}

int main() 
{
    std::vector<std::string> inputData;
    std::vector< std::vector<int> > bingoCards;
    std::vector< std::vector< std::vector <int> > >markedCards;

//    std::ifstream inputFile("InputFile.txt", std::ifstream::in); // Open for reading only with ifstream
    std::ifstream inputFile("InputFile.txt", std::ifstream::in); // Open for reading only with ifstream
   
    inputData = getInputData (inputFile);
    int inputSize = inputData.size();
    std::string delimiter;
    int finalVal(0);
    
    // Line 1 is the numbers in order
    std::vector<int> bingoNumbers = splitStringToIntCommas(inputData.at(0));
    
    // Reject blank lines, and turn all the data into vectorized integers
    for ( int i=1 ; i < inputSize ; i++ ) {
        if ( !inputData.at(i).empty() ){
            bingoCards.push_back( splitStringToIntISS(inputData.at(i), delimiter=' '));
        }
        
    }

    // Somewhat wasteful of data, but we're practicing 3D vectors
    for ( int i=0 ; i < 2 ; i++ ) {
        markedCards.push_back(bingoCards);
    }

    
    // Zeroize the marked section of the cards
    for (int j=0 ; j < markedCards[0].size() ; j++ ) {
        for (int k=0 ; k < markedCards[0][0].size() ; k++ ) {
            markedCards[1][j][k] = 0;
        }
    }
    
    // Iterate the bingo numbers 
    for (int binNum=0 ; binNum < bingoNumbers.size() ; binNum++ ) {
//        std::cout << bingoNumbers.at(binNum) << std::endl;
        for (int j=0 ; j < markedCards[0].size() ; j++ ) {
            int cardNum = j/5; // integer trunc to get the card number
            for (int k=0 ; k < markedCards[0][0].size() ; k++ ) {
               if ( markedCards[0][j][k] == bingoNumbers.at(binNum) ) {
                    markedCards[1][j][k] = 1;
                    trackWinner testWinner (checkWinner(markedCards, j, k));
//                    if( checkWinner(markedCards, j, k).isWinner ) {
                    if( testWinner.isWinner ) {
//                        std::cout << "Card Num" << countUnmarked(markedCards, testWinner.cardNum) << std::endl;
//                        std::cout << "Bin Num" << bingoNumbers.at(binNum) << std::endl;
                        finalVal = countUnmarked(markedCards, testWinner.cardNum) * bingoNumbers.at(binNum); 
                        goto endloop; 
                    }
               }
            }
        }
    }
    endloop:
    std::cout << "Final Value: " << finalVal << std::endl;
//    for (int i=0 ; i < bingoCards.size() ; i++ ) {
//            std::cout <<  bingoCards[i][0] << " " << bingoCards[i][1]  << " " << bingoCards[i][2] << " " << bingoCards[i][3] << " " << bingoCards[i][4] << " " << std::endl;
//            std::cout <<  markedCards[0][i][0] << " " << markedCards[0][i][1]  << " " << markedCards[0][i][2] << " " << markedCards[0][i][3] << " " << markedCards[0][i][4] << " " << std::endl;
//            std::cout <<  markedCards[1][i][0] << " " << markedCards[1][i][1]  << " " << markedCards[1][i][2] << " " << markedCards[1][i][3] << " " << markedCards[1][i][4] << " " << std::endl;
//    }
    return 0;
}
