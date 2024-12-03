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
//  srand( time(nullptr) * 703); //種子碼 do it in main func.

	int x = getRandomNum(1, 1000); //1~1000 隨機取值 
	return SPD >= x ; //若速度大於隨機值，則躲避成功 
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
        bool successful = skills[skillID]->useSkill(this); // Pass this MagicPet object，檢查是否成功攻擊（命中率、使用次數） 
        
        if(! successful)  
        	return false;
    }
    else
    {
    	cout << "沒有這招...\n";
    	return false;
	}
    	
	if(opponent->dodgeSuccessfully())
	{
		cout << opponent->name << "成功躲過攻擊\n"; 
		return false;
	}
	int damage = ATK + skills[skillID]->power - opponent->DFS; //攻擊力 + 招式強度 - 防禦 
	if(this->dominate(opponent))
	{
		cout << "屬性克制！ "; 
		damage *= 2; //傷害兩倍 
	}
	cout << "對 " << opponent->name << " 造成 " << damage << " 傷害"; 
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
	<< "\n血量 " << p.HP << " / " << p.maxHP
	<< "攻擊 " << p.ATK << "\n防禦 " << p.DFS << " , 速度 " << p.SPD; 
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
//  srand( time(nullptr) * 703); //種子碼 do it in main func.

	int x = getRandomNum(1, 1000); //1~1000 隨機取值 
	return SPD >= x ; //若速度大於隨機值，則躲避成功 
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
        bool successful = skills[skillID]->useSkill(this); // Pass this MagicPet object，檢查是否成功攻擊（命中率、使用次數） 
        
        if(! successful)  
        	return false;
    }
    else
    {
    	cout << "沒有這招...\n";
    	return false;
	}
    	
	if(opponent->dodgeSuccessfully())
	{
		cout << opponent->name << "成功躲過攻擊\n"; 
		return false;
	}
	int damage = ATK + skills[skillID]->power - opponent->DFS; //攻擊力 + 招式強度 - 防禦 
	if(this->dominate(opponent))
	{
		cout << "屬性克制！ "; 
		damage *= 2; //傷害兩倍 
	}
	cout << "對 " << opponent->name << " 造成 " << damage << " 傷害"; 
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
	<< "\n血量 " << p.HP << " / " << p.maxHP
	<< "攻擊 " << p.ATK << "\n防禦 " << p.DFS << " , 速度 " << p.SPD; 
	return out;
}
>>>>>>> e52650bad2b5a7d275424c7ec98ae5c46c037c70
