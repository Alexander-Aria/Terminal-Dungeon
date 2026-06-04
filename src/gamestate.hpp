#pragma once

#include "player.hpp"

class GameState{
    private:
        int stage = 0;
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
