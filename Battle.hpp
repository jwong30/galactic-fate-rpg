///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - Let the Battle Begin! (Containers) - ECE 205 - Spring 2026
//
/// @file    Battle.hpp
/// @authors James Wong, Lenard Cabero, Nahyun Koo
///////////////////////////////////////////////////////////////////////////////

#ifndef BATTLE_HPP
#define BATTLE_HPP

#include <string>
#include "PlayerCharacter.hpp"

// Time delay
void delay(int milliseconds);

// Battle loop
bool startBattle(PlayerCharacter* player, std::string enemyName, std::string planetName);

#endif
