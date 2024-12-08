#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// �w�]���Ť����̰��šA���P�_�i�ڪ��t�׼W�[���ӷ|���P
int exps[6] = {0, 220, 450, 700, 1000, 1500};
float maxHPs[6] = {60, 70, 84, 106, 130, 160};
int attackPowers[6] = {10, 12, 16, 24, 34, 45};
int defensePowers[6] = {6, 8, 12, 18, 26, 36};
int speeds[6] = {30, 35, 42, 54, 64, 78};
float escapeRate[6] = {0.1, 0.2, 0.35, 0.5, 0.65, 0.8};
string types[5] = {"��","��","��","��","�g"};

// --------------------------- �d������ ---------------------------
class Pet {
protected:
    string name;
    string type;
    float maxHP;
    float currentHP;
    int attackPower;
    int defensePower;
    int speed;
    int level;
    int exp;

public:
    Pet(string name, string type) 
    : name(name), type(type), maxHP(maxHPs[0]), currentHP(maxHPs[0]), attackPower(attackPowers[0]), defensePower(defensePowers[0]), speed(speeds[0]), level(1), exp(0) {};
    Pet(string type, int maxHP, int attackPower, int defensePower, int speed) 
    : name("�����ͪ�"), type(type), maxHP(maxHP), currentHP(maxHP), attackPower(attackPower), defensePower(defensePower), speed(speed) {};

    string getName() const { return name; }
    string getType() const { return type; }
    int getHP() const { return currentHP; }
    int getMaxHP() const { return maxHP; }
    int getAttackPower() const { return attackPower; }
    int getDefense() const { return defensePower; }
    int getSpeed() const { return speed; }

    // �ݧ�
    // �Q����
    void takeDamage(int damage) {
        currentHP -= damage;
        if (currentHP < 0) currentHP = 0;
    }

    bool isAlive() const { return currentHP > 0; }

    virtual void print() const {
        cout << "�d���W�١G" << name << "\n";
        cout << "�ݩʡG" << type << "\n";
        cout << "���šG" << level << "\n";
        cout << "�g��ȡG" << exp << "\n";
        cout << "��q�G" << currentHP << "��" << maxHP << "\n";
        cout << "�����O�G" << attackPower << "\n";
        cout << "���m�O�G" << defensePower << "\n";
        cout << "�t�סG" << speed << "\n\n";
    }   
};

// --------------------------- ���a�d�� ---------------------------
class PlayerPet : public Pet {
public:
    PlayerPet(string name, string type)
        : Pet(name, type) {};

    // �������G���]�t�b win�Blose�̭�
    void levelAdjust() {
      if (exp >= exps[5]) {
        level = 6;
      }
      else if (exp >= exps[4]) {
        level = 5;
      }
      else if (exp >= exps[3]) {
        level = 4;
      }
      else if (exp >= exps[2]) {
        level = 3;
      }
      else if (exp >= exps[1]) {
        level = 2;
      }
      else
      {
        level = 1;
      }

      maxHP = maxHPs[level - 1];
      attackPower = attackPowers[level - 1];
      defensePower = defensePowers[level - 1];
      speed = speeds[level - 1];
      currentHP = maxHP;
    }

    bool escapeSuccess() {
      double randomValue = static_cast<double>(rand()) / RAND_MAX;
      return (randomValue < escapeRate[level - 1]) ? true : false;
    }

    // �������G��Ĺ�B�m
    void win() {
      exp += 50;
      levelAdjust();
    }

    void lose() {
      exp -= 50;
      levelAdjust();
    }

    void die() {
      exp = 0;
      levelAdjust();
    }
};       

// --------------------------- ���a�� ---------------------------
class Player {
private:
    vector<PlayerPet*> pets;

public:
    void addPet(PlayerPet* newPet) { pets.push_back(newPet); }
    PlayerPet* getPet(int idx) { return pets[idx]; }

    // �ݹ�@
    int findSecondMaxHP() {
      int firstMaxHP = 0, secondMaxHP = 0;
      for (int i = 0; i < 5; i++) {
        // Keep track of the largest and second largest number
        if (pets[i]->getMaxHP() > firstMaxHP)
        {
            secondMaxHP = firstMaxHP;
            firstMaxHP = pets[i]->getMaxHP();
        }
        else if (pets[i]->getMaxHP() == firstMaxHP)
        {
            secondMaxHP = firstMaxHP;
        }
        else if (pets[i]->getMaxHP() > secondMaxHP)
        {
            secondMaxHP = pets[i]->getMaxHP();
        }
      }

      return secondMaxHP;
    }

    int findSecondAttackPower() {
      int firstAttackPower = 0, secondAttackPower = 0;
      for (int i = 0; i < 5; i++) {
        // Keep track of the largest and second largest number
        if (pets[i]->getAttackPower() > firstAttackPower)
        {
            secondAttackPower = firstAttackPower;
            firstAttackPower = pets[i]->getAttackPower();
        }
        else if (pets[i]->getAttackPower() == firstAttackPower)
        {
            secondAttackPower = firstAttackPower;
        }
        else if (pets[i]->getAttackPower() > secondAttackPower)
        {
            secondAttackPower = pets[i]->getAttackPower();
        }
      }

      return secondAttackPower;
    }

    int findSecondDefensePower() {
      int firstDefensePower = 0, secondDefensePower = 0;
      for (int i = 0; i < 5; i++) {
        // Keep track of the largest and second largest number
        if (pets[i]->getDefense() > firstDefensePower)
        {
            secondDefensePower = firstDefensePower;
            firstDefensePower = pets[i]->getDefense();
        }
        else if (pets[i]->getDefense() == firstDefensePower)
        {
            secondDefensePower = firstDefensePower;
        }
        else if (pets[i]->getDefense() > secondDefensePower)
        {
            secondDefensePower = pets[i]->getDefense();
        }
      }

      return secondDefensePower;
    }

    int findSecondSpeed() {
      int firstSpeed = 0, secondSpeed = 0;
      for (int i = 0; i < 5; i++) {
        // Keep track of the largest and second largest number
        if (pets[i]->getSpeed() > firstSpeed)
        {
            secondSpeed = firstSpeed;
            firstSpeed = pets[i]->getSpeed();
        }
        else if (pets[i]->getSpeed() == firstSpeed)
        {
            secondSpeed = firstSpeed;
        }
        else if (pets[i]->getSpeed() > secondSpeed)
        {
            secondSpeed = pets[i]->getSpeed();
        }
      }

      return secondSpeed;
    }
};

// --------------------------- �q���d�� ---------------------------
class ComputerPet : public Pet {
public:
    ComputerPet(string type, int maxHP, int attackPower, int defensePower, int speed)
        : Pet(type, maxHP, attackPower, defensePower, speed) {};
    
    void print() {
        cout << "�d���W�١G" << name << "\n";
        cout << "�ݩʡG" << type << "\n";
        cout << "��q�G" << currentHP << "��" << maxHP << "\n";
        cout << "�����O�G" << attackPower << "\n";
        cout << "���m�O�G" << defensePower << "\n";
        cout << "�t�סG" << speed << "\n\n";
    };
};

// --------------------------- �C���� ---------------------------
class Game {
private:
    int round = 1;
    int lastAdvRd = -1;  // ���a�W�@���ϥζi���������^�X
    bool playerEscape = false;
    vector<PlayerPet*> playerPets;
    vector<ComputerPet*> computerPets;

public:
    void addPlayerPet(PlayerPet* pet)
    {
      playerPets.push_back(pet);
    }

    void addComputerPet(ComputerPet* pet)
    {
      computerPets.push_back(pet);
    }

    PlayerPet* getPlayerPet(int idx)
    {
      return playerPets[idx];
    }

    ComputerPet* getComputerPet(int idx)
    {
      return computerPets[idx];
    }

    void startBattle(Player& player) {
        // ����X���a�d�����ݩʲĤG�j�ƭȧ@���q���d���ƭȰ��
        int maxHP = player.findSecondMaxHP();
        int attackPower = player.findSecondAttackPower();
        int defensePower = player.findSecondDefensePower();
        int speed = player.findSecondDefensePower();

        ComputerPet pet1(types[rand() % 5], maxHP + 5 * ((- 1) ^ (rand() % 2)), attackPower + 3 * ((- 1) ^ (rand() % 2)), defensePower + 2 * ((- 1) ^ (rand() % 2)), speed + 3 * ((- 1) ^ (rand() % 2)));
        ComputerPet pet2(types[rand() % 5], maxHP + 5 * ((- 1) ^ (rand() % 2)), attackPower + 3 * ((- 1) ^ (rand() % 2)), defensePower + 2 * ((- 1) ^ (rand() % 2)), speed + 3 * ((- 1) ^ (rand() % 2)));
        ComputerPet* pet1ptr = &(pet1);
        ComputerPet* pet2ptr = &(pet2);
        addComputerPet(pet1ptr);
        addComputerPet(pet2ptr);

        cout << "�z�J�쪺����ݩʬ��G" << getComputerPet(0)->getType() << "�B" << getComputerPet(1)->getType() << "\n";
        cout << "�A�ݭn���X�Ⱖ�d�����ԡA�п�J�����X���Ĥ@���d���W�١G�]���d���N�|�w�]���Ĥ@�^�X�ڤ誺�X���d���^";
        string petName1;
        int pet1Idx = -1;
        string petName2;
        int pet2Idx = -1;

        while(pet1Idx == -1) {
          cin >> petName1;
          for(int i = 0; i < 5; i++) {
    
            if(petName1 == player.getPet(i)->getName()) {
              pet1Idx = i;
              break;
            }
          }
          if(pet1Idx == -1)
          {
            cout << "��J�L�ġI�z�å��֦����W�٪��d���A�Э��s��J�G";
          }
        }
        cout << "�п�J�����X���ĤG���d���W�١G";
        while(pet2Idx == -1)
        {
          cin >> petName2;
          int sameAs1 = false;
          for(int i = 0; i < 5; i++)
          {
            if(petName2 == player.getPet(i)->getName())
            {
              if(i != pet1Idx)
              {
                pet2Idx = i;
                break;
              }
              else 
              {
                cout << "�z��~�H��L���d���F��I�Э��s��J�G";
                sameAs1 = true;
                break;
              }
            }
          }
          if(sameAs1 == false and pet2Idx == -1)
          {
            cout << "��J�L�ġI�z�å��֦����W�٪��d���A�Э��s��J�G";
          }
        }

        addPlayerPet(player.getPet(pet1Idx));
        addPlayerPet(player.getPet(pet2Idx));

        int idxPlayer = 0;
        int idxComputer = 0;
        PlayerPet* playerPet = getPlayerPet(idxPlayer);
        ComputerPet* computerPet = getComputerPet(idxComputer);

        cout << "\n\n��Զ}�l�I" << endl;

        bool playerStillIn = true;

        while ((getPlayerPet(0)->isAlive() or getPlayerPet(1)->isAlive())
        and (getComputerPet(0)->isAlive() or getComputerPet(1)->isAlive())
        and !playerEscape)
        {
          cout << "\n\n\nRound " << round << "\n" << "����P�ɥX�ۡI\n";
          cout << "���^�X�ڤ謣�X�X�X" << "\n";
          playerPet->print();
          cout << "���^�X�Ĥ謣�X�X�X" << "\n";
          computerPet->print();
          cout << "�п�ܱz���o�_����ʡ]�H�Ʀr�^�С^�G\n1.���q����\n2.�i������ ";
          if(lastAdvRd == -1 or (lastAdvRd != -1 and round - lastAdvRd >= 3))
          {
            cout << "�]���^�X�i�ϥΡ^\n";
          }
          else
          {
            cout << "�]���^�X���}��^\n";
          }
          cout << "3.���m\n4.�k�]\n";
          string playerChoice;
          string computerChoice;
          string allComChoices[2] = {"1", "3"};
          computerChoice = allComChoices[rand() % 2];

          while(true)
          {
            cin >> playerChoice;

            if(playerChoice == "1")  // ���a��ܴ��q����
            {
              if(computerChoice == "1")
              {
                cout << "�Ĥ�]�ϥX�F�����I\n";
                playerPet->takeDamage(computerPet->getAttackPower());
                cout << "�D���Ĥ�����I�ڤ��q��" << computerPet->getAttackPower() << "\n";
                computerPet->takeDamage(playerPet->getAttackPower());
                cout << "���]�]�D���ڤ������q��" << playerPet->getAttackPower() << "\n";
              }
              else
              {
                cout << "�Ĥ��ܨ��m�I\n";
                if(computerPet->getDefense() >= playerPet->getAttackPower())
                {
                  cout << "�Ĥ�ױ��F�A�������A�]���@�v�L�ˡC\n";
                }
                else
                {
                  computerPet->takeDamage(playerPet->getAttackPower() - computerPet->getDefense());
                  cout << "�Ĥ�D���ڤ�����A��q��" << playerPet->getAttackPower() - computerPet->getDefense() << "\n";
                }
              }
              break;
            }
            else if (playerChoice == "2" and (lastAdvRd == -1 or (lastAdvRd != -1 and round - lastAdvRd >= 3)))  // ���a��ܶi������
            {
              if(computerChoice == "1")
              {
                cout << "�Ĥ�]�ϥX�F�����I\n";
                playerPet->takeDamage(computerPet->getAttackPower());
                cout << "�D���Ĥ�����I�ڤ��q��" << computerPet->getAttackPower() << "\n";

                if (playerPet->getType() == "��" and computerPet->getType() == "��") {
                  computerPet->takeDamage((playerPet->getAttackPower()) * 2);
                  cout << "�]���ڤ�ϥX�i�������B�ݩʬ۫g�A���D���ڤ������q��" << (playerPet->getAttackPower()) * 2 << "\n";
                }
                else if (playerPet->getType() == "��" and computerPet->getType() == "�g") {
                  computerPet->takeDamage((playerPet->getAttackPower()) * 2);
                  cout << "�]���ڤ�ϥX�i�������B�ݩʬ۫g�A���D���ڤ������q��" << (playerPet->getAttackPower()) * 2 << "\n";
                }
                else if (playerPet->getType() == "��" and computerPet->getType() == "��") {
                  computerPet->takeDamage((playerPet->getAttackPower()) * 2);
                  cout << "�]���ڤ�ϥX�i�������B�ݩʬ۫g�A���D���ڤ������q��" << (playerPet->getAttackPower()) * 2 << "\n";
                }
                else if (playerPet->getType() == "��" and computerPet->getType() == "��") {
                  computerPet->takeDamage((playerPet->getAttackPower()) * 2);
                  cout << "�]���ڤ�ϥX�i�������B�ݩʬ۫g�A���D���ڤ������q��" << (playerPet->getAttackPower()) * 2 << "\n";
                }
                else if (playerPet->getType() == "�g" and computerPet->getType() == "��") {
                  computerPet->takeDamage((playerPet->getAttackPower()) * 2);
                  cout << "�]���ڤ�ϥX�i�������B�ݩʬ۫g�A���D���ڤ������q��" << (playerPet->getAttackPower()) * 2 << "\n";
                }
                else {
                  computerPet->takeDamage((playerPet->getAttackPower()) * 2);
                  cout << "�]���ڤ�ϥX�i�������A���D���ڤ������q��" << (playerPet->getAttackPower()) * 1.5 << "\n";
                }
              }
              else
              {
                cout << "�Ĥ��ܨ��m�I\n";

                if (playerPet->getType() == "��" and computerPet->getType() == "��") {
                  if(computerPet->getDefense() < ((playerPet->getAttackPower()) * 2)) {
                    computerPet->takeDamage((playerPet->getAttackPower()) * 2 - computerPet->getDefense());
                    cout << "�]���ڤ�ϥX�i�������B�ݩʬ۫g�A���D���ڤ������q��" << (playerPet->getAttackPower()) * 2 - computerPet->getDefense() << "\n";
                  }
                  else
                  {
                    cout << "���ױ��F�A���i�������Ӳ@�v�L��\n";
                  }
                }
                else if (playerPet->getType() == "��" and computerPet->getType() == "�g") {
                  if(computerPet->getDefense() < ((playerPet->getAttackPower()) * 2)) {
                    computerPet->takeDamage((playerPet->getAttackPower()) * 2 - computerPet->getDefense());
                    cout << "�]���ڤ�ϥX�i�������B�ݩʬ۫g�A���D���ڤ������q��" << (playerPet->getAttackPower()) * 2 - computerPet->getDefense() << "\n";
                  }
                  else
                  {
                    cout << "���ױ��F�A���i�������Ӳ@�v�L��\n";
                  }
                }
                else if (playerPet->getType() == "��" and computerPet->getType() == "��") {
                  if(computerPet->getDefense() < ((playerPet->getAttackPower()) * 2)) {
                    computerPet->takeDamage((playerPet->getAttackPower()) * 2 - computerPet->getDefense());
                    cout << "�]���ڤ�ϥX�i�������B�ݩʬ۫g�A���D���ڤ������q��" << (playerPet->getAttackPower()) * 2 - computerPet->getDefense() << "\n";
                  }
                  else
                  {
                    cout << "���ױ��F�A���i�������Ӳ@�v�L��\n";
                  }
                }
                else if (playerPet->getType() == "��" and computerPet->getType() == "��") {
                  if(computerPet->getDefense() < ((playerPet->getAttackPower()) * 2)) {
                    computerPet->takeDamage((playerPet->getAttackPower()) * 2 - computerPet->getDefense());
                    cout << "�]���ڤ�ϥX�i�������B�ݩʬ۫g�A���D���ڤ������q��" << (playerPet->getAttackPower()) * 2 - computerPet->getDefense() << "\n";
                  }
                  else
                  {
                    cout << "���ױ��F�A���i�������Ӳ@�v�L��\n";
                  }
                }
                else if (playerPet->getType() == "�g" and computerPet->getType() == "��") {
                  if(computerPet->getDefense() < ((playerPet->getAttackPower()) * 2)) {
                    computerPet->takeDamage((playerPet->getAttackPower()) * 2 - computerPet->getDefense());
                    cout << "�]���ڤ�ϥX�i�������B�ݩʬ۫g�A���D���ڤ������q��" << (playerPet->getAttackPower()) * 2 - computerPet->getDefense() << "\n";
                  }
                  else
                  {
                    cout << "���ױ��F�A���i�������Ӳ@�v�L��\n";
                  }
                }
                else {
                  if(computerPet->getDefense() < ((playerPet->getAttackPower()) * 1.5)) {
                    computerPet->takeDamage((playerPet->getAttackPower()) * 1.5 - computerPet->getDefense());
                    cout << "�]���ڤ�ϥX�i�������A���D���ڤ������q��" << (playerPet->getAttackPower()) * 1.5 - computerPet->getDefense() << "\n";
                  }
                  else
                  {
                    cout << "���ױ��F�A���i�������Ӳ@�v�L��\n";
                  }
                }
              }
              lastAdvRd = round;
              break;
            }
            else if (playerChoice == "3")  // ���a��ܨ��m
            {
              if(computerChoice == "1")
              {
                cout << "�Ĥ�ϥX�F�����I\n";
                if(playerPet->getDefense() >= computerPet->getAttackPower())
                {
                  cout << "�A���\�ױ��Ĥ誺�����A�]���@�v�L�ˡC\n";
                }
                else
                {
                  playerPet->takeDamage(computerPet->getAttackPower() - playerPet->getDefense());
                  cout << "�ڤ�]�D�Ĥ�����A��q��" << computerPet->getAttackPower() - playerPet->getDefense() << "\n";
                }                
              }
              else
              {
                cout << "�Ĥ�]��ܨ��m�A���^�X�w�M�׹L�I\n";
              }
              break;
            }
            else if (playerChoice == "4")  // ���a��ܰk�]
            {
              if(computerChoice == "1") {
                if(playerPet->escapeSuccess()) {
                  playerEscape = true;
                  cout << "�Ĥ�ϥX�����I\n���ڤ�k�]���\�]�Ӳ@�v�L�ˡA�h�X�԰��C\n";
                }
                else {
                  cout << "�Ĥ�ϥX�����I\n���ڤ�k�]���Ѧӥ����������A��q��" << computerPet->getAttackPower() << "\n";
                  playerPet->takeDamage(computerPet->getAttackPower());
                }
              }
              else {
                playerEscape = true;
                cout << "�Ĥ��ܨ��m�I\n�ڤ覨�\�k�]�A�h�X�԰��C\n";
              }
              break;
            }
            else
            {
              cout << "�ާ@�L�ġA�Э��s��J�G";
            }
          }

          cout << "�g�L���^�X�A����{�b�����A���G\n";
          playerPet->print();
          computerPet->print();

          if(playerEscape)
          {
           cout << "�ڤ�k�]���\�I�԰������C\n";
           if(!(getPlayerPet(0)->isAlive())) {
             getPlayerPet(0)->die();
           }

           if(!(getPlayerPet(1)->isAlive())) {
             getPlayerPet(1)->die();
           }
           break;
          }

          if(!playerPet->isAlive())  // �ڤ�{�b�o���w�Ա�
          {
            if(!getPlayerPet(0)->isAlive() and !getPlayerPet(1)->isAlive()) {
              if(getComputerPet(0)->isAlive() or getComputerPet(1)->isAlive()) {
                cout << "�z���Ⱖ�d�����ԱѡA�Ĥ�Ĺ�o�����԰����ӧQ�I\n";
                getPlayerPet(0)->die();
                getPlayerPet(1)->die();
              }
              else {
                cout << "���誺�d�����ԱѡA�����԰�����I\n";
                getPlayerPet(0)->die();
                getPlayerPet(1)->die();
              }
              break;
            }
            else
            {
              cout << "�z���Ӱ��d���w�ԱѡA�ڤ�b�U�@�^�X�N���X�t�@���d���W���I\n";
              if(idxPlayer == 0)
              {
                playerPet = getPlayerPet(1);
                idxPlayer = 1;
              }
              else
              {
                idxPlayer = 0;
                playerPet = getPlayerPet(0);
              }
            }
          }
          else {  // �ڤ�{�b�o���٬���
            if (!getComputerPet(0)->isAlive() and !getComputerPet(1)->isAlive())
            {
              cout << "�Ĥ�Ⱖ�d�����Q���ѡA���߱z��o�����԰����ӧQ�I\n";
              if(getPlayerPet(0)->isAlive()) {
                getPlayerPet(0)->win();
              }
              else {
                getPlayerPet(0)->die();
              }

              if(getPlayerPet(1)->isAlive()) {
                getPlayerPet(1)->win();
              }
              else {
                getPlayerPet(1)->die();
              }
              break;
            }
            else if(idxPlayer == 0 and getPlayerPet(1)->isAlive())
            {
              cout << "�z�O�_���b�U�^�X�󴫤W���d���H �]yes / no�^";
              string change;
              while(true)
              {
                cin >> change;
                if(change == "yes")
                {
                  cout << "�ڤ�b�U�^�X�N���d���W���I\n";
                  idxPlayer = 1;
                  playerPet = getPlayerPet(1);
                  break;
                }
                else if(change == "no")
                {
                  cout << "�ڤ�b�U�^�X�N�������d���W���I\n";
                  break;
                }
                else
                {
                  cout << "��J�L�ġI�Э��s��J�G";
                }
              }
            }
            else if(idxPlayer == 1 and getPlayerPet(0)->isAlive())
            {
              cout << "�z�O�_���b�U�^�X�󴫤W���d���H �]yes / no�^";
              string change;
              while(true) {
                cin >> change;
                if(change == "yes") {
                  cout << "�ڤ�b�U�^�X�N���d���W���I\n";
                  idxPlayer = 0;
                  playerPet = getPlayerPet(0);
                  break;
                }
                else if(change == "no"){
                  cout << "�ڤ�U�^�X�N�������d���W���I\n";
                  break;
                }
                else{
                  cout << "��J�L�ġI�Э��s��J�G";
                }
              }
            }
          }


          if(!(computerPet->isAlive()))
          {
            if(idxComputer == 0)
            {
              cout << "�Ĥ覹���d���w�Q���Q�A�U�^�X�N���X�ĤG���d�����ԡI\n";
              idxComputer = 1;
              computerPet = getComputerPet(1);
            }
          }
          round++;
        }
    }
};

// --------------------------- �D�{�� ---------------------------
int main() {
    srand(static_cast<unsigned>(time(0))); // �]�w�H���ؤl

    Player player;
    PlayerPet pet1("���ݩ��d��", "��");
    PlayerPet pet2("���ݩ��d��", "��");
    PlayerPet pet3("���ݩ��d��", "��");
    PlayerPet pet4("���ݩ��d��", "��");
    PlayerPet pet5("�g�ݩ��d��", "�g");
    player.addPet(&pet1);
    player.addPet(&pet2);
    player.addPet(&pet3);
    player.addPet(&pet4);
    player.addPet(&pet5);

    cout << "�w��i�J�C���I\n";


    while (true) {
        cout << "\n\n\n�H�U�O�z�ثe�֦����d����T�G\n";
        for (int i = 0; i < 5; i++) {
            player.getPet(i)->print();
        }
        while(true) {      
          cout << "�A�ǳƦn�[�J�s�԰��F�ܡH�]yes / no�^\n";
          string ans;
          cin >> ans;
          if (ans == "yes") {
              Game game;
              game.startBattle(player);
              break;
          } else if (ans == "no") {
              continue;
          } else {
              cout << "��J�L�ġI�Э��s��J�C\n";
              continue;
          }
        }
    }

    return 0;
}

// �p�G�ݤ����A��ڻ����
