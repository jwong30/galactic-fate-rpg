///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 13a - Let the Battle Begin! (Containers) - ECE 205 - Spring 2026
//
/// @file    PlayerCharacter.cpp
/// @authors James Wong, Lenard Cabero, Nahyun Koo
///////////////////////////////////////////////////////////////////////////////

#include "PlayerCharacter.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// 1. Game Character Constructor
PlayerCharacter::PlayerCharacter(string& name, int r) : GameCharacter(name) {
    this->race = r;
    this->health = 100;
    this->moveCount = 0;

    // Default Abilities Set to 0
    this->strengthBonus = 0;
    this->forceSensitivity = 0;
    this->techPower = 0;

    // Stats for each race
    if (race == 0) { // Wookiee
        attack = 15;
        defense = 10;
        strengthBonus = 20;

    } else if (race == 1) { // Human
        attack = 10;
        defense = 10;
        forceSensitivity = 15;

    } else if (race == 2) {
        // Android
        attack = 8;
        defense = 15;
        techPower = 25;
    }
}

// 2. Dice Roll

// 1: Miss (0%)
// 2. Low Roll (80%)
// 3. Base Damage (90%)
// 4. High Roll (100%)
// 5. Critical Hit (150%)

double PlayerCharacter::rollDice() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 5);

    int roll = distribution(gen);
    cout << name << " rolled a " << roll << "!" << endl;

        switch (roll) {
            case 1: cout << "Miss! (0 dmg)" << endl; return 0.0;
            case 2: cout << "Low Damage! (80% dmg)" << endl; return 0.8;
            case 3: cout << "Neutral Damage! (90% dmg)" << endl; return 0.9;
            case 4: cout << "High Damage! (100% dmg)" << endl; return 1.0;
            case 5: cout << "CRITICAL HIT! (150% dmg)" << endl; return 1.5;
            default: return 0.0;
        }
    }

// 3. Print Stats
void PlayerCharacter::printStats() {
    string raceNames[] = {"Wookiee", "Human", "Android"};
    
    cout << "---------- Stats for " << name << " ----------" << endl;
    cout << "Race: " << raceNames[race] << endl;
    cout << "Health: " << health << endl;
    cout << "Attack: " << attack << endl;
    cout << "Defense: " << defense << endl;

    if (forceSensitivity > 0) cout << "Force Sensitivity: " << forceSensitivity << endl;
    if (strengthBonus > 0) cout << "Strength Bonus: " << strengthBonus << endl;
    if (techPower > 0) cout << "Tech Power: " << techPower << endl;

    cout << "-----------------------------------" << endl;
}

// 4. Damage Calculator
int PlayerCharacter::dealDamage() {
    double multiplier = rollDice();
    int basePower = attack + strengthBonus + forceSensitivity + techPower;
    return (int)(basePower * multiplier);
}

void PlayerCharacter::takeDamage(int damage) {
    int reducedDamage = damage - (defense / 5);
    if (reducedDamage < 0) reducedDamage = 0;

    health -= reducedDamage;
    if (health < 0) health = 0;
    cout << name << " took " << reducedDamage << " damage! Remaining Health: " << health << endl;
}

int PlayerCharacter::getHealth() {
    return health;
}

bool PlayerCharacter::isAlive() {
    return health > 0;
}

// 5. Race Moves

// Wookiee Skills
int PlayerCharacter::wookieeSmash() {
    cout << name << " performs a Wookiee Smash!" << endl;
    return dealDamage();
}

void PlayerCharacter::roarIntimidate(PlayerCharacter* enemy) { // Lowers Enemies Defense
    cout << name << " lets out a deafening ROAR! Enemy defense fell." << endl;
    enemy->setDefense(enemy->getDefense() - 5);
}

// Human Skills
int PlayerCharacter::lightsaberStrike() {
    cout << name << " swings a lightsaber!" << endl;
    return dealDamage();
}
void PlayerCharacter::forcePush(PlayerCharacter* enemy) { // Stuns The Enemy (skips their turn)
    cout << name << " uses Force Push! The enemy is staggered!" << endl;
    enemy->setSkip(true);
}

// Android Skills
int PlayerCharacter::blasterShot() {
    cout << name << " fires a precise Blaster Shot!" << endl;
    return dealDamage();
}
void PlayerCharacter::energyShield() { // Increase User's Defense
    cout << name << " activates an Energy Shield!" << name << " defense rose!" << endl;
    this->defense += 10;
}

void PlayerCharacter::resetHealth() {
    health = 100;
    moveCount = 0;
    setSkip(false);
}
