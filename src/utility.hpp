#pragma once

#include <random>
#include <iostream>

using std::cin;
using std::cout;

class Random{
    private:
        std::mt19937 gen;

    public:
        Random() : gen(std::random_device{}()) {}

        int Int(int min, int max){
            std::uniform_int_distribution<> dist(min, max);
            return dist(gen);
        }
};

inline void Ignore(){cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');}

template <typename T>
inline void NumInput(T &num){
    while(!(cin >> num)){
        cin.clear();
        Ignore();
        cout << "Invalid input!\n";
        cout << "Try again : ";
    }
}

inline bool YesorNo(){
    int opt = 0;

    cout << "1. Yes\n2. No\n\n- ";
    NumInput(opt);
    if(opt == 1) return true;
    else return false;
}

inline bool operator==(const Items &item, const string &name){
    if(item.GetName() == name) return true;
    else return false;
}

inline bool operator!=(const Items &item, const string &name){
    if(item.GetName() == name) return false;
    else return true;
}