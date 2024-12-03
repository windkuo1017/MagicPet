#include <iostream>
#include <string>
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
  Skill(int _CD, string _name, int _hitRate):formerCD(_CD),CD(0),name(_name),hitRate(_hitRate){}
  Skill(const Skill& another):name(another.name),CD(another.CD),timesUsed(another.timesUsed),hitRate(another.hitRate),formerCD(another.formerCD){} //copy constructor
  virtual ~Skill() = default;
  void skillUsed(){CD = formerCD;} //使用後技能CD恢復
  void reduceCD(){if(CD > 0) CD--;}
  void printSkill(){cout << *this;} //展示技能名稱
  virtual bool useSkill(MagicPet* pokemon); //使用技能
  bool hitFail(){return getRandomNum(1,100) > hitRate;} //判定技能是否命中
  friend ostream& operator<<(ostream& os, const Skill& skill)

};


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
