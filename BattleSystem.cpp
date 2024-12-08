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
            cout << formatMsg("《系統訊息》", "31", true) << prompt << "\n >> ";
            string petName;
            cin >> petName;

            for (int i = 0; i < 5; i++) {
                if (petName == player.getPet(i)->getName() && i != excludeIdx) {
                    return i; // Return valid pet index
                }
            }
            cout << formatMsg("《系統訊息》", "31", true) << "輸入無效！您並未擁有此名稱的寵物";
            if (excludeIdx != -1) {
                cout << "或該寵物已被選擇";
            }
            cout << "，請重新輸入：" << endl;
        }
    };

    // Choose the first pet
    int pet1Idx = getValidPetIndex("你需要派出兩隻寵物應戰，請輸入欲派出的第一隻寵物名稱：（此寵物將會預設為第一回合我方的出戰寵物）");

    // Choose the second pet
    int pet2Idx = getValidPetIndex("請輸入欲派出的第二隻寵物名稱：", pet1Idx);

    // Add pets to player's team
    addPlayerPet(player.getPet(pet1Idx));
    addPlayerPet(player.getPet(pet2Idx));
}

// Function to handle both player and computer actions
void BattleSystem::bothTakingAction(PlayerPet*& playerPet, ComputerPet* computerPet, int &idxPlayer) {
    // cout << "進來了!" << endl;
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
                throw out_of_range("選項超出範圍！");
            }
        } catch (const invalid_argument& e) {
            cout << formatMsg("《系統訊息》", "31", true)  << "無效的字串，無法轉換為整數！請再輸入一次" << endl;
            continue;
        } catch (const out_of_range& e) {
            cout << formatMsg("《系統訊息》", "31", true)  << e.what() << " 請再輸入一次" << endl;
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
            cout << formatMsg("《系統訊息》", "31", true) << "嘗試逃跑中..." << endl;
            sleep(1);
            if (getRandomNum(0,100) < 50) {
                cout << formatMsg("《系統訊息》", "31", true) << "逃跑Successfully！戰鬥結束！" << endl;
                playerEscape = true;
                return;
            } else {
                cout << formatMsg("《系統訊息》", "31", true) << "逃跑失敗！系統寵物發動反擊！" << endl;
                computerPet->attack(playerPet, computerChoice);
                return;
            }
        }else if (playerChoice == 4) {
            
            idxPlayer = 1 - idxPlayer; // Switch to the other pet
            playerPet = getPlayerPet(idxPlayer);
            cout << formatMsg("《系統訊息》", "31", true) << "場上寵物現在更換為" << playerPet->name << "！" <<endl;
            sleep(0.5);
            cout << formatMsg("《系統訊息》", "31", true) << "你主動更換了寵物，視同發動一次技能。現在換系統方攻擊！" <<endl;
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

    cout << formatMsg("《系統訊息》", "31", true)<< "您遇到的對手屬性為：" << getComputerPet(0)->getType() << "、" << getComputerPet(1)->getType() << "\n";
    sleep(1);
    choosePlayerPets(player);

    // Record which pets will be sent into battle
    int idxPlayer = 0;
    int idxComputer = 0;
    int computerDeadCnt = 0;
    PlayerPet* playerPet = getPlayerPet(idxPlayer);
    ComputerPet* computerPet = getComputerPet(idxComputer);

    cout << "\n\n"  << formatMsg("《系統訊息》", "31", true) << "對戰開始！\n" << endl;

    while (true) {
        cout << "———————————————— Round " << round << " ————————————————\n" 
        // << "雙方同時出招！\n"
        ;

        cout << "【我方派出】" << "\n";
        playerPet->print();
        

        cout << "【敵方派出】" << "\n";
        computerPet->print();

        sleep(1);
        cout << "\n請選擇您欲發起的行動（以數字回覆）：\n　　1.普通攻擊\n　　2.進階攻擊 ";
        if (playerPet->skills[1]->CD == 0) {
            cout << "（此回合可使用）\n";
        } else {
            cout << "（此回合不開放）\n";
        }
        cout << "　　3.逃跑\n　　4.換角\n";


        bothTakingAction(playerPet, computerPet, idxPlayer);

        cout << "\n" << formatMsg("《系統訊息》", "31", true) << "經過此回合，雙方現在的狀態為：\n";
        cout << "【我方】" << "\n";
        playerPet->print();
        cout << "\n【敵方】" << "\n";
        computerPet->print();
        
        sleep(1);

        // Check if the player has escaped
        if (playerEscape) {
            cout << formatMsg("《系統訊息》", "31", true)<< "我方逃跑Successfully，戰鬥結束。\n";
            cout << "————————————————————————————————————————————————————————————————" << endl;
            for (int i = 0; i < 2; ++i) {
                getPlayerPet(i)->heal();
                if (!(getPlayerPet(i)->isAlive())) {
                    getPlayerPet(i)->lose();
                }
            }
            break;
        }

        // Handle defeat and victory
        // 玩家這局死了
        if (!playerPet->isAlive()) {
            // 如果玩家都死了
            if (!getPlayerPet(0)->isAlive() && !getPlayerPet(1)->isAlive()) {
                if (getComputerPet(0)->isAlive() || getComputerPet(1)->isAlive()) {
                    cout << formatMsg("《系統訊息》", "31", true)<< "您的兩隻寵物均戰敗，敵方贏得此次戰鬥的勝利！\n";
                    cout << "————————————————————————————————————————————————————————————————" << endl;

                    for (int i = 0; i < 2; i++){
                        getPlayerPet(i)->lose();
                    }
                    
                } else {
                    cout << formatMsg("《系統訊息》", "31", true)<< "雙方的寵物全戰敗，此次戰鬥平手！\n";
                    cout << "————————————————————————————————————————————————————————————————" << endl;
                }

                for (int i = 0; i < 2; i++){
                    getPlayerPet(i)->heal();
                    getPlayerPet(i)->skills[1]->reduceCD(true);
                }

                sleep(0.5);
                alignTime(12,0.3);
                break;

            // 如果只有死第一隻
            } else {
                cout << formatMsg("《系統訊息》", "31", true) << "您的該隻寵物已戰敗，我方在下一回合將派出另一隻寵物上場！\n";
                idxPlayer = 1 - idxPlayer; // Switch to the other pet
                playerPet = getPlayerPet(idxPlayer);

                // 如果系統這局也死了
                if((!getComputerPet(idxComputer)->isAlive()) && computerDeadCnt == 0 ){
                    cout << formatMsg("《系統訊息》", "31", true) << "敵方寵物被打敗了，系統換兵上陣！\n";
                    idxComputer = 1 - idxComputer; // Switch to the other enemy pet
                    computerPet = getComputerPet(idxComputer);
                    computerDeadCnt++;
                }else{
                    cout << formatMsg("《系統訊息》", "31", true)<< "雙方的寵物全戰敗，此次戰鬥平手！\n";
                    cout << "————————————————————————————————————————————————————————————————" << endl;
                
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
        // 玩家寵物仍然活著
        else{ 
            // 電腦兩個都死了
            if (!getComputerPet(0)->isAlive() && !getComputerPet(1)->isAlive()) {
                cout << formatMsg("《系統訊息》", "31", true) << "敵方兩隻寵物均被打敗，恭喜您獲得此次戰鬥的勝利！\n";
                cout << "————————————————————————————————————————————————————————————————" << endl;
                for (int i = 0; i < 2; ++i) {
                    if (getPlayerPet(i)->isAlive()) {
                        // cout << "DEBUG " << getPlayerPet(i)->name << "alive, HP=" << getPlayerPet(i)->getHP() << endl;
                        getPlayerPet(i)->win();
                    }
                    getPlayerPet(i)->heal();
                    //CD回復
                    getPlayerPet(i)->skills[1]->reduceCD(true);
                }
                sleep(0.5);
                alignTime(10,0.3);

                break;

            // 但電腦死了
            }else if ((!getComputerPet(0)->isAlive() || !getComputerPet(1)->isAlive()) && computerDeadCnt == 0 ) {
                cout << formatMsg("《系統訊息》", "31", true) << "敵方寵物被打敗了，系統換兵上陣！\n";
                idxComputer = 1 - idxComputer; // Switch to the other enemy pet
                computerPet = getComputerPet(idxComputer);
                computerDeadCnt++;
            }
        }

        round++;

        alignTime(10,0.08);
    }
}
