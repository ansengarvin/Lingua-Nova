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

    generate_word();

}

void Word::change_settings(Settings imported_settings) {

    settings = imported_settings;

}

void Word::generate_word() {

    string temp = "";
    int num_consonants = (int)settings.middle_consonants.size();
    int num_vowels = (int)settings.middle_vowels.size();

    //int random_length = rand() % ((settings.max_number_syllables+1) - settings.min_number_syllables) + settings.min_number_syllables;

    int random_length = grab_syllable_length();
    cout << "G" << random_length;

    for (int i = 0; i < random_length; i++) {

        //GENERATE FIRST SYLLABLE
        if (i == 0) {

            if (settings.first_consonants.size() < 1 && settings.first_vowels.size() < 1) {

                cout << "ERROR: No first vowels or consonants" << endl;
                word.append("E-R-R-O-R");
                return;

            }

            else if (settings.first_vowels.size() < 1 && settings.first_consonants.size() >= 1) {
                word.append(settings.first_consonants[rand() % settings.first_consonants.size()]);
                word.append(settings.middle_vowels[rand() % settings.middle_vowels.size()]);        
            }

            else if (settings.first_vowels.size() >=1 && settings.first_consonants.size() < 1){

                word.append(settings.first_vowels[rand() % settings.first_vowels.size()]);
            }

            else {

                if (rand() % 100 < 50) {

                    word.append(settings.first_consonants[rand() % settings.first_consonants.size()]);
                    word.append(settings.middle_vowels[rand() % settings.middle_vowels.size()]);

                }

                else {

                    word.append(settings.first_vowels[rand() % settings.first_vowels.size()]);

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

                word.append(settings.middle_consonants[rand() % settings.middle_consonants.size()]);
                word.append(settings.middle_vowels[rand() % settings.middle_vowels.size()]);
                word.append(settings.last_consonants[rand() % settings.last_consonants.size()]);

            }

            else if (settings.last_consonants.size() < 1 && settings.last_vowels.size() >= 1) {

                word.append(settings.middle_consonants[rand() % settings.middle_consonants.size()]);
                word.append(settings.last_vowels[rand() % settings.last_vowels.size()]);

            }

            else {

                if ((rand() % 100) < 50) {
                    word.append(settings.middle_consonants[rand() % settings.middle_consonants.size()]);
                    word.append(settings.middle_vowels[rand() % settings.middle_vowels.size()]);
                    word.append(settings.last_consonants[rand() % settings.last_consonants.size()]);
                }

                else {
                    word.append(settings.middle_consonants[rand() % settings.middle_consonants.size()]);
                    word.append(settings.last_vowels[rand() % settings.last_vowels.size()]);
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
                word.append(settings.middle_consonants[rand() % settings.middle_consonants.size()]);
                word.append(settings.middle_vowels[rand() % settings.middle_vowels.size()]);
                
            }
        }
    }
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

        if (settings.syllable_distribution[i] == 0) {

            continue;

        }
        
        else if (seed < settings.syllable_distribution[i] + previous) {

            return i+1;

        }

        else {

            previous = previous + settings.syllable_distribution[i];

        }

    }

}