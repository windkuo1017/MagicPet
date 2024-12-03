#include <iostream>
#include <string>
#include "MagicPet.h"
using namespace std;

int getRandomNum(int min, int max);


class Skill
{
friend class MagicPet;
protected:
  string name;
  const int power = 50;
  int CD;//當前CD
  int formerCD;//使用技能的CD
  int hitRate;//命中率
  int timesUsed = 0;//已使用次數

public:
  Skill(int _CD, string _name, int _hitRate);
  Skill(const Skill& another);
  virtual ~Skill() = default;
  void skillUsed(); //使用後技能CD恢復
  void reduceCD();
  void printSkill(); //展示技能名稱
  virtual bool useSkill(MagicPet* pokemon); //使用技能
  bool hitFail(); //判定技能是否命中
  friend ostream& operator<<(ostream& os, const Skill& skill);
};


class SpecialSkill : public Skill
{
friend class MagicPet; 
protected:
  string type; //招式屬性
  int timesLimit; //使用次數限制

public:
  SpecialSkill(int _CD, string _name, int _hitRate, string _type, int _timesLimit);
  
  SpecialSkill(const SpecialSkill& another); // copy constructor
  ~SpecialSkill() override;
  bool useSkill(MagicPet* pokemon) override;
  bool usedTooMuch();
  friend ostream& operator<<(ostream& os, const SpecialSkill& skill);
 };
