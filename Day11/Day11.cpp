#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

struct Monkey {
    vector<long long> startingItems;
    string operation;
    int test;
    int ifT;
    int ifF;
    long long inspections;
    Monkey() : operation(""), test(0), ifT(0), ifF(0), inspections(0) {} 
};

std::vector<std::string> split(const std::string str, char delimiter) {
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string token;
  while (std::getline(ss, token, delimiter)) {
    token.erase(0, token.find_first_not_of(' '));
    token.erase(token.find_last_not_of(' ') + 1);
    tokens.push_back(token);
  }
  return tokens;
}

void printMonkey(Monkey monkey) {
    cout << "New Monkey" << endl;
    cout << "Starting Items: ";
    for(int i= 0; i < monkey.startingItems.size(); i++){
        cout << monkey.startingItems[i];
        cout << " , ";
    }
    cout << "\nOperation: " << monkey.operation << endl;
    cout << "Test: ";
    cout << monkey.test << endl;
    cout << "if True: ";
    cout << monkey.ifT << endl;
    cout << "if False: ";
    cout << monkey.ifF << endl;
}

long long applyOperation(long long currWorry, string operation) {
    vector<string> chunks = split(operation, ' ');
    long long LHS = 0;
    long long RHS = 0;
    if (chunks.size() == 3) {
        if(chunks[0] == "old") {
            LHS = currWorry;
        } else {
            LHS = static_cast<long long>(stoi(chunks[0]));
        }
        if(chunks[2] == "old") {
            RHS = currWorry;
        } else {
            RHS = static_cast<long long>(stoi(chunks[2]));
        }
        switch(chunks[1][0]){
            case '+':
                return LHS + RHS;
            case '-':
                return LHS - RHS;
            case '*':
                return LHS * RHS;
        }
    }
    
    exit(0);
}

int main(){
    ifstream file;
    file.open("monkeys.txt");
    if(!file.is_open()){
        cout<<"Unable to open the file."<<endl;
        return 1;
    }
    
    string line;
    vector<string> lines;

    long long worryLevel;
    vector<Monkey> monkeys;
    int product = 1;

    while(getline(file, line)){
        lines.push_back(line);
    }

    for( int i = 0; i < lines.size(); i++){
        if (lines[i].rfind("Monkey", 0) == 0){
            monkeys.push_back(Monkey());
        }
        else if (lines[i].find("Starting items") != string::npos){
            vector<string> stringItems = split(lines[i].substr(18, lines[i].length()), ',');
            for (string item : stringItems){
                monkeys.back().startingItems.push_back(stoi(item));
            }
        }
        else if (lines[i].find("Operation") != string::npos){
            monkeys.back().operation = lines[i].substr(19, lines[i].length());
        }
        else if (lines[i].find("Test") != string::npos){
            vector<string> words = split(lines[i], ' ');
            monkeys.back().test = stoi(words.back());
            product *= stoi(words.back());
        }
        else if (lines[i].find("If true") != string::npos){
            monkeys.back().ifT = stoi(lines[i].substr(lines[i].length() - 1, lines[i].length()));
        }
        else if (lines[i].find("If false") != string::npos){
            monkeys.back().ifF = stoi(lines[i].substr(lines[i].length() - 1, lines[i].length()));
        }
        else{
            printMonkey(monkeys.back());
            continue;
        }
    }

    // Begin the rounds
    for (int rounds = 0; rounds < 10000; rounds ++) {
        for(int monki = 0; monki < monkeys.size(); monki++){
            for(int item = 0; item < monkeys[monki].startingItems.size(); item++){
                if (monkeys[monki].startingItems[item] == -1){
                    continue;
                }
                worryLevel = monkeys[monki].startingItems[item];
                worryLevel = applyOperation(worryLevel, monkeys[monki].operation);
                // This division rule only applied in part one
                // worryLevel = worryLevel / 3;
                // This modification rule only applies to part two
                worryLevel = worryLevel % product;
                if(worryLevel % monkeys[monki].test == 0) {
                    monkeys[monkeys[monki].ifT].startingItems.push_back(worryLevel);
                    monkeys[monki].startingItems[item] = -1;
                } else {
                    monkeys[monkeys[monki].ifF].startingItems.push_back(worryLevel);
                    monkeys[monki].startingItems[item] = -1;
                }
                monkeys[monki].inspections = monkeys[monki].inspections + 1;
            }
        }
        for(int monki = 0; monki < monkeys.size(); monki++){
            for(int item = 0; item < monkeys[monki].startingItems.size(); item++){
                auto it = remove_if(monkeys[monki].startingItems.begin(), monkeys[monki].startingItems.end(),  [](const int i) {return i == -1; });
                monkeys[monki].startingItems.erase(it, monkeys[monki].startingItems.end());
            }
        }
    }

    // sanity check
    // for(int monki = 0; monki < monkeys.size(); monki++){
    //     printMonkey(monkeys[monki]);
    // }

    // determine the top two inspectors
    vector<long long> monkeyInspects;
    for(int monki = 0; monki < monkeys.size(); monki++){
        monkeyInspects.push_back(monkeys[monki].inspections);
    }
    sort(monkeyInspects.begin(), monkeyInspects.end(), greater<long long>());
    long long output = monkeyInspects[0] * monkeyInspects[1];
    cout << "Final answer : " << output << endl;
    cout << monkeyInspects[0] << endl;
    cout << monkeyInspects[1] << endl;
    file.close();
    return 0;
}