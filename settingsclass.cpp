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
    
    parse_settings_from_ini(config, vowels, "vowels");

    parse_settings_from_ini(config, consonants, "consonants");

    parse_settings_from_ini(config, excluded_first_syllable_vowels, "excluded_first_syllable_vowels");

    parse_settings_from_ini(config, excluded_first_syllable_consonants, "excluded_first_syllable_consonants");

    parse_settings_from_ini(config, excluded_first_syllable_vowels, "excluded_middle_syllable_vowels");

    parse_settings_from_ini(config, excluded_first_syllable_vowels, "excluded_middle_syllable_vowels");

    parse_settings_from_ini(config, excluded_last_syllable_vowels, "excluded_last_syllable_vowels");
    
    parse_settings_from_ini(config, excluded_last_syllable_consonants, "excluded_last_syllable_consonants");
    
    min_number_syllables = config.GetInteger("settings", "min_syllables", -1);
    max_number_syllables = config.GetInteger("settings","max_syllables", -1);

}

void Settings::parse_settings_from_ini(INIReader config, vector<string> &intended_setting, string setting_name) {

    string raw_settings_string = config.GetString("settings", setting_name, "");
    string temp_substring = "";
    for (int i = 0; i < raw_settings_string.length(); i++) {
        if (raw_settings_string[i] != ',') {
            temp_substring.push_back(raw_settings_string[i]);
        }
        else {
            intended_setting.push_back(temp_substring);
            temp_substring = "";
        }
        if (i == (raw_settings_string.length()-1)) {
            intended_setting.push_back(temp_substring);
        }
    }

}

//Copy this from Settings::Settings if you need to use it for some reason in the future.
void Settings::change_settings(INIReader config) {


}

void Settings::print_all_settings() {

    print_individual_vector_setting(consonants, "consonants");
    print_individual_vector_setting(vowels, "vowels");
    print_individual_vector_setting(excluded_first_syllable_consonants, "first_syllable_consonants");
    print_individual_vector_setting(excluded_first_syllable_vowels, "first_syllable_vowels");
    print_individual_vector_setting(excluded_last_syllable_consonants, "last_syllable_consonants");
    print_individual_vector_setting(excluded_last_syllable_vowels, "last_syllable_vowels");

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