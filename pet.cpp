#include <iostream>

class MagicPet{
    private:
    int HP;
    int maxHP;
    string type;
    int Exp;
    int level;
    int ATK; //attack
    int DFS; //defense
    int SPD; //speed
    Skill skill;
    
    public:
    void initializeHP();
    bool avoidSuccessfully(int speed);
    

}