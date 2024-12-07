#ifndef PET_H
#define PET_H

#include <string>
#include <vector>
#include <iostream>
#include "FunctionsAndConsts.h"
using namespace std;

// 前向宣告
class Skill;

class Pet {
    // 友元類
    friend class Player;
    friend class Skill;
    friend class BattleSystem;

protected:
    string name;
    string type;
    float maxHP;
    float currentHP;
    int attackPower;
    int defensePower;
    int speed;
    int level;
    int exp;

    vector<Skill*> skills;

public:
    // 建構函數
    Pet(string name, string type);
    Pet(string type, int maxHP, int attackPower, int defensePower, int speed);

    // Getter 函數
    string getName() const;
    string getType() const;
    int getHP() const;
    int getMaxHP() const;
    int getAttackPower() const;
    int getDefensePower() const;
    int getSpeed() const;

    // 行為函數
    void takeDamage(int damage);
    bool isAlive() const;
    virtual void print() const;
    bool dodgeSuccessfully() const;
    bool dominate(Pet* opponent) const;
    int attack(Pet* opponent, int skillID);
};

// PlayerPet 類宣告
class PlayerPet : public Pet {
public:
    PlayerPet(string name, string type);

    void levelAdjust();
    bool escapeSuccess();
    void win();
    void lose();
    void heal();
};

// ComputerPet 類宣告
class ComputerPet : public Pet {
public:
    ComputerPet(string type, int maxHP, int attackPower, int defensePower, int speed);

    void print() const override;
};

#endif
