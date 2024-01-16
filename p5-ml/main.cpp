// Project UID db1f506d06d84ab787baf250c265e24e

#include <map>
#include <set>
#include <iostream>
#include <string>
#include "csvstream.h"
#include <cmath>
#include <float.h>

using namespace std;

class Classifier
{
private:
    /* data */
    // label
    // The total number of posts in the entire training set.
    int total = 0; 
    // The number of unique words in the entire training set. (The vocabulary size.)
    set<string> uniqueWords; 
    // For each word w, number of posts in entire training set that contain word w.
    map<string, int> numPostW;
    // For each label C, number of posts with that label C.
    map<string, int> numPostC;
    // For each label C and word w, the number of posts with label C that contain w.
    // <label, <word, number>>
    map<string, map<string, int>> numPostCW;
    map<string, double> logLikehood;
    map<string, double> logPrior;
    bool debug = false;


public:
    

    Classifier(/* args */);
    ~Classifier();
    // train the classifier and make predictions for new piazza posts
    
    void setDebug(bool debug_in){
        debug = debug_in;
    }
    
    void inputData(csvstream &csvin){

        // A row is a map<string, string>, key = column name, value = datum
        map<string, string> row;

        if (debug) {
            cout << "training data:" << endl;
        }

        // Read file
        while (csvin >> row) {
            string tag = row["tag"];
            string content = row["content"];
            insertRow(tag, content);       
            total += 1;
        }
        cout << "trained on " << total << " examples" << endl;

        if (debug) {
            cout << "vocabulary size = " << uniqueWords.size() << endl;
        }

        cout << "\n";
    }

    void train(){
        if (debug) {
            cout << "classes:" << endl;
        }

        calculatePrior();

        if (debug) {
            cout << "classifier parameters:" <<endl;
        }

        // calculate total log-prior + log-likehood
        for (auto itLabel : numPostC) {
            string label = itLabel.first;
            for (auto itword : numPostCW[label]) { 
                string word = itword.first;
                double likehood = calculateLikehood(label, word);
                if (debug) {
                    cout << "  " << label << ":" << word << ",";
                    cout << " count = " << numPostCW[label][word] << ",";
                    cout << " log-likelihood = " << likehood << endl;
                }
            }
        }

        if (debug) {
            cout << "\n";
        }
    }

    void predFrame(csvstream &test_data){
        // Prepare
        map <string, string> test_row; // <col name, col content>
        int corrected = 0;
        int test_total = 0;

        cout << "test data:" << endl;

        while (test_data >> test_row) {
            string correct_tag = test_row["tag"];
            string test_content = test_row["content"];

            string pred_label = "";
            double log_prob = predSentence(unique_words(test_content), pred_label);

            cout << "  correct = " << correct_tag << ", predicted = " << pred_label 
                << ", log-probability score = " << log_prob << endl;
            cout << "  content = " << test_content << endl;
            cout << "\n";

            if (correct_tag == pred_label) {
                corrected += 1;
            }
            test_total += 1;
        }

        cout << "performance: " << corrected << " / " << test_total 
            << " posts predicted correctly" << endl;
    }

private:
    // MODIFIES: uniqueWords
    // EFFECTS: Return a set of unique whitespace delimited words.x 
    //          and update new word into uniqueWords
    set<string> unique_words(const string &str) {
        istringstream source(str);
        set<string> words;
        string word;
        while (source >> word) {
            words.insert(word);
            uniqueWords.insert(word);
        }
        return words;
    }
    

    // MODIFIES: uniqueWords, numPostC, numPostW, numPostCW
    // EFFECTS : increase numPostC, numPostW, and numPostCW by 1, print infor as desired
    void insertRow(const string &label, const string &content){
        if (debug) {
            cout << "  label = " << label << ", content = " << content << endl;
        }
        numPostC[label] += 1;
        set<string> split = unique_words(content);

        for (string word : split){
            numPostW[word] += 1;
            numPostCW[label][word] += 1;
        }
    }

    void calculatePrior(){
        for (auto itLabel : numPostC) { // double?
            double prior = log(double(itLabel.second) / double(total));
            logPrior[itLabel.first] = prior;
            if (debug) {
                cout << "  " << itLabel.first << ", " << itLabel.second 
                    << " examples, log-prior = " << prior << endl;
            }
        }
    }

    // MODIFIES: prob
    // EFFECTS : 
    // Avoid 0
    double calculateLikehood(const string &label, const string &word){
        double likehood = 0;
        double numerator = double(numPostCW[label][word]);
        double denumerator = double(numPostC[label]);

        if (numerator == 0){
            numerator = numPostW[word];
            denumerator = double (total);
        }

        if (numerator == 0) {
            numerator = 1;
        }

        likehood = log(numerator / denumerator);

        return likehood; 
    }

    double predSentence(const set<string> &words, string &pred_label) {
        double max_score = -DBL_MAX; // Since all ln give nigative results

        for (auto itLabel : numPostC) {
            string label = itLabel.first;
            double score = logPrior[label];

            for (string word : words) {
                score += calculateLikehood(label, word);
            }
            if (score > max_score) {
                max_score = score;
                pred_label = label;
            }
        }
        return max_score;
    }
};

Classifier::Classifier(/* args */)
{
}

Classifier::~Classifier()
{
}

int main(int argc, char **argv) {
    cout.precision(3);
    Classifier classifier;

    if (argc != 3 && argc !=4){
        cout  <<  "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]"  <<  endl;
        return -1;
    }

    bool debug_in = false;
    if (argc == 4){
        if (string(argv[3]) == "--debug"){
            debug_in = true;
        }else{
            cout  <<  "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]"  <<  endl;
            return -1;
        }
    }

    string trainFile = argv[1];
    string testFile = argv[2];
    csvstream train_in(trainFile, ',', false);
    csvstream test_in(testFile, ',', false);

    // 1. load data (update nums, total, words set)
    // 2. train (private: calculate prob & likehood)
    // 3. test 
    // [output (debug or not)]

    classifier.setDebug(debug_in);
    classifier.inputData(train_in);
    classifier.train();
    classifier.predFrame(test_in);
}   

    
