#ifndef SENTIMENTANALYZER_H
#define SENTIMENTANALYZER_H
#include "DSString.h"
#include <map>
#include <vector>
#include <fstream>
#include <cstring>
#include <utility>
#include <iomanip>
using namespace std;
class SentimentAnalyzer{
    private:
        //sentiment counts, positive or negative
        map<DSString, pair<int, int>> sentimentCounts;
        //+
        map<DSString, bool> positiveWords;
        //-
        map<DSString, bool> negativeWords;
        vector<DSString> misclassified;
    public:
        //method to train sentiment analyzer with an inputted file
        void trainModel(DSString trainingFile);
        //method to test sentiment analyzer with an inputted file
        void testModel(DSString testFile);
        //method to validate model
        void validateModel(DSString trainingFile, DSString testingFile, DSString validationFile);
};
#endif