///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - Let the Battle Begin! (Containers) - ECE 205 - Spring 2026
//
/// @file    main.cpp
/// @authors James Wong, Lenard Cabero, Nahyun Koo
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

#include "PlayerCharacter.hpp"
#include "Jedi.hpp"
#include "Sith.hpp"
#include "Planet.hpp"
#include "Battle.hpp"


// adding json file 
#include <fstream> 
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

int main() {
    srand(time(0));
    string characterName;
    int characterRace;
    int characterProfession;

    // 1. Introduction
    cout << "\n------------------------------------------------------------" << endl;
    cout << "       A long time ago in a galaxy far, far away..." << endl;
    delay(2000);
    cout << "\n         GALACTIC FATE: PATHS OF THE FORCE!" << endl;
    cout << "\n------------------------------------------------------------" << endl;

    cout << "\n[ Press Enter to Begin Your Journey ]" << endl;
    cin.get();

    // 2. Character Creation
    cout << "\nIdentify yourself, traveler (Name): ";
    getline(cin >> ws, characterName);

    cout << "\n================ SELECT YOUR RACE ================" << endl;
    cout << "[0] WOOKIEE:   Mighty warriors known for incredible strength and loyalty." << endl;
    cout << "[1] HUMAN:     Versatile and balanced, with a natural affinity for the Force." << endl;
    cout << "[2] ANDROID:   Highly logical and durable, utilizing advanced technology." << endl;
    cout << "========================================================\n" << endl;

    // Race Input

int createMode;
cout << "1. Manual Character Creation\n2. Load Character from JSON\nSelection: ";
cin >> createMode;

 if (createMode == 2) {
    ifstream f("galactic.json");

    if (!f.is_open()) {
        cout << "Error: Could not open galactic.json." << endl;
        return 1;
    }

    json data = json::parse(f);

    characterName = data["default_character"]["name"].get<string>();
    characterRace = data["default_character"]["race"].get<int>();
    characterProfession = data["default_character"]["profession"].get<int>();

    cout << "Character loaded from JSON: " << characterName << endl;
 } else {
    // 기존의 manual 입력 코드 (이름, 종족, 진영 선택)
     while (true) {
        cout << "Select Race (0-2): ";
        if (cin >> characterRace && characterRace >= 0 && characterRace <= 2) {
            break;
        } else {
            cout << "Invalid selection. Please enter 0, 1, or 2." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }



      cout << "\n\n================ SELECT YOUR ALIGNMENT ================" << endl;
    cout << "[0] JEDI:  Guardians of peace, following the Light Side of the Force." << endl;
    cout << "[1] SITH:  Seekers of power, fueled by the Dark Side of the Force." << endl;
    cout << "=========================================================\n" << endl;

    // Path Input
    while (true) {
        cout << "Select Path (0-1): ";
        if ((cin >> characterProfession) && (characterProfession == 0 || characterProfession == 1)) {
            break;
        } else {
            cout << "Invalid selection. Please enter [0] Jedi or [1] Sith." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}


   

    PlayerCharacter* player;

    if (characterProfession == 0) {
        player = new Jedi(characterName, characterRace);
    } else {
        player = new Sith(characterName, characterRace);
    }

    // 3. Holocron Training
    cout << "\n\n[ ACCESSING HOLOCRON TRAINING... ]" << endl;
    delay(1000);
    cout << "\n============================================================" << endl;
    cout << "                   COMBAT RULES AND DATA                    " << endl;
    cout << "============================================================" << endl;
    cout << "1. ATTACKING:  Damage is (Base Power + Ability) * Dice Roll." << endl;
    cout << "2. DICE ROLLS: Range from 1 (Miss) to 5 (150% Critical Hit)." << endl;
    cout << "3. SPECIALS:   Move 3 requires 2 turns of energy to charge." << endl;
    cout << "4. VICTORY:    Reduced enemy health to 0 to survive." << endl;
    cout << "5. MORALITY:   Sparing enemies increases Force Points (Light Side)." << endl;
    cout << "               Finishing off decreases Force Points (Dark Side)." << endl;
    cout << "============================================================\n" << endl;


    cout << "Press Enter to initialize teleport...";
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    cin.get();

    cout << "\nInitializing transmission..." << endl;
    delay(1000);
    cout << "Transporting " << characterName << " to the Outer Rim..." << endl;

    // 4. Display Stats
    cout << "\n\nYour character data:" << endl;
    player->printStats();

    // 5. Galaxy Container
    vector<Planet> galaxy;

    //json
    ifstream f_galaxy("galactic.json");
    json data = json::parse(f_galaxy);

    for (auto& ep : data["galaxy_episodes"]) {
        galaxy.push_back(Planet(
            ep["planet"].get<string>(), 
            ep["episode"].get<string>(), 
            ep["intel"].get<string>(), 
            ep["mission"].get<string>(), 
            ep["enemy"].get<string>()
        ));
    }

    for (size_t i = 0; i < galaxy.size(); ++i) {
        if (!galaxy[i].visit(player) || !player->isAlive()) {
            cout << "\nYour journey ends here. GAME OVER." << endl;
            delete player;
            return 0;
        }

        galaxy[i].handleMorality(player);

        if (!player->isAlive()) {
            cout << "\nBetrayal took your life. GAME OVER." << endl;
            delete player;
            return 0;
        }

        if (i < galaxy.size() - 1) {
            cout << "\n[ Please Enter to Jump to Hyperspace ]" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    // 6. Final Boss
    if (player->isAlive()) {
        int FP = player->getMorality();
        string bossName = "";

        if (FP <= 0) bossName = "Obi-Wan Kenobi";
        else if (FP >= 100) bossName = "Darth Vader";

        if (bossName != "") {
            cout << "\n[!] A powerful presence approaches..." << endl;
            player->resetHealth();

            if (!startBattle(player, bossName, "The Final Duel")) {
                    cout << "\n========================================" << endl;
                    if (bossName == "Obi-Wan Kenobi") {
                        cout << "Obi-Wan: You were the chosen one!" << endl;
                    } else {
                        cout << "Darth Vader: 'You are beaten." << endl;
                    }
                    delete player;
                    return 0;
                }
            }
        }

        // 7. Ending
        cout << "\n===== FINAL OUTCOME =====" << endl;
        cout << "Final Force Points: " << player->getMorality() << endl;

        if (player->getMorality() >= 75) {
            cout << "\nSTATUS: [LIGHT SIDE] - You have restored the Republic!" << endl;
        }
        else if (player->getMorality() <= 25) {
            cout << "\nSTATUS: [DARK SIDE] - You have founded the Galactic Empire!" << endl;
        }
        else {
            cout << "\nSTATUS: [NEUTRAL] - You walk the path of a Gray Jedi." << endl;
        }

        delete player;
        return 0;
    }

