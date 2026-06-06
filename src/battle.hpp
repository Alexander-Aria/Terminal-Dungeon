#pragma once

class GameState;
class Player;
class Enemy;
class Stats;

int Battle(GameState &game, Enemy &enemytype);
int StatusCheck(Stats &playerstats, Stats &enemystats);
int Attack(Stats &attackerstats, Stats &defenderstats, bool &defend);
void PlayerTurn(Player &player, Enemy &enemy, bool &playerdefend, bool &enemydefend);
void EnemyTurn(Player &player, Enemy &enemy, bool &playerdefend, bool &enemydefend);