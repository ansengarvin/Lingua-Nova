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

        void choose_first_consonant();
        void choose_middle_consonant();
        void choose_last_consonant();

        void choose_first_vowel();
        void choose_middle_vowel();
        void choose_last_vowel();
};

#endif