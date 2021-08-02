#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>
#include "settingsclass.h"
#include "word.h"
#include "inih-master/cpp/INIReader.h"

using namespace std;

int main() {
    srand((unsigned int)time(NULL));

    //Opening config.txt
    INIReader config("config.ini");

    int num_words = config.GetInteger("global", "num_words", -1);

    Settings s1(config);

    s1.print_all_settings();

    vector<Word> wordlist;

    for (int i = 0; i < num_words; i++) {

        Word new_word(s1);

        wordlist.push_back(new_word);

    }

    for (int i = 0; i < num_words; i++) {

        cout << wordlist[i].word << endl;

    }
    

    return 0;
}