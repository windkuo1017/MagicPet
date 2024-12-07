#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Pet.h" // 假設 PlayerPet 類在 PlayerPet.h 中
#include "FunctionsAndConsts.h"

class Pet; // 前置宣告
class Skill; // 前置宣告
class BattleSystem; // 前置宣告

// --------------------------- 玩家類 ---------------------------
class Player {
    friend class Pet;
    friend class Skill;
    friend class BattleSystem;

private:
    std::vector<PlayerPet*> pets;  // 玩家擁有的寵物

public:
    // 添加新的寵物到玩家
    void addPet(PlayerPet* newPet);

    // 根據索引獲取寵物
    PlayerPet* getPet(int idx);

    template <typename T>
    int findSecondMaxAttribute(T (Pet::*getAttribute)() const);

    // 查找第二高的最大HP
    int findSecondMaxHP();

    // 查找第二高的攻擊力
    int findSecondAttackPower();

    // 查找第二高的防禦力
    int findSecondDefensePower();

    // 查找第二高的速度
    int findSecondSpeed();
};

#endif // PLAYER_H
