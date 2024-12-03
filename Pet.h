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
    string type; //�ݩ� 
    int Exp; //�g��� 
    static const int EXP_LV = 10; //�ɵ��p����A�D���� 
    int level;
    static const int MAX_LV = 100; //�̤j���� 
   
    int HP; //�{�b�� HP 
    int maxHP;
    int ATK; //attack
    int DFS; //defense
    int SPD; //speed



	bool dodgeSuccessfully() const; //�O�_���\���� 
	bool dominate(MagicPet* opponent) const; //�O�_�J����
	
public:
	MagicPet(string name, string type, int HP, int s);
	MagicPet(const MagicPet& other);
	~MagicPet();
 
	//getters
	string getName() const { return name; }
	string getType() const { return type; }
	int getHP() const { return HP; } 
	
	vector<Skill*> skills;
	
	void initializeHP() { HP = maxHP; } //�X���ɦ^�Ц�q�̤ܳj��
	bool attack(MagicPet* opponent, int skillID); //�H�� skillID �ۧ���opponent 
	void reduceSkillsCD(); //�C�^�X�����ɡA��� CD �ɶ� 
    virtual void getExpAfterBattle(bool win); //��o�g�� 
    virtual void levelUp(); //�ɵ��i�ϯ�O���� 
};

ostream& operator<<(ostream& out, const MagicPet& p); //��X MagicPet ����O��T 

#endif 

