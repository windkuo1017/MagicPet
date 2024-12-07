#include "Player.h"
#include "Pet.h" // 假設 PlayerPet 類的實作在 PlayerPet.h 中
#include "FunctionsAndConsts.h"
#include <sstream>

// 添加新的寵物到玩家
void Player::addPet(PlayerPet* newPet) {
    pets.push_back(newPet);
}

// 根據索引獲取寵物
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

// // 查找第二高的最大HP
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

// // 查找第二高的攻擊力
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

// // 查找第二高的防禦力
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

// // 查找第二高的速度
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
