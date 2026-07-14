# Galactic Fate

Galactic Fate is a text-based C++ role-playing game built as a three-person final project for ECE 205. The game features turn-based combat, morality-based decisions, JSON-driven game data, character-specific abilities, and branching outcomes.

## My Contributions

My main contributions included:

- Combat system
- Morality system
- JSON game data
- Approximately half of the class files
- Character abilities, battle flow, and decision-based outcomes

## Features

- Turn-based battles
- Player and enemy character classes
- Character-specific abilities
- JSON-based story and game data
- Morality choices that affect the ending
- Multiple encounters and boss fights

## Technologies

- C++
- JSON
- Object-oriented programming
- Inheritance and polymorphism
- Dynamic memory management

## Team

Built with a three-person team for ECE 205.

Team members:

- James Wong
- Lenard Cabero
- Nahyun Koo

## How to Run

This project uses the single-header `nlohmann/json` library included in the repository as `json.hpp`. The game also expects `galactic.json` to be in the same directory as the executable when it runs.

Compile from the project root:

```bash
g++ -std=c++11 main.cpp Battle.cpp GameCharacter.cpp Jedi.cpp Planet.cpp PlayerCharacter.cpp Sith.cpp -o game
```

Run on macOS/Linux:

```bash
./game
```

On Windows with MinGW or another compatible `g++` toolchain, compile and run with:

```powershell
g++ -std=c++11 main.cpp Battle.cpp GameCharacter.cpp Jedi.cpp Planet.cpp PlayerCharacter.cpp Sith.cpp -o game.exe
.\game.exe
```

## Notes

This public repository is a cleaned portfolio version of the original course project. It does not include the private repository history.
