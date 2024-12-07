#include "Pet.h"
#include "Skill.h" // 假設有 Skill 類的實現
#include "FunctionsAndConsts.h"
#include <algorithm> // for max
#include <cstdlib>   // for rand
#include <ctime>     // for time
#include <sstream>

using namespace std;

// 1206修改


// Pet 建構函數(玩家的)
Pet::Pet(string name, string type)
    : name(name), type(type), maxHP(maxHPs[0]), currentHP(maxHPs[0]), attackPower(attackPowers[0]), defensePower(defensePowers[0]), speed(speeds[0]), level(1), exp(0) {
        Skill *skill1 = new Skill(0, "一般攻擊", 90, type);
        skills.push_back(skill1);

        Skill *skill2 = new Skill(3, "特殊攻擊", 50, type);
        skills.push_back(skill2);

    }

// Pet 建構函數(電腦的)
Pet::Pet(string type, int maxHP, int attackPower, int defensePower, int speed)
    : name("系統"), type(type), maxHP(maxHPs[0]), currentHP(maxHPs[0]), attackPower(attackPowers[0]), defensePower(defensePowers[0]), speed(speeds[0]) {
        Skill *skill1 = new Skill(0, "一般攻擊", 50, type);
        skills.push_back(skill1);

        Skill *skill2 = new Skill(3, "特殊攻擊", 40, type);
        skills.push_back(skill2);
    }

// Getter 函數
string Pet::getName() const { return name; }
string Pet::getType() const { return type; }
int Pet::getHP() const { return currentHP; }
int Pet::getMaxHP() const { return maxHP; }
int Pet::getAttackPower() const { return attackPower; }
int Pet::getDefensePower() const { return defensePower; }
int Pet::getSpeed() const { return speed; }

// 行為函數
void Pet::takeDamage(int damage) {
    currentHP -= damage;
    if (currentHP < 0) currentHP = 0;
}

bool Pet::isAlive() const { return currentHP > 0; }

void Pet::print() const {
    cout << "寵物名稱：" << name << "\t";
    cout << "屬性：" << type << "\t";
    cout << "血量：" << currentHP << "／" << maxHP << "\t";
    cout << "攻擊力：" << attackPower << "\t";
    cout << "防禦力：" << defensePower << "\t";
    cout << "速度：" << speed << "\t";
    cout << "經驗值：" << exp << "\t";
    cout << "等級：" << level << "\n";
}

bool Pet::dodgeSuccessfully() const {
    // 生成 1 到 100 的隨機數
    int x = getRandomNum(1, 100);
    // 若速度大於隨機值，則躲避成功
    bool result = getSpeed() > x;  // 使用 'x' 作為隨機數

    // 顯示是否躲避成功
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
    cout << "DEBUG 檢查點1" << endl;
    if (!skills[skillID - 1]->useSkill(this))
        return 0;

    cout << "DEBUG 檢查點2" << endl;
    // cout << "DEBUG 速度((((((((((((((())))))))))" << opponent->speed << endl;
    if (opponent->dodgeSuccessfully()) {
        cout << opponent->name << "成功躲過攻擊\n"; 
        return 0;
    }

    cout << "DEBUG 檢查點3" << endl;
    // cout << attackPower << ", " << skills[skillID]->power << ", " << opponent->defensePower << endl;
    int damage = attackPower 
                // + skills[skillID]->power 
                - opponent->defensePower;

    cout << "DEBUG 檢查點4" << endl;
    if (skillID == 2) { // 大招
        damage *= dominate(opponent) ? 2 : 1.5;
        if (dominate(opponent))
            cout << "屬性克制！ ";
    }

    cout << "DEBUG 檢查點5" << endl;

    damage = max(damage, 0);
    cout << name << "對 " << opponent->name << " 造成了" << damage << "點傷害" << endl; 
    opponent->currentHP -= damage;
    sleep(0.5);

    return 0;
}

// PlayerPet 類實現
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

// ComputerPet 類實現
ComputerPet::ComputerPet(string type, int maxHP, int attackPower, int defensePower, int speed)
    : Pet(type, maxHP, attackPower, defensePower, speed) {}

void ComputerPet::print() const{
    cout << "寵物名稱：" << name << "\t";
    cout << "屬性：" << type << "\t";
    cout << "血量：" << currentHP << "／" << maxHP << "\t";
    cout << "攻擊力：" << attackPower << "\t";
    cout << "防禦力：" << defensePower << "\t";
    cout << "速度：" << speed << "\n";
}
