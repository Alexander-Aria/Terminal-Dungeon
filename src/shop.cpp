#include "shop.hpp"
#include "utility.hpp"

#include <iostream>
using std::cout;

void ShopFunction(Player &player, const Shop &config){
    Shop shop(config);
    int opt = 0;

    while(true){
        cout << "\n_____________________________________________\n";
        cout << "Welcome Traveler!\n";
        cout << "Care to look at my wares?\n\n";
        cout << "0. Finish\n1. Buy\n2. Sell\n\n- ";
        NumInput(opt);

        switch(opt){
            case 0:
                cout << "\nBest of luck for your adventure!\n\n";
                return;
            case 1:
                shop.Buy(player);
                break;
            case 2:
                shop.Sell(player);
                break;
            default:
                cout << "Invalid Input!\n";
        }
    }
}

void Shop::Buy(Player &player){
    int opt = 0;

    while(true){
        cout << "Gold : " << player.GetGold() << "\n";
        ShowEquipment(GetInventory(), true);
        ShowInventory(GetInventory(), true);
        cout << "\n-2 to buy weapon.\n-1 to buy armor.\n0 to finish.\n\n- ";
        NumInput(opt);

        if(opt > 0 && opt <= size(GetInventory().GetConsumables())){
            if(GetInventory().GetConsumables()[opt-1].GetValue() <= player.GetGold()){
                player.GetGold() -= GetInventory().GetConsumables()[opt-1].GetValue();
                player.GetInventory().GetConsumables().push_back(GetInventory().GetConsumables()[opt-1]);
                cout << "You bought " << GetInventory().GetConsumables()[opt-1].GetName() << ".\n\n";
                GetInventory().GetConsumables().erase(GetInventory().GetConsumables().begin() + opt-1);
            }
            else cout << "You don't have enough gold!\n";
        }
        else if(opt == -1){
            if(GetInventory().GetArmor().GetValue() <= player.GetGold()){
                cout << "You bought " << GetInventory().GetArmor().GetName() << ".\n\n";
                player.GetGold() -= GetInventory().GetArmor().GetValue();
                player.ChangeEquipment(GetInventory().GetArmor());
                GetInventory().GetArmor() = NoArmor();
            }
            else cout << "You don't have enough gold!\n";
        }
        else if(opt == -2){
            if(GetInventory().GetWeapon().GetValue() <= player.GetGold()){
                cout << "You bought " << GetInventory().GetWeapon().GetName() << ".\n\n";
                player.GetGold() -= GetInventory().GetWeapon().GetValue();
                player.ChangeEquipment(GetInventory().GetWeapon());
                GetInventory().GetWeapon() = NoWeapon();
            }
            else cout << "You don't have enough gold!\n";
        }
        else if(opt == 0) return;
        else cout << "Invalid Input!\n";
    }
}

void Shop::Sell(Player &player){
    int opt = 0;

    while(true){
        cout << "Gold : " << player.GetGold() << "\n";
        ShowInventory(player.GetInventory(), true);
        cout << "\n0 to finish.\n\n- ";
        NumInput(opt);

        if(opt > 0 && opt <= size(player.GetInventory().GetConsumables())){
            cout << player.GetInventory().GetConsumables()[opt-1].GetName() << " was sold for " << player.GetInventory().GetConsumables()[opt-1].GetValue() << ".\n\n";
            player.GetGold() += player.GetInventory().GetConsumables()[opt-1].GetValue();
            GetInventory().GetConsumables().push_back(player.GetInventory().GetConsumables()[opt-1]);
            player.GetInventory().GetConsumables().erase(player.GetInventory().GetConsumables().begin() + opt-1);
        }
        else if(opt == 0) return;
        else cout << "Invalid Input!\n";
    }
}