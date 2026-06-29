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
        Enemy(
            const Stats &s,
            const Inventory &i, 
            const string &n, 
            const string &d,
            const int &greward,
            const int &ereward
        ) : Entity(s, i), name(n), description(d), goldreward(greward), expreward(ereward) {}

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

enum class BanditType{
    REGULAR,
    LEADER
};

class BanditEnemy : public Enemy{
    private:
        BanditType bandittype = BanditType::REGULAR;
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
            const int &block,
            const BanditType &type
        ) : Enemy(s, n, d, greward, ereward), slashchance(slash), blockchance(block), bandittype(type) {}

        void Turn(Player &player) override;
};

enum class GolemType{
    ROCK,
    ICE,
    FIRE
};

class GolemEnemy : public Enemy{
    private:
        GolemType golemtype;
        int bashchance = 0;
        int magicchance = 0;
    public:
        GolemEnemy(
            const Stats &s, 
            const string &n, 
            const string &d,
            const int &greward,
            const int &ereward,
            const int &bash,
            const int &magic,
            const GolemType &type
        ) : Enemy(s, n, d, greward, ereward), bashchance(bash), magicchance(magic), golemtype(type) {}

        void Turn(Player &player) override;
};

enum class GuardType{
    PATROL,
    ROYALGUARD
};

class GuardEnemy : public Enemy{
    private:
        GuardType guardtype;
        int slashchance = 0;
        int shieldchance = 0;
    public:
        GuardEnemy(
            const Stats &s, 
            const Inventory &i,
            const string &n, 
            const string &d,
            const int &greward,
            const int &ereward,
            const int &slash,
            const int &shield,
            const GuardType &type
        ) : Enemy(s, i, n, d, greward, ereward), slashchance(slash), shieldchance(shield), guardtype(type) {}

        void Turn(Player &player) override;
};

class ArcherEnemy : public Enemy{
    private:
        int shootchance;
        int chargechance;
    public:
        ArcherEnemy(
            const Stats &s, 
            const Inventory &i,
            const string &n, 
            const string &d,
            const int &greward,
            const int &ereward,
            const int &shoot,
            const int &charge
        ) : Enemy(s, i, n, d, greward, ereward), shootchance(shoot), chargechance(charge) {}

        void Turn(Player &player) override;
};

class KnightEnemy : public Enemy{
    private:
        int heavyblowchance;
        int shieldchance;
    public:
        KnightEnemy(
            const Stats &s, 
            const Inventory &i,
            const string &n, 
            const string &d,
            const int &greward,
            const int &ereward,
            const int &heavyblow,
            const int &shield
        ) : Enemy(s, i, n, d, greward, ereward), heavyblowchance(heavyblow), shieldchance(shield) {}

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
    Stats(80, 80, 12, 5), 
    "Alpha Bat", 
    "The leader of the bats.", 
    50, 
    75,
    40,
    60
);}

inline WolfEnemy WolfCub() {return WolfEnemy(
    Stats(60, 60, 12, 5), 
    "Wolf Cub", 
    "A young wolf cub.", 
    20, 
    30,
    50,
    50,
    0
);}

inline WolfEnemy FemaleWolf() {return WolfEnemy(
    Stats(100, 100, 15, 6),
    "Female Wolf",
    "A female wolf and a grieving mother of a wolf cub.",
    50,
    100,
    70,
    30,
    0
);}

inline WolfEnemy MaleWolf() {return WolfEnemy(
    Stats(120, 120, 18, 8),
    "Male Wolf",
    "A male wolf and a father of a wolf cub.",
    80,
    125,
    50,
    30,
    20
);}

inline WolfEnemy TrainedWolf() {return WolfEnemy(
    Stats(150, 150, 27, 12),
    "Trained Wolf",
    "A trained male wolf. It is the archer's pet.",
    50,
    75,
    40,
    30,
    30
);}

inline BanditEnemy Bandit() {return BanditEnemy(
    Stats(100, 100, 12, 6), 
    "Bandit", 
    "A bandit. Possibly one of many living in the dungeon.", 
    100, 
    70,
    70,
    30,
    BanditType::REGULAR
);}

inline BanditEnemy BanditLeader() {return BanditEnemy(
    Stats(125, 125, 18, 8), 
    "Bandit Leader", 
    "One of the leader of the bandits. He is armed with a powerful crossbow and a sharp dagger.", 
    250, 
    100,
    70,
    30,
    BanditType::LEADER
);}

inline GolemEnemy BrokenGolem() {return GolemEnemy(
    Stats(125, 400, 10, 17), 
    "Broken Golem", 
    "A guardian of a temple. It has been damaged by the bandits.", 
    300, 
    150,
    50,
    20,
    GolemType::ROCK
);}

inline GolemEnemy IceGolem() {return GolemEnemy(
    Stats(250, 250, 20, 7), 
    "Ice Golem", 
    "A powerful but fragile golem. The weakest of it's kind.", 
    300, 
    150,
    50,
    50,
    GolemType::ICE
);}

inline GuardEnemy PatrolGuard() {return GuardEnemy(
    Stats(160, 160, 20, 12), 
    Inventory({}, Shield(), NoRanged(), NoArmor()),
    "Patroling Guard", 
    "A patroling guard of an unknown clan. His shield made ranged weapon ineffective.", 
    200,
    100,
    40,
    60,
    GuardType::PATROL
);}

inline GuardEnemy RoyalGuard() {return GuardEnemy(
    Stats(180, 180, 30, 15), 
    Inventory({}, Shield(), NoRanged(), NoArmor()),
    "Royal Guard", 
    "A royal guard of an unknown clan. His shield and heavy armor made ranged weapon ineffective.", 
    200,
    150,
    30,
    70,
    GuardType::ROYALGUARD
);}

inline ArcherEnemy Archer() {return ArcherEnemy(
    Stats(130, 130, 35, 10), 
    Inventory({}, NoMelee(), ShortBow(), NoArmor()),
    "Archer", 
    "An archer of an unknown clan. Equipped with a short bow.", 
    200,
    150,
    50,
    50
);}

inline KnightEnemy Knight() {return KnightEnemy(
    Stats(215, 215, 30, 20), 
    Inventory({}, Shield(), NoRanged(), NoArmor()),
    "Knight", 
    "The clan leader's personal fighter. Equipped with a long sword and heavy armor. No weaknesses in sight.", 
    150,
    200,
    50,
    50
);}