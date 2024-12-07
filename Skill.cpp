#include "Skill.h"
#include "Pet.h" // 假設你有 Pet 類的實作
#include "FunctionsAndConsts.h"
#include <sstream>

// Skill 類建構子
Skill::Skill(int _CD, string _name, int _hitRate, string _type)
    : formerCD(_CD), CD(0), name(_name), hitRate(_hitRate), type(_type) {}

    // string name;        // 技能名稱
    // string type;        // 技能類型
    // const int power = 5; // 技能傷害
    // int CD;             // 當前CD
    // int formerCD;       // 使用技能的CD
    // int hitRate;        // 命中率

// Skill 類複製建構子
Skill::Skill(const Skill& another)
    : name(another.name), CD(another.CD), hitRate(another.hitRate), formerCD(another.formerCD) {}

// 輸出流運算符重載，印技能資訊
ostream& operator<<(ostream& os, const Skill& skill) {
    os << skill.name << "\n";
    os << "技能傷害：" << skill.power << "\n";
    os << "當前CD：" << skill.CD << "\n";
    os << "命中率：" << skill.hitRate << "\n";
    return os;
}

// 減少技能CD
void Skill::reduceCD() {
    if (CD > 0) {
        CD--;
    }
}

// 使用技能後恢復CD
void Skill::skillUsed() {
    CD = formerCD;
}

// 打印技能資訊
void Skill::printSkill() {
    cout << *this;
}

// 判定技能是否命中
bool Skill::hitFail() {
    return getRandomNum(0, 100) > hitRate;  // 假設你有一個隨機數生成函數
}

// 使用技能
bool Skill::useSkill(Pet* pokemon) {
    if (CD) {
        cout << "目前無法使用此技能\n";
        return false;
    }

    skillUsed();

    if (hitFail()) {
        cout << pokemon->getName() << "發動了攻擊，但沒打中！\n";
        sleep(0.5);
        return false;
    }
    return true;
}
