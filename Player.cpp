#include "Player.h"
#include "Pet.h" // ���] PlayerPet ������@�b PlayerPet.h ��
#include "FunctionsAndConsts.h"
#include <sstream>

// �K�[�s���d���쪱�a
void Player::addPet(PlayerPet* newPet) {
    pets.push_back(newPet);
}

// �ھگ�������d��
PlayerPet* Player::getPet(int idx) {
    return pets[idx];
}

template <typename T>
int Player::findSecondMaxAttribute(T (Pet::*getAttribute)() const) {
    int firstMax = 0, secondMax = 0;
    for (int i = 0; i < 5; i++) {
        int attributeValue = (pets[i]->*getAttribute)();
        if (attributeValue > firstMax) {
            secondMax = firstMax;
            firstMax = attributeValue;
        } else if (attributeValue > secondMax) {
            secondMax = attributeValue;
        }
    }
    return secondMax;
}


int Player::findSecondMaxHP() {
    return findSecondMaxAttribute(&Pet::getMaxHP);
}


int Player::findSecondAttackPower() {
    return findSecondMaxAttribute(&Pet::getAttackPower);
}

int Player::findSecondDefensePower() {
    return findSecondMaxAttribute(&Pet::getDefensePower);
}

int Player::findSecondSpeed() {
    return findSecondMaxAttribute(&Pet::getSpeed);
}

// // �d��ĤG�����̤jHP
// int Player::findSecondMaxHP() {
//     int firstMaxHP = 0, secondMaxHP = 0;
//     for (int i = 0; i < 5; i++) {
//         // Keep track of the largest and second largest number
//         if (pets[i]->getMaxHP() > firstMaxHP) {
//             secondMaxHP = firstMaxHP;
//             firstMaxHP = pets[i]->getMaxHP();
//         } else if (pets[i]->getMaxHP() > secondMaxHP) {
//             secondMaxHP = pets[i]->getMaxHP();
//         }
//     }
//     return secondMaxHP;
// }

// // �d��ĤG���������O
// int Player::findSecondAttackPower() {
//     int firstAttackPower = 0, secondAttackPower = 0;
//     for (int i = 0; i < 5; i++) {
//         // Keep track of the largest and second largest number
//         if (pets[i]->getAttackPower() > firstAttackPower) {
//             secondAttackPower = firstAttackPower;
//             firstAttackPower = pets[i]->getAttackPower();
//         } else if (pets[i]->getAttackPower() > secondAttackPower) {
//             secondAttackPower = pets[i]->getAttackPower();
//         }
//     }
//     return secondAttackPower;
// }

// // �d��ĤG�������m�O
// int Player::findSecondDefensePower() {
//     int firstDefensePower = 0, secondDefensePower = 0;
//     for (int i = 0; i < 5; i++) {
//         // Keep track of the largest and second largest number
//         if (pets[i]->getDefensePower() > firstDefensePower) {
//             secondDefensePower = firstDefensePower;
//             firstDefensePower = pets[i]->getDefensePower();
//         } else if (pets[i]->getDefensePower() > secondDefensePower) {
//             secondDefensePower = pets[i]->getDefensePower();
//         }
//     }
//     return secondDefensePower;
// }

// // �d��ĤG�����t��
// int Player::findSecondSpeed() {
//     int firstSpeed = 0, secondSpeed = 0;
//     for (int i = 0; i < 5; i++) {
//         // Keep track of the largest and second largest number
//         if (pets[i]->getSpeed() > firstSpeed) {
//             secondSpeed = firstSpeed;
//             firstSpeed = pets[i]->getSpeed();
//         } else if (pets[i]->getSpeed() > secondSpeed) {
//             secondSpeed = pets[i]->getSpeed();
//         }
//     }
//     return secondSpeed;
//  }
