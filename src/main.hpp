#include "class.hpp"

// Utility Functions
template <typename T>
void NumInput(T &num);
void Ignore();

// Game Functions
int Battle(int &stage, GameState &game, Enemy &enemytype);
int StatusCheck(Stats &playerstats, Stats &enemystats);
void Game();
void InventoryAccess(Player &player);
void PlayerTurn(Player &player, Enemy &enemy, bool &playerdefend, bool &enemydefend);
void EnemyTurn(Player &player, Enemy &enemy, bool &playerdefend, bool &enemydefend);

void StageZero(int &stage, GameState &game);

int Attack(Stats &attackerstats, Stats &defenderstats, bool &defend);
