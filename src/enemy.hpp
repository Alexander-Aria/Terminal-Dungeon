#pragma once

#include "entity.hpp"

#include <string>
using std::string;

class Player;

class Enemy : public Entity{
    private:
        string name = "Undefined Enemy";
        string description = "No Description";
        int goldreward = 0;
        int expreward = 0;
    public:
        Enemy() {}
        Enemy(
            const Stats &s, 
            const string &n, 
            const string &d,
            const int &greward,
            const int &ereward
        ) : Entity(s), name(n), description(d), goldreward(greward), expreward(ereward) {}

        const string &GetName() const {return name;}
        const string &GetDescription() const {return description;}
        const int &GetGoldReward() const {return goldreward;}
        const int &GetExpReward() const {return expreward;}

        virtual void Turn(Player &player);
};

class BatEnemy : public Enemy{
    private:
        int slashchance = 80;
        int blockchance = 20;
    public:
        BatEnemy(
            const Stats &s, 
            const string &n, 
            const string &d,
            const int &greward,
            const int &ereward,
            const int &slash,
            const int &block
        ) : Enemy(s, n, d, greward, ereward), slashchance(slash), blockchance(block){}

        void Turn(Player &player) override;
};

class WolfEnemy : public Enemy{
    private:
        int slashchance = 50;
        int blockchance = 50;
        int howlchance = 0;
    public:
        WolfEnemy(
            const Stats &s, 
            const string &n, 
            const string &d,
            const int &greward,
            const int &ereward,
            const int &slash,
            const int &block,
            const int &howl
        ) : Enemy(s, n, d, greward, ereward), slashchance(slash), blockchance(block), howlchance(howl) {}

        void Turn(Player &player) override;
};

class BanditEnemy : public Enemy{
    private:
        int slashchance = 0;
        int blockchance = 0;
    public:
        BanditEnemy(
            const Stats &s, 
            const string &n, 
            const string &d,
            const int &greward,
            const int &ereward,
            const int &slash,
            const int &block
        ) : Enemy(s, n, d, greward, ereward), slashchance(slash), blockchance(block){}

        void Turn(Player &player) override;
};

inline Enemy Dummy() {return Enemy(
    Stats(100, 100, 0, 5),
    "Dummy",
    "A practice dummy.",
    0,
    0
);}

inline BatEnemy Bat() {return BatEnemy(
    Stats(50, 50, 8, 5), 
    "Bat", 
    "An agressive and territorial bat.", 
    30, 
    50,
    80,
    20
);}

inline BatEnemy AlphaBat() { return BatEnemy(
    Stats(80, 80, 10, 5), 
    "Alpha Bat", 
    "The leader of the bats.", 
    50, 
    80,
    40,
    60
);}

inline WolfEnemy WolfCub() {return WolfEnemy(
    Stats(60, 60, 10, 6), 
    "Wolf Cub", 
    "A young wolf cub.", 
    20, 
    30,
    50,
    50,
    0
);}

inline WolfEnemy FemaleWolf() {return WolfEnemy(
    Stats(120, 120, 15, 8),
    "Female Wolf",
    "A female wolf and a grieving mother of a wolf cub.",
    50,
    150,
    70,
    30,
    0
);}

inline WolfEnemy MaleWolf() {return WolfEnemy(
    Stats(150, 150, 18, 10),
    "Male Wolf",
    "A male wolf and a father of a wolf cub.",
    80,
    200,
    50,
    30,
    20
);}

inline BanditEnemy Bandit() {return BanditEnemy(
    Stats(100, 100, 15, 6), 
    "Bandit", 
    "A bandit. Possibly one of many living in the dungeon.", 
    100, 
    75,
    70,
    30
);}

inline BanditEnemy BanditLeader() {return BanditEnemy(
    Stats(150, 150, 20, 8), 
    "Bandit Leader", 
    "One of the leader of the bandits. He is armed with a powerful crossbow and a sharp dagger.", 
    250, 
    150,
    70,
    30
);}
