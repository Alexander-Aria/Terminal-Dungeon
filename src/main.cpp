#include "gamestate.hpp"
#include "stages.hpp"
#include "utility.hpp"

#include <iostream>

using std::cout;
using std::cin;

void Game(){
    GameState game;
    bool loop = true;

    while(loop){
        switch(game.GetStage()){
            case 0:
                StageZero(game.GetStage(), game);
                break;
        }
        if(game.GetStage() == 10){
            cout << "Congratulations!\n";
            cout << "You won the game!\n";
            cout << "Thanks for playing!\n";
            loop = false;
        }
        else if(game.GetStage() == -1){
            cout << "You died!\n";
            loop = false;
        }
    }
}

int main(){
    int opt, status = 0;

    cout << "______________________________\n";
    cout << "Terminal Dungeon\n";
    cout << "0. Exit\n1. Start\n\n- ";
    NumInput<int> (opt);
    switch(opt){
        case 0:
            cout << "Exiting...\n";
            return 0;
        case 1:
            Game();
            break;
        case 2:
            cout << "Invalid input!\n";
    }
}