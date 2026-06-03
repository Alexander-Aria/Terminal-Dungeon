#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <cmath>

using namespace std;

class Items{
    private:
        string name = "Undefined Item";
        string description = "No Description";
    public:
        Items(){}
        Items(const string &n, const string &d){
            name = n;
            description = d;
        }

        const string &GetName() const {return name;};
        const string &GetDescription() const {return description;};
};

class Consumables : public Items{
    private:
        struct{
        int healthgain = 0;
        } effect;
    public:
        Consumables(){}
        Consumables(string &name, string &description, int &health):Items(name, description){
            effect.healthgain = health;
        }

        const int &GetHealth(){return effect.healthgain;}
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
        int maxhealth = 100;
        int strength = 10;
        int defense = 10;
    public:
        Stats(){}
        Stats(const int &h, const int &mh, const int &str, const int &def){
            health = h;
            maxhealth = mh;
            strength = str;
            defense = def;
        }

        int &GetHealth(){return health;}
        int &GetMaxHealth(){return maxhealth;}
        int &GetStrength(){return strength;}
        int &GetDefense(){return defense;}
};

class Player{
    private:
        Stats stats;
        Inventory inventory;
    public:
        Player(){}

        Stats &GetStats(){return stats;}
        Inventory &GetInventory(){return inventory;}
};

class Enemy{
    private:
        Stats stats;
        string name = "Undefined Enemy";
        string description = "No Description";
    public:
        Enemy(){}
        Enemy(const Stats &s, const string &n, const string &d){
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
        Player player;
    public:
        GameState(){};

        int &GetStage(){return stage;}
        int &GetStatus(){return status;}
        Player &GetPlayer(){return player;}

        void HealthReset(){player.GetStats().GetHealth() = player.GetStats().GetMaxHealth();}
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