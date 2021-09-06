#ifndef SETTINGSCLASS_H
#define SETTINGSCLASS_H
#include <fstream>
#include <vector>
#include "inih-master/cpp/INIReader.h"

using namespace std;

class Settings {

    public:

        vector<string> consonant_pool;
        vector<string> vowel_pool;
        vector<string> consonant_spelling;
        vector<string> vowel_spelling;

        vector<int> syllable_distribution;
        bool capitalize_words;
        
        vector<string> first_consonants;
        vector<string> first_consonant_spelling;
        vector<int> first_consonant_distribution;
        vector<string> middle_consonants;
        vector<string> middle_consonant_spelling;
        vector<int> middle_consonant_distribution;
        vector<string> last_consonants;
        vector<string> last_consonant_spelling;
        vector<int> last_consonant_distribution;
        
        vector<string> first_vowels;
        vector<string> first_vowel_spelling;
        vector<int> first_vowel_distribution;
        vector<string> middle_vowels;
        vector<string> middle_vowel_spelling;
        vector<int> middle_vowel_distribution;;
        vector<string> last_vowels;
        vector<string> last_vowel_spelling;
        vector<int> last_vowel_distribution;
        
        //Consonant cluster string vectors are commented because I want to handle them on-the-fly using dist

        int first_consonant_cluster_chance;
        //vector<string> first_consonant_clusters;
        vector<string> excluded_first_consonant_clusters;
        int middle_consonant_cluster_chance;
        //vector<string> middle_consonant_clusters;
        vector<string> excluded_middle_consonant_clusters;
        int last_consonant_cluster_chance;
        //vector<string> last_consonant_clusters;
        vector<string> excluded_last_consonant_clusters;

        int first_diphthong_chance;
        //vector<string> first_diphthongs;
        int middle_diphthong_chance;
        //vector<string> middle_diphthongs;
        int last_diphthong_chance;
        //vector<string> last_diphthongs;

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

        vector<string> generate_spelling_vector(vector<string>, vector<string>, vector<string>);

        void change_settings(INIReader);

        void print_all_settings();

        void print_str_vector(vector<string> &, string);

        void print_int_vector(vector<int> &, string);

        void insurance();
};

#endif