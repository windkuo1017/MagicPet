#ifndef BATTLE_SYSTEM_H
#define BATTLE_SYSTEM_H

#include <iostream>
#include <vector>
#include <string>
#include "Pet.h"  // Assuming you have a ComputerPet class
#include "Player.h"  // Assuming the Player class is already defined
#include "FunctionsAndConsts.h"

using namespace std;

class BattleSystem {
private:
    int round = 1;
    bool playerEscape = false;
    vector<PlayerPet*> playerPets;
    vector<ComputerPet*> computerPets;

public:
    void addPlayerPet(PlayerPet* pet);
    void addComputerPet(ComputerPet* pet);
    PlayerPet* getPlayerPet(int idx);
    ComputerPet* getComputerPet(int idx);

    // Let player choose pets for the battle
    void choosePlayerPets(Player& player);
    

    // Let both player and computer pet take actions
    void bothTakingAction(PlayerPet*& playerPet, ComputerPet* computerPet, int &idxPlayer);

    // Start the battle
    void startBattle(Player& player);
};

#endif
