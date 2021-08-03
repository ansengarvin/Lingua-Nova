#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include <algorithm>
#include "settingsclass.h"
#include "word.h"
#include "inih-master/cpp/INIReader.h"

using namespace std;

int main() {
    cout << "Welcome to the best name generator" << endl;
    srand((unsigned int)time(NULL));

    //Opening config.txt
    INIReader config("config.ini");

    int num_words = config.GetInteger("global", "num_words", -1);

    Settings s1(config);

    s1.print_all_settings();

    vector<Word> wordlist;

    int n = 0;

    while (wordlist.size() < num_words && n < 10000) {

        Word new_word(s1);
        bool cool = 1;
        for (int i = 0; i < wordlist.size(); i++) {

            if (new_word.word == wordlist[i].word) {
                cool = 0;
                n++;
            }

        }

        if(cool) {
            wordlist.push_back(new_word);
            n = 0;
        }
    }

    if (n == 10000) {

        cout << "ERROR: Too many words rejected. Try adding more consonants / vowels, or reducing the number of words to be generated." << endl;
        return 420;

    }

    string desired_filename = config.GetString("global", "filename", "default");

    ofstream NewFile("../generated_files/" + desired_filename);
    
    for (int i = 0; i < num_words; i++) {

        wordlist[i].word[0] = toupper(wordlist[i].word[0]);
        cout << "Writing " << wordlist[i].word << endl;
        NewFile << wordlist[i].word;
        NewFile << endl;

    }
    

    return 0;
}