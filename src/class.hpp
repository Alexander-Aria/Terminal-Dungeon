#include <iostream>
#include <vector>
#include <random>
#include <limits>

class Items{
    private:
        string name;
    public:
        const string &GetName() const {return name;};
};

class Consumables : public Items{

};

class Inventory{
    private:
        vector<Items> consumables;
    public:
        Inventory(){};
};

class Stats{
    private:
        int health = 100, maxhealth = 100;
    public:
        Stats(){};

        int &GetHealth(){return health;}
        int &GetMaxHealth(){return maxhealth;}

};

class GameState{
    private:
        int stage = 0;
        int status = 0;
        Stats player;
        Inventory items;
    public:
        GameState(){};

        int &GetStage(){return stage;}
        int &GetStatus(){return status;}
        Stats &GetStats(){return player;}
        Inventory &GetItems(){return items;}
};

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