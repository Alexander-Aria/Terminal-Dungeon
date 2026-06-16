#include "enemy.hpp"
#include "player.hpp"
#include "utility.hpp"

void Enemy::Turn(Player &player, bool &playerdefend, bool &enemydefend){cout << GetName() << " does nothing!\n\n";}

void BatEnemy::Turn(Player &player, bool &playerdefend, bool &enemydefend){
    Random RNG;
    int RNGnum = RNG.Int(1,100);
    Choice choice = Choice::NOTHING;

    if(RNGnum <= slashchance) choice = Choice::SLASH;
    else if(RNGnum >= 100 - defendchance) choice = Choice::DEFEND;

    switch(choice){
        case Choice::SLASH:
            cout << GetName() << " attacks!\n";
            Slash(GetStats(), player.GetStats(), playerdefend);
            break;
        case Choice::DEFEND:
            cout << GetName() << " is defending!\n\n";
            enemydefend = true;
            break;
        default:
            cout << GetName() << " does nothing!\n\n";
    }
}

void WolfEnemy::Turn(Player &player, bool &playerdefend, bool &enemydefend){
    Random RNG;
    int RNGnum = RNG.Int(1,100);
    Choice choice = Choice::NOTHING;


    if(RNGnum <= slashchance) choice = Choice::SLASH;
    else if(RNGnum > 100 - (defendchance + howlchance) && RNGnum <= 100 - howlchance) choice = Choice::DEFEND;
    else if(RNGnum > 100 - howlchance) choice = Choice::HOWL;

    switch(choice){
        case Choice::SLASH:
            cout << GetName() << " attacks!\n";
            Slash(GetStats(), player.GetStats(), playerdefend);
            break;
        case Choice::DEFEND:
            cout << GetName() << " is defending!\n\n";
            enemydefend = true;
            break;
        case Choice::HOWL:
            cout << GetName() << " howls!\n";
            Howl(player.GetStats());
            break;
        default:
            cout << GetName() << " does nothing!\n\n";
    }
}

void BanditEnemy::Turn(Player &player, bool &playerdefend, bool &enemydefend){
    Random RNG;
    int RNGnum = RNG.Int(1,100);
    Choice choice = Choice::NOTHING;

    if(playerdefend) choice = Choice::STAB;
    else if(RNGnum <= slashchance) choice = Choice::SLASH;
    else if(RNGnum >= 100 - defendchance) choice = Choice::DEFEND;

    switch(choice){
        case Choice::SLASH:
            cout << GetName() << " attacks!\n";
            Slash(GetStats(), player.GetStats(), playerdefend);
            break;
        case Choice::STAB:
            cout << GetName() << " stabs!\n";
            Stab(GetStats(), player.GetStats(), playerdefend);
            break;
        case Choice::DEFEND:
            cout << GetName() << " is defending!\n\n";
            enemydefend = true;
            break;
        default:
            cout << GetName() << " does nothing!\n\n";
    }
}