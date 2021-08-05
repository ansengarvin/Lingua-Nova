#ifndef WORD_H
#define WORD_H

#include "settingsclass.h"
#include <iostream>
#include <string>

using namespace std;

class Word {

    public:
        string word;
        string definition;
        Settings settings;

        Word();

        Word(Settings imported_settings);

        bool add_cluster(int);

        void change_settings(Settings imported_settings);

        void generate_word();

        void print_word();

        int grab_syllable_length();
};

#endif