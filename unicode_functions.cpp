#include <iostream>
#include <string>
#include <vector>
#include "unicode_functions.h"

using namespace std;

string uni_toupper(string chr) {

    vector<vector<string>> upper = {
        {"A","E","I","O","U"},
        {"æ","ǽ","æ̀","æ̂","æ̃","ǣ"},
        {"Á","É","Í","Ó","Ú"},
        {"À","È","Ì","Ò","Ù"}
    };
    vector<vector<string>> lower = {
        {"a","e","i","o","u"},
        {"Æ","Ǽ","Æ̀","Æ̂","Æ̃","Ǣ"},
        {"á","é","í","ó","ú"},
        {"à","è","ì","ò","ù"}
    };

    for (int i = 0; i < lower.size(); i++) {
        for (int j = 0; j < lower[i].size(); j++) {
            if (chr == lower[i][j]) {

                return upper[i][j];

            }
        }
    }

    cout << "No match found" << endl;
    return chr;

}