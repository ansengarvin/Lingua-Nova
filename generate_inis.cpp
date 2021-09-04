#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void cpy(ifstream & src, ofstream & dst) {

    string line;
    while(getline(src, line)) {
        cout << "copying_line" << endl;
        dst << line << "\n";
    }

}



int main() {

    vector<string> inis {"ship_generic", "corvette", "cruiser", "battleship", "titan", "colussus", "science", "colonizer", "constructor", "transport", "military_station_small", "ion_cannon",
        "ship_class_names","fleet_names","machine_defense", "machine_assault_1", "machine_assault_2", "machine_assault_3", "defense_army", "assault_army", "slave_army", "clone_army", "undead_army", "robotic_army", "robotic_defense_army", "psionic_army", "xenomorph_army", "gene_warrior_army", "occupation_army", "robotic_occupation_army", "primitive_army", "industrial_army", "postatomic_army",
        "ship_generic","pc_desert","pc_tropical","pc_arid","pc_continental","pc_ocean","pc_tundra","pc_arctic","pc_savannah","pc_alpine",
        "full_names","full_names_male","full_names_female","first_names","first_names_male","first_names_female","second_names","regnal_first_names","regnal_first_names_male","regnal_first_names_female","regnal_second_names"
    };


    ifstream src("config.ini", ios::binary);
    
    for (int i = 0; i < inis.size(); i++) {

        cout << "making for " + inis[i] << endl;
        ofstream dst("../stellaris_inis/" + inis[i] + ".ini", ios::binary);

        cout << "copying" << endl;
        cpy(src,dst);
        dst.close();
        src.clear();
        src.seekg(0);
    }

    ofstream dst("../stellaris_inis/config.ini", ios::binary);
        cpy(src,dst);
        dst.close();
        src.clear();
        src.seekg(0);

    return 0;
}