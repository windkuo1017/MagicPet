<<<<<<< HEAD
#include "Skill.h"
#include "MagicPet.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


MagicPet::MagicPet(string n, string t, int H, int s)
: name(n), type(t), maxHP(H), HP(H), Exp(0), level(1), ATK(10), DFS(5), SPD(s) {}


MagicPet::MagicPet(const MagicPet& other) 
:name(other.name), type(other.type), maxHP(other.maxHP), HP(other.HP),
    Exp(other.Exp), level(other.level), ATK(other.ATK), DFS(other.DFS), SPD(other.SPD)
{
    for(Skill* skill : other.skills)
		skills.push_back(new Skill(*skill)); // Deep copy
}

MagicPet::~MagicPet()
{
	for(Skill* skill : skills)
		delete skill;
}

bool MagicPet::dodgeSuccessfully() const 
{
//  srand( time(nullptr) * 703); //�ؤl�X do it in main func.

	int x = getRandomNum(1, 1000); //1~1000 �H������ 
	return SPD >= x ; //�Y�t�פj���H���ȡA�h���צ��\ 
}

bool MagicPet::dominate(MagicPet* opponent) const 
{
    if ((type == "gold" && opponent->type == "wood") ||
        (type == "wood" && opponent->type == "mud") ||
        (type == "mud" && opponent->type == "water") ||
        (type == "water" && opponent->type == "fire") ||
        (type == "fire" && opponent->type == "gold")) 
	{
        return true;
    }
	else
	{
        return false;
    }
}

bool MagicPet::attack(MagicPet* opponent, int skillID)
{
    if (skillID < skills.size()) 
	{
        bool successful = skills[skillID]->useSkill(this); // Pass this MagicPet object�A�ˬd�O�_���\�����]�R���v�B�ϥΦ��ơ^ 
        
        if(! successful)  
        	return false;
    }
    else
    {
    	cout << "�S���o��...\n";
    	return false;
	}
    	
	if(opponent->dodgeSuccessfully())
	{
		cout << opponent->name << "���\���L����\n"; 
		return false;
	}
	int damage = ATK + skills[skillID]->power - opponent->DFS; //�����O + �ۦ��j�� - ���m 
	if(this->dominate(opponent))
	{
		cout << "�ݩʧJ��I "; 
		damage *= 2; //�ˮ`�⭿ 
	}
	cout << "�� " << opponent->name << " �y�� " << damage << " �ˮ`"; 
	opponent->HP -= damage;
	return true;
}

void MagicPet::reduceSkillsCD()
{
	for(Skill* skill : skills)
	{
		skill->reduceCD();
	}
};

void MagicPet::levelUp()
{ 
	maxHP += 2;
	ATK += 2;
	DFS += 2;
}


void MagicPet::getExpAfterBattle(bool win)
{
	if(win) 
	{
        Exp += 30;
        cout << name << " gained EXP for winning!\n";   
	}
	while(this->Exp >= pow(level, 2) * EXP_LV)
		this->levelUp();
}



ostream& operator<<(ostream& out, const MagicPet& p)
{
	out << p.name << " (" << p.type << ")  lv " << p.level
	<< "\n��q " << p.HP << " / " << p.maxHP
	<< "���� " << p.ATK << "\n���m " << p.DFS << " , �t�� " << p.SPD; 
	return out;
}
=======
#include "Skill.h"
#include "MagicPet.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


MagicPet::MagicPet(string n, string t, int H, int s)
: name(n), type(t), maxHP(H), HP(H), Exp(0), level(1), ATK(10), DFS(5), SPD(s) {}


MagicPet::MagicPet(const MagicPet& other) 
:name(other.name), type(other.type), maxHP(other.maxHP), HP(other.HP),
    Exp(other.Exp), level(other.level), ATK(other.ATK), DFS(other.DFS), SPD(other.SPD)
{
    for(Skill* skill : other.skills)
		skills.push_back(new Skill(*skill)); // Deep copy
}

MagicPet::~MagicPet()
{
	for(Skill* skill : skills)
		delete skill;
}

bool MagicPet::dodgeSuccessfully() const 
{
//  srand( time(nullptr) * 703); //�ؤl�X do it in main func.

	int x = getRandomNum(1, 1000); //1~1000 �H������ 
	return SPD >= x ; //�Y�t�פj���H���ȡA�h���צ��\ 
}

bool MagicPet::dominate(MagicPet* opponent) const 
{
    if ((type == "gold" && opponent->type == "wood") ||
        (type == "wood" && opponent->type == "mud") ||
        (type == "mud" && opponent->type == "water") ||
        (type == "water" && opponent->type == "fire") ||
        (type == "fire" && opponent->type == "gold")) 
	{
        return true;
    }
	else
	{
        return false;
    }
}

bool MagicPet::attack(MagicPet* opponent, int skillID)
{
    if (skillID < skills.size()) 
	{
        bool successful = skills[skillID]->useSkill(this); // Pass this MagicPet object�A�ˬd�O�_���\�����]�R���v�B�ϥΦ��ơ^ 
        
        if(! successful)  
        	return false;
    }
    else
    {
    	cout << "�S���o��...\n";
    	return false;
	}
    	
	if(opponent->dodgeSuccessfully())
	{
		cout << opponent->name << "���\���L����\n"; 
		return false;
	}
	int damage = ATK + skills[skillID]->power - opponent->DFS; //�����O + �ۦ��j�� - ���m 
	if(this->dominate(opponent))
	{
		cout << "�ݩʧJ��I "; 
		damage *= 2; //�ˮ`�⭿ 
	}
	cout << "�� " << opponent->name << " �y�� " << damage << " �ˮ`"; 
	opponent->HP -= damage;
	return true;
}

void MagicPet::reduceSkillsCD()
{
	for(Skill* skill : skills)
	{
		skill->reduceCD();
	}
};

void MagicPet::levelUp()
{ 
	maxHP += 2;
	ATK += 2;
	DFS += 2;
}


void MagicPet::getExpAfterBattle(bool win, int xp)
{
	if(win) 
	{
        Exp += xp;
        cout << name << " gained EXP for winning!\n";   
	}
	while(this->Exp >= pow(level, 2) * EXP_LV)
		this->levelUp();
}



ostream& operator<<(ostream& out, const MagicPet& p)
{
	out << p.name << " (" << p.type << ")  lv " << p.level
	<< "\n��q " << p.HP << " / " << p.maxHP
	<< "���� " << p.ATK << "\n���m " << p.DFS << " , �t�� " << p.SPD; 
	return out;
}
>>>>>>> e52650bad2b5a7d275424c7ec98ae5c46c037c70
