#ifndef MagicPet_H
#define MagicPet_H

#include <string>
#include <vector>
using namespace std;

class Skill; // Forward declaration

class MagicPet 
{
protected:
    string name;
    string type; //屬性 
    int Exp; //經驗值 
    static const int EXP_LV = 10; //升等計算單位，非公式 
    int level;
    static const int MAX_LV = 100; //最大等級 
   
    int HP; //現在的 HP 
    int maxHP;
    int ATK; //attack
    int DFS; //defense
    int SPD; //speed



	bool dodgeSuccessfully() const; //是否成功躲避 
	bool dominate(MagicPet* opponent) const; //是否克制對手
	
public:
	MagicPet(string name, string type, int HP, int s);
	MagicPet(const MagicPet& other);
	~MagicPet();
 
	//getters
	string getName() const { return name; }
	string getType() const { return type; }
	int getHP() const { return HP; } 
	
	vector<Skill*> skills;
	
	void initializeHP() { HP = maxHP; } //出場時回覆血量至最大值
	bool attack(MagicPet* opponent, int skillID); //以第 skillID 招攻擊opponent 
	void reduceSkillsCD(); //每回合結束時，減少 CD 時間 
    virtual void getExpAfterBattle(bool win); //獲得經驗 
    virtual void levelUp(); //升等可使能力提升 
};

ostream& operator<<(ostream& out, const MagicPet& p); //輸出 MagicPet 的能力資訊 

#endif 

