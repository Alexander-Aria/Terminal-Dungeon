#include "enemy.hpp"
#include "player.hpp"
#include "utility.hpp"

void Enemy::Turn(Player &player){cout << GetName() << " does nothing!\n\n";}

void BatEnemy::Turn(Player &player){
    Random RNG;
    int RNGnum = RNG.Int(1,100);
    Choice choice = Choice::NOTHING;

    if(RNGnum <= slashchance) choice = Choice::SLASH;
    else if(RNGnum >= 100 - blockchance && !GetBlock()) choice = Choice::BLOCK;
    else choice = Choice::SLASH;

    switch(choice){
        case Choice::SLASH:
            cout << GetName() << " attacks!\n";
            Slash(player);
            break;
        case Choice::BLOCK:
            cout << GetName() << " is blocking!\n\n";
            GetBlock() = true;
            break;
        default:
            cout << GetName() << " does nothing!\n\n";
    }
}

void WolfEnemy::Turn(Player &player){
    Random RNG;
    int RNGnum = RNG.Int(1,100);
    Choice choice = Choice::NOTHING;

    if(RNGnum <= slashchance) choice = Choice::SLASH;
    else if(RNGnum > 100 - (blockchance + howlchance) && RNGnum <= 100 - howlchance && !GetBlock()) choice = Choice::BLOCK;
    else if(RNGnum > 100 - howlchance) choice = Choice::HOWL;
    else choice = Choice::SLASH;

    switch(choice){
        case Choice::SLASH:
            cout << GetName() << " attacks!\n";
            Slash(player);
            break;
        case Choice::BLOCK:
            cout << GetName() << " is blocking!\n\n";
            GetBlock() = true;
            break;
        case Choice::HOWL:
            cout << GetName() << " howls!\n";
            Howl(player.GetStats());
            break;
        default:
            cout << GetName() << " does nothing!\n\n";
    }
}

void BanditEnemy::Turn(Player &player){
    Random RNG;
    int RNGnum = RNG.Int(1,100);
    Choice choice = Choice::NOTHING;

    if(player.GetBlock()){
        if(GetName() == "Bandit Leader") choice = Choice::DOUBLESHOT;
        else choice = Choice::STAB;
    }
    else if(RNGnum <= slashchance) choice = Choice::SLASH;
    else if(RNGnum >= 100 - blockchance && !GetBlock()) choice = Choice::BLOCK;
    else choice = Choice::SLASH;

    switch(choice){
        case Choice::SLASH:
            cout << GetName() << " attacks!\n";
            Slash(player);
            break;
        case Choice::STAB:
            cout << GetName() << " stabs!\n";
            Stab(player);
            break;
        case Choice::DOUBLESHOT:
            cout << GetName() << "shot you twice with a crossbow!\n";
            DoubleShot(player);
            break;
        case Choice::BLOCK:
            cout << GetName() << " is blocking!\n\n";
            GetBlock() = true;
            break;
        default:
            cout << GetName() << " does nothing!\n\n";
    }
}