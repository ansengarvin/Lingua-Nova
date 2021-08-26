#include "word.h"
#include "settingsclass.h"
#include <string>
#include <cctype>

Word::Word() {

    word = "";
    definition = "";

}

Word::Word(Settings imported_settings) {

    settings = imported_settings;
    generate_word(1);

}

void Word::change_settings(Settings imported_settings) {

    settings = imported_settings;

}

void Word::generate_word(bool use_extraneous) {

    if (use_extraneous) {

        for (int i = 0; i < settings.preneous.size(); i++) {

            if (settings.preneous[i] == "{WORD}") {
                generate_word(0);
            }

            else {
                word.append(settings.preneous[i]);
            }
            word.append(" ");
        }
    }
    
    string temp = "";
    int num_consonants = (int)settings.middle_consonants.size();
    int num_vowels = (int)settings.middle_vowels.size();

    //int random_length = rand() % ((settings.max_number_syllables+1) - settings.min_number_syllables) + settings.min_number_syllables;

    int random_length = grab_syllable_length();
    //cout << "G" << random_length;

    for (int i = 0; i < random_length; i++) {

        //GENERATE FIRST SYLLABLE
        if (i == 0) {

            if (settings.first_consonants.size() < 1 && settings.first_vowels.size() < 1) {
                cout << "ERROR: No first vowels or consonants" << endl;
                word.append("E-R-R-O-R");
                return;
            }

            else if (settings.first_vowels.size() < 1 && settings.first_consonants.size() >= 1) {
                choose_first_consonant();
                choose_middle_vowel();      
            }

            else if (settings.first_vowels.size() >=1 && settings.first_consonants.size() < 1){
                choose_first_vowel();
            }

            else {

                if (rand() % 100 < 50) {
                    choose_first_consonant();
                    choose_middle_vowel();
                }

                else {
                    choose_first_vowel();

                    if (random_length == 1 && rand() % 100 < 50) {
                        choose_middle_consonant();
                    }
                }
            }
        }

        //GENERATE LAST SYLLABLE
        else if (i == (random_length - 1)) {
            
            if (settings.last_consonants.size() < 1 && settings.last_vowels.size() < 1) {
                cout << "ERROR: No last consonants or vowels to choose from" << endl;
                word.append("E-R-R-O-R");
            }

            else if (settings.last_consonants.size() >= 1 && settings.last_vowels.size() < 1) {
                choose_middle_consonant();
                choose_middle_vowel();
                choose_last_consonant();
            }

            else if (settings.last_consonants.size() < 1 && settings.last_vowels.size() >= 1) {
                choose_middle_consonant();
                choose_last_vowel();
            }

            else {

                if ((rand() % 100) < 50) {
                    choose_middle_consonant();
                    choose_middle_vowel();
                    choose_last_consonant();
                }

                else {
                    choose_middle_consonant();
                    choose_last_vowel();
                }
            }
        }
        
        //GENERATE MIDDLE SYLLABLE
        else {
            
            if (settings.middle_consonants.size() < 1 || settings.middle_vowels.size() < 1) {
                cout << "ERROR: You must have at least one middle consonant AND at least one middle vowel" << endl;
                word.append("E-R-R-O-R");
            }

            else {
                choose_middle_consonant();
                choose_middle_vowel();       
            }
        }
    }

    if (use_extraneous) {

        for (int i = 0; i < settings.extraneous.size(); i++) {

            word.append(" ");
            if (settings.extraneous[i] == "{WORD}") {
                generate_word(0);
            }

            else {
                word.append(settings.extraneous[i]);
            }
        }
    }
}

bool Word::add_cluster(int chance) {
    
    int num = rand() % 100 + 1;
    //cout << "Num is " << num << " and chance is " << chance << endl;
    
    if (num <= chance)
         return true;

    else
        return false;


}

void Word::print_word() {

    cout << word << endl;

}

int Word::grab_syllable_length() {

    int array_sum = 0;

    for (int i = 0; i < settings.syllable_distribution.size(); i++) {

        array_sum = array_sum + settings.syllable_distribution[i];

    }

    int seed = rand() % array_sum;
    int previous = 0;

    for (int i = 0; i < settings.syllable_distribution.size(); i++) {
        
        if (seed < settings.syllable_distribution[i] + previous) {

            return i+1;

        }

        else {

            previous = previous + settings.syllable_distribution[i];

        }
    }
}

int Word::select_from_dist(vector<string> pool, vector<int> dist) {

    //cout << "attemping to choose from distribution" << endl;

    //cout << "p: " << dist.size() << " " << pool.size() << endl;
    
    if (dist.size() != pool.size()) {

        cout << "ERROR: Require same number of distribution numbers as phonemes" << endl;
        exit(0);

    }

    int sum = 0;

    //cout << "setting dist sum" << endl;

    for (int i = 0; i < dist.size(); i++) {

        sum = sum + dist[i];

    }

    //cout << "getting rng number based on dist" << endl;

    int rng = rand() % sum + 1;
    int previous = 0;

    //cout << "selecting i from dist" << endl;

    for (int i = 0; i < dist.size(); i++) {

        //cout << "i=" << i << endl;
        if (rng <= dist[i] + previous) {

            //cout << "attempting to return i" << endl;
            return i;

        }
            

        else
            previous = previous + i;

    }
}

void Word::choose_first_consonant() {

    //cout << "choosing first consonant" << endl;

    string temp;
    
    int rng = select_from_dist(settings.first_consonants, settings.first_consonant_distribution);
    
    if (add_cluster(settings.first_consonant_cluster_chance)) {

        temp.append(settings.first_consonant_clusters[rand() % settings.first_consonant_clusters.size()]);
        
    }
        
    else {

        word.append(settings.first_consonants[rng]);
        temp.append(settings.first_consonant_spelling[rng]);

    }

    if (settings.capitalize_words) {
        temp[0] = toupper(temp[0]);
    }

    spelling.append(temp);

}

void Word::choose_middle_consonant() {

    //cout << "choosing middle consonant" << endl;

    int rng = select_from_dist(settings.middle_consonants, settings.middle_consonant_distribution);
    
    if (add_cluster(settings.middle_consonant_cluster_chance))
        word.append(settings.middle_consonant_clusters[rand() % settings.middle_consonant_clusters.size()]);

    else {
        word.append(settings.middle_consonants[rng]);
        spelling.append(settings.middle_consonant_spelling[rng]);
    }        

}

void Word::choose_last_consonant() {

    //cout << "choosing last consonant" << endl;

    int rng = select_from_dist(settings.last_consonants, settings.last_consonant_distribution);
    
    if (add_cluster(settings.last_consonant_cluster_chance))
	    word.append(settings.last_consonant_clusters[rand() % settings.last_consonant_clusters.size()]);

    else {
        word.append(settings.last_consonants[rng]);
        spelling.append(settings.last_consonant_spelling[rng]);
    }

}

void Word::choose_first_vowel() {

    //cout << "choosing first vowel" << endl;

    string temp;
    int rng = select_from_dist(settings.first_vowels, settings.first_vowel_distribution);

    word.append(settings.first_vowels[rng]);
    
    temp.append(settings.first_vowel_spelling[rng]);

    if (settings.capitalize_words)
        temp[0] = toupper(temp[0]);


    spelling.append(temp);


}

void Word::choose_middle_vowel() {

    //cout << "choosing middle vowel" << endl;

    int rng = select_from_dist(settings.middle_vowels, settings.middle_vowel_distribution);
    
    word.append(settings.middle_vowels[rng]);
    spelling.append(settings.middle_vowel_spelling[rng]);

}

void Word::choose_last_vowel() {

    //cout << "choosing last vowel" << endl;

    int rng = select_from_dist(settings.last_vowels, settings.last_vowel_distribution);

    //cout << "rng=" << rng << endl;

    word.append(settings.last_vowels[rng]);
    spelling.append(settings.last_vowel_spelling[rng]);

}