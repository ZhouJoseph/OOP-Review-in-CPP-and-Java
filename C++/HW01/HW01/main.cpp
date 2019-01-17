//
//  main.cpp
//  HW01
//
//  Created by 周凯旋 on 1/16/19.
//  Copyright © 2019 Kaixuan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// decrypts the char based on the steps given
char decrypt_char(char encrypted_char, int step){
    if(encrypted_char >= 'a' && encrypted_char <= 'z'){
        return (encrypted_char - 'a' - step >= 0) ? encrypted_char - step : ('z' + (encrypted_char - 'a' - step) + 1);
    }
    return encrypted_char;
}

// decrypt the given string based on the steps given
void decrypt_string(string& encrypted_string, int step){
    for (size_t i = 0; i < encrypted_string.size(); ++i) {
        encrypted_string[i] = decrypt_char(encrypted_string[i], step);
    }
}

int main() {
    string file_to_be_open = "file.txt";
    ifstream ifs(file_to_be_open); //open the file
    if (!ifs) { // check if the file exists
        cerr << "Could not open the file.\n";
        exit(1);
    }
    int step; string line; vector<string> collection;
    
    ifs >> step;
    getline(ifs, line); //get rid of the first line of the file

    while(getline(ifs,line)){
        decrypt_string(line, step);
        collection.push_back(line);
    }
    
    for (size_t i = 0; i < collection.size(); ++i) {
        cout << collection[collection.size() - i] << endl;
    }
    
    ifs.close();
}
