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
            cout << formatMsg("�m�t�ΰT���n", "31", true) << prompt << "\n >> ";
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
void BattleSystem::bothTakingAction(PlayerPet*& playerPet, ComputerPet* computerPet, int &idxPlayer) {
    // cout << "�i�ӤF!" << endl;
    int playerChoice;

    // Assume the computer will use its strongest attack if available
    int computerChoice = 1; // Default to the second skill
    // [DEBUG] cout << (computerPet->skills.size()) << ", " << (computerPet->skills[1] != nullptr) << ", " << (computerPet->skills[1]->CD) << endl;
    if (computerPet->skills.size() > 1 && computerPet->skills[1] != nullptr && computerPet->skills[1]->CD == 0) {
        computerChoice = 2; // Choose the strongest attack if the cooldown is zero
    }

    while(true) {
        cout << ">> " ;
        string option;
        cin >> option;
        int size = option.size();

        try {
            playerChoice = stoi(option); // Attempt to convert

            // Range check
            if (size != 1 ||playerChoice > 4 || playerChoice <= 0) {
                throw out_of_range("�ﶵ�W�X�d��I");
            }
        } catch (const invalid_argument& e) {
            cout << formatMsg("�m�t�ΰT���n", "31", true)  << "�L�Ī��r��A�L�k�ഫ����ơI�ЦA��J�@��" << endl;
            continue;
        } catch (const out_of_range& e) {
            cout << formatMsg("�m�t�ΰT���n", "31", true)  << e.what() << " �ЦA��J�@��" << endl;
            continue;
        }

        // Handle actions based on the player's choice
        if (playerChoice <= 2) {
            if(playerPet->attack(computerPet, playerChoice) == -2){
                continue;
            }
            computerPet->attack(playerPet, computerChoice);
            return;
        } else if (playerChoice == 3) {
            cout << formatMsg("�m�t�ΰT���n", "31", true) << "���հk�]��..." << endl;
            sleep(1);
            if (getRandomNum(0,100) < 50) {
                cout << formatMsg("�m�t�ΰT���n", "31", true) << "�k�]Successfully�I�԰������I" << endl;
                playerEscape = true;
                return;
            } else {
                cout << formatMsg("�m�t�ΰT���n", "31", true) << "�k�]���ѡI�t���d���o�ʤ����I" << endl;
                computerPet->attack(playerPet, computerChoice);
                return;
            }
        }else if (playerChoice == 4) {
            
            idxPlayer = 1 - idxPlayer; // Switch to the other pet
            playerPet = getPlayerPet(idxPlayer);
            cout << formatMsg("�m�t�ΰT���n", "31", true) << "���W�d���{�b�󴫬�" << playerPet->name << "�I" <<endl;
            sleep(0.5);
            cout << formatMsg("�m�t�ΰT���n", "31", true) << "�A�D�ʧ󴫤F�d���A���P�o�ʤ@���ޯ�C�{�b���t�Τ�����I" <<endl;
            computerPet->attack(playerPet, computerChoice);
            return;
        }
        
    }
}

// Function to start the battle
void BattleSystem::startBattle(Player& player) {

    int maxHP = player.findSecondMaxHP();
    int attackPower = player.findSecondAttackPower();
    int defensePower = player.findSecondDefensePower();

    int speed = player.findSecondSpeed();


    // Create computer pets
    ComputerPet pet1(types[getRandomNum(0, 4)], maxHP + getRandomNum(-10, 10), attackPower + getRandomNum(-3, 5), defensePower + getRandomNum(-2, 5), speed + getRandomNum(-3, 5));
    ComputerPet pet2(types[getRandomNum(0, 4)], maxHP + getRandomNum(-10, 20), attackPower + getRandomNum(-3, 10), defensePower + getRandomNum(-2, 10), speed + getRandomNum(-3, 10));
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
    int computerDeadCnt = 0;
    PlayerPet* playerPet = getPlayerPet(idxPlayer);
    ComputerPet* computerPet = getComputerPet(idxComputer);

    cout << "\n\n"  << formatMsg("�m�t�ΰT���n", "31", true) << "��Զ}�l�I\n" << endl;

    while (true) {
        cout << "�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X Round " << round << " �X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X\n" 
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
        cout << "�@�@3.�k�]\n�@�@4.����\n";


        bothTakingAction(playerPet, computerPet, idxPlayer);

        cout << "\n" << formatMsg("�m�t�ΰT���n", "31", true) << "�g�L���^�X�A����{�b�����A���G\n";
        cout << "�i�ڤ�j" << "\n";
        playerPet->print();
        cout << "\n�i�Ĥ�j" << "\n";
        computerPet->print();
        
        sleep(1);

        // Check if the player has escaped
        if (playerEscape) {
            cout << formatMsg("�m�t�ΰT���n", "31", true)<< "�ڤ�k�]Successfully�A�԰������C\n";
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
            // �p�G���a�����F
            if (!getPlayerPet(0)->isAlive() && !getPlayerPet(1)->isAlive()) {
                if (getComputerPet(0)->isAlive() || getComputerPet(1)->isAlive()) {
                    cout << formatMsg("�m�t�ΰT���n", "31", true)<< "�z���Ⱖ�d�����ԱѡA�Ĥ�Ĺ�o�����԰����ӧQ�I\n";
                    cout << "�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X" << endl;

                    for (int i = 0; i < 2; i++){
                        getPlayerPet(i)->lose();
                    }
                    
                } else {
                    cout << formatMsg("�m�t�ΰT���n", "31", true)<< "���誺�d�����ԱѡA�����԰�����I\n";
                    cout << "�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X" << endl;
                }

                for (int i = 0; i < 2; i++){
                    getPlayerPet(i)->heal();
                    getPlayerPet(i)->skills[1]->reduceCD(true);
                }

                sleep(0.5);
                alignTime(12,0.3);
                break;

            // �p�G�u�����Ĥ@��
            } else {
                cout << formatMsg("�m�t�ΰT���n", "31", true) << "�z���Ӱ��d���w�ԱѡA�ڤ�b�U�@�^�X�N���X�t�@���d���W���I\n";
                idxPlayer = 1 - idxPlayer; // Switch to the other pet
                playerPet = getPlayerPet(idxPlayer);

                // �p�G�t�γo���]���F
                if((!getComputerPet(idxComputer)->isAlive()) && computerDeadCnt == 0 ){
                    cout << formatMsg("�m�t�ΰT���n", "31", true) << "�Ĥ��d���Q���ѤF�A�t�δ��L�W�}�I\n";
                    idxComputer = 1 - idxComputer; // Switch to the other enemy pet
                    computerPet = getComputerPet(idxComputer);
                    computerDeadCnt++;
                }else{
                    cout << formatMsg("�m�t�ΰT���n", "31", true)<< "���誺�d�����ԱѡA�����԰�����I\n";
                    cout << "�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X" << endl;
                
                    for (int i = 0; i < 2; i++){
                        getPlayerPet(i)->heal();
                        getPlayerPet(i)->skills[1]->reduceCD(true);
                    }

                    sleep(0.5);
                    alignTime(20,0.1);
                    break;
                }
            }
        } 
        // ���a�d�����M����
        else{ 
            // �q����ӳ����F
            if (!getComputerPet(0)->isAlive() && !getComputerPet(1)->isAlive()) {
                cout << formatMsg("�m�t�ΰT���n", "31", true) << "�Ĥ�Ⱖ�d�����Q���ѡA���߱z��o�����԰����ӧQ�I\n";
                cout << "�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X�X" << endl;
                for (int i = 0; i < 2; ++i) {
                    if (getPlayerPet(i)->isAlive()) {
                        // cout << "DEBUG " << getPlayerPet(i)->name << "alive, HP=" << getPlayerPet(i)->getHP() << endl;
                        getPlayerPet(i)->win();
                    }
                    getPlayerPet(i)->heal();
                    //CD�^�_
                    getPlayerPet(i)->skills[1]->reduceCD(true);
                }
                sleep(0.5);
                alignTime(10,0.3);

                break;

            // ���q�����F
            }else if ((!getComputerPet(0)->isAlive() || !getComputerPet(1)->isAlive()) && computerDeadCnt == 0 ) {
                cout << formatMsg("�m�t�ΰT���n", "31", true) << "�Ĥ��d���Q���ѤF�A�t�δ��L�W�}�I\n";
                idxComputer = 1 - idxComputer; // Switch to the other enemy pet
                computerPet = getComputerPet(idxComputer);
                computerDeadCnt++;
            }
        }

        round++;

        alignTime(10,0.08);
    }
}
