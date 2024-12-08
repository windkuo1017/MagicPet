#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// 預設等級六為最高級，不同寶可夢的速度增加應該會不同
int exps[6] = {0, 220, 450, 700, 1000, 1500};
float maxHPs[6] = {60, 70, 84, 106, 130, 160};
int attackPowers[6] = {10, 12, 16, 24, 34, 45};
int defensePowers[6] = {6, 8, 12, 18, 26, 36};
int speeds[6] = {30, 35, 42, 54, 64, 78};
float escapeRate[6] = {0.1, 0.2, 0.35, 0.5, 0.65, 0.8};
string types[5] = {"金","木","水","火","土"};

// --------------------------- 寵物基類 ---------------------------
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
    : name("未知生物"), type(type), maxHP(maxHP), currentHP(maxHP), attackPower(attackPower), defensePower(defensePower), speed(speed) {};

    string getName() const { return name; }
    string getType() const { return type; }
    int getHP() const { return currentHP; }
    int getMaxHP() const { return maxHP; }
    int getAttackPower() const { return attackPower; }
    int getDefense() const { return defensePower; }
    int getSpeed() const { return speed; }

    // 待改
    // 被攻擊
    void takeDamage(int damage) {
        currentHP -= damage;
        if (currentHP < 0) currentHP = 0;
    }

    bool isAlive() const { return currentHP > 0; }

    virtual void print() const {
        cout << "寵物名稱：" << name << "\n";
        cout << "屬性：" << type << "\n";
        cout << "等級：" << level << "\n";
        cout << "經驗值：" << exp << "\n";
        cout << "血量：" << currentHP << "／" << maxHP << "\n";
        cout << "攻擊力：" << attackPower << "\n";
        cout << "防禦力：" << defensePower << "\n";
        cout << "速度：" << speed << "\n\n";
    }   
};

// --------------------------- 玩家寵物 ---------------------------
class PlayerPet : public Pet {
public:
    PlayerPet(string name, string type)
        : Pet(name, type) {};

    // 未完成：應包含在 win、lose裡面
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

    // 未完成：輸贏處置
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

// --------------------------- 玩家類 ---------------------------
class Player {
private:
    vector<PlayerPet*> pets;

public:
    void addPet(PlayerPet* newPet) { pets.push_back(newPet); }
    PlayerPet* getPet(int idx) { return pets[idx]; }

    // 待實作
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

// --------------------------- 電腦寵物 ---------------------------
class ComputerPet : public Pet {
public:
    ComputerPet(string type, int maxHP, int attackPower, int defensePower, int speed)
        : Pet(type, maxHP, attackPower, defensePower, speed) {};
    
    void print() {
        cout << "寵物名稱：" << name << "\n";
        cout << "屬性：" << type << "\n";
        cout << "血量：" << currentHP << "／" << maxHP << "\n";
        cout << "攻擊力：" << attackPower << "\n";
        cout << "防禦力：" << defensePower << "\n";
        cout << "速度：" << speed << "\n\n";
    };
};

// --------------------------- 遊戲類 ---------------------------
class Game {
private:
    int round = 1;
    int lastAdvRd = -1;  // 玩家上一次使用進階攻擊的回合
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
        // 先找出玩家寵物個屬性第二大數值作為電腦寵物數值基準
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

        cout << "您遇到的對手屬性為：" << getComputerPet(0)->getType() << "、" << getComputerPet(1)->getType() << "\n";
        cout << "你需要派出兩隻寵物應戰，請輸入欲派出的第一隻寵物名稱：（此寵物將會預設為第一回合我方的出戰寵物）";
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
            cout << "輸入無效！您並未擁有此名稱的寵物，請重新輸入：";
          }
        }
        cout << "請輸入欲派出的第二隻寵物名稱：";
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
                cout << "您方才以選過此寵物了喔！請重新輸入：";
                sameAs1 = true;
                break;
              }
            }
          }
          if(sameAs1 == false and pet2Idx == -1)
          {
            cout << "輸入無效！您並未擁有此名稱的寵物，請重新輸入：";
          }
        }

        addPlayerPet(player.getPet(pet1Idx));
        addPlayerPet(player.getPet(pet2Idx));

        int idxPlayer = 0;
        int idxComputer = 0;
        PlayerPet* playerPet = getPlayerPet(idxPlayer);
        ComputerPet* computerPet = getComputerPet(idxComputer);

        cout << "\n\n對戰開始！" << endl;

        bool playerStillIn = true;

        while ((getPlayerPet(0)->isAlive() or getPlayerPet(1)->isAlive())
        and (getComputerPet(0)->isAlive() or getComputerPet(1)->isAlive())
        and !playerEscape)
        {
          cout << "\n\n\nRound " << round << "\n" << "雙方同時出招！\n";
          cout << "此回合我方派出——" << "\n";
          playerPet->print();
          cout << "此回合敵方派出——" << "\n";
          computerPet->print();
          cout << "請選擇您欲發起的行動（以數字回覆）：\n1.普通攻擊\n2.進階攻擊 ";
          if(lastAdvRd == -1 or (lastAdvRd != -1 and round - lastAdvRd >= 3))
          {
            cout << "（此回合可使用）\n";
          }
          else
          {
            cout << "（此回合不開放）\n";
          }
          cout << "3.防禦\n4.逃跑\n";
          string playerChoice;
          string computerChoice;
          string allComChoices[2] = {"1", "3"};
          computerChoice = allComChoices[rand() % 2];

          while(true)
          {
            cin >> playerChoice;

            if(playerChoice == "1")  // 玩家選擇普通攻擊
            {
              if(computerChoice == "1")
              {
                cout << "敵方也使出了攻擊！\n";
                playerPet->takeDamage(computerPet->getAttackPower());
                cout << "遭受敵方攻擊！我方血量減" << computerPet->getAttackPower() << "\n";
                computerPet->takeDamage(playerPet->getAttackPower());
                cout << "對方也因遭受我方攻擊血量減" << playerPet->getAttackPower() << "\n";
              }
              else
              {
                cout << "敵方選擇防禦！\n";
                if(computerPet->getDefense() >= playerPet->getAttackPower())
                {
                  cout << "敵方擋掉了你的攻擊，因此毫髮無傷。\n";
                }
                else
                {
                  computerPet->takeDamage(playerPet->getAttackPower() - computerPet->getDefense());
                  cout << "敵方遭受我方攻擊，血量減" << playerPet->getAttackPower() - computerPet->getDefense() << "\n";
                }
              }
              break;
            }
            else if (playerChoice == "2" and (lastAdvRd == -1 or (lastAdvRd != -1 and round - lastAdvRd >= 3)))  // 玩家選擇進階攻擊
            {
              if(computerChoice == "1")
              {
                cout << "敵方也使出了攻擊！\n";
                playerPet->takeDamage(computerPet->getAttackPower());
                cout << "遭受敵方攻擊！我方血量減" << computerPet->getAttackPower() << "\n";

                if (playerPet->getType() == "金" and computerPet->getType() == "木") {
                  computerPet->takeDamage((playerPet->getAttackPower()) * 2);
                  cout << "因為我方使出進階攻擊且屬性相剋，對方遭受我方攻擊血量減" << (playerPet->getAttackPower()) * 2 << "\n";
                }
                else if (playerPet->getType() == "木" and computerPet->getType() == "土") {
                  computerPet->takeDamage((playerPet->getAttackPower()) * 2);
                  cout << "因為我方使出進階攻擊且屬性相剋，對方遭受我方攻擊血量減" << (playerPet->getAttackPower()) * 2 << "\n";
                }
                else if (playerPet->getType() == "水" and computerPet->getType() == "火") {
                  computerPet->takeDamage((playerPet->getAttackPower()) * 2);
                  cout << "因為我方使出進階攻擊且屬性相剋，對方遭受我方攻擊血量減" << (playerPet->getAttackPower()) * 2 << "\n";
                }
                else if (playerPet->getType() == "火" and computerPet->getType() == "金") {
                  computerPet->takeDamage((playerPet->getAttackPower()) * 2);
                  cout << "因為我方使出進階攻擊且屬性相剋，對方遭受我方攻擊血量減" << (playerPet->getAttackPower()) * 2 << "\n";
                }
                else if (playerPet->getType() == "土" and computerPet->getType() == "水") {
                  computerPet->takeDamage((playerPet->getAttackPower()) * 2);
                  cout << "因為我方使出進階攻擊且屬性相剋，對方遭受我方攻擊血量減" << (playerPet->getAttackPower()) * 2 << "\n";
                }
                else {
                  computerPet->takeDamage((playerPet->getAttackPower()) * 2);
                  cout << "因為我方使出進階攻擊，對方遭受我方攻擊血量減" << (playerPet->getAttackPower()) * 1.5 << "\n";
                }
              }
              else
              {
                cout << "敵方選擇防禦！\n";

                if (playerPet->getType() == "金" and computerPet->getType() == "木") {
                  if(computerPet->getDefense() < ((playerPet->getAttackPower()) * 2)) {
                    computerPet->takeDamage((playerPet->getAttackPower()) * 2 - computerPet->getDefense());
                    cout << "因為我方使出進階攻擊且屬性相剋，對方遭受我方攻擊血量減" << (playerPet->getAttackPower()) * 2 - computerPet->getDefense() << "\n";
                  }
                  else
                  {
                    cout << "對方擋掉了你的進階攻擊而毫髮無傷\n";
                  }
                }
                else if (playerPet->getType() == "木" and computerPet->getType() == "土") {
                  if(computerPet->getDefense() < ((playerPet->getAttackPower()) * 2)) {
                    computerPet->takeDamage((playerPet->getAttackPower()) * 2 - computerPet->getDefense());
                    cout << "因為我方使出進階攻擊且屬性相剋，對方遭受我方攻擊血量減" << (playerPet->getAttackPower()) * 2 - computerPet->getDefense() << "\n";
                  }
                  else
                  {
                    cout << "對方擋掉了你的進階攻擊而毫髮無傷\n";
                  }
                }
                else if (playerPet->getType() == "水" and computerPet->getType() == "火") {
                  if(computerPet->getDefense() < ((playerPet->getAttackPower()) * 2)) {
                    computerPet->takeDamage((playerPet->getAttackPower()) * 2 - computerPet->getDefense());
                    cout << "因為我方使出進階攻擊且屬性相剋，對方遭受我方攻擊血量減" << (playerPet->getAttackPower()) * 2 - computerPet->getDefense() << "\n";
                  }
                  else
                  {
                    cout << "對方擋掉了你的進階攻擊而毫髮無傷\n";
                  }
                }
                else if (playerPet->getType() == "火" and computerPet->getType() == "金") {
                  if(computerPet->getDefense() < ((playerPet->getAttackPower()) * 2)) {
                    computerPet->takeDamage((playerPet->getAttackPower()) * 2 - computerPet->getDefense());
                    cout << "因為我方使出進階攻擊且屬性相剋，對方遭受我方攻擊血量減" << (playerPet->getAttackPower()) * 2 - computerPet->getDefense() << "\n";
                  }
                  else
                  {
                    cout << "對方擋掉了你的進階攻擊而毫髮無傷\n";
                  }
                }
                else if (playerPet->getType() == "土" and computerPet->getType() == "水") {
                  if(computerPet->getDefense() < ((playerPet->getAttackPower()) * 2)) {
                    computerPet->takeDamage((playerPet->getAttackPower()) * 2 - computerPet->getDefense());
                    cout << "因為我方使出進階攻擊且屬性相剋，對方遭受我方攻擊血量減" << (playerPet->getAttackPower()) * 2 - computerPet->getDefense() << "\n";
                  }
                  else
                  {
                    cout << "對方擋掉了你的進階攻擊而毫髮無傷\n";
                  }
                }
                else {
                  if(computerPet->getDefense() < ((playerPet->getAttackPower()) * 1.5)) {
                    computerPet->takeDamage((playerPet->getAttackPower()) * 1.5 - computerPet->getDefense());
                    cout << "因為我方使出進階攻擊，對方遭受我方攻擊血量減" << (playerPet->getAttackPower()) * 1.5 - computerPet->getDefense() << "\n";
                  }
                  else
                  {
                    cout << "對方擋掉了你的進階攻擊而毫髮無傷\n";
                  }
                }
              }
              lastAdvRd = round;
              break;
            }
            else if (playerChoice == "3")  // 玩家選擇防禦
            {
              if(computerChoice == "1")
              {
                cout << "敵方使出了攻擊！\n";
                if(playerPet->getDefense() >= computerPet->getAttackPower())
                {
                  cout << "你成功擋掉敵方的攻擊，因此毫髮無傷。\n";
                }
                else
                {
                  playerPet->takeDamage(computerPet->getAttackPower() - playerPet->getDefense());
                  cout << "我方因遭敵方攻擊，血量減" << computerPet->getAttackPower() - playerPet->getDefense() << "\n";
                }                
              }
              else
              {
                cout << "敵方也選擇防禦，此回合安然度過！\n";
              }
              break;
            }
            else if (playerChoice == "4")  // 玩家選擇逃跑
            {
              if(computerChoice == "1") {
                if(playerPet->escapeSuccess()) {
                  playerEscape = true;
                  cout << "敵方使出攻擊！\n但我方逃跑成功因而毫髮無傷，退出戰鬥。\n";
                }
                else {
                  cout << "敵方使出攻擊！\n但我方逃跑失敗而正中對方攻擊，血量減" << computerPet->getAttackPower() << "\n";
                  playerPet->takeDamage(computerPet->getAttackPower());
                }
              }
              else {
                playerEscape = true;
                cout << "敵方選擇防禦！\n我方成功逃跑，退出戰鬥。\n";
              }
              break;
            }
            else
            {
              cout << "操作無效，請重新輸入：";
            }
          }

          cout << "經過此回合，雙方現在的狀態為：\n";
          playerPet->print();
          computerPet->print();

          if(playerEscape)
          {
           cout << "我方逃跑成功！戰鬥結束。\n";
           if(!(getPlayerPet(0)->isAlive())) {
             getPlayerPet(0)->die();
           }

           if(!(getPlayerPet(1)->isAlive())) {
             getPlayerPet(1)->die();
           }
           break;
          }

          if(!playerPet->isAlive())  // 我方現在這隻已戰敗
          {
            if(!getPlayerPet(0)->isAlive() and !getPlayerPet(1)->isAlive()) {
              if(getComputerPet(0)->isAlive() or getComputerPet(1)->isAlive()) {
                cout << "您的兩隻寵物均戰敗，敵方贏得此次戰鬥的勝利！\n";
                getPlayerPet(0)->die();
                getPlayerPet(1)->die();
              }
              else {
                cout << "雙方的寵物全戰敗，此次戰鬥平手！\n";
                getPlayerPet(0)->die();
                getPlayerPet(1)->die();
              }
              break;
            }
            else
            {
              cout << "您的該隻寵物已戰敗，我方在下一回合將派出另一隻寵物上場！\n";
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
          else {  // 我方現在這隻還活著
            if (!getComputerPet(0)->isAlive() and !getComputerPet(1)->isAlive())
            {
              cout << "敵方兩隻寵物均被打敗，恭喜您獲得此次戰鬥的勝利！\n";
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
              cout << "您是否欲在下回合更換上場寵物？ （yes / no）";
              string change;
              while(true)
              {
                cin >> change;
                if(change == "yes")
                {
                  cout << "我方在下回合將更換寵物上場！\n";
                  idxPlayer = 1;
                  playerPet = getPlayerPet(1);
                  break;
                }
                else if(change == "no")
                {
                  cout << "我方在下回合將維持原寵物上場！\n";
                  break;
                }
                else
                {
                  cout << "輸入無效！請重新輸入：";
                }
              }
            }
            else if(idxPlayer == 1 and getPlayerPet(0)->isAlive())
            {
              cout << "您是否欲在下回合更換上場寵物？ （yes / no）";
              string change;
              while(true) {
                cin >> change;
                if(change == "yes") {
                  cout << "我方在下回合將更換寵物上場！\n";
                  idxPlayer = 0;
                  playerPet = getPlayerPet(0);
                  break;
                }
                else if(change == "no"){
                  cout << "我方下回合將維持原寵物上場！\n";
                  break;
                }
                else{
                  cout << "輸入無效！請重新輸入：";
                }
              }
            }
          }


          if(!(computerPet->isAlive()))
          {
            if(idxComputer == 0)
            {
              cout << "敵方此隻寵物已被打被，下回合將派出第二隻寵物應戰！\n";
              idxComputer = 1;
              computerPet = getComputerPet(1);
            }
          }
          round++;
        }
    }
};

// --------------------------- 主程式 ---------------------------
int main() {
    srand(static_cast<unsigned>(time(0))); // 設定隨機種子

    Player player;
    PlayerPet pet1("金屬性寵物", "金");
    PlayerPet pet2("木屬性寵物", "木");
    PlayerPet pet3("水屬性寵物", "水");
    PlayerPet pet4("火屬性寵物", "火");
    PlayerPet pet5("土屬性寵物", "土");
    player.addPet(&pet1);
    player.addPet(&pet2);
    player.addPet(&pet3);
    player.addPet(&pet4);
    player.addPet(&pet5);

    cout << "歡迎進入遊戲！\n";


    while (true) {
        cout << "\n\n\n以下是您目前擁有的寵物資訊：\n";
        for (int i = 0; i < 5; i++) {
            player.getPet(i)->print();
        }
        while(true) {      
          cout << "你準備好加入新戰鬥了嗎？（yes / no）\n";
          string ans;
          cin >> ans;
          if (ans == "yes") {
              Game game;
              game.startBattle(player);
              break;
          } else if (ans == "no") {
              continue;
          } else {
              cout << "輸入無效！請重新輸入。\n";
              continue;
          }
        }
    }

    return 0;
}

// 如果看不懂再跟我說嗚嗚
