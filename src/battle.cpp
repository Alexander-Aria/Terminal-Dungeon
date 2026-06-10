#include "battle.hpp"
#include "gamestate.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "utility.hpp"

#include <iostream>

using std::cout;

void Battle(GameState &game, Enemy &enemy){
    Random RNG;
    int battlestatus = 0;
    bool playerdefend = false, enemydefend = false;

    cout << enemy.GetName() << " appeared!\n";
    cout << "Description : " << enemy.GetDescription() << "\n";
    while(battlestatus == 0){
        cout << "__________________________\n";
        cout << "Player Health : " << game.GetPlayer().GetStats().GetHealth() << "\n";
        cout << enemy.GetName() << " Health : " << enemy.GetStats().GetHealth() << "\n\n";

        PlayerTurn(game.GetPlayer(), enemy, playerdefend, enemydefend);
        battlestatus = StatusCheck(game.GetPlayer().GetStats(), enemy.GetStats());
        if(battlestatus != 0) break;

        EnemyTurn(game.GetPlayer(), enemy, playerdefend, enemydefend);
        battlestatus = StatusCheck(game.GetPlayer().GetStats(), enemy.GetStats());
        if(battlestatus != 0) break;
    }
    if(battlestatus == -1){
        game.GetStatus() = Status::LOSE;
    }
    else if(battlestatus == 1){
        cout << "\nYou won!\n";
        game.GetPlayer().GetExp() += enemy.GetExpReward();
        game.GetPlayer().GetGold() += enemy.GetGoldReward();
        cout << "You gained " << enemy.GetExpReward() << " experience and " << enemy.GetGoldReward() << " gold!\n\n";
        game.GetPlayer().LevelUp();
    }
    game.BattleStateReset();
}

int StatusCheck(Stats &playerstats, Stats &enemystats){
    if(playerstats.GetHealth() <= 0) return -1;
    else if(enemystats.GetHealth() <= 0) return 1;
    else return 0;
}

void PlayerTurn(Player &player, Enemy &enemy, bool &playerdefend, bool &enemydefend){
    int opt = 0;
    bool finish = false;

    while(!finish){
        cout << "1. Attack\n2. Defend\n3. Items\n4. Surrender\n\n- ";
        NumInput(opt);

        switch(opt){
            case 1:
                cout << "___________________________\n";
                cout << "0. Back\n1. Slash | High Damage\n2. Stab  | Medium Damage, Piercing (breaks defense)\n\n- ";
                NumInput(opt);
                switch(opt){
                    case 1:
                        cout << "You slashed the enemy!\n";
                        enemy.GetStats().GetHealth() -= Slash(player.GetStats(), enemy.GetStats(), enemydefend);
                        finish = true;
                        break;
                    case 2:
                        cout << "You stabbed the enemy!\n";
                        enemy.GetStats().GetHealth() -= Stab(player.GetStats(), enemy.GetStats(), enemydefend);
                        finish = true;
                        break;
                }
                break;
            case 2:
                cout << "You are defending!\n\n";
                playerdefend = true;
                finish = true;
                break;
            case 3:
                if(InventoryAccess(player, BattleState::INBATTLE)) finish = true;
                break;
            case 4:
                player.GetStats().GetHealth() = 0;
                finish = true;
                break;
            default:
                cout << "Invalid Input!\n\n";
        }
    }
}

void EnemyTurn(Player &player, Enemy &enemy, bool &playerdefend, bool &enemydefend){
    Random RNG;
    int RNGnum = RNG.Int(1,100);
    int choice = 0;

    if(enemydefend == true) choice = 1;
    else{
        if(RNGnum <= enemy.GetAttChance()) choice = 1;
        else if(RNGnum > 100 - enemy.GetDefChance()) choice = 2;
    }

    // 0 = Nothing, 1 = Attack, 2 = Defend
    switch(choice){
        case 1:
            cout << enemy.GetName() << " attacks!\n";
            player.GetStats().GetHealth() -= Slash(enemy.GetStats(), player.GetStats(), playerdefend);
            break;
        case 2:
            enemydefend = true;
            cout << enemy.GetName() << " is defending!\n\n";
            break;
        default:
            cout << enemy.GetName() << " does nothing!\n\n";
    }
}

int Slash(Stats &attackerstats, Stats &defenderstats, bool &defend){
    Random RNG;
    double basedamage = 10.0 * attackerstats.GetStrength()/defenderstats.GetDefense();
    int damage; 
    
    if(defend){
        damage = static_cast<int>(round(0.5 * RNG.Int(round(0.8 * basedamage), round(1.2 * basedamage))));
        if(RNG.Int(0,2) == 0){
            cout << "The defense is broken!\n";
            defend = false;
        }
        else cout << "The defenders defense held strong!\n";
    }
    else damage = static_cast<int>(RNG.Int(round(0.8 * basedamage), round(1.2 * basedamage)));

    cout << "The attacker dealt " << damage << " damage!\n\n";
    return damage;
}

int Stab(Stats &attackerstats, Stats &defenderstats, bool &defend){
    Random RNG;
    double basedamage = 6.0 * attackerstats.GetStrength()/defenderstats.GetDefense();
    int damage; 
    
    damage = static_cast<int>(RNG.Int(round(0.8 * basedamage), round(1.2 * basedamage)));
    if(defend) {
        cout << "The defense is broken!\n";
        defend = false;
    }

    cout << "The attacker dealt " << damage << " damage!\n\n";
    return damage;
}