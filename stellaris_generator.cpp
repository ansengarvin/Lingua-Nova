#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include "settingsclass.h"
#include "word.h"
#include "inih-master/cpp/INIReader.h"

using namespace std;

void initialize_marker_vector(vector<vector<int>> & markers, vector<vector<string>> & categories) {

    for (int i = 0; i < categories.size(); i++) {

        vector<int> temp;
        
        markers.push_back(temp);

        for (int j = 0; j < categories[i].size(); j++) {

            markers[i].push_back(0);

        }
    }
}

void add_words(ofstream & nf, int marker, int num_words, vector<vector<Word>> wordlists, vector<int> ini_tracker) {
    
    for (int j = 0; j < num_words; j++) {
        nf << "\"";
        nf << wordlists[marker][ini_tracker[marker]].spelling + "\"";
        if (j < num_words - 1)
            nf << ",";
        ini_tracker[marker]++;
    }


}

void generate_word_array(int num_words, vector<Word> & wordlist, Settings & s1) {

    int n = 0;
    
    while (wordlist.size() < num_words && n < 10000) {

        Word new_word(s1);
        bool cool = 1;
        for (int i = 0; i < wordlist.size(); i++) {

            if (new_word.word == wordlist[i].word) {
                cool = 0;
                n++;
            }

        }

        if(cool) {
            wordlist.push_back(new_word);
            n = 0;
            //cout << "A|";
        }

        else {
            //cout << "R|";
        }
    }

    if (n == 10000) {

        cout << "ERROR: Too many words rejected. Try adding more consonants / vowels, or reducing the number of words to be generated." << endl;
        exit(0);

    }
}

int main() {
    cout << "Welcome to the best name generator" << endl;
    srand((unsigned int)time(NULL));

    INIReader stellaris("stellaris.ini");

    string cfg = stellaris.GetString("global","config.ini","config.ini");

    //Opening config.txt
    INIReader config(cfg);

    int num_words = config.GetInteger("global", "num_words", -1);

    vector<string> sections {
        "ship_names","ship_class_names","fleet_names","army_names","planet_names","character_names"
    };
    
    vector<vector<string>> categories {
        /*ship_names_ini*/{"generic", "corvette", "cruiser", "battleship", "titan", "colussus", "science", "colonizer", "constructor", "transport", "military_station_small", "ion_cannon"},
        /*ship_class_names_ini*/{"generic"},
        /*fleet_names_ini*/{"random_names"},
        /*army_names_ini*/{"machine_defense", "machine_assault_1", "machine_assault_2", "machine_assault_3", "defense_army", "assault_army", "slave_army", "clone_army", "undead_army", "robotic_army", "robotic_defense_army", "psionic_army", "xenomorph_army", "gene_warrior_army", "occupation_army", "robotic_occupation_army", "primitive_army", "industrial_army", "postatomic_army"},
        /*planet_names_ini*/{"generic","pc_desert","pc_tropical","pc_arid","pc_continental","pc_ocean","pc_tundra","pc_arctic","pc_savannah","pc_alpine"},
        /*character_names_ini*/{"full_names","full_names_male","full_names_female","first_names","first_names_male","first_names_female","second_names","regnal_first_names","regnal_first_names_male","regnal_first_names_female","regnal_second_names"}
    };

    vector<vector<int>> word_num_vct;
    vector<string> inis;
    vector<int> ini_sums;
    vector<int> ini_tracker;
    vector<vector<int>> markers;
    vector<vector<int>> itervar;
    initialize_marker_vector(markers, categories);

    
    for (int i = 0; i < categories.size(); i++) {
        vector<int> grump;
        word_num_vct.push_back(grump);
        for (int j = 0; j < categories[i].size(); j++) {
            bool existant = 0;
            string temp = stellaris.GetString(sections[i] + "_ini",categories[i][j],stellaris.GetString("global","default_ini","config.ini"));
            int tnum = stellaris.GetInteger(sections[i] + "_num",categories[i][j],0);
            word_num_vct[i].push_back(tnum);

            if (inis.size() == 0) {

                inis.push_back(temp);
                ini_sums.push_back(tnum);


            }

            else {

                int krabs = -1;
                
                for (int n = 0; n < inis.size(); n++) {
                    krabs = n;
                    if (temp == inis[n]) {
                        ini_sums[n] = ini_sums[n] + tnum;
                        markers[i][j] = n;
                        existant = 1;
                        break;
                    }
                }

                if (existant == 0) {
                    inis.push_back(temp);
                    ini_sums.push_back(tnum);
                    markers[i][j] = krabs + 1;

                }
            }
        }
    }

    for (int i = 0; i < ini_sums.size(); i++) {
        ini_tracker.push_back(0);
    }

    cout << "printing markers" << endl;
    for (int i = 0; i < markers.size(); i++) {

        for (int j = 0; j < markers[i].size(); j++) {

            cout << markers[i][j];

        }
        cout << endl;
    }

    cout << "printing word_num_vct" << endl;
    for (int i = 0; i < word_num_vct.size(); i++) {

        for (int j = 0; j < word_num_vct[i].size(); j++) {

            cout << word_num_vct[i][j] << "+";

        }
        cout << endl;
    }

    cout << "printing inis" << endl;
    for (int x = 0; x < inis.size(); x++) {

        cout << inis[x] << " ";

    }
    cout << endl;

    cout << "printing sums" << endl;
    for (int i = 0; i < ini_sums.size(); i++) {

        cout << ini_sums[i] << " ";

    }
    cout << endl;

    vector<vector<Word>> wordlists;

    cout << "making wordlists" << endl;
    for (int i = 0; i < ini_sums.size(); i++) {

        vector<Word> temp;
        INIReader tempinir("../stellaris_inis/" + inis[i]);
        Settings s1(tempinir,"generic");
        generate_word_array(ini_sums[i],temp,s1);
        wordlists.push_back(temp);

    }

    /*
    cout << "trying to print worz" << endl;
    for (int i = 0; i < wordlists.size(); i++) {
        for (int j = 0; j < wordlists[i].size(); j++) {
            cout << wordlists[i][j].spelling << "-";
        }
        cout << endl;
    }
    */

    /*
    */
    
    string desired_filename = config.GetString("global", "filename", "default");

    ofstream nf("../name_lists/" + desired_filename);

    string tab = "\t";
    string nl = "\n";

    /*
    for (int i = 0; i < num_words; i++) {

        //wordlist[i].word[0] = toupper(wordlist[i].word[0]);
        //cout << "PS: " << wordlist[i].word << endl;

    }

    auto rng = default_random_engine{};
    shuffle(begin(wordlist), end(wordlist), rng);


    for (int i = 0; i < num_words; i++) {
        cout << wordlist[i].word << " || " << wordlist[i].spelling << endl;
        NewFile << wordlist[i].word << " || " << wordlist[i].spelling << endl;
        NewFile << endl;
    }
    */

    bool seq_bool = 0;

    nf << "### " + config.GetString("global", "name", "default") << endl; // using endl instead of nl here to clear the buffer, in case something went wrong in word gen.
    nf << "### Generated by the Novacro Language Generator " + nl + nl;

    nf << config.GetString("stellaris", "acronym", "TSTX") + " = {" + nl;
    nf << tab + "category = \"generated\"" + nl;
    nf << tab + "ship_names = {" + nl + nl;

    vector<string> ship_types = {"generic","corvette","destroyer","cruiser","battleship","titan","colossus","science","colonizer","constructor","transport","military_station_small","ion_cannon"};

    cout << "Selecting ship names" << endl;
    //categories[0]==ship_names section
    for (int i = 0; i < categories[0].size(); i++) {
        int mk = markers[0][i];
        nf << tab + tab + ship_types[i] + " = {" + nl;
        nf << tab + tab + tab;
        //GENERATING NAMES
        add_words(nf, markers[0][i],word_num_vct[0][i],wordlists,ini_tracker);
        //---------
        nf << nl + tab + tab + "}" + nl;

        if (i != ship_types.size() - 1)
            nf << nl;
    }

    nf << tab + "}" + nl + nl;

    cout << "Selecting ship class names" << endl;
    //categories[1]=ship_class_names, [1][0]=generic
    nf << tab + "ship_class_names = {" + nl;
    nf << tab + tab + categories[1][0]+ " = {" + nl;
    nf << tab + tab + tab;
    //GENERATE NAMES HERE
    add_words(nf, markers[1][0],word_num_vct[1][0],wordlists,ini_tracker);
    //There are no non-generic names for this class.
    nf << nl + tab + tab + "}" + nl;
    nf << tab + "}" + nl + nl;


    seq_bool = stellaris.GetBoolean("fleet_names_sequential_titles","prefix_suffix",1);
    
    nf << tab + "fleet_names = {" + nl;
    nf << tab + tab + "random_names = {" + nl;
    //GENERATE NAMES HERE
    //Make sure to add an option for "'s" and another option for fleet_type (e.g. "armada", "navy", etc)
    nf << nl + tab + tab + "}" + nl;
    nf << tab + tab + "sequential_name =";
    //ADDING SEQUENTIAL NAMES
    cout << "seq_bool=" << seq_bool << endl;
    if (!seq_bool) {
        nf << "\"%O% " + stellaris.GetString("fleet_names_sequential_titles","sequential_title","nov_is_great") + "\" ";
    }
    
    else {
        nf << "\"" + stellaris.GetString("fleet_names_sequential_titles","sequential_title","nov_is_great") + " %C%\"";
    }
    nf << nl;
    nf << tab + "}" + nl + nl;

    //ARMIES
    nf << tab + "army_names = {" + nl + nl;

    vector<string> army_types = {"machine_defense", "machine_assault_1", "machine_assault_2", "machine_assault_3", "defense_army", "assault_army", "slave_army", "clone_army", "undead_army", "robotic_army", "robotic_defense_army", "psionic_army", "xenomorph_army", "gene_warrior_army", "occupation_army", "robotic_occupation_army", "primitive_army", "industrial_army", "postatomic_army"};

    for (int i = 0; i < army_types.size(); i++) {

        nf << tab + tab + army_types[i] + " = {" + nl;
        nf << tab + tab + tab + "random_names = {" + nl;
        //for (int i = 0; i <)
        nf << tab + tab + tab + "}" + nl;
        nf << tab + tab + tab + "sequential_name = %O%" + " INSERT"/*INSERT HERE*/ + nl;
        nf << tab + tab + "}" + nl;

        if (i != army_types.size() - 1)
            nf << nl;
    }
    nf << tab + "}" + nl + nl;

    //PLANETS
    nf << tab + "planet_names = {" + nl;

    vector<string> planet_types = {"generic","pc_desert","pc_tropical","pc_arid","pc_continental","pc_ocean","pc_tundra","pc_arctic","pc_savannah","pc_alpine"};
    
    for (int i = 0; i < planet_types.size(); i++) {

        nf << tab + tab + planet_types[i] + " = {" + nl;
        nf << tab + tab + tab + "names = {" + nl;
        //GENERATE NAMES HERE//
        nf << tab + tab + tab + "}" + nl;
        nf << tab + tab + "}" + nl;

        if (i != planet_types.size() - 1)
            nf << nl;
    }
    nf << tab + "}" + nl + nl;

    //CHARACTER NAMES
    nf << tab + "character_names = {" + nl;
    nf << tab + tab + "default = {" + nl;

    vector<string> character_name_types = {"full_names","full_names_male","full_names_female","first_names","first_names_male","first_names_female","second_names","regnal_first_names","regnal_first_names_male","regnal_first_names_female","regnal_second_names"};

    for (int i = 0; i < character_name_types.size(); i++) {

        nf << tab + tab + tab + character_name_types[i] + " = {" + nl;
        //GENERATE NAMES HERE
        nf << tab + tab + tab + "}" + nl;

        if (i != character_name_types.size() - 1)
            nf << nl;

    }

    nf << tab + tab + "}" + nl;
    nf << tab + "}" + nl;

    return 0;
}