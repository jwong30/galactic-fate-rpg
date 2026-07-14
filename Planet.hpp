///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 14a - Let the Battle Begin! (Containers) - ECE 205 - Spring 2026
//
/// @file    Planet.hpp
/// @authors James Wong, Lenard Cabero, Nahyun Koo
///////////////////////////////////////////////////////////////////////////////

#ifndef PLANET_HPP
#define PLANTER_HPP

#include <string>
#include "PlayerCharacter.hpp"

class Planet {
private:
    std::string planetName;
    std::string episodeTitle;
    std::string description;
    std::string mission;
    std::string enemyName;

public:
    Planet(std::string name, std::string ep, std::string desc, std::string miss, std::string enemy);
    bool visit(PlayerCharacter* player);
    void handleMorality(PlayerCharacter* player);
};

#endif
