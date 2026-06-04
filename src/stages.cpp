#include "stages.hpp"
#include "enemy.hpp"
#include "battle.hpp"
#include "utility.hpp"

#include <iostream>

using std::cout;
using std::cin;

void StageZero(int &stage, GameState &game){
    char choice = 'n';
    Enemy wolfcub(Stats(50, 50, 3, 5), "Wolf Cub", "A young wolf cub.");

    cout << "Do you want to play the tutorial? y/n?";
    cin >> choice;
    Ignore();
    if(choice == 'y'){
        Battle(stage, game, wolfcub);
    }
    stage++;
}