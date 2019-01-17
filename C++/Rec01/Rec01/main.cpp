//
//  main.cpp
//  Rec01
//
//  Created by 周凯旋 on 1/16/19.
//  Copyright © 2019 Kaixuan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

string file_to_be_open = "life.txt";
size_t map_length; // for building the additioanl layer;
string border;

//A living cell with two or three neighboring living cells survives into the next generation. A living cell with fewer than two living neighbors dies of loneliness and a living cell with more than three living neighbors will die from overcrowding.
//Each empty/dead cell that has exactly three living neighbors--no more, no fewer-- comes to life in the next generation.


char is_alive(size_t row, size_t col, const vector<string>& population){
//    calculating neighbour's situation
    int count_alive = 0;
    for(int i = -1; i < 2; ++i ){
        for(int j = -1; j < 2; ++j){
            if(population[row + i][col + j] == '*'){ count_alive++; }
        }
    }
    
//    conditionally return alive or death
    if(population[row][col] == '*'){
        if(count_alive == 3 || count_alive == 4){ return '*'; }
    }else{
        if(count_alive == 3){return '*';}
    }
    return '-';
}


//  This function build the map with borders.
//  Only call once when initialize the world.
void build_map(ifstream& ifs, string& line, vector<string>& population){
    
    for (size_t i = 0; i < map_length; ++i) { border += "-"; }
    population.push_back(border);
    population.push_back("-" + line + "-");
    
    while(getline(ifs, line)){
        population.push_back("-" + line + "-");
    }
    population.push_back(border);
}

//  It's job is to print the world(2d vector)
void print_map(const vector<string>& population){
    cout << "======================" << endl;
    for(size_t row = 1; row < population.size() - 1; ++row){
        cout << "{";
        for(size_t col = 1; col < population[row].length() - 1; ++col){
            cout << population[row][col];
        }
        cout << "}" << endl;
    }
    cout << "======================" << endl;
}

//  Changing the world to the next generation
void transition(vector<string>& population){
    vector<string> new_world(population);
    
    for(size_t row = 1; row < population.size() - 1; ++row){
        for(size_t col = 1; col < population[row].length() - 1; ++col){
//            assign each person's new situation to the new world
            new_world[row][col] = is_alive(row, col, population);
        }
    }
    
//    directly changing population to new_world instead of returning a whole vector;
    population = new_world;
}

int main() {
    ifstream ifs(file_to_be_open);
    if(!ifs){
        cerr << "cannot open file " << file_to_be_open << endl;
        exit(1);
    }

    vector<string> population;
    string line;
//    Construct the vector with an additional layer for convenienve
//    Set up
    getline(ifs, line);
    map_length = line.length() + 2;
    build_map(ifs,line,population);
    cout << "Initial World\n";
    print_map(population);
    cout << endl;
    
    for (int i = 1; i < 11; ++i) {
        cout << "Generation " << i << endl;
        transition(population);
        print_map(population);
    }
    
    ifs.close();
}
