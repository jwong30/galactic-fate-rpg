///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - Let the Battle Begin! (Containers) - ECE 205 - Spring 2026
//
/// @file    Planet.cpp
/// @authors James Wong, Lenard Cabero, Nahyun Koo
///////////////////////////////////////////////////////////////////////////////

#include "Planet.hpp"
#include "Battle.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

Planet::Planet(string name, string ep, string desc, string miss, string enemy)
    : planetName(name), episodeTitle(ep), description(desc), mission(miss), enemyName(enemy) {}

bool Planet::visit(PlayerCharacter* player) {
    cout << "\n\n\n====================================================" << endl;
    cout << "||             " << episodeTitle << "         ||" << endl;
    cout << "====================================================" << endl;

    delay(1500);
    cout << "\nLOCATION: " << planetName << endl;
    cout << "\nINTEL:   " << description << endl;
    cout << "\nMISSION: " << mission << "\n" << endl;

    player->resetHealth();
    return startBattle(player, enemyName, planetName);
}

void Planet::handleMorality(PlayerCharacter *player) {
    // Moral decision
    int finalChoice;
    cout << "\n===== BATTLE OUTCOME =====" << endl;
    cout << "[1] SPARE (+25 FP)" << endl;
    cout << "[2] FINISH OFF (-25 FP)" << endl;

    while (true) {
        cout << "Selection: ";
        if (cin >> finalChoice && finalChoice == 1 || finalChoice == 2) {
            break;
        } else {
            cout << "There is no middle ground. Choose 1 or 2." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    if (finalChoice == 1) {
        player->setMorality(player->getMorality() + 25);
        cout << "\nYou chose mercy. The Light Side grows stronger." << endl;

        if ((rand() % 100) < 30) {
            cout << "\n!!! BETRAYAL !!! The enemy strikes as you turn away!" << endl;
            player->takeDamage(100);
        }
    } else {
        player->setMorality(player->getMorality() - 25);
        cout << "\nYou strike them down. The Dark Side grows stronger." << endl;
    }
}


