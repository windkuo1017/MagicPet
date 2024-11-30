#include <iostream>
#include <vector> 
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

const int SKILL_CNT = 3; 

int getRandomNum(int min, int max)
{
	return rand() % max + min;
}

class MagicPet
{
friend ostream& operator<<(ostream& out, const MagicPet& p);

protected:
    string name;
    string type; //屬性 
    int Exp;
    static const int EXP_LV = 10;
    int level;
    static const int MAX_LV = 100;
   
    int HP;
    int maxHP;
    int ATK; //attack
    int DFS; //defense
    int SPD; //speed
    
    vector<Skill*> skills;
   
public:
	MagicPet(string name, string type, int HP, int s);
	MagicPet(const MagicPet& other);
	~MagicPet();
	
    void initializeHP() { HP = maxHP; } //出場時回覆血量至最大值 
    string getName() const { return name; }
	string getType() const { return type; }
	int getHP() const { return HP; } 
	
    bool dodgeSuccessfully() const; //是否成功躲避 
    
    
	bool dominate(MagicPet* opponent) const; //0:被克制 1:克制
	
	void attack(MagicPet* opponent, int skillID); //以第 skillID 招攻擊opponent 

	void reduceSkillsCD(); //每回合結束時，減少 CD 時間 

    virtual void getExpAfterBattle(bool win, int exp); //獲得經驗 
    
    virtual void levelUp() { maxHP += 2; ATK += 2; DFS += 2;} //升等可使能力提升 
};

ostream& operator<<(ostream& out, const MagicPet& p); //輸出 MagicPet 的能力資訊 

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
//   srand( time(nullptr) * 703); //種子碼 do it in main func.
//	srand(123); //debug

	int x = getRandomNum(1, 1000); //1~1000 隨機取值 
	
	return SPD >= x ; //若速度大於隨機值，則躲避成功 
}


bool MagicPet::dominate(MagicPet* opponent)  const //0:被克制 1:克制
{
   if( (type == "gold" && opponent->type == "wood") ||
	(type == "wood" && opponent->type == "mud") ||
	(type == "mud" && opponent->type == "water") ||
	(type == "water" && opponent->type == "fire") ||
	(type == "fire" && opponent->type == "gold") )
		return true;
	
	else
		return false;
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
		
	int damage = ATK + skills[skillID]->power - opponent->DFS;　//攻擊力+招式強度-防禦 
	
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


class goldPet: public MagicPet
{
public:
    goldPet(string name, int HP, int speed) : MagicPet(name, "gold", HP, speed) {}
    
	void bonusAfterBattle(bool win) override 
	{
		MagicPet::getExpAfterBattle(win, 100); //gold gets more EXP
	}
};


class waterPet: public MagicPet
{
public:
    waterPet(string name, int HP, int speed) : MagicPet(name, "water", HP, speed) {}
    
    void levelUp()
    {
    	MagicPet::levelUp();
    	this->SPD += 3;
	}
    
	void bonusAfterBattle(bool win) override 
	{
		MagicPet::getExpAfterBattle(win, 30);
	}
};


class firePet: public MagicPet
{
public:
    firePet(string name, int HP, int speed) : MagicPet(name, "fire", HP, speed) {}
    
    void levelUp()
    {
    	MagicPet::levelUp();
    	this->ATK += 3;
	}
    
	void bonusAfterBattle(bool win) override 
	{
		MagicPet::getExpAfterBattle(win, 30);
	}
};


class woodPet: public MagicPet
{
public:
    woodPet(string name, int HP, int speed) : MagicPet(name, "wood", HP, speed) {}
    
    void levelUp()
    {
    	MagicPet::levelUp();
    	this->maxHP += 3;
	}
    
	void bonusAfterBattle(bool win) override 
	{
		MagicPet::getExpAfterBattle(win, 30);
	}
};

class mudPet: public MagicPet
{
public:
    mudPet(string name, int HP, int speed) : MagicPet(name, "mud", HP, speed) {}
    
    void levelUp()
    {
    	MagicPet::levelUp();
    	this->DFS += 3;
	}
    
	void bonusAfterBattle(bool win) override 
	{
		MagicPet::getExpAfterBattle(win, 30);
	}
};

ostream& operator<<(ostream& out, const MagicPet& p)
{
	out << p.name << " (" << p.type << ")  lv " << p.level
	<< "\n血量 " << p.HP << " / " << p.maxHP
	<< "攻擊 " << p.ATK << "\n防禦 " << p.DFS << " , 速度 " << p.SPD; 
	
	return out;
}
