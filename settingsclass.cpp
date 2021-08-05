#include <iostream>
#include <fstream>
#include "settingsclass.h"
#include "inih-master/cpp/INIReader.h"

using namespace std;

Settings::Settings() {

    //cout << "ERROR: No config file provided for setting creation." << endl;

}

Settings::Settings(INIReader config) {

    if (config.GetInteger("global", "example_mode", 0) < 1) {
        syllable_distribution = parse_int_vector_from_ini(config, "settings", "syllable_distribution");
        first_consonant_cluster_chance = config.GetInteger("settings","first_consonant_cluster_chance",0);
        middle_consonant_cluster_chance = config.GetInteger("settings","middle_consonant_cluster_chance",0);
        last_consonant_cluster_chance = config.GetInteger("settings","last_consonant_cluster_chance",0);
        
        //cout << "Adding consonants to settings" << endl;
        vector<string> consonant_pool = parse_vector_from_ini(config, "settings", "consonant_pool");

        //vector<string> pool_with_clusters = create_consonant_clusters(consonant_pool);
        
        //cout << "Snipping FC" << endl;
        first_consonants = remove_excluded_phonemes(consonant_pool, parse_vector_from_ini(config, "settings", "excluded_first_consonants"));
        if (first_consonant_cluster_chance >= 1) {
        first_consonant_clusters = create_consonant_clusters(first_consonants);
        first_consonant_clusters = remove_excluded_phonemes(first_consonant_clusters, parse_vector_from_ini(config, "settings", "excluded_first_consonants"));
        }
        //cout << "Snipping MC" << endl;
        middle_consonants = remove_excluded_phonemes(consonant_pool, parse_vector_from_ini(config, "settings", "excluded_middle_consonants"));
        if (middle_consonant_cluster_chance >= 1) {
            middle_consonant_clusters = create_consonant_clusters(middle_consonants);
            middle_consonant_clusters = remove_excluded_phonemes(middle_consonant_clusters, parse_vector_from_ini(config, "settings", "excluded_middle_consonants"));
        }
        //cout << "Snipping LC" << endl;
        last_consonants = remove_excluded_phonemes(consonant_pool, parse_vector_from_ini(config, "settings", "excluded_last_consonants"));
        if (last_consonant_cluster_chance >= 1) {
            last_consonant_clusters = create_consonant_clusters(last_consonants);
            last_consonant_clusters = remove_excluded_phonemes(last_consonant_clusters, parse_vector_from_ini(config, "settings", "excluded_last_consonants"));
        }

        //cout << "Adding vowels to settings" << endl;
        vector<string> vowel_pool = parse_vector_from_ini(config, "settings", "vowel_pool");

        //cout << "Snipping FV" << endl;
        first_vowels = remove_excluded_phonemes(vowel_pool, parse_vector_from_ini(config, "settings", "excluded_first_vowels"));
        //cout << "Snipping MV" << endl;
        middle_vowels = remove_excluded_phonemes(vowel_pool, parse_vector_from_ini(config, "settings", "excluded_middle_vowels"));
        //cout << "Snipping LV" << endl;
        last_vowels = remove_excluded_phonemes(vowel_pool, parse_vector_from_ini(config, "settings", "excluded_last_vowels"));
        
        //min_number_syllables = config.GetInteger("settings", "min_syllables", -1);
        //max_number_syllables = config.GetInteger("settings","max_syllables", -1);
    }

    else {

        vector<string> examples = parse_vector_from_ini(config, "examples", "word_examples");

    }

}

/*OBSOLETE CODE
vector<int> Settings::set_syllable_distribution(INIReader config) {

    vector<int> raw = parse_int_vector_from_ini(config, "settings", "syllable_distribution");
    vector<int> temp;

    for (int i = 0; i < raw.size(); i++) {

        for (int j = 0; j < raw[i]; j++) {

            temp.push_back(i+1);

        }
    }

    return temp;
}
*/

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

vector<int> Settings::parse_int_vector_from_ini(INIReader config, string section, string setting_name) {

    vector<int> temp_vector;
    string raw_settings_string = config.GetString(section, setting_name, "");
    string temp_substring = "";
    for (int i = 0; i < raw_settings_string.length(); i++) {
        if (raw_settings_string[i] != ',') {
            temp_substring.push_back(raw_settings_string[i]);
        }
        else {
            temp_vector.push_back(stoi(temp_substring));
            temp_substring = "";
        }
        if (i == (raw_settings_string.length()-1)) {
            temp_vector.push_back(stoi(temp_substring));
        }
    }

    return temp_vector;
}

void Settings::parse_settings_from_example_words(vector<string> example) {

    for(int i = 0; i < example.size(); i++) {

        for(int j = 0; j < example[i].size(); j++) {

            example[i][j] = tolower(example[i][j]);

        }
    }
}

vector<string> Settings::create_consonant_clusters(vector<string> pool) {

    vector<string> temp;
    
    for (int i = 0; i < pool.size(); i++) {
        for (int j = 0; j < pool.size(); j++) {
            string str = "";
            if (i == j) {
                continue;
            }
            else {
                str.append(pool[i]);
                str.append(pool[j]);
            }
            temp.push_back(str);
        }
    }

    return temp;
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
    print_individual_vector_setting(first_consonant_clusters, "first_consonant_clusters");
    print_individual_vector_setting(middle_consonant_clusters, "middle_consonant_clusters");
    print_individual_vector_setting(last_consonant_clusters, "last_consonant_clusters");
    print_individual_int_vector_setting(syllable_distribution, "syllable_distribution");

    //cout << "min syllables: " << min_number_syllables << endl;
    //cout << "max syllables: " << max_number_syllables << endl;
}

void Settings::print_individual_vector_setting(vector<string> &vs, string setting_name) {

    cout << setting_name << ": ";
    
    for (int i = 0; i < vs.size(); i++) {

        cout << vs[i] << "|";

    }

    cout << endl;
}

void Settings::print_individual_int_vector_setting(vector<int> &vs, string setting_name) {

    cout << setting_name << ": ";
    
    for (int i = 0; i < vs.size(); i++) {

        cout << vs[i] << "|";

    }

    cout << endl;
}