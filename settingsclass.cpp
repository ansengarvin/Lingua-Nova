#include <iostream>
#include <fstream>
#include "settingsclass.h"
#include "inih-master/cpp/INIReader.h"

using namespace std;

Settings::Settings() {

    min_number_syllables = 0;
    max_number_syllables = 0;

}

Settings::Settings(INIReader config) {

    if (config.GetInteger("global", "example_mode", 0) < 1) {
        //cout << "Adding consonants to settings" << endl;
        vector<string> consonant_pool = parse_vector_from_ini(config, "settings", "consonant_pool");

        //cout << "Snipping FC" << endl;
        first_consonants = remove_excluded_phonemes(consonant_pool, parse_vector_from_ini(config, "settings", "excluded_first_consonants"));
        //cout << "Snipping MC" << endl;
        middle_consonants = remove_excluded_phonemes(consonant_pool, parse_vector_from_ini(config, "settings", "excluded_middle_consonants"));
        //cout << "Snipping LC" << endl;
        last_consonants = remove_excluded_phonemes(consonant_pool, parse_vector_from_ini(config, "settings", "excluded_last_consonants"));

        //cout << "Adding vowels to settings" << endl;
        vector<string> vowel_pool = parse_vector_from_ini(config, "settings", "vowel_pool");

        //cout << "Snipping FV" << endl;
        first_vowels = remove_excluded_phonemes(vowel_pool, parse_vector_from_ini(config, "settings", "excluded_first_vowels"));
        //cout << "Snipping MV" << endl;
        middle_vowels = remove_excluded_phonemes(vowel_pool, parse_vector_from_ini(config, "settings", "excluded_middle_vowels"));
        //cout << "Snipping LV" << endl;
        last_vowels = remove_excluded_phonemes(vowel_pool, parse_vector_from_ini(config, "settings", "excluded_last_vowels"));
        
        min_number_syllables = config.GetInteger("settings", "min_syllables", -1);
        max_number_syllables = config.GetInteger("settings","max_syllables", -1);
    }

    else {

        vector<string> examples = parse_vector_from_ini(config, "examples", "word_examples");

    }

}

vector<string> Settings::parse_vector_from_ini(INIReader config, string section, string setting_name) {

    vector<string> temp_vector;
    string raw_settings_string = config.GetString(section, setting_name, "");
    string temp_substring = "";
    for (int i = 0; i < raw_settings_string.length(); i++) {
        if (raw_settings_string[i] != ',') {
            temp_substring.push_back(raw_settings_string[i]);
        }
        else {
            temp_vector.push_back(temp_substring);
            temp_substring = "";
        }
        if (i == (raw_settings_string.length()-1)) {
            temp_vector.push_back(temp_substring);
        }
    }

    cout << "Temp vector size is " << temp_vector.size() << endl;
    cout << "Returning temp vector" << endl;
    return temp_vector;
}

void Settings::parse_settings_from_example_words(vector<string> example) {

    for(int i = 0; i < example.size(); i++) {

        for(int j = 0; j < example[i].size(); j++) {

            example[i][j] = tolower(example[i][j]);

        }
    }
}

vector<string> Settings::remove_excluded_phonemes(vector<string> pool, vector<string> exclude_pool) {

    vector<string> temp;
    
    if (exclude_pool.size() == 0) {
        cout << "Exclude pool size is zero" << endl;
        return pool;
    }

    //If any letter in the pool is excluded, do not add to the final string.
    for (int i = 0; i < pool.size(); i++) {

        bool is_okay = 1;

        for (int j = 0; j < exclude_pool.size(); j++) {

            if (pool[i] == exclude_pool[j]) {
                
                cout << pool[i] << " is equal to " << exclude_pool[j] << endl;
                is_okay = 0;

            }

        }

        if (is_okay) {

            cout << "pushing " << pool[i] << " to temp" << endl;
            temp.push_back(pool[i]);

        }
    }

    return temp;
}

//Copy this from Settings::Settings if you need to use it for some reason in the future.
void Settings::change_settings(INIReader config) {


}

void Settings::print_all_settings() {

    cout << "Attempting to print settings" << endl;
    print_individual_vector_setting(first_consonants, "first_consonants");
    print_individual_vector_setting(middle_consonants, "middle_consonants");
    print_individual_vector_setting(last_consonants, "last_consonants");
    print_individual_vector_setting(first_vowels, "first_vowels");
    print_individual_vector_setting(middle_vowels, "middle_vowels");
    print_individual_vector_setting(last_vowels, "last_vowels");

    cout << "min syllables: " << min_number_syllables << endl;
    cout << "max syllables: " << max_number_syllables << endl;
}

void Settings::print_individual_vector_setting(vector<string> &vs, string setting_name) {

    cout << setting_name << ": ";
    
    for (int i = 0; i < vs.size(); i++) {

        cout << vs[i] << "|";

    }

    cout << endl;
}