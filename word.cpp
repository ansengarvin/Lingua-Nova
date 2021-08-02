#include "word.h"
#include "settingsclass.h"
#include <string>

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
    int num_vowels = (int)settings.vowels.size();
    int num_consonants = (int)settings.consonants.size();

    //Random length between minimum length and maximum length
    int random_length = rand() % ((settings.max_number_syllables+1) - settings.min_number_syllables) + settings.min_number_syllables;

    if (random_length > 1) {

        random_length = random_length - 2;

    }

    

    for (int i = 0; i < random_length; i++) {
        
        word.append(settings.consonants[rand() % num_consonants]);
        word.append(settings.vowels[rand() % num_vowels]);
        
    }
}

void Word::print_word() {

    cout << word << endl;

}