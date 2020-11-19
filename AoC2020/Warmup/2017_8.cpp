// AoC2020.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>

using namespace std;

typedef bool(*comparator)(int, int);

bool gt(int a, int b) {
  return a > b;
}

bool ge(int a, int b) {
  return a >= b;
}

bool lt(int a, int b) {
  return a < b;
}

bool le(int a, int b) {
  return a <= b;
}

bool ne(int a, int b) {
  return a != b;
}

bool eq(int a, int b) {
  return a == b;
}

int main() {

    ifstream input("input.txt");

    string x;

    //1: register, 2: dec/inc, 3: val, 4: cond_reg, 5: cond_cond, 6: cond_val 
    regex rule("(\\w+) (dec|inc) (-?[0-9]+) if (\\w+) (<|>|>=|<=|==|!=) (-?[0-9]+)");

    map<string, int> registers;

    string reg[1000];
    int inc[1000];
    int val[1000];
    string cond_reg[1000];
    comparator cond_cond[1000];
    int cond_val[1000];

    int index = 0;
    if (input.is_open()) {
        while (getline(input, x)) {

            smatch sm;
            regex_match(x, sm, rule);

            registers.insert(pair<string, int>(sm[1], 0));

            reg[index] = sm[1];
            inc[index] = sm[2] == "inc" ? 1 : -1;
            val[index] = stoi(sm[3]);
            cond_reg[index] = sm[4];

            if (sm[5] == ">") {
                cond_cond[index] = gt;
            }
            else if (sm[5] == ">=") {
                cond_cond[index] = ge;
            }
            else if (sm[5] == "<") {
                cond_cond[index] = lt;
            }
            else if (sm[5] == "<=") {
                cond_cond[index] = le;
            }
            else if (sm[5] == "==") {
                cond_cond[index] = eq;
            }
            else if (sm[5] == "!=") {
                cond_cond[index] = ne;
            }

            cond_val[index] = stoi(sm[6]);

            index++;
        }
    }

    int max_val_ever = 0;
    for (int i = 0; i < index; i++) {
        int cond_reg_value = registers[cond_reg[i]];
        if (cond_cond[i](cond_reg_value, cond_val[i])) {
            registers[reg[i]] +=  inc[i] * val[i];
            if (registers[reg[i]] > max_val_ever)
                max_val_ever = registers[reg[i]];
        }     
    }

    int max_val = 0;

    for (int i = 0; i < size(reg); i++) {
        int temp_val = registers[reg[i]];
        if (temp_val > max_val) {
            max_val = temp_val;
        }
    }
    cout << max_val << endl;
    cout << max_val_ever << endl;
}
