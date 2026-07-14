///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - Let the Battle Begin! (Containers) - ECE 205 - Spring 2026
//
/// @file    Battle.cpp
/// @authors James Wong, Lenard Cabero, Nahyun Koo
///////////////////////////////////////////////////////////////////////////////

#include "Battle.hpp"
#include "Jedi.hpp"
#include "Sith.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>

using namespace std;

// Moved Battle Code from Main

// Time delay function
void delay(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

// Start Battle
bool startBattle(PlayerCharacter* player, string enemyName, string planetName) {
    int enemyRace = rand() % 3;
    int enemyProfession = rand() % 2;

    PlayerCharacter* enemy;

    // Standard Enemy
    if (enemyProfession == 0) {
        enemy = new Jedi(enemyName, enemyRace);
    } else {
        enemy = new Sith(enemyName, enemyRace);
    }

    bool destinyTriggered = false;

    // Boss Stats
    if (enemyName == "Obi-Wan Kenobi" || enemyName == "Darth Vader") {
        enemy->setHealth(200);
        enemy->setAttack(18);
        enemy->setDefense(12);

        cout << "\n====================================================" << endl;
        if (enemyName == "Obi-Wan Kenobi") {
            cout << "[ BOSS ALERT ]: Obi-Wan Kenobi has the High Ground!" << endl;
            cout << "Obi-Wan: I will do what I must." << player->getName() << "..." << endl;
        } else if (enemyName == "Darth Vader") {
            cout << "\n[ BOSS ALERT ]: Darth Vader emerges from the shadows!" << endl;
            cout << "Darth Vader: The Force is with you " << player->getName() << "..." <<endl;
        }
        cout << "\n====================================================" << endl;
        enemy->printStats();
    } else {
        cout << "\nA " << enemyName << " appears on " << planetName << "!" << endl;
        enemy->printStats();
    }

    cout << "\n\n===== LET THE BATTLE BEGIN! =====" << endl;
    int round = 1;

    while (player->isAlive() && enemy->isAlive()) {
        cout << "\n\n==========[ ROUND " << round << " ]==========" << endl;

        if (!player->getSkip()) {
            cout << "\n[ Your Turn ]" << endl;
            cout << "[1] Attack" << endl;
            cout << "[2] Run Away" << endl;
            cout << "Selection: ";

            int battleChoice;
            cin >> battleChoice;

            if (battleChoice == 2) {
                if ((rand() % 100) < 30) {
                    cout << "\n" << player->getName() << " successfully fled the battle!" << endl;
                    delete enemy;
                    return false;
                }
                else {
                    cout << "\nEscape failed! " << enemyName << " blocks your path!" << endl;
                    player->setSkip(false);
                }
            } else {
                player->performAction(enemy);
                player->incrementMoveCount();
            }
        } else {
            cout << "\n" << player->getName() << " is staggered and skips their turn." << endl;
            player->setSkip(false);
        }

        if (!enemy->isAlive()) break;

        // Enemy Attacks with Boss Moves
        if (!enemy->getSkip()) {
            cout << "\n\n[ " << enemyName << "'s Turn ]" << endl;
            enemy->incrementMoveCount();

            if (enemyName == "Obi-Wan Kenobi") {
                cout << "Obi-Wan Kenobi uses [SORESU STRIKE]!" << endl;
            }
            else if (enemyName == "Darth Vader") {
                cout << "Darth Vader uses [FORCE CRUSH]!" << endl;
            }
            else {
                cout << enemy->getName() << " attacks!" << endl;
            }

            player->takeDamage(enemy->dealDamage());
        } else {
            cout << "\n" << enemy->getName() << " is staggered and skips their turn!" << endl;
            enemy->setSkip(false);
        }

        if (!destinyTriggered && player->getHealth() <= 30 && player->isAlive()
            && (enemyName == "Obi-Wan Kenobi" || enemyName == "Darth Vader")) {

            destinyTriggered = true;
            cout << "\n[ !!! MOMENT OF DESTINY !!! ]" << endl;
            int choice;
            if (enemyName == "Obi-Wan Kenobi") {
                cout << "Obi-Wan: It's over! I have the high ground!" << endl;
                cout << "[1] \"Obi-Wan, forgive me...\" (Return to Light)" << endl;
                cout << "[2] \"I HATE YOU!\" (SECOND WIND- Dark Side: +50 HP, +10 ATK)" << endl;
                while (!(cin >> choice) || (choice < 1 || choice > 2)) {
                    cout << "Choose 1 or 2: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                if (choice == 1) {
                    player->setMorality(100);
                    cout << "\nYou cast aside your anger. The Light returns." << endl;
                } else {
                    int h = player->getHealth() + 50;
                    player->setHealth(h > 100 ? 100 : h);
                    player->setAttack(player->getAttack() + 10);
                    cout << "\n\"YOU WERE THE CHOSEN ONE!\" Obi-Wan cries out as your rage heals you!" << endl;
                }
            } else {
                cout << "Vader: Join me, and together we can rule the galaxy as father and son!" << endl;
                cout << "[1] \"I am a Jedi, like my father before me!\" (SECOND WIND- Light Side: +50 HP, +10 DEF)" << endl;
                cout << "[2] \"I will join you, Master.\" (Fall to Darkness)" << endl;
                while (!(cin >> choice) || (choice < 1 || choice > 2)) {
                    cout << "Choose 1 or 2: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                if (choice == 2) {
                    player->setMorality(0);
                    cout << "\n\"Good. Your journey towards the Dark Side is complete\"" << endl;
                } else {
                    int h = player->getHealth() + 50;
                    player->setHealth(h > 100 ? 100 : h);
                    player->setAttack(player->getAttack() + 10);
                    cout << "\n\"So be it...Jedi.\" Vader prepares for your final stand!" << endl;
                }
            }

    }

        delay(1000);
        cout << "\n----- Current Health -----" << endl;
        cout << player->getName() << ": " << player->getHealth() << endl;
        cout << enemy->getName() << ": " << enemy->getHealth() << endl;

        round++;
    }

    bool playerWon = player->isAlive();
    delete enemy;
    return playerWon;
}
