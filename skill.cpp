#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int getRandomNum(int min, int max)
{
	return rand() % max + min;
}

class Skill
{
friend class MagicPet;
protected:
  string name;
  const int power = 50;
  int CD;
  int formerCD;
  int hitRate;
  int timesUsed = 0;

public:
  virtual Skill(int _CD, string _name, int _hitRate):formerCD(_CD),CD(0),name(_name),hitRate(_hitRate); 
  Skill(const Skill& another); //copy constructor
  void skillUsed(){CD = formerCD;}
  void reduceCD(){CD--;}
  bool useSkill(MagicPet pokemon);
  void printSkill(){cout << *this;}
  bool hitFail();
  friend ostream& operator<<(ostream& os, const Skill& skill)
  {
    os << skill.name << "\n";
    os << "招式威力：" << skill.power << "\n";
    os << "當前CD回合：" << skill.CD;
    return os;
  }
}


bool Skill::useSkill(MagicPet* pokemon)
{
    if(CD == 0)
      skillUsed();
    else
    {
      cout << "當前無法使用此技能\n";
      return false;
    }
    timesUsed ++;
    if(hitFail())
    {
      cout << "哈哈，" << pokemon->getName() << "沒打中唷！";
      return false;
    }
    else
      return true;
}

bool Skill::hitFail()
{
  int x = getRandomNum(1,100);
  if(x > hitRate)
    return true;
  else
    return false;
}

Skill::Skill(const Skill& another)
{
  CD = another.CD;
  formerCD = another.formerCD;
  hitRate = another.hitRate;
}


class SpecialSkill : public Skill
{
friend class MagicPet; 
  protected:
  string type;
  int timesLimit;

  public:
  SpecialSkill(string _name,string _type,int _timesLimit):Skill(5,_name),type(_type),timesLimit(_timesLimit){}
  SpecialSkill(SpecialSkill* another)
  {
    skill(SpecialSkill* another);
    type = another.type;
    timesLimit = another.timesLimit;
  }
  bool usedTooMuch()
  {
    if(timesUsed > timesLimit)
    {
      cout << "無法再使用此技能\n";
      return true;
    }
    return false;
  }
  
}




