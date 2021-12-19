/* 
--- Part Two ---

On the other hand, it might be wise to try a different strategy: let the giant squid win.

You aren't sure how many bingo boards a giant squid could play at once, so rather than waste time counting its arms, the safe thing to do is to figure out which board will win last and choose that one. That way, no matter which boards it picks, it will win for sure.

In the above example, the second board is the last to win, which happens after 13 is eventually called and its middle column is completely marked. If you were to keep playing until this point, the second board would have a sum of unmarked numbers equal to 148 for a final score of 148 * 13 = 1924.

Figure out which board will win last. Once it wins, what would its final score be?

*/

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "stdio.h"
#include <algorithm>
#include "getInputData.h"

#define CO(e) std::cout << e << std::endl

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
            sumColumns += markedCards[1][ (j/5)*5 + m][k];
            // Push the value to a card boundary, then bring the row back down
            // to the appropriate card.
            if ( ( j - (j/5)*5 ) == k ) { 
                 
                sumDiags += markedCards[1][(j/5)*5 + m][m];
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

    std::ifstream inputFile("InputFile.txt", std::ifstream::in); // Open for reading only with ifstream
//    std::ifstream inputFile("SampleFile.txt", std::ifstream::in); // Open for reading only with ifstream
   
    inputData = getInputData (inputFile);
    int inputSize = inputData.size();
    std::string delimiter;
    int finalVal(0);
    int numBoards(0);
//    std::vector< std::vector< int > > winnerList(0);
    std::vector< int > winnerList;
    std::vector< int > winningValues;
    // Line 1 is the numbers in order
    std::vector<int> bingoNumbers = splitStringToIntCommas(inputData.at(0));
    
    // Reject blank lines, and turn all the data into vectorized integers
    for ( int i=1 ; i < inputSize ; i++ ) {
        if ( !inputData.at(i).empty() ){
            bingoCards.push_back( splitStringToIntISS(inputData.at(i), delimiter=' '));
        }
        
    }
    numBoards = bingoCards.size()/5;

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
                        if(std::count(winnerList.begin(), winnerList.end(), cardNum)) {
                            continue;
                        }
                        else {
                            winnerList.push_back(cardNum);
                            winningValues.push_back(finalVal);
                        }


                    }
               }
            }
        }
    }

    CO("Final Value:");
    CO(winningValues.at(winningValues.size()-1));
//    for (int i=0 ; i < bingoCards.size() ; i++ ) {
//            std::cout <<  bingoCards[i][0] << " " << bingoCards[i][1]  << " " << bingoCards[i][2] << " " << bingoCards[i][3] << " " << bingoCards[i][4] << " " << std::endl;
//            std::cout <<  markedCards[0][i][0] << " " << markedCards[0][i][1]  << " " << markedCards[0][i][2] << " " << markedCards[0][i][3] << " " << markedCards[0][i][4] << " " << std::endl;
//            std::cout <<  markedCards[1][i][0] << " " << markedCards[1][i][1]  << " " << markedCards[1][i][2] << " " << markedCards[1][i][3] << " " << markedCards[1][i][4] << " " << std::endl;
//    }
    return 0;
}
