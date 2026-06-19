#pragma once

class GameState;
class Player;
class Enemy;
class Stats;

void Battle(GameState &game, Enemy &enemy);
int StatusCheck(Player &player, Enemy &enemy);
void PlayerTurn(Player &player, Enemy &enemy);
void EnemyTurn(Player &player, Enemy &);