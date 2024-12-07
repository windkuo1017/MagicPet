#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Pet.h" // ���] PlayerPet ���b PlayerPet.h ��
#include "FunctionsAndConsts.h"

class Pet; // �e�m�ŧi
class Skill; // �e�m�ŧi
class BattleSystem; // �e�m�ŧi

// --------------------------- ���a�� ---------------------------
class Player {
    friend class Pet;
    friend class Skill;
    friend class BattleSystem;

private:
    std::vector<PlayerPet*> pets;  // ���a�֦����d��

public:
    // �K�[�s���d���쪱�a
    void addPet(PlayerPet* newPet);

    // �ھگ�������d��
    PlayerPet* getPet(int idx);

    template <typename T>
    int findSecondMaxAttribute(T (Pet::*getAttribute)() const);

    // �d��ĤG�����̤jHP
    int findSecondMaxHP();

    // �d��ĤG���������O
    int findSecondAttackPower();

    // �d��ĤG�������m�O
    int findSecondDefensePower();

    // �d��ĤG�����t��
    int findSecondSpeed();
};

#endif // PLAYER_H
