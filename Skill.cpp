#include "Skill.h"
#include "Pet.h" // ���]�A�� Pet ������@
#include "FunctionsAndConsts.h"
#include <sstream>

// Skill ���غc�l
Skill::Skill(int _CD, string _name, int _hitRate, string _type)
    : formerCD(_CD), CD(0), name(_name), hitRate(_hitRate), type(_type) {}

    // string name;        // �ޯ�W��
    // string type;        // �ޯ�����
    // const int power = 5; // �ޯ�ˮ`
    // int CD;             // ��eCD
    // int formerCD;       // �ϥΧޯ઺CD
    // int hitRate;        // �R���v

// Skill ���ƻs�غc�l
Skill::Skill(const Skill& another)
    : name(another.name), CD(another.CD), hitRate(another.hitRate), formerCD(another.formerCD) {}

// ��X�y�B��ŭ����A�L�ޯ��T
ostream& operator<<(ostream& os, const Skill& skill) {
    os << skill.name << "\n";
    os << "�ޯ�ˮ`�G" << skill.power << "\n";
    os << "��eCD�G" << skill.CD << "\n";
    os << "�R���v�G" << skill.hitRate << "\n";
    return os;
}

// ��֧ޯ�CD
void Skill::reduceCD(bool isDefault) {
    if (isDefault==false){
        if (CD > 0) CD--;
    }else{
        CD = 0;
    }
    
    
}

// �ϥΧޯ���_CD
void Skill::skillUsed() {
    CD = formerCD;
}

// ���L�ޯ��T
void Skill::printSkill() {
    cout << *this;
}

// �P�w�ޯ�O�_�R��
bool Skill::hitFail() {
    return getRandomNum(0, 100) > hitRate;  // ���]�A���@���H���ƥͦ����
}

// �ϥΧޯ�
int Skill::useSkill(Pet* pokemon) {
    if (CD) {
        cout << formatMsg("�m�t�ΰT���n", "31", true) << "�ثe�L�k�ϥΦ��ޯ�\n";
        return -2;
    }

    skillUsed();

    if (hitFail()) {
        cout << formatMsg("�m�t�ΰT���n", "31", true)  << pokemon->getName() << "�o�ʤF�����A���S�����I\n";
        sleep(0.5);
        return 0;
    }
    return 1;
}
