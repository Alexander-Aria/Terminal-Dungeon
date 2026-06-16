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
        PlayerTurn(game.GetPlayer(), enemy, playerdefend, enemydefend);
        battlestatus = StatusCheck(game.GetPlayer(), enemy);
        if(battlestatus != 0) break;

        EnemyTurn(game.GetPlayer(), enemy, playerdefend, enemydefend);
        battlestatus = StatusCheck(game.GetPlayer(), enemy);
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

int StatusCheck(Player &player, Enemy &enemy){
    if(player.IsDead()) return -1;
    else if(enemy.IsDead()) return 1;
    else return 0;
}

void PlayerTurn(Player &player, Enemy &enemy, bool &playerdefend, bool &enemydefend){
    int opt = 0;
    bool finish = false;

    while(!finish){
        cout << "__________________________\n";
        cout << "Player Health : " << player.GetStats().GetHealth() << "\n";
        cout << enemy.GetName() << " Health : " << enemy.GetStats().GetHealth() << "\n\n";
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
                        player.Slash(player.GetStats(), enemy.GetStats(), enemydefend);
                        finish = true;
                        break;
                    case 2:
                        cout << "You stabbed the enemy!\n";
                        player.Stab(player.GetStats(), enemy.GetStats(), enemydefend);
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
                if(player.InventoryAccess(BattleState::INBATTLE)) finish = true;
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

void EnemyTurn(Player &player, Enemy &enemy, bool &playerdefend, bool &enemydefend) {enemy.Turn(player, playerdefend, enemydefend);}

