#pragma once

#include "player.hpp"

class GameState{
    private:
        int stage = 0;
        // Status 0 = on going, 1 = win, -1 = lose, -2 = turn back
        int status = 0;
        Player player;
    public:
        GameState(){};

        int &GetStage(){return stage;}
        int &GetStatus(){return status;}
        Player &GetPlayer(){return player;}

        void HealthReset(){player.GetStats().GetHealth() = player.GetStats().GetMaxHealth();}
};

void Game();
