#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include "SString.h"
#include <map>

using namespace std;
float evaluateReviews(map<SString,int> &wordList,vector<SString> &reviews,bool positive,vector<int> &ids) { //function that uses the generated map to assign point values to a review
   float numCorrect = 0;
    for(int i = 0; i < reviews.size() && i < 10000; i ++) { // iterate through the vector of reviews that need to be evaluated
        int reviewScore = 0;

        for(auto it = wordList.begin(); it != wordList.end();) { // iterate through the entire map of SStrings and see if the review contains that word

            if(reviews[i].contains(it->first.getData())) {
                reviewScore += it->second; // add the mapped value of the word to the "Score" of the review
            }
            it++; // increment the iterator to continue down the list
        }
        if(reviewScore > -250 && positive) { // if the review score is higher than -250, and the review is positive, increment the number of correctly identified reviews
            numCorrect++;
        } else if(reviewScore < -250 && !positive) { // if the review score is lower than -250 and the review is negative, increment the number of correctly identified reviews
            numCorrect++;
        } else {
            if(positive) ids.push_back(i); // otherwise add the index of the review to a vector of the incorrectly identified review indexes
            else if(!positive) ids.push_back(i + 5000);
        }

    }
    return numCorrect; // return the total number of correct reviews
}
void removeuselessWords(map<SString,int> &map) { // function to remove all values in the map with a mapped value of 0
    for(auto it = map.begin(); it != map.end();) { // iterate through the entire map
        if((it->second) == 0) { // if the mapped value is 0, remove the value from the map
            it = map.erase(it);
        } else {
            it++; // otherwise increment the iterator
        }
    }
}


void generateLookupTable(vector<SString> &reviews, map<SString, int> &words, int numToAdd) { // function to generate the map of words

    for (int i = 0; i < reviews.size() && i < 7500; i++) { // for loop that iterates through the reviews
        for (int j = 0; j < reviews[i].getNumWords(); j++) { // for loop that iterates through each word of the review at index i
            if(reviews[i].wordAt(j).getSize() < 4) break; // skip over words that are less than 4 characters
            auto x = (words.emplace(reviews[i].wordAt(j), 0)); // create a pair with SString,Int where the int is the "positivity" of the word
            if (!x.second) {
                words[reviews[i].wordAt(j)]+= numToAdd; // if the word is already in the map, increment the positivity value of that word by either 1 or -1 depending on which review type is being passed

            }
        }
    }
}

void parseFile(ifstream &file, vector<SString> &pReview, vector<SString> &nReview, ofstream &output) {
    int numPos = 0;
    int numNeg = 0;
    int numReviews = 0;
    map<SString,int> words; // create the map of Sstring,Int that allows us to lookup the positivity score of an individual word
    vector<SString> previewsToEvaluate; // positive reviews that need to be evaluated
    vector<SString> nreviewsToEvaluate;// negative reviews that need to be evaluated
    vector<int> ids; // Vector of the Id's that were incorrectly identified
    while (!file.eof() && numReviews < 40000) { // read in the "test set" of reviews
        char buffer[20000]; // buffer for reading in

        file.getline(buffer, 20000);
        int bufferSize = strlen(buffer);
        SString test = SString(buffer); // create an SString with whatever was contained within the buffer
        if (test.contains("positive", bufferSize - 9)) { // check to see if the word positive is contained in the last 9 characters
            numPos++;
            pReview.push_back(test); // add the SString to the vector of positive reviews to learn from if it does contain the word positive
        } else if (test.contains("negative", bufferSize - 9)) { // same as above but checking for the word negative in the last 9 characters
            numNeg++;
            nReview.push_back(test); // if it contains negative in the last 9 characters, then push it back to the negative reviews list
        }
        numReviews++; // value that allows only yhe first 40k reviews to be read in


    }
    numReviews = 0;
    while (!file.eof() && numReviews < 10000) { // same as previous while loop but this one is filling the review list that still needs to be evaulated
        char buffer[20000];
        file.getline(buffer, 20000);
        int bufferSize = strlen(buffer);
        SString test = SString(buffer);
        if (test.contains("positive", bufferSize - 9)) {
            numPos++;
            previewsToEvaluate.push_back(test);
        } else if (test.contains("negative", bufferSize - 9)) {
            numNeg++;
            nreviewsToEvaluate.push_back(test);
        }
        numReviews++;


    }
    cout << "Generating Positive review table" <<endl;
    generateLookupTable(pReview,words,1); // call to generate the map's values using the positive reviews
    cout << "Generating negative review table" <<endl;
    generateLookupTable(nReview,words,-1); // call to generate the map's values using the negative reviews


    removeuselessWords(words); // removes all words with a mapped value of 0 so the program doesnt have to bother checking those words
    cout << "Evaluating previews" <<endl;
    float positivePercentCorrect = evaluateReviews(words,previewsToEvaluate,true,ids); // evaluates the list of positive reviews and returns a float for the number it got correct
    cout <<"Evaluating nReviews" <<endl;
   float negativePercentCorrect = evaluateReviews(words,nreviewsToEvaluate,false,ids); // evaluated the list of negative reviews and returns a float for the number it got correct
   float percentRight = (positivePercentCorrect + negativePercentCorrect) / 10000; // math to find percent correct out of the last 10000
    output << "PERCENT CORRECT: " << percentRight <<endl; // puts the percent correct into the file
    output << "------- ID of Incorrect -------" <<endl;
    for(int i = 0; i < ids.size(); i ++) { // iterates through the vector of incorrectly identified id's and prints them to the file
        output << "ID: " <<ids[i] <<endl;
    }



}

int main(int argc, char** argv) {
    if(argc == 1) Catch::Session().run(); // runs catch session
    else cout << "Running no Test" <<endl;
    std::ofstream fout(argv[2]);
    ifstream input;
    input.open(argv[1]);

    vector<SString> positiveReviews, negativeReviews;
    parseFile(input, positiveReviews, negativeReviews,fout); // function that gets the ball rolling for this program 60% ACCURACY IN CLION :) Finally

    fout.close(); // close the file
    return 0;
}



