#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

class Player
{
protected:
  string name;
  vector<MagicPet> magicPets;
public:
	Player();
  Player(string playerName);
  MagicPet& getMagicPet(string petName);
  void addMagicPet(MagicPet& newPet);
// 使用 vector，因此不用寫 destructor
};

Player::Player() : name("") {};
Player::Player(string playerName) : name(playerName) {}

MagicPet& Player::getMagicPet(string petName)
{
  for(int i = 0; i < this -> magicPets.size(); i++)
  {
    if(this -> magicPets[i].getPetName() == petName) 
    // getPetName() 要等另外一組實作 class MagicPet 
    {
      return &(this -> magicPets[i]);
    }
  };
return nullptr;  // 在此狀況下要使玩家重新輸入
}

void Player::addMagicPet(MagicPet& newPet)
{
	magicPets.push_back(newPet);
}


class BattleSystem
{
protected:
  vector<MagicPet> teamPlayer;
  vector<MagicPet> teamComputer;
  int roundCnt;
  int idx;
public:
	BattleSystem();
};



int main()
{
  return 0;
}