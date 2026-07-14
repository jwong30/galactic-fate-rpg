///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab 13a - Let the Battle Begin! (Containers) - ECE 205 - Spring 2026
//
/// @file    Jedi.hpp
/// @authors James Wong, Lenard Cabero, Nahyun Koo
///////////////////////////////////////////////////////////////////////////////

#ifndef JEDI_HPP
#define JEDI_HPP

#include "PlayerCharacter.hpp"

class Jedi : public PlayerCharacter {

public:
    Jedi(std::string& name, int race);
    void performAction(PlayerCharacter* enemy) override;
};

#endif

