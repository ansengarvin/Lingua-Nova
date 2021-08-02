#ifndef SETTINGSCLASS_H
#define SETTINGSCLASS_H
#include <fstream>
#include <vector>
#include "inih-master/cpp/INIReader.h"

using namespace std;

class Settings {

    public:
        vector<string> vowels;
        vector<string> consonants;
        vector<string> excluded_first_syllable_consonants;
        vector<string> excluded_first_syllable_vowels;
        vector<string> excluded_middle_syllable_consonants;
        vector<string> excluded_middle_syllable_vowels;
        vector<string> excluded_last_syllable_consonants;
        vector<string> excluded_last_syllable_vowels;
        int min_number_syllables;
        int max_number_syllables;

        Settings();

        Settings(INIReader);

        void parse_settings_from_ini(INIReader, vector<string> &, string);

        void change_settings(INIReader);

        void print_all_settings();

        void print_individual_vector_setting(vector<string> &, string);
};

#endif