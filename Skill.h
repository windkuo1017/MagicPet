#ifndef SKILL_H
#define SKILL_H

#include <string>
#include <iostream>
using namespace std;

class Pet; // 前置宣告

// --------------------------- 技能類 ---------------------------
class Skill {
    friend class Player;
    friend class Pet;
    friend class BattleSystem;

protected:
    string name;        // 技能名稱
    string type;        // 技能類型
    const int power = 5; // 技能傷害
    int CD;             // 當前CD
    int formerCD;       // 使用技能的CD
    int hitRate;        // 命中率

public:
    Skill(int _CD, string _name, int _hitRate, string _type);  // 建構子
    Skill(const Skill& another);  // 複製建構子
    ~Skill() = default;   // 虛擬析構子

    void skillUsed();   // 使用後技能CD恢復
    void reduceCD(bool isDefault = 0);    // 減少CD
    void printSkill();  // 展示技能名稱
    int useSkill(Pet* pokemon); // 使用技能
    bool hitFail();     // 判定技能是否命中

    // 重載輸出流運算符
    friend ostream& operator<<(ostream& os, const Skill& skill);
};

#endif // SKILL_H
