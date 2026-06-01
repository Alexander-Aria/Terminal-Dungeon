#include "class.hpp"

using namespace std;

// Backend Functions
template <typename T>
void NumInput(T &num);
void Ignore();

// Game Functions
int Battle(int &stage, GameState &game);
void Start(int &stage, GameState &game);
void Game(int save);
