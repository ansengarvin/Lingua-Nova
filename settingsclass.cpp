#include <iostream>
#include <fstream>
#include "settingsclass.h"
#include "inih-master/cpp/INIReader.h"

using namespace std;

Settings::Settings() {

    //cout << "ERROR: No config file provided for setting creation." << endl;

}

Settings::Settings(INIReader config, string section) {

    if (config.GetInteger("global", "example_mode", 0) < 1) {
        syllable_distribution = parse_int_vector_from_ini(config, section, "syllable_distribution");
        capitalize_words = config.GetInteger(section,"capitalize_word",1);
        //cout << "Capitalize_words=" << capitalize_words;

        first_consonant_cluster_chance = config.GetInteger(section,"first_consonant_cluster_chance",0);
        middle_consonant_cluster_chance = config.GetInteger(section,"middle_consonant_cluster_chance",0);
        last_consonant_cluster_chance = config.GetInteger(section,"last_consonant_cluster_chance",0);
        
        //cout << "Adding consonants to settings" << endl;
        consonant_pool = parse_vector_from_ini(config, section, "consonant_pool");

        //cout << "Setting phoneme distribution" << endl;
        vector<int> consonant_distribution = set_initial_distribution(config, section, "consonant_distribution", consonant_pool);

        consonant_spelling = parse_vector_from_ini(config, section, "consonant_spelling");

        if (consonant_pool.size() != consonant_spelling.size()) {

            cout << "ERROR: consonant pool is not same size as it's spelling pool" << endl;
            exit(0);

        }

        //vector<string> pool_with_clusters = create_consonant_clusters(consonant_pool);
        
        //cout << "Snipping FC" << endl;
        first_consonants = remove_excluded_phonemes(consonant_pool, parse_vector_from_ini(config, section, "excluded_first_consonants"), consonant_distribution, first_consonant_distribution);
        first_consonant_spelling = generate_spelling_vector(first_consonants, consonant_pool, consonant_spelling);
        if (first_consonant_cluster_chance) {
            first_consonant_clusters = create_consonant_clusters(first_consonants);
            //first_consonant_clusters = remove_excluded_phonemes(first_consonant_clusters, parse_vector_from_ini(config, section, "excluded_first_consonants"));
        }
        //cout << "Snipping MC" << endl;
        middle_consonants = remove_excluded_phonemes(consonant_pool, parse_vector_from_ini(config, section, "excluded_middle_consonants"), consonant_distribution, middle_consonant_distribution);
        middle_consonant_spelling = generate_spelling_vector(middle_consonants, consonant_pool, consonant_spelling);
        if (middle_consonant_cluster_chance) {
            middle_consonant_clusters = create_consonant_clusters(middle_consonants);
            //middle_consonant_clusters = remove_excluded_phonemes(middle_consonant_clusters, parse_vector_from_ini(config, section, "excluded_middle_consonants"));
        }
        //cout << "Snipping LC" << endl;
        last_consonants = remove_excluded_phonemes(consonant_pool, parse_vector_from_ini(config, section, "excluded_last_consonants"), consonant_distribution, last_consonant_distribution);
        last_consonant_spelling = generate_spelling_vector(last_consonants, consonant_pool, consonant_spelling);
        if (last_consonant_cluster_chance) {
            last_consonant_clusters = create_consonant_clusters(last_consonants);
            //last_consonant_clusters = remove_excluded_phonemes(last_consonant_clusters, parse_vector_from_ini(config, section, "excluded_last_consonants"));
        }

        //cout << "Adding vowels to settings" << endl;
        vowel_pool = parse_vector_from_ini(config, section, "vowel_pool");
        vector<int> vowel_distribution = set_initial_distribution(config, section, "vowel_distribution", vowel_pool);
        vowel_spelling = parse_vector_from_ini(config, section, "vowel_spelling");

        if (vowel_pool.size() != vowel_spelling.size()) {

            cout << "ERROR: vowel pool is not same size as it's spelling pool" << endl;
            exit(0);

        }

        //cout << "Snipping FV" << endl;
        first_vowels = remove_excluded_phonemes(vowel_pool, parse_vector_from_ini(config, section, "excluded_first_vowels"), vowel_distribution, first_vowel_distribution);
        first_vowel_spelling = generate_spelling_vector(first_vowels, vowel_pool, vowel_spelling);
        //cout << "Snipping MV" << endl;
        middle_vowels = remove_excluded_phonemes(vowel_pool, parse_vector_from_ini(config, section, "excluded_middle_vowels"), vowel_distribution, middle_vowel_distribution);
        middle_vowel_spelling = generate_spelling_vector(middle_vowels, vowel_pool, vowel_spelling);
        //cout << "Snipping LV" << endl;
        last_vowels = remove_excluded_phonemes(vowel_pool, parse_vector_from_ini(config, section, "excluded_last_vowels"), vowel_distribution, last_vowel_distribution);
        last_vowel_spelling = generate_spelling_vector(last_vowels, vowel_pool, vowel_spelling);
        
        //min_number_syllables = config.GetInteger(section, "min_syllables", -1);
        //max_number_syllables = config.GetInteger(section,"max_syllables", -1);
        preneous = parse_vector_from_ini(config, section, "preneous");
        extraneous = parse_vector_from_ini(config, section, "extraneous");
    }

    else {

        vector<string> examples = parse_vector_from_ini(config, "examples", "word_examples");

    }

}

vector<int> Settings::set_initial_distribution(INIReader config, string section, string setting, vector<string> pool) {

    vector<int> distribution;
    
    if (config.GetInteger(section, "enable_phoneme_distribution", 0)) {
        
        distribution = parse_int_vector_from_ini(config, section, setting);

        print_int_vector(distribution, "distribution");
        print_str_vector(pool, "pool");
        
        if (pool.size() != distribution.size()) {

            cout << "Error: Distribution is smaller than pool." << endl;
            exit(0);
        }
    }

    else {

        for (int i = 0; i < pool.size(); i++) {

            distribution.push_back(1);

        }
    }

    return distribution;
}

/*OBSOLETE CODE
vector<int> Settings::set_syllable_distribution(INIReader config) {

    vector<int> raw = parse_int_vector_from_ini(config, section, "syllable_distribution");
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

vector<string> Settings::remove_excluded_phonemes(vector<string> pool, vector<string> exclude_pool, vector<int> pool_dist, vector<int> &dist) {

    vector<string> temp;

    //If any letter in the pool is excluded, do not add to the final string.
    for (int i = 0; i < pool.size(); i++) {

        bool is_okay = 1;

        for (int j = 0; j < exclude_pool.size(); j++) {

            if (pool[i] == exclude_pool[j]) {
                
                //cout << pool[i] << " is equal to " << exclude_pool[j] << endl;
                is_okay = 0;

            }

        }

        if (is_okay) {

            //cout << "pushing " << pool[i] << " to temp" << endl;
            temp.push_back(pool[i]);
            dist.push_back(pool_dist[i]);

        }
    }

    return temp;
}

vector<string> Settings::generate_spelling_vector(vector<string> shorty, vector<string> pool, vector<string> spelling_pool) {

    //cout << "Generating spelling vector" << endl;
    
    if (pool.size() != spelling_pool.size()) {

        cout << "Pool size is not equal to spelling pool size" << endl;
        exit(0);

    }
    
    vector<string> new_pool;
    
    for (int i = 0; i < shorty.size(); i++) {

        //cout << "i=" << i << ",";

        for (int j = 0; j < pool.size(); j++) {
            //cout << "j=" << j << ":";

            if (shorty[i] == pool[j]) {
                //cout << "F|" << endl;
                new_pool.push_back(spelling_pool[j]);
                continue;
            }

        }
    }

    return new_pool;
}

//Copy this from Settings::Settings if you need to use it for some reason in the future.
void Settings::change_settings(INIReader config) {


}

void Settings::print_all_settings() {

    cout << "Attempting to print settings" << endl;
    print_int_vector(syllable_distribution, "syllable_distribution");
    cout << endl;
    print_str_vector(first_consonants, "first_consonants");
    print_int_vector(first_consonant_distribution, "first_consonant_distribution");
    print_str_vector(middle_consonants, "middle_consonants");
    print_int_vector(middle_consonant_distribution, "middle_consonant_distribution");
    print_str_vector(last_consonants, "last_consonants");
    print_int_vector(last_consonant_distribution, "last_consonant_distribution");
    cout << endl;
    print_str_vector(first_vowels, "first_vowels");
    print_int_vector(first_vowel_distribution, "first_vowel_distribution");
    print_str_vector(middle_vowels, "middle_vowels");
    print_int_vector(middle_vowel_distribution, "middle_vowel_distribution");
    print_str_vector(last_vowels, "last_vowels");
    print_int_vector(middle_vowel_distribution, "middle_vowel_distribution");
    cout << endl;
    print_str_vector(first_consonant_clusters, "first_consonant_clusters");
    print_str_vector(middle_consonant_clusters, "middle_consonant_clusters");
    print_str_vector(last_consonant_clusters, "last_consonant_clusters");
    print_int_vector(syllable_distribution, "syllable_distribution");

    //cout << "min syllables: " << min_number_syllables << endl;
    //cout << "max syllables: " << max_number_syllables << endl;
}

void Settings::print_str_vector(vector<string> &vs, string setting_name) {

    cout << setting_name << ": ";
    
    for (int i = 0; i < vs.size(); i++) {

        cout << vs[i] << "|";

    }

    cout << endl;
}

void Settings::print_int_vector(vector<int> &vs, string setting_name) {

    cout << setting_name << ": ";
    
    for (int i = 0; i < vs.size(); i++) {

        cout << vs[i] << "|";

    }

    cout << endl;
}