#pragma once

#include <random>
#include <iostream>

using std::cin;
using std::cout;

void Ignore(){cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');}

template <typename T>
void NumInput(T &num){
    while(!(cin >> num)){
        cin.clear();
        Ignore();
        cout << "Invalid input!\n";
        cout << "Try again : ";
    }
}

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