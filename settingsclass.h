#ifndef SETTINGSCLASS_H
#define SETTINGSCLASS_H
#include <fstream>
#include <vector>
#include "inih-master/cpp/INIReader.h"

using namespace std;

class Settings {

    public:
        vector<string> first_consonants;
        vector<string> first_vowels;
        vector<string> middle_consonants;
        vector<string> middle_vowels;
        vector<string> last_consonants;
        vector<string> last_vowels;
        int min_number_syllables;
        int max_number_syllables;

        Settings();

        Settings(INIReader);

        vector<string> parse_vector_from_ini(INIReader, string, string);

        void parse_settings_from_example_words(vector<string> example);

        vector<string> remove_excluded_phonemes(vector<string>, vector<string>);

        void change_settings(INIReader);

        void print_all_settings();

        void print_individual_vector_setting(vector<string> &, string);
};

#endif