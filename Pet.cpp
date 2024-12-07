#include "Pet.h"
#include "Skill.h" // ���]�� Skill ������{
#include "FunctionsAndConsts.h"
#include <algorithm> // for max
#include <cstdlib>   // for rand
#include <ctime>     // for time
#include <sstream>

using namespace std;

// 1206�ק�


// Pet �غc���(���a��)
Pet::Pet(string name, string type)
    : name(name), type(type), maxHP(maxHPs[0]), currentHP(maxHPs[0]), attackPower(attackPowers[0]), defensePower(defensePowers[0]), speed(speeds[0]), level(1), exp(0) {
        Skill *skill1 = new Skill(0, "�@�����", 90, type);
        skills.push_back(skill1);

        Skill *skill2 = new Skill(3, "�S�����", 50, type);
        skills.push_back(skill2);

    }

// Pet �غc���(�q����)
Pet::Pet(string type, int maxHP, int attackPower, int defensePower, int speed)
    : name("�t��"), type(type), maxHP(maxHPs[0]), currentHP(maxHPs[0]), attackPower(attackPowers[0]), defensePower(defensePowers[0]), speed(speeds[0]) {
        Skill *skill1 = new Skill(0, "�@�����", 50, type);
        skills.push_back(skill1);

        Skill *skill2 = new Skill(3, "�S�����", 40, type);
        skills.push_back(skill2);
    }

// Getter ���
string Pet::getName() const { return name; }
string Pet::getType() const { return type; }
int Pet::getHP() const { return currentHP; }
int Pet::getMaxHP() const { return maxHP; }
int Pet::getAttackPower() const { return attackPower; }
int Pet::getDefensePower() const { return defensePower; }
int Pet::getSpeed() const { return speed; }

// �欰���
void Pet::takeDamage(int damage) {
    currentHP -= damage;
    if (currentHP < 0) currentHP = 0;
}

bool Pet::isAlive() const { return currentHP > 0; }

void Pet::print() const {
    cout << "�d���W�١G" << name << "\t";
    cout << "�ݩʡG" << type << "\t";
    cout << "��q�G" << currentHP << "��" << maxHP << "\t";
    cout << "�����O�G" << attackPower << "\t";
    cout << "���m�O�G" << defensePower << "\t";
    cout << "�t�סG" << speed << "\t";
    cout << "�g��ȡG" << exp << "\t";
    cout << "���šG" << level << "\n";
}

bool Pet::dodgeSuccessfully() const {
    // �ͦ� 1 �� 100 ���H����
    int x = getRandomNum(1, 100);
    // �Y�t�פj���H���ȡA�h���צ��\
    bool result = getSpeed() > x;  // �ϥ� 'x' �@���H����

    // ��ܬO�_���צ��\
    cout << "Dodge successful: " << result << endl;

    return result; 
}

bool Pet::dominate(Pet* opponent) const {
    return (type == "gold" && opponent->type == "wood") ||
           (type == "wood" && opponent->type == "mud") ||
           (type == "mud" && opponent->type == "water") ||
           (type == "water" && opponent->type == "fire") ||
           (type == "fire" && opponent->type == "gold");
}

int Pet::attack(Pet* opponent, int skillID) {
    cout << "DEBUG �ˬd�I1" << endl;
    if (!skills[skillID - 1]->useSkill(this))
        return 0;

    cout << "DEBUG �ˬd�I2" << endl;
    // cout << "DEBUG �t��((((((((((((((())))))))))" << opponent->speed << endl;
    if (opponent->dodgeSuccessfully()) {
        cout << opponent->name << "���\���L����\n"; 
        return 0;
    }

    cout << "DEBUG �ˬd�I3" << endl;
    // cout << attackPower << ", " << skills[skillID]->power << ", " << opponent->defensePower << endl;
    int damage = attackPower 
                // + skills[skillID]->power 
                - opponent->defensePower;

    cout << "DEBUG �ˬd�I4" << endl;
    if (skillID == 2) { // �j��
        damage *= dominate(opponent) ? 2 : 1.5;
        if (dominate(opponent))
            cout << "�ݩʧJ��I ";
    }

    cout << "DEBUG �ˬd�I5" << endl;

    damage = max(damage, 0);
    cout << name << "�� " << opponent->name << " �y���F" << damage << "�I�ˮ`" << endl; 
    opponent->currentHP -= damage;
    sleep(0.5);

    return 0;
}

// PlayerPet ����{
PlayerPet::PlayerPet(string name, string type) 
    : Pet(name, type) {}

void PlayerPet::levelAdjust() {
    level = 1;
    for (int i = 5; i >= 1; --i) {
        if (exp >= exps[i]) {
            level = i + 1;
            break;
        }
    }

    maxHP = maxHPs[level - 1];
    attackPower = attackPowers[level - 1];
    defensePower = defensePowers[level - 1];
    speed = speeds[level - 1];
    currentHP = maxHP;
}

bool PlayerPet::escapeSuccess() {
    double randomValue = static_cast<double>(rand()) / RAND_MAX;
    return ((randomValue < escapeRate[level - 1]) ? true : false);
}

void PlayerPet::win() {
    exp += 50;
    levelAdjust();
}

void PlayerPet::lose() {
    exp -= 50;
    levelAdjust();
}

void PlayerPet::heal() {
    currentHP = maxHP;
}

// ComputerPet ����{
ComputerPet::ComputerPet(string type, int maxHP, int attackPower, int defensePower, int speed)
    : Pet(type, maxHP, attackPower, defensePower, speed) {}

void ComputerPet::print() const{
    cout << "�d���W�١G" << name << "\t";
    cout << "�ݩʡG" << type << "\t";
    cout << "��q�G" << currentHP << "��" << maxHP << "\t";
    cout << "�����O�G" << attackPower << "\t";
    cout << "���m�O�G" << defensePower << "\t";
    cout << "�t�סG" << speed << "\n";
}
