#include "BattleSystem.h"
#include "FunctionsAndConsts.h"
#include "Skill.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <sstream>

using namespace std;

void BattleSystem::addPlayerPet(PlayerPet* pet) {
    playerPets.push_back(pet);
}

void BattleSystem::addComputerPet(ComputerPet* pet) {
    computerPets.push_back(pet);
}

PlayerPet* BattleSystem::getPlayerPet(int idx) {
    return playerPets[idx];
}

ComputerPet* BattleSystem::getComputerPet(int idx) {
    return computerPets[idx];
}

// Helper function to validate the player's pet choice
void BattleSystem::choosePlayerPets(Player& player) {
    auto getValidPetIndex = [&](const string& prompt, int excludeIdx = -1) -> int {
        while (true) {
            cout << formatMsg("�m�t�ΰT���n", "31", true) << prompt << "\n";
            string petName;
            cin >> petName;

            for (int i = 0; i < 5; i++) {
                if (petName == player.getPet(i)->getName() && i != excludeIdx) {
                    return i; // Return valid pet index
                }
            }
            cout << formatMsg("�m�t�ΰT���n", "31", true) << "��J�L�ġI�z�å��֦����W�٪��d��";
            if (excludeIdx != -1) {
                cout << "�θ��d���w�Q���";
            }
            cout << "�A�Э��s��J�G" << endl;
        }
    };

    // Choose the first pet
    int pet1Idx = getValidPetIndex("�A�ݭn���X�Ⱖ�d�����ԡA�п�J�����X���Ĥ@���d���W�١G�]���d���N�|�w�]���Ĥ@�^�X�ڤ誺�X���d���^");

    // Choose the second pet
    int pet2Idx = getValidPetIndex("�п�J�����X���ĤG���d���W�١G", pet1Idx);

    // Add pets to player's team
    addPlayerPet(player.getPet(pet1Idx));
    addPlayerPet(player.getPet(pet2Idx));
}

// Function to handle both player and computer actions
void BattleSystem::bothTakingAction(PlayerPet* playerPet, ComputerPet* computerPet) {
    // cout << "�i�ӤF!" << endl;
    int playerChoice;

    // Assume the computer will use its strongest attack if available
    int computerChoice = 1; // Default to the second skill
    // [DEBUG] cout << (computerPet->skills.size()) << ", " << (computerPet->skills[1] != nullptr) << ", " << (computerPet->skills[1]->CD) << endl;
    if (computerPet->skills.size() > 1 && computerPet->skills[1] != nullptr && computerPet->skills[1]->CD == 0) {
        computerChoice = 2; // Choose the strongest attack if the cooldown is zero
    }

    while(true) {
        string option;
        cin >> option;

        try {
            playerChoice = stoi(option); // Attempt to convert

            // Range check
            if (playerChoice >= 4 || playerChoice <= 0) {
                throw out_of_range("�ﶵ�W�X�d��I");
            }
        } catch (const invalid_argument& e) {
            cout << "�L�Ī��r��A�L�k�ഫ����ơI�ЦA��J�@��" << endl;
            continue;
        } catch (const out_of_range& e) {
            cout << e.what() << " �ЦA��J�@��" << endl;
            continue;
        }

        // Handle actions based on the player's choice
        if (playerChoice <= 2) {
            playerPet->attack(computerPet, playerChoice);
            computerPet->attack(playerPet, computerChoice);
            return;
        } else if (playerChoice == 3) {
            cout << "���հk�]��..." << endl;
            sleep(1);
            if (getRandomNum(0,100) < 50) {
                cout << "�k�]���\�I�԰������I" << endl;
                playerEscape = true;
                return;
            } else {
                cout << "�k�]���ѡI�t���d���o�ʤ����I" << endl;
                computerPet->attack(playerPet, computerChoice);
                return;
            }
        }
        
    }
}

// Function to start the battle
void BattleSystem::startBattle(Player& player) {
    // Get second highest stats from player's pets
    int maxHP = player.findSecondMaxHP();
    int attackPower = player.findSecondAttackPower();
    int defensePower = player.findSecondDefensePower();
    int speed = player.findSecondSpeed();

    // Create computer pets
    ComputerPet pet1(types[getRandomNum(0, 4)], maxHP + getRandomNum(-5, 5), attackPower + getRandomNum(-3, 5), defensePower + getRandomNum(-2, 5), speed + getRandomNum(-3, 5));
    ComputerPet pet2(types[getRandomNum(0, 4)], maxHP + getRandomNum(-5, 5), attackPower + getRandomNum(-3, 5), defensePower + getRandomNum(-2, 5), speed + getRandomNum(-3, 5));
    ComputerPet* pet1ptr = &(pet1);
    ComputerPet* pet2ptr = &(pet2);
    addComputerPet(pet1ptr);
    addComputerPet(pet2ptr);

    cout << formatMsg("�m�t�ΰT���n", "31", true)<< "�z�J�쪺����ݩʬ��G" << getComputerPet(0)->getType() << "�B" << getComputerPet(1)->getType() << "\n";
    sleep(1);
    choosePlayerPets(player);

    // Record which pets will be sent into battle
    int idxPlayer = 0;
    int idxComputer = 0;
    PlayerPet* playerPet = getPlayerPet(idxPlayer);
    ComputerPet* computerPet = getComputerPet(idxComputer);

    cout << "\n\n��Զ}�l�I" << endl;

    while (true) {
        cout << "\n\n\n�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X Round " << round << " �X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X\n" 
        // << "����P�ɥX�ۡI\n"
        ;

        cout << "�i�ڤ謣�X�j" << "\n";
        playerPet->print();
        

        cout << "�i�Ĥ謣�X�j" << "\n";
        computerPet->print();

        sleep(1);
        cout << "\n�п�ܱz���o�_����ʡ]�H�Ʀr�^�С^�G\n�@�@1.���q����\n�@�@2.�i������ ";
        if (playerPet->skills[1]->CD == 0) {
            cout << "�]���^�X�i�ϥΡ^\n";
        } else {
            cout << "�]���^�X���}��^\n";
        }
        cout << "�@�@3.�k�]\n";


        bothTakingAction(playerPet, computerPet);

        cout << "\n" << formatMsg("�m�t�ΰT���n", "31", true) << "�g�L���^�X�A����{�b�����A���G\n";
        cout << "�i�ڤ�j" << "\n";
        playerPet->print();
        cout << "�i�Ĥ�j" << "\n";
        computerPet->print();
        
        sleep(1);

        // Check if the player has escaped
        if (playerEscape) {
            cout << "�ڤ�k�]���\�A�԰������C\n";
            cout << "�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X" << endl;
            for (int i = 0; i < 2; ++i) {
                getPlayerPet(i)->heal();
                if (!(getPlayerPet(i)->isAlive())) {
                    getPlayerPet(i)->lose();
                }
            }
            break;
        }

        // Handle defeat and victory
        // ���a�o�����F
        if (!playerPet->isAlive()) {
            if (!getPlayerPet(0)->isAlive() && !getPlayerPet(1)->isAlive()) {
                if (getComputerPet(0)->isAlive() || getComputerPet(1)->isAlive()) {
                    cout << "�z���Ⱖ�d�����ԱѡA�Ĥ�Ĺ�o�����԰����ӧQ�I\n";
                } else {
                    cout << "���誺�d�����ԱѡA�����԰�����I\n";
                }
                getPlayerPet(0)->lose();
                getPlayerPet(1)->lose();
                break;
            } else {
                cout << "�z���Ӱ��d���w�ԱѡA�ڤ�b�U�@�^�X�N���X�t�@���d���W���I\n";
                idxPlayer = 1 - idxPlayer; // Switch to the other pet
                playerPet = getPlayerPet(idxPlayer);
            }
        } 
        // ���a�d�����M����
        else{ 
            // �q����ӳ����F
            if (!getComputerPet(0)->isAlive() && !getComputerPet(1)->isAlive()) {
                cout << "�Ĥ�Ⱖ�d�����Q���ѡA���߱z��o�����԰����ӧQ�I\n";
                for (int i = 0; i < 2; ++i) {
                    getPlayerPet(i)->heal();
                    if (getPlayerPet(i)->isAlive()) {
                        getPlayerPet(i)->win();
                    }
                }
                break;
            }else if (!getComputerPet(0)->isAlive() || !getComputerPet(1)->isAlive()) {
                idxComputer = 1 - idxComputer; // Switch to the other enemy pet
                computerPet = getComputerPet(idxComputer);
            }
        }

        round++;
        sleep(2);
    }
}
