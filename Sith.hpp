///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 13a - Let the Battle Begin! (Containers) - ECE 205 - Spring 2026
//
/// @file    Sith.hpp
/// @authors James Wong, Lenard Cabero, Nahyun Koo
///////////////////////////////////////////////////////////////////////////////

#ifndef SITH_HPP
#define SITH_HPP

#include "PlayerCharacter.hpp"

class Sith : public PlayerCharacter {

public:
    Sith(std::string& name, int race);
    void performAction(PlayerCharacter* enemy) override;
};

#endif
