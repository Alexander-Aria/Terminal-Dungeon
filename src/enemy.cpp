#include "enemy.hpp"
#include "player.hpp"
#include "utility.hpp"

void Enemy::Turn(Player &player, bool &playerblock, bool &enemyblock){cout << GetName() << " does nothing!\n\n";}

void BatEnemy::Turn(Player &player, bool &playerblock, bool &enemyblock){
    Random RNG;
    int RNGnum = RNG.Int(1,100);
    Choice choice = Choice::NOTHING;

    if(RNGnum <= slashchance) choice = Choice::SLASH;
    else if(RNGnum >= 100 - blockchance && !enemyblock) choice = Choice::BLOCK;
    else choice = Choice::SLASH;

    switch(choice){
        case Choice::SLASH:
            cout << GetName() << " attacks!\n";
            Slash(GetStats(), player.GetStats(), playerblock);
            break;
        case Choice::BLOCK:
            cout << GetName() << " is blocking!\n\n";
            enemyblock = true;
            break;
        default:
            cout << GetName() << " does nothing!\n\n";
    }
}

void WolfEnemy::Turn(Player &player, bool &playerblock, bool &enemyblock){
    Random RNG;
    int RNGnum = RNG.Int(1,100);
    Choice choice = Choice::NOTHING;

    if(RNGnum <= slashchance) choice = Choice::SLASH;
    else if(RNGnum > 100 - (blockchance + howlchance) && RNGnum <= 100 - howlchance && !enemyblock) choice = Choice::BLOCK;
    else if(RNGnum > 100 - howlchance) choice = Choice::HOWL;
    else choice = Choice::SLASH;

    switch(choice){
        case Choice::SLASH:
            cout << GetName() << " attacks!\n";
            Slash(GetStats(), player.GetStats(), playerblock);
            break;
        case Choice::BLOCK:
            cout << GetName() << " is blocking!\n\n";
            enemyblock = true;
            break;
        case Choice::HOWL:
            cout << GetName() << " howls!\n";
            Howl(player.GetStats());
            break;
        default:
            cout << GetName() << " does nothing!\n\n";
    }
}

void BanditEnemy::Turn(Player &player, bool &playerblock, bool &enemyblock){
    Random RNG;
    int RNGnum = RNG.Int(1,100);
    Choice choice = Choice::NOTHING;

    if(playerblock){
        if(GetName() == "Bandit Leader") choice = Choice::DOUBLESHOT;
        else choice = Choice::STAB;
    }
    else if(RNGnum <= slashchance) choice = Choice::SLASH;
    else if(RNGnum >= 100 - blockchance && !enemyblock) choice = Choice::BLOCK;
    else choice = Choice::SLASH;

    switch(choice){
        case Choice::SLASH:
            cout << GetName() << " attacks!\n";
            Slash(GetStats(), player.GetStats(), playerblock);
            break;
        case Choice::STAB:
            cout << GetName() << " stabs!\n";
            Stab(GetStats(), player.GetStats(), playerblock);
            break;
        case Choice::DOUBLESHOT:
            cout << GetName() << "shot you twice with a crossbow!\n";
            DoubleShot(GetStats(), player.GetStats(), playerblock);
            break;
        case Choice::BLOCK:
            cout << GetName() << " is blocking!\n\n";
            enemyblock = true;
            break;
        default:
            cout << GetName() << " does nothing!\n\n";
    }
}