#pragma once

#include "entity.hpp"
#include <string>

using std::string;

enum class EnemyType{
    REGULAR,
    BANDITS
};

class Enemy : public Entity{
    private:
        EnemyType enemytype = EnemyType::REGULAR;
        string name = "Undefined Enemy";
        string description = "No Description";
        int goldreward = 0;
        int expreward = 0;
        int attchance = 0;
        int defchance = 0;
    public:
        Enemy() {}
        Enemy(
            const EnemyType &type,
            const Stats &s, 
            const string &n, 
            const string &d,
            const int &greward,
            const int &ereward,
            const int &ac,
            const int &dc
        ) : enemytype(type), Entity(s), name(n), description(d), goldreward(greward), expreward(ereward), attchance(ac), defchance(dc) {}

        const EnemyType &GetEnemyType() const {return enemytype;}
        const string &GetName() const {return name;}
        const string &GetDescription() const {return description;}
        const int &GetGoldReward() const {return goldreward;}
        const int &GetExpReward() const {return expreward;}
        const int &GetAttChance() const {return attchance;}
        const int &GetDefChance() const {return defchance;}
};

inline Enemy Dummy() {return Enemy(
    EnemyType::REGULAR,
    Stats(200, 200, 0, 5),
    "Dummy",
    "A practice dummy.",
    0,
    0,
    0,
    0
);}

inline Enemy Bat() {return Enemy(
    EnemyType::REGULAR,
    Stats(50, 50, 8, 5), 
    "Bat", 
    "An agressive and territorial bat.", 
    30, 
    50,
    80,
    20
);}

inline Enemy AlphaBat() { return Enemy(
    EnemyType::REGULAR,
    Stats(80, 80, 10, 5), 
    "Alpha Bat", 
    "The leader of the bats.", 
    50, 
    80,
    40,
    60
);}

inline Enemy WolfCub() {return Enemy(
    EnemyType::REGULAR,
    Stats(60, 60, 10, 6), 
    "Wolf Cub", 
    "A young wolf cub.", 
    20, 
    30,
    50,
    50
);}

inline Enemy FemaleWolf() {return Enemy(
    EnemyType::REGULAR,
    Stats(120, 120, 15, 8),
    "Female Wolf",
    "A female wolf and a grieving mother of a wolf cub.",
    50,
    150,
    60,
    40
);}

inline Enemy MaleWolf() {return Enemy(
    EnemyType::REGULAR,
    Stats(150, 150, 18, 10),
    "Male Wolf",
    "A male wolf and a furious father of a wolf cub.",
    80,
    200,
    60,
    40
);}

inline Enemy Bandit() {return Enemy(
    EnemyType::BANDITS,
    Stats(100, 100, 15, 6), 
    "Bandit", 
    "A hunting bandit. Possibly one of many living in the dungeon.", 
    100, 
    75,
    70,
    30
);}

