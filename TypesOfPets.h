<<<<<<< HEAD
#ifndef TypesOfPet_H
#define TypesOfPet_H

#include "Pet.h"

// Gold Pet
class GoldPet : public MagicPet {
public:
    GoldPet(string name, int HP, int speed);
    void getExpAfterBattle(bool win) override;
};

// Water Pet
class WaterPet : public MagicPet {
public:
    WaterPet(string name, int HP, int speed);
    void levelUp() override;
    void getExpAfterBattle(bool win) override;
};

// Fire Pet
class FirePet : public MagicPet {
public:
    FirePet(string name, int HP, int speed);
    void levelUp() override;
    void getExpAfterBattle(bool win) override;
};

// Wood Pet
class WoodPet : public MagicPet {
public:
    WoodPet(string name, int HP, int speed);
    void levelUp() override;
    void getExpAfterBattle(bool win) override;
};

// Mud Pet
class MudPet : public MagicPet {
public:
    MudPet(string name, int HP, int speed);
    void levelUp() override;
    void getExpAfterBattle(bool win) override;
};

#endif

=======
#ifndef TypesOfPet_H
#define TypesOfPet_H

#include "Pet.h"

// Gold Pet
class GoldPet : public MagicPet {
public:
    GoldPet(string name, int HP, int speed);
    void getExpAfterBattle(bool win) override;
};

// Water Pet
class WaterPet : public MagicPet {
public:
    WaterPet(string name, int HP, int speed);
    void levelUp() override;
    void getExpAfterBattle(bool win) override;
};

// Fire Pet
class FirePet : public MagicPet {
public:
    FirePet(string name, int HP, int speed);
    void levelUp() override;
    void getExpAfterBattle(bool win) override;
};

// Wood Pet
class WoodPet : public MagicPet {
public:
    WoodPet(string name, int HP, int speed);
    void levelUp() override;
    void getExpAfterBattle(bool win) override;
};

// Mud Pet
class MudPet : public MagicPet {
public:
    MudPet(string name, int HP, int speed);
    void levelUp() override;
    void getExpAfterBattle(bool win) override;
};

#endif

>>>>>>> e52650bad2b5a7d275424c7ec98ae5c46c037c70
