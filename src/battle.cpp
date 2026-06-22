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

    cout << enemy.GetName() << " appeared!\n";
    cout << "Description : " << enemy.GetDescription() << "\n";
    while(battlestatus == 0){
        PlayerTurn(game.GetPlayer(), enemy);
        battlestatus = StatusCheck(game.GetPlayer(), enemy);
        if(battlestatus != 0) break;

        EnemyTurn(game.GetPlayer(), enemy);
        battlestatus = StatusCheck(game.GetPlayer(), enemy);
        if(battlestatus != 0) break;
    }
    if(battlestatus == -1){
        game.GetStatus() = Status::LOSE;
    }
    else if(battlestatus == 1){
        cout << "You won!\n";
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

void PlayerTurn(Player &player, Enemy &enemy){
    if(player.GetUsingWeapon() == WeaponType::MELEE) player.MeleeOption(enemy);
    else player.RangedOption(enemy);
}

void EnemyTurn(Player &player, Enemy &enemy) {enemy.Turn(player);}

