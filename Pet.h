#ifndef PET_H
#define PET_H

#include <string>
#include <vector>
#include <iostream>
#include "FunctionsAndConsts.h"
using namespace std;

// �e�V�ŧi
class Skill;

class Pet {
    // �ͤ���
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
    // �غc���
    Pet(string name, string type);
    Pet(string type, int maxHP, int attackPower, int defensePower, int speed);

    // Getter ���
    string getName() const;
    string getType() const;
    int getHP() const;
    int getMaxHP() const;
    int getAttackPower() const;
    int getDefensePower() const;
    int getSpeed() const;

    // �欰���
    void takeDamage(int damage);
    bool isAlive() const;
    virtual void print() const;
    bool dodgeSuccessfully() const;
    bool dominate(Pet* opponent) const;
    int attack(Pet* opponent, int skillID);
};

// PlayerPet ���ŧi
class PlayerPet : public Pet {
public:
    PlayerPet(string name, string type);

    void levelAdjust();
    bool escapeSuccess();
    void win();
    void lose();
    void heal();
};

// ComputerPet ���ŧi
class ComputerPet : public Pet {
public:
    ComputerPet(string type, int maxHP, int attackPower, int defensePower, int speed);

    void print() const override;
};

#endif
