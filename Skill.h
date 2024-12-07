#ifndef SKILL_H
#define SKILL_H

#include <string>
#include <iostream>
using namespace std;

class Pet; // �e�m�ŧi

// --------------------------- �ޯ��� ---------------------------
class Skill {
    friend class Player;
    friend class Pet;
    friend class BattleSystem;

protected:
    string name;        // �ޯ�W��
    string type;        // �ޯ�����
    const int power = 5; // �ޯ�ˮ`
    int CD;             // ��eCD
    int formerCD;       // �ϥΧޯ઺CD
    int hitRate;        // �R���v

public:
    Skill(int _CD, string _name, int _hitRate, string _type);  // �غc�l
    Skill(const Skill& another);  // �ƻs�غc�l
    ~Skill() = default;   // �����R�c�l

    void skillUsed();   // �ϥΫ�ޯ�CD��_
    void reduceCD(bool isDefault = 0);    // ���CD
    void printSkill();  // �i�ܧޯ�W��
    int useSkill(Pet* pokemon); // �ϥΧޯ�
    bool hitFail();     // �P�w�ޯ�O�_�R��

    // ������X�y�B���
    friend ostream& operator<<(ostream& os, const Skill& skill);
};

#endif // SKILL_H
