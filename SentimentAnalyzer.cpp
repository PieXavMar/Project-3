#include "SentimentAnalyzer.h"
#include <set>
#include <sstream>
//training method
void SentimentAnalyzer::trainModel(DSString fileName){
    ifstream input(fileName.c_str());
    if(!input.is_open()){
        cout << "ERROR Opening File" << '\n';
        return;
    }
    char* buffer = new char[1000];
    input.getline(buffer, 1000);
    while(!input.eof()){
        input.getline(buffer, 1000, ',');
        if(strlen(buffer) == 0){
            break;
        }
        //determine snetiment
        bool isPositive = buffer[0] == '4';
        for(int i = 0; i < 4; i++){
            input.getline(buffer, 1000, ',');
        }
        //read tweet
        input.getline(buffer, 1000);
        //tokenize using delimiters
        char* token = strtok(buffer, "!,@#$%^&*()_+/-|{}[];:\"'?~.<> 1234567890\\");
        while(token != nullptr){
            DSString word = token;
            //only words longer than two characters
            if(word.length() > 2){
                word.toLower();
                if(sentimentCounts.find(word) == sentimentCounts.end()){
                    sentimentCounts[word] = isPositive ? make_pair(1, 0) : make_pair(0, 1);
                } 
                else{
                    if(isPositive){
                        //increment positive count
                        sentimentCounts[word].first++;
                    }
                    else{
                        //increment negative count
                        sentimentCounts[word].second++;
                    }
                }
            }
            token = strtok(nullptr, "!,@#$%^&*()_+/-|{}[];:\"'?~.<> 1234567890\\");
        }
    }
    //iterate through and calculate percentage
    for(const auto& entry : sentimentCounts){
        int total = entry.second.first + entry.second.second;
        //words with higher count than 6
        if(total > 6){
            double probability = static_cast<double>(entry.second.first) / total;
            if(probability > 0.6){
                positiveWords[entry.first] = true;
            } 
            else if(probability < 0.4){
                positiveWords[entry.first] = false;
            }
        }
    }
}
//testing function
void SentimentAnalyzer::testModel(DSString fileName){
    ifstream input(fileName.c_str());
    if(!input.is_open()){
        cout << "ERROR Opening File" << '\n';
        return;
    }
    char* buffer = new char[1000];
    input.getline(buffer, 1000);
    //parse file
    while(!input.eof()){
        input.getline(buffer, 1000, ',');
        if(strlen(buffer) == 0){
            break;
        }
        DSString id = buffer;
        for(int i = 0; i < 3; i++){
            input.getline(buffer, 1000, ',');
        }
        //read tweet
        input.getline(buffer, 1000);
        //tokenize tweet
        char* token = strtok(buffer, "!,@#$%^&*()_+/-|{}[];:\"'?~.<> 1234567890\\");
        int sentimentScore = 0;
        while(token != nullptr){
            DSString word = token;
            if(word.length() > 2){
                word.toLower();
                if(positiveWords.find(word) != positiveWords.end()){
                    sentimentScore += positiveWords[word] ? 1 : -1;
                }
            }
            token = strtok(nullptr, "!,@#$%^&*()_+/-|{}[];:\"'?~.<> 1234567890\\");
        }
        //store sentiment score
        sentimentResults[id] = sentimentScore >= 0;
    }
}
//validation function
void SentimentAnalyzer::validateModel(DSString trainingFile, DSString testingFile, DSString outputFile){
    ifstream input(trainingFile.c_str());
    if(!input.is_open()){
        cout << "ERROR Opening File" << '\n';
        return;
    }
    char* buffer = new char[1000];
    input.getline(buffer, 1000);
    while(!input.eof()){
        input.getline(buffer, 1000, ',');
        if(strlen(buffer) == 0){
            break;
        }
        bool isPositive = buffer[0] == '4';
        input.getline(buffer, 1000);
        DSString id = buffer;
        //prediction vs sentiment
        if(sentimentResults[id] != isPositive){
            misclassified.push_back(id);
        }
    }
    //output validation
    ofstream output(outputFile.c_str());
    double accuracy = 1.0 - static_cast<double>(misclassified.size()) / sentimentResults.size();
    output << setprecision(3) << accuracy << endl;
    for(const auto& entry : sentimentResults){
        output << (entry.second ? "4," : "0,") << entry.first << endl;
    }
    output.close();
}