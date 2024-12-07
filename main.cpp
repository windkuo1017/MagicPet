#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <random>
#include <thread>
#include <chrono>
#include <stdexcept>

#include "Player.h"
#include "Pet.h" 
#include "FunctionsAndConsts.h"
#include "Skill.h"
#include "BattleSystem.h"

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(0))); // 設定隨機種子

    Player player;
    PlayerPet pet1("金", "gold");
    PlayerPet pet2("木", "wood");
    PlayerPet pet3("水", "water");
    PlayerPet pet4("火", "fire");

    PlayerPet pet5("土", "mud");
    player.addPet(&pet1);
    player.addPet(&pet2);
    player.addPet(&pet3);
    player.addPet(&pet4);
    player.addPet(&pet5);

    cout << formatMsg("《系統訊息》", "31", true)  << "歡迎進入遊戲！\n";
    sleep(0.5);

    while (true) {
        cout << "\n\n\n" << formatMsg("《系統訊息》", "31", true) << "以下是您目前擁有的寵物資訊：\n";
        for (int i = 0; i < 5; i++) {
            player.getPet(i)->print();
        }
        sleep(1);

        while(true) {      
          cout << "\n" << formatMsg("《系統訊息》", "31", true) << "你準備好加入新戰鬥了嗎？（yes / no）\n>> ";
          string ans;
          cin >> ans;
          strLower(ans);

          if (ans == "yes" || ans == "y" || ans == "是" || ans == "1") {
              BattleSystem game;
              game.startBattle(player);
              break;
          } else if (ans == "no" || ans == "n" || ans == "否" || ans == "0") {
                sleep(0.5);
                continue;
          } else {
              cout  << formatMsg("《系統訊息》", "31", true) << "輸入無效！請重新輸入。\n";
              sleep(0.5);
              continue;
          }
        }
    }

    system("PAUSE");
    return 0;
}

