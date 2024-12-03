#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int getRandomNum(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

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
  Skill(int _CD, string _name, int _hitRate):formerCD(_CD),CD(0),name(_name),hitRate(_hitRate){}
  Skill(const Skill& another):name(another.name),CD(another.CD),timesUsed(another.timesUsed),hitRate(another.hitRate),formerCD(another.formerCD){} //copy constructor
  virtual ~Skill() = default;
  void skillUsed(){CD = formerCD;} //使用後技能CD恢復
  void reduceCD(){if(CD > 0) CD--;}
  void printSkill(){cout << *this;} //展示技能名稱
  virtual bool useSkill(MagicPet* pokemon); //使用技能
  bool hitFail(){return getRandomNum(1,100) > hitRate;} //判定技能是否命中
  friend ostream& operator<<(ostream& os, const Skill& skill)
  {
      os << skill.name << "\n";
      os << "招式威力：" << skill.power << "\n";
      os << "當前CD回合：" << skill.CD << "\n";
      os << "技能命中率：" << skill.hitRate << "%\n";
      os << "已使用次數：" << skill.timesUsed << "\n";
      return os;
  }

};

bool Skill::useSkill(MagicPet* pokemon)
{
    if(CD){
    cout << "當前無法使用此技能\n";
      return false;
    }
    skillUsed();
    timesUsed ++;
    if(hitFail())
    {
      cout << "哈哈，" << pokemon->getName() << "沒打中唷！";
      return false;
    }
    return true;
}
class SpecialSkill : public Skill
{
friend class MagicPet; 
  protected:
  string type; //招式屬性
  int timesLimit; //使用次數限制

  public:
  SpecialSkill(int _CD, string _name, int _hitRate, string _type, int _timesLimit)
  :Skill(_CD, _name, _hitRate),type(_type),timesLimit(_timesLimit){}
  SpecialSkill(const SpecialSkill& another)
  :Skill(another),type(another.type),timesLimit(another.timesLimit){} // copy constructor
  ~SpecialSkill() override;
  bool useSkill(MagicPet* pokemon) override;
  bool usedTooMuch();
  friend ostream& operator<<(ostream& os, const SpecialSkill& skill)
  {
      os << static_cast<const Skill&>(skill); 
      os << "招式屬性：" << skill.type << "\n";
      os << "使用次數限制：" << skill.timesLimit << "\n";
      return os;
  }
};



bool SpecialSkill::usedTooMuch()
{
  if(timesUsed >= timesLimit)
  {
    cout << "無法再使用此技能\n";
    return true;
  }
  return false;
}

bool SpecialSkill::useSkill(MagicPet* pokemon)
{
    if (usedTooMuch()) return false;
    return Skill::useSkill(pokemon); 
}