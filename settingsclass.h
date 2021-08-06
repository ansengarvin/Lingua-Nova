#ifndef SETTINGSCLASS_H
#define SETTINGSCLASS_H
#include <fstream>
#include <vector>
#include "inih-master/cpp/INIReader.h"

using namespace std;

class Settings {

    public:
        vector<int> syllable_distribution;
        bool capitalize_words;
        
        vector<string> first_consonants;
        vector<int> first_consonant_distribution;
        vector<string> middle_consonants;
        vector<int> middle_consonant_distribution;
        vector<string> last_consonants;
        vector<int> last_consonant_distribution;
        
        vector<string> first_vowels;
        vector<int> first_vowel_distribution;
        vector<string> middle_vowels;
        vector<int> middle_vowel_distribution;;
        vector<string> last_vowels;
        vector<int> last_vowel_distribution;
        
        int first_consonant_cluster_chance;
        vector<string> first_consonant_clusters;
        int middle_consonant_cluster_chance;
        vector<string> middle_consonant_clusters;
        int last_consonant_cluster_chance;
        vector<string> last_consonant_clusters;

        int first_diphthong_chance;
        vector<string> first_diphthongs;
        int middle_diphthong_chance;
        vector<string> middle_diphthongs;
        int last_diphthong_chance;
        vector<string> last_diphthongs;

        vector<string> preneous;
        vector<string> extraneous;

        Settings();

        Settings(INIReader, string);

        vector<int> set_initial_distribution(INIReader, string, string, vector<string>);

        vector<string> parse_vector_from_ini(INIReader, string, string);

        vector<int> parse_int_vector_from_ini(INIReader, string, string);

        //vector<int> set_syllable_distribution(INIReader config);

        void parse_settings_from_example_words(vector<string>);

        vector<string> create_consonant_clusters(vector<string>);

        vector<string> remove_excluded_phonemes(vector<string>, vector<string>, vector<int>, vector<int> &);

        void change_settings(INIReader);

        void print_all_settings();

        void print_str_vector(vector<string> &, string);

        void print_int_vector(vector<int> &, string);
};

#endif