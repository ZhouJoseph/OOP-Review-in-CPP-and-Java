//
//  main.cpp
//  hw02
//
//  Created by 周凯旋 on 1/21/19.
//  Copyright © 2019 Kaixuan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Warrior;

void after_battle(Warrior& a, Warrior& b);

struct Warrior{
    Warrior(const string& name, int power):name(name),power(power){}
    
    
    void reset_power(Warrior& warrior, int new_power){
        warrior.power = new_power;
    }
    
    void battle(Warrior& opponent){
        cout << this->name << " battles " << opponent.name << endl;
        if(this->power == 0 && opponent.power == 0){
            cout << "Oh, NO! They're both dead! Yuck!" << endl; return;
        }else if(this->power == 0 || opponent.power == 0){
            cout << "He's dead, " << (this->power == 0 ? this->name : opponent.name) << endl; return;
        }else if(this->power == opponent.power){
            cout << "Mutual Annihilation: " << this->name << " and " << opponent.name << " die at each other's hands" << endl;

        }else{
            string winner_announcement = this->power > opponent.power ? (this->name + " defeats " + opponent.name) : (opponent.name + " defeats " + this->name);
            cout << winner_announcement << endl;
        }
        
        after_battle(*this, opponent);
    }
    string name;
    int power;
};

void after_battle(Warrior& a, Warrior& b){
    if(a.power !=0 && b.power != 0){
        int old_power_a = a.power;
        int old_power_b = b.power;
        a.power = old_power_a - old_power_b > 0 ? old_power_a - old_power_b : 0;
        b.power = old_power_b - old_power_a > 0 ? old_power_b - old_power_a : 0;
    }
}

size_t locate_warrior(const string& name, const vector<Warrior>& warriors){
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i].name == name) {
            return i;
        }
    }
    return warriors.size();
}

void status_handler(const vector<Warrior>& warriors){
    for (size_t i = 0; i < warriors.size(); ++i) {
        cout << warriors[i].name << " " << warriors[i].power << endl;
    }
}

int main() {
    ifstream ifs("warrior.txt");
    if(!ifs){
        cerr << "No file found" << endl;
        exit(1);
    }
    string command;
    vector<Warrior> warriors;
    while(ifs >> command){
        if(command == "Warrior"){
            string name; int power;
            ifs >> name >> power;
            Warrior new_warrior(name,power);
            warriors.push_back(new_warrior);
        }else if(command == "Status"){
            status_handler(warriors);
        }else if(command == "Battle"){
            string warrior_a, warrior_b;
            ifs >> warrior_a >> warrior_b;
            warriors[locate_warrior(warrior_a, warriors)].battle(warriors[locate_warrior(warrior_b, warriors)]);
        }
    }
    ifs.close();
}
