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
            player.GetStats().GetHealth() -= Slash(GetStats(), player.GetStats(), playerdefend);
            cout << GetName() << " attacks!\n";
            break;
        case Choice::DEFEND:
            enemydefend = true;
            cout << GetName() << " is defending!\n\n";
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
    else if(RNGnum >= 100 - defendchance) choice = Choice::DEFEND;

    switch(choice){
        case Choice::SLASH:
            player.GetStats().GetHealth() -= Slash(GetStats(), player.GetStats(), playerdefend);
            cout << GetName() << " attacks!\n";
            break;
        case Choice::DEFEND:
            enemydefend = true;
            cout << GetName() << " is defending!\n\n";
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
            player.GetStats().GetHealth() -= Slash(GetStats(), player.GetStats(), playerdefend);
            cout << GetName() << " attacks!\n";
            break;
        case Choice::STAB:
            player.GetStats().GetHealth() -= Stab(GetStats(), player.GetStats(), playerdefend);
            cout << GetName() << " stabs!\n";
            break;
        case Choice::DEFEND:
            enemydefend = true;
            cout << GetName() << " is defending!\n\n";
            break;
        default:
            cout << GetName() << " does nothing!\n\n";
    }
}