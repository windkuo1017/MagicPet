#include "TypesOfPets.h"

// Gold Pet
GoldPet::GoldPet(string name, int HP, int speed) : MagicPet(name, "gold", HP, speed) {}

void GoldPet::getExpAfterBattle(bool win) {
    MagicPet::getExpAfterBattle(win, 100); // Gold gets more EXP
}

// Water Pet
WaterPet::WaterPet(string name, int HP, int speed) : MagicPet(name, "water", HP, speed) {}

void WaterPet::levelUp() {
    MagicPet::levelUp();
    this->SPD += 3; // Water gets more speed when leveling up
}

void WaterPet::getExpAfterBattle(bool win) {
    MagicPet::getExpAfterBattle(win, 30);
}


// Fire Pet
FirePet::FirePet(string name, int HP, int speed) : MagicPet(name, "fire", HP, speed) {}

void FirePet::levelUp() {
    MagicPet::levelUp();
    this->ATK += 3; // Fire gets more attack when leveling up
}

void FirePet::getExpAfterBattle(bool win) {
    MagicPet::getExpAfterBattle(win, 30);
}


// Wood Pet
WoodPet::FirePet(string name, int HP, int speed) : MagicPet(name, "wood", HP, speed) {}

void WoodPet::levelUp() {
    MagicPet::levelUp();
    this->maxHP += 3; // Wood gets more maxHP when leveling up
}

void WoodPet::getExpAfterBattle(bool win) {
    MagicPet::getExpAfterBattle(win, 30);
}


// Mud Pet
MudPet::MudPet(string name, int HP, int speed) : MagicPet(name, "mud", HP, speed) {}

void MudPet::levelUp() {
    MagicPet::levelUp();
    this->DFS += 3; // Mud gets more DFS when leveling up
}

void MudPet::getExpAfterBattle(bool win) {
    MagicPet::getExpAfterBattle(win, 30);
}


