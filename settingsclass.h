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
        int first_consonant_cluster_chance;
        vector<string> first_consonant_clusters;

        vector<string> middle_consonants;
        vector<string> middle_vowels;
        int middle_consonant_cluster_chance;
        vector<string> middle_consonant_clusters;

        vector<string> last_consonants;
        vector<string> last_vowels;
        int last_consonant_cluster_chance;
        vector<string> last_consonant_clusters;
        //int min_number_syllables;
        //int max_number_syllables;
        vector<int> syllable_distribution;

        Settings();

        Settings(INIReader);

        vector<string> parse_vector_from_ini(INIReader, string, string);

        vector<int> parse_int_vector_from_ini(INIReader, string, string);

        //vector<int> set_syllable_distribution(INIReader config);

        void parse_settings_from_example_words(vector<string>);

        vector<string> create_consonant_clusters(vector<string>);

        vector<string> remove_excluded_phonemes(vector<string>, vector<string>);

        void change_settings(INIReader);

        void print_all_settings();

        void print_individual_vector_setting(vector<string> &, string);

        void print_individual_int_vector_setting(vector<int> &, string);
};

#endif