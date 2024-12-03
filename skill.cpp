#include <iostream>
#include <cstdlib>
#include "skill.h"
using namespace std;

int getRandomNum(int min, int max)
{
	return rand() % (max - min + 1) + min;
}


  friend Skill::ostream& operator<<(ostream& os, const Skill& skill)
  {
      os << skill.name << "\n";
      os << "招式威力：" << skill.power << "\n";
      os << "當前CD回合：" << skill.CD << "\n";
      os << "技能命中率：" << skill.hitRate << "%\n";
      os << "已使用次數：" << skill.timesUsed << "\n";
      return os;
  }



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


  friend SpecialSkill::ostream& operator<<(ostream& os, const SpecialSkill& skill)
  {
      os << static_cast<const Skill&>(skill); 
      os << "招式屬性：" << skill.type << "\n";
      os << "使用次數限制：" << skill.timesLimit << "\n";
      return os;
  }

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