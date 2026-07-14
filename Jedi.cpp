///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 13a - Let the Battle Begin! (Containers) - ECE 205 - Spring 2026
//
/// @file    Jedi.cpp
/// @authors James Wong, Lenard Cabero, Nahyun Koo
///////////////////////////////////////////////////////////////////////////////
///

#include "Jedi.hpp"
#include <iostream>

// Constructor
Jedi::Jedi(std::string& name, int race) : PlayerCharacter(name, race) {}

// Choose move options based on race
void Jedi::performAction(PlayerCharacter* enemy) {
    int choice;
    int basePower = attack + strengthBonus + forceSensitivity + techPower;
    std::cout << "\n--- JEDI BATTLE MENU ---" << std::endl;

    if (race == 0) {
        // Wookiee
        std::cout << "1: WOOKIE SMASH [ Power: " << basePower << "]: A powerful physical strike." << std::endl;
        std::cout << "2: ROAR INTIMIDATE [Utility]: Frighten the enemy to lower their Defense." << std::endl;
        std::cout << "3: [SPECIAL] GROUND SLAM: Massive impact that stuns the enemy." << std::endl;
        std::cout << "----------------------------------------" << std::endl;

        std::cout << "\n" << name << " chooses: ";
        while (true) {
            std::cout << "\n" << name << " chooses: ";
            if (std::cin >> choice && choice >= 1 && choice <= 3) {
                break;
            } else {
                std::cout << "Focus, " << name << "! Choose a valid move (1-3)." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        if (choice == 3) {
            if (moveCount >= 2) {
                std::cout << name << " uses [GROUND SLAM]!" << std::endl; // Attacks Enemy
                enemy->setSkip(true); // Stuns Enemy
            }

            else {
                std::cout << "\nSpecial not ready! (Requires 2 turns of combat first)" << std::endl;
                std::cout << name << " uses [WOOKIE SMASH] instead!" << std::endl;
                enemy->takeDamage(wookieeSmash());
            }
        }
        else if (choice == 2) {
            roarIntimidate(enemy);
        }
        else {
            enemy->takeDamage(wookieeSmash());
        }
    }

    else if (race == 1) { // Human
        std::cout << "1: LIGHTSABER STRIKE [Power: " << basePower << "]: A precise slash." << std::endl;
        std::cout << "2: FORCE PUSH [Utility]: Uses the Force to stagger the enemy. skipping their turn." << std::endl;
        std::cout << "3: [SPECIAL] ASSURED STRIKE: An unblockable hit that lowers enemy Defense." << std::endl;
        std::cout << "----------------------------------------" << std::endl;

        while (true) {
            std::cout << "\n" << name << " chooses: ";
            if (std::cin >> choice && choice >= 1 && choice <= 3) {
                break;
            } else {
                std::cout << "Focus, " << name << "! Choose a valid move (1-3)." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        if (choice == 3) {
            if (moveCount >= 2) {
                std::cout << name << " uses [ASSURED STRIKE]! Enemy defense fell!" << std::endl;
                enemy->setDefense(enemy->getDefense() - 5); // Lower Defense
                enemy->takeDamage(basePower); // Guaranteed hit
            }
            else {
                std::cout << "\nSpecial not ready! (Requires 2 turns of combat first)" << std::endl;
                std::cout << name << " uses [LIGHTSABER STRIKE] instead!" << std::endl;
                enemy->takeDamage(lightsaberStrike());
            }
        }
        else if (choice == 2) {
            forcePush(enemy);
        }
        else {
            enemy->takeDamage(lightsaberStrike());
        }
    }

    else if (race == 2) { //Android
        std::cout << "1: BLASTER SHOT [Power: " << basePower << "]: High-velocity energy bolt." << std::endl;
        std::cout << "2: ENERGY SHIELD [Utility]: Recalibrates armor to increase your Defense" << std::endl;
        std::cout << "3: SENTRY DROIDS [SPECIAL] : Deploy droids for a double-attack barrage." << std::endl;
        std::cout << "----------------------------------------" << std::endl;

        while (true) {
            std::cout << "\n" << name << " chooses: ";
            if (std::cin >> choice && choice >= 1 && choice <= 3) {
                break;
            } else {
                std::cout << "Focus, " << name << "! Choose a valid move (1-3)." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        if (choice == 3) {
            if (moveCount >= 2) {
                std::cout << name << " deploys [Sentry Droids]" << std::endl;
                enemy->takeDamage(dealDamage()); // Hit 1
                std::cout << name << " Hits once!" << std::endl;
                enemy->takeDamage(dealDamage()); // Hit 2
                std::cout << name << " Hits twice!" << std::endl;
                enemy->setAttack(enemy->getAttack() - 2); // Lower Attack
                std::cout << "Enemy attack is lowered" << std::endl;
            }
            else {
                std::cout << "\nSpecial not ready! (Requires 2 turns of combat first)" << std::endl;
                std::cout << name << " uses [BLASTER SHOT] instead!" << std::endl;
                enemy->takeDamage(blasterShot());
            }
        }
        else if (choice == 2) {
            energyShield();
        }
        else {
            enemy->takeDamage(blasterShot());
        }
    }
}

