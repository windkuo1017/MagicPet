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
    srand(static_cast<unsigned>(time(0))); // �]�w�H���ؤl

    Player player;
    PlayerPet pet1("��", "gold");
    PlayerPet pet2("��", "wood");
    PlayerPet pet3("��", "water");
    PlayerPet pet4("��", "fire");

    PlayerPet pet5("�g", "mud");
    player.addPet(&pet1);
    player.addPet(&pet2);
    player.addPet(&pet3);
    player.addPet(&pet4);
    player.addPet(&pet5);

    cout << formatMsg("�m�t�ΰT���n", "31", true)  << "�w��i�J�C���I\n";
    sleep(0.5);

    cout << endl;
    cout << endl;
    cout << "�i�i�i�i�i�i��  �i�i�i�i�i�� �i�i�i�i�i�i�i�i�ߢi�i�i�i�i�i�i�i�ߢi�i��     �i�i�i�i�i�i�i�ߢi�i�i�i�i�i�� �i�i�i�i�i�i�i�ߢi�i�i�i�i�i�i�i�ߢi�i�i�i�i�i�i��                                              \n";
    cout << "�i�i�ݢ����i�i�ߢi�i�ݢ����i�i���㢤���i�i�ݢ������㢤���i�i�ݢ�����i�i��     �i�i�ݢ���������i�i�ݢ����i�i�ߢi�i�ݢ����������㢤���i�i�ݢ�����i�i�ݢ���������i�i��                                           \n";
    cout << "�i�i�i�i�i�i����i�i�i�i�i�i�i��   �i�i��      �i�i��   �i�i��     �i�i�i�i�i��  �i�i�i�i�i�i����i�i�i�i�i��     �i�i��   �i�i�i�i�i�i�i���㢤��                                           \n";
    cout << "�i�i�ݢ����i�i�ߢi�i�ݢ����i�i��   �i�i��      �i�i��   �i�i��     �i�i�ݢ�����  �i�i�ݢ������� �i�i�ݢ�����     �i�i��   �㢤�������i�i���i�i��                                           \n";
    cout << "�i�i�i�i�i�i����i�i��  �i�i��   �i�i��      �i�i��   �i�i�i�i�i�i�i�ߢi�i�i�i�i�i�i�ߢi�i��     �i�i�i�i�i�i�i��   �i�i��   �i�i�i�i�i�i�i���㢤��                                           \n";
    cout << "�㢤���������� �㢤��  �㢤��   �㢤��      �㢤��   �㢤�������������㢤�������������㢤��     �㢤������������   �㢤��   �㢤������������                                              \n";
    cout << "                                                                                                                                 \n";
    cout << "    �i�i�i�i�i�i�� �i�i�ߢi�i�i�i�i�i�i�ߢi�i�i�i�i�i�i��     �i�i�i�i�i�i�� �i�i�i�i�i�i�i��     �i�i�i�i�i�i�ߢi�i��  �i�i�� �i�i�i�i�i�� �i�i�i��   �i�i�i�ߢi�i�i�i�i�i�� �i�i�� �i�i�i�i�i�i�� �i�i�i��   �i�i�ߢi�i�i�i�i�i�i��\n";
    cout << "    �i�i�ݢ����i�i�ߢi�i���i�i�ݢ���������i�i�ݢ���������    �i�i�ݢ������i�i�ߢi�i�ݢ���������    �i�i�ݢ���������i�i��  �i�i���i�i�ݢ����i�i�ߢi�i�i�i�� �i�i�i�i���i�i�ݢ����i�i�ߢi�i���i�i�ݢ������i�i�ߢi�i�i�i��  �i�i���i�i�ݢ���������\n";
    cout << "    �i�i�i�i�i�i����i�i���i�i�i�i�i�i�i�ߢi�i�i�i�i��      �i�i��   �i�i���i�i�i�i�i��      �i�i��     �i�i�i�i�i�i�i���i�i�i�i�i�i�i���i�i�ݢi�i�i�i�ݢi�i���i�i�i�i�i�i����i�i���i�i��   �i�i���i�i�ݢi�i�� �i�i���i�i�i�i�i�i�i��\n";
    cout << "    �i�i�ݢ����i�i�ߢi�i���㢤�������i�i���i�i�ݢ�����      �i�i��   �i�i���i�i�ݢ�����      �i�i��     �i�i�ݢ����i�i���i�i�ݢ����i�i���i�i����i�i����i�i���i�i�ݢ������� �i�i���i�i��   �i�i���i�i����i�i�ߢi�i���㢤�������i�i��\n";
    cout << "    �i�i��  �i�i���i�i���i�i�i�i�i�i�i���i�i�i�i�i�i�i��    ��i�i�i�i�i�i����i�i��         ��i�i�i�i�i�i�ߢi�i��  �i�i���i�i��  �i�i���i�i�� �㢤�� �i�i���i�i��     �i�i����i�i�i�i�i�i����i�i�� ��i�i�i�i���i�i�i�i�i�i�i��\n";
    cout << "    �㢤��  �㢤���㢤���㢤�������������㢤������������     �㢤���������� �㢤��          �㢤�����������㢤��  �㢤���㢤��  �㢤���㢤��     �㢤���㢤��     �㢤�� �㢤���������� �㢤��  �㢤�������㢤������������\n";
                                                                                                                                    
    sleep(1);

    while (true) {
        cout << "\n\n\n" << formatMsg("�m�t�ΰT���n", "31", true) << "�H�U�O�z�ثe�֦����d����T�G\n";
        for (int i = 0; i < 5; i++) {
            player.getPet(i)->print();
        }
        sleep(1);

        while(true) {      
          cout << "\n" << formatMsg("�m�t�ΰT���n", "31", true) << "�A�ǳƦn�[�J�s�԰��F�ܡH�]yes / no�^\n>> ";
          string ans;
          cin >> ans;
          strLower(ans);

          if (ans == "yes" || ans == "y" || ans == "�O" || ans == "1") {
              BattleSystem game;
              game.startBattle(player);
              break;
          } else if (ans == "no" || ans == "n" || ans == "�_" || ans == "0") {
                sleep(0.5);
                continue;
          } else {
              cout  << formatMsg("�m�t�ΰT���n", "31", true) << "��J�L�ġI�Э��s��J�C\n";
              sleep(0.5);
              continue;
          }
        }
    }

    system("PAUSE");
    return 0;
}

