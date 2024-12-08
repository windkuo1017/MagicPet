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
    srand(static_cast<unsigned>(time(0))); // ³]©wÀH¾÷ºØ¤l

    Player player;
    PlayerPet pet1("ª÷", "gold");
    PlayerPet pet2("¤ì", "wood");
    PlayerPet pet3("¤ô", "water");
    PlayerPet pet4("¤õ", "fire");

    PlayerPet pet5("¤g", "mud");
    player.addPet(&pet1);
    player.addPet(&pet2);
    player.addPet(&pet3);
    player.addPet(&pet4);
    player.addPet(&pet5);

    cout << formatMsg("¡m¨t²Î°T®§¡n", "31", true)  << "Åwªï¶i¤J¹CÀ¸¡I\n";
    sleep(0.5);

    cout << endl;
    cout << endl;
    cout << "¢i¢i¢i¢i¢i¢iùß  ¢i¢i¢i¢i¢iùß ¢i¢i¢i¢i¢i¢i¢i¢iùß¢i¢i¢i¢i¢i¢i¢i¢iùß¢i¢iùß     ¢i¢i¢i¢i¢i¢i¢iùß¢i¢i¢i¢i¢i¢iùß ¢i¢i¢i¢i¢i¢i¢iùß¢i¢i¢i¢i¢i¢i¢i¢iùß¢i¢i¢i¢i¢i¢i¢iùß                                              \n";
    cout << "¢i¢iùÝ¢¤¢¤¢i¢iùß¢i¢iùÝ¢¤¢¤¢i¢iùßùã¢¤¢¤¢i¢iùÝ¢¤¢¤ùåùã¢¤¢¤¢i¢iùÝ¢¤¢¤ùå¢i¢iùø     ¢i¢iùÝ¢¤¢¤¢¤¢¤ùå¢i¢iùÝ¢¤¢¤¢i¢iùß¢i¢iùÝ¢¤¢¤¢¤¢¤ùåùã¢¤¢¤¢i¢iùÝ¢¤¢¤ùå¢i¢iùÝ¢¤¢¤¢¤¢¤ùå¢i¢iùß                                           \n";
    cout << "¢i¢i¢i¢i¢i¢iùÝùå¢i¢i¢i¢i¢i¢i¢iùø   ¢i¢iùø      ¢i¢iùø   ¢i¢iùø     ¢i¢i¢i¢i¢iùß  ¢i¢i¢i¢i¢i¢iùÝùå¢i¢i¢i¢i¢iùß     ¢i¢iùø   ¢i¢i¢i¢i¢i¢i¢iùßùã¢¤ùå                                           \n";
    cout << "¢i¢iùÝ¢¤¢¤¢i¢iùß¢i¢iùÝ¢¤¢¤¢i¢iùø   ¢i¢iùø      ¢i¢iùø   ¢i¢iùø     ¢i¢iùÝ¢¤¢¤ùå  ¢i¢iùÝ¢¤¢¤¢¤ùå ¢i¢iùÝ¢¤¢¤ùå     ¢i¢iùø   ùã¢¤¢¤¢¤¢¤¢i¢iùø¢i¢iùß                                           \n";
    cout << "¢i¢i¢i¢i¢i¢iùÝùå¢i¢iùø  ¢i¢iùø   ¢i¢iùø      ¢i¢iùø   ¢i¢i¢i¢i¢i¢i¢iùß¢i¢i¢i¢i¢i¢i¢iùß¢i¢iùø     ¢i¢i¢i¢i¢i¢i¢iùß   ¢i¢iùø   ¢i¢i¢i¢i¢i¢i¢iùøùã¢¤ùå                                           \n";
    cout << "ùã¢¤¢¤¢¤¢¤¢¤ùå ùã¢¤ùå  ùã¢¤ùå   ùã¢¤ùå      ùã¢¤ùå   ùã¢¤¢¤¢¤¢¤¢¤¢¤ùåùã¢¤¢¤¢¤¢¤¢¤¢¤ùåùã¢¤ùå     ùã¢¤¢¤¢¤¢¤¢¤¢¤ùå   ùã¢¤ùå   ùã¢¤¢¤¢¤¢¤¢¤¢¤ùå                                              \n";
    cout << "                                                                                                                                 \n";
    cout << "    ¢i¢i¢i¢i¢i¢iùß ¢i¢iùß¢i¢i¢i¢i¢i¢i¢iùß¢i¢i¢i¢i¢i¢i¢iùß     ¢i¢i¢i¢i¢i¢iùß ¢i¢i¢i¢i¢i¢i¢iùß     ¢i¢i¢i¢i¢i¢iùß¢i¢iùß  ¢i¢iùß ¢i¢i¢i¢i¢iùß ¢i¢i¢iùß   ¢i¢i¢iùß¢i¢i¢i¢i¢i¢iùß ¢i¢iùß ¢i¢i¢i¢i¢i¢iùß ¢i¢i¢iùß   ¢i¢iùß¢i¢i¢i¢i¢i¢i¢iùß\n";
    cout << "    ¢i¢iùÝ¢¤¢¤¢i¢iùß¢i¢iùø¢i¢iùÝ¢¤¢¤¢¤¢¤ùå¢i¢iùÝ¢¤¢¤¢¤¢¤ùå    ¢i¢iùÝ¢¤¢¤¢¤¢i¢iùß¢i¢iùÝ¢¤¢¤¢¤¢¤ùå    ¢i¢iùÝ¢¤¢¤¢¤¢¤ùå¢i¢iùø  ¢i¢iùø¢i¢iùÝ¢¤¢¤¢i¢iùß¢i¢i¢i¢iùß ¢i¢i¢i¢iùø¢i¢iùÝ¢¤¢¤¢i¢iùß¢i¢iùø¢i¢iùÝ¢¤¢¤¢¤¢i¢iùß¢i¢i¢i¢iùß  ¢i¢iùø¢i¢iùÝ¢¤¢¤¢¤¢¤ùå\n";
    cout << "    ¢i¢i¢i¢i¢i¢iùÝùå¢i¢iùø¢i¢i¢i¢i¢i¢i¢iùß¢i¢i¢i¢i¢iùß      ¢i¢iùø   ¢i¢iùø¢i¢i¢i¢i¢iùß      ¢i¢iùø     ¢i¢i¢i¢i¢i¢i¢iùø¢i¢i¢i¢i¢i¢i¢iùø¢i¢iùÝ¢i¢i¢i¢iùÝ¢i¢iùø¢i¢i¢i¢i¢i¢iùÝùå¢i¢iùø¢i¢iùø   ¢i¢iùø¢i¢iùÝ¢i¢iùß ¢i¢iùø¢i¢i¢i¢i¢i¢i¢iùß\n";
    cout << "    ¢i¢iùÝ¢¤¢¤¢i¢iùß¢i¢iùøùã¢¤¢¤¢¤¢¤¢i¢iùø¢i¢iùÝ¢¤¢¤ùå      ¢i¢iùø   ¢i¢iùø¢i¢iùÝ¢¤¢¤ùå      ¢i¢iùø     ¢i¢iùÝ¢¤¢¤¢i¢iùø¢i¢iùÝ¢¤¢¤¢i¢iùø¢i¢iùøùã¢i¢iùÝùå¢i¢iùø¢i¢iùÝ¢¤¢¤¢¤ùå ¢i¢iùø¢i¢iùø   ¢i¢iùø¢i¢iùøùã¢i¢iùß¢i¢iùøùã¢¤¢¤¢¤¢¤¢i¢iùø\n";
    cout << "    ¢i¢iùø  ¢i¢iùø¢i¢iùø¢i¢i¢i¢i¢i¢i¢iùø¢i¢i¢i¢i¢i¢i¢iùß    ùã¢i¢i¢i¢i¢i¢iùÝùå¢i¢iùø         ùã¢i¢i¢i¢i¢i¢iùß¢i¢iùø  ¢i¢iùø¢i¢iùø  ¢i¢iùø¢i¢iùø ùã¢¤ùå ¢i¢iùø¢i¢iùø     ¢i¢iùøùã¢i¢i¢i¢i¢i¢iùÝùå¢i¢iùø ùã¢i¢i¢i¢iùø¢i¢i¢i¢i¢i¢i¢iùø\n";
    cout << "    ùã¢¤ùå  ùã¢¤ùåùã¢¤ùåùã¢¤¢¤¢¤¢¤¢¤¢¤ùåùã¢¤¢¤¢¤¢¤¢¤¢¤ùå     ùã¢¤¢¤¢¤¢¤¢¤ùå ùã¢¤ùå          ùã¢¤¢¤¢¤¢¤¢¤ùåùã¢¤ùå  ùã¢¤ùåùã¢¤ùå  ùã¢¤ùåùã¢¤ùå     ùã¢¤ùåùã¢¤ùå     ùã¢¤ùå ùã¢¤¢¤¢¤¢¤¢¤ùå ùã¢¤ùå  ùã¢¤¢¤¢¤ùåùã¢¤¢¤¢¤¢¤¢¤¢¤ùå\n";
                                                                                                                                    
    sleep(1);

    while (true) {
        cout << "\n\n\n" << formatMsg("¡m¨t²Î°T®§¡n", "31", true) << "¥H¤U¬O±z¥Ø«e¾Ö¦³ªºÃdª«¸ê°T¡G\n";
        for (int i = 0; i < 5; i++) {
            player.getPet(i)->print();
        }
        sleep(1);

        while(true) {      
          cout << "\n" << formatMsg("¡m¨t²Î°T®§¡n", "31", true) << "§A·Ç³Æ¦n¥[¤J·s¾Ô°«¤F¶Ü¡H¡]yes / no¡^\n>> ";
          string ans;
          cin >> ans;
          strLower(ans);

          if (ans == "yes" || ans == "y" || ans == "¬O" || ans == "1") {
              BattleSystem game;
              game.startBattle(player);
              break;
          } else if (ans == "no" || ans == "n" || ans == "§_" || ans == "0") {
                sleep(0.5);
                continue;
          } else {
              cout  << formatMsg("¡m¨t²Î°T®§¡n", "31", true) << "¿é¤JµL®Ä¡I½Ð­«·s¿é¤J¡C\n";
              sleep(0.5);
              continue;
          }
        }
    }

    system("PAUSE");
    return 0;
}

