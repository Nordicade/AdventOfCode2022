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
    vector<int> startingItems;
    string operation;
    int test;
    int ifT;
    int ifF;
    int inspections;
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

int applyOperation(int currWorry, string operation) {
    vector<string> chunks = split(operation, ' ');
    int LHS = 0;
    int RHS = 0;
    if (chunks.size() == 3) {
        if(chunks[0] == "old") {
            // cout << currWorry << endl;
            LHS = currWorry;
        } else {
            LHS = stoi(chunks[0]);
        }
        if(chunks[2] == "old") {
            RHS = currWorry;
        } else {
            RHS = stoi(chunks[2]);
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
    file.open("test.txt");
    if(!file.is_open()){
        cout<<"Unable to open the file."<<endl;
        return 0;
    }
    
    string line;
    vector<string> lines;

    int worryLevel;
    vector<Monkey> monkeys;

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

    cout << "\n\n" << endl;

    // Begin the rounds
    for (int rounds = 0; rounds < 1; rounds ++) {
        for(int monki = 0; monki < monkeys.size(); monki++){
            for(int item : monkeys[monki].startingItems){
                worryLevel = item;
                cout << "WL : " << worryLevel << endl;
                worryLevel = applyOperation(worryLevel, monkeys[monki].operation);
                cout << "WL : " << worryLevel << endl;
                worryLevel = worryLevel / 3;
                cout << "WL : " << worryLevel << endl;

                cout << "Before throwing : " << endl;
                for(int debug = 0; debug < monkeys[monki].startingItems.size(); debug++){
                    cout << monkeys[monki].startingItems[debug] << ", ";
                }
                cout << "" << endl;

                if(worryLevel % monkeys[monki].test == 0) {
                    monkeys[monki].startingItems.erase(monkeys[monki].startingItems.begin());
                    monkeys[monkeys[monki].ifT].startingItems.push_back(item);
                    cout << "true" << endl;
                    cout << "thrown to " << monkeys[monki].ifT << endl;
                    cout << "After throwing : ";
                    for(int debug = 0; debug < monkeys[monki].startingItems.size(); debug++){
                        cout << monkeys[monki].startingItems[debug]  << ", ";
                    }
                    cout << "" << endl;
                } else {
                    monkeys[monki].startingItems.erase(monkeys[monki].startingItems.begin());
                    monkeys[monkeys[monki].ifF].startingItems.push_back(item);
                    cout << "false" << endl;
                    cout << "thrown to " << monkeys[monki].ifF << endl;
                    cout << "After throwing : ";
                    for(int debug = 0; debug < monkeys[monki].startingItems.size(); debug++){
                        cout << monkeys[monki].startingItems[debug] << ", ";
                    }
                    cout << "" << endl;
                }
                monkeys[monki].inspections = monkeys[monki].inspections + 1;
            }
        }
    }

    cout << " - - - - " << endl;

    // sanity check
    for(int monki = 0; monki < monkeys.size(); monki++){
        printMonkey(monkeys[monki]);
    }
    exit(0);

    // determine the top two inspectors
    vector<int> monkeyInspects;
    for(int monki = 0; monki < monkeys.size(); monki++){
        monkeyInspects.push_back(monkeys[monki].inspections);
    }
    sort(monkeyInspects.begin(), monkeyInspects.end(), greater<int>());
    int output = monkeyInspects[0] * monkeyInspects[1];
    cout << "Final answer : " << output << endl;
    file.close();
    return 0;
}