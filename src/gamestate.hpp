#pragma once

#include "player.hpp"

enum class Status{
    ONGOING = 0,
    WIN = 1,
    LOSE = -1,
    TURNBACK = -2
};

class GameState{
    private:
        int stage = 0;
        Status status = Status::ONGOING;
        Player player;
    public:
        GameState(){};

        int &GetStage(){return stage;}
        Status &GetStatus(){return status;}
        Player &GetPlayer(){return player;}

        void HealthReset(){player.GetStats().GetHealth() = player.GetStats().GetMaxHealth();}
};

void Game();
