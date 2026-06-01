#include <iostream>
#include <vector>
#include <random>
#include <limits>

class Items{
    private:
        string name = "Undefined Item";
        string description = "No Description";
    public:
        Items(){}
        Items(string &n, string &d){
            name = n;
            description = d;
        }

        const string &GetName() const {return name;};
        const string &GetDescription() const {return description;};
};

class Consumables : public Items{
    private:
        int healthgain = 0;
    public:
        Consumables(){}
        Consumables(string &name, string &description, int &health):Items(name, description){
            healthgain = health;
        }

        const int &GetHealth(){return healthgain;}
};

class Inventory{
    private:
        vector<Consumables> consumables;
    public:
        Inventory(){}

        vector<Consumables> &GetConsumables(){return consumables;}
};

class Stats{
    private:
        int health = 100;
    public:
        Stats(){}
        Stats(int h){
            health = h;
        }

        int &GetHealth(){return health;}
};

class Enemy{
    private:
        Stats stats;
        string name = "Undefined Enemy";
        string description = "No Description";
    public:
        Enemy(){}
        Enemy(Stats s, string n, string d){
            stats = s;
            name = n;
            description = d;
        }

        Stats &GetStats(){return stats;}
        string &GetName(){return name;}
        string &GetDescription(){return description;}
};

class GameState{
    private:
        int stage = 0;
        int status = 0;
        Stats playerstats;
        Inventory items;
    public:
        GameState(){};

        int &GetStage(){return stage;}
        int &GetStatus(){return status;}
        Stats &GetStats(){return playerstats;}
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