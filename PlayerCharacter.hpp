///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 13a - Let the Battle Begin! (Containers) - ECE 205 - Spring 2026
//
/// @file    PlayerCharacter.hpp
/// @authors James Wong, Lenard Cabero, Nahyun Koo
///////////////////////////////////////////////////////////////////////////////

#ifndef PLAYERCHARACTER_HPP
#define PLAYERCHARACTER_HPP

#include "GameCharacter.hpp"
#include <string>
#include <iostream>
#include <random>

class PlayerCharacter : public GameCharacter {
protected:
    // Base Stats
    int health, defense, attack;
    int race; // 0: Wookiee, 1: Human, 2: Android

    // Ability Stats
    int forceSensitivity; // Wookiee
    int strengthBonus; // Human
    int techPower; // Android

    // Turn-Base Effects
    int moveCount; // Tracks moves for Special
    bool skipTurn = false; // For Force Push / Ground Slam / Force Lightning
    int morality = 50; // Morality System starting Neutral

public:
    // Constructor
    PlayerCharacter(std::string& name, int race);

    // Virtual Perform Action
    virtual void performAction(PlayerCharacter* enemy) = 0;

    // Setters
    void incrementMoveCount() { moveCount++; }
    int getMoveCount() { return moveCount; }

    void printStats();
    double rollDice();
    void takeDamage(int damage);
    int dealDamage();
    int getHealth();
    bool isAlive();
    
    void resetHealth();

    // Battle Logic
    void setDefense(int d) { defense = d; }
    int getDefense() { return defense; }
    void setAttack(int a) { attack = a; }
    int getAttack() { return attack; }
    void setSkip(bool s) { skipTurn = s; }
    bool getSkip() { return skipTurn; }

    // Morality
    void setMorality(int m) {
        morality = m;
        if (morality < 0) morality = 0;
        if (morality > 100) morality = 100;
    }
    int getMorality() { return morality; }

    // Health
    void setHealth(int h) { health = h; }

    // Race Specific Moves
    
    // 1. Wookiee (Race 0)
    int wookieeSmash();
    void roarIntimidate(PlayerCharacter* enemy);

    // 2. Human (Race 1)
    int lightsaberStrike();
    void forcePush(PlayerCharacter* enemy);

    // 3. Android (Race 2)
    int blasterShot();
    void energyShield();

};

#endif
