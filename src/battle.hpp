#pragma once

#include "gamestate.hpp"
#include "enemy.hpp"

int Battle(int &stage, GameState &game, Enemy &enemytype);
int StatusCheck(Stats &playerstats, Stats &enemystats);
int Attack(Stats &attackerstats, Stats &defenderstats, bool &defend);
void PlayerTurn(Player &player, Enemy &enemy, bool &playerdefend, bool &enemydefend);
void EnemyTurn(Player &player, Enemy &enemy, bool &playerdefend, bool &enemydefend);