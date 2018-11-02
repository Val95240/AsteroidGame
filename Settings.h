#ifndef SETTINGS
#define SETTINGS

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

namespace settings
{
    int const WIDTH = 800;
    int const HEIGHT = 800;
    int const NB_WEAPONS = 4;
    int const NB_UPGRADES = 10;

    std::string const FONT_FILE = "arial.ttf";
    std::string const NAME[101] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "Num0", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9", "<Escape>", "<LControl>", "<LShift>", "<LAlt>", "<LSystem>", "<RControl>", "<RShift>", "<RAlt>", "<RSysten>", "<Menu>", "(", ")", ":", ",", ".", "\"", "/", "\\", "~", "=", "-", "<Space>", "<Enter>", "<Backspace>", "<Tab>", "<PageUp>", "<PageDown>", "<End>", "<Home>", "<Insert>", "<Delete>", "<Add>", "<Substract>", "<Multiply>", "<Divide>", "<Left>", "<Right>", "<Up>", "<Down>", "NumPag0", "Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5", "Numpad6", "Numpad7", "Numpad8", "Numpad9", "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>", "<F11>", "<F12>", "<F13>", "<F14>", "<F15>", "<Pause>"};
    sf::Color const TEAM_COLORS[4] = {sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow};
    sf::Color const COLORS[8] = {sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::White, sf::Color::Magenta, sf::Color::Cyan, sf::Color::Black};

    extern int HITBOX;

    extern int NB_PLAYERS;
    extern int TEAMS[4];
    extern int FRIENDLY_FIRE;
    extern int SHIP_LIFE;

    extern int AST_DENSITY;
    extern int AUTH_WEAP[NB_WEAPONS];
    extern int UPG_DENSITY;
    extern double PROBA_UPGRADES[NB_UPGRADES];

    extern int UP_KEY[4];
    extern int DOWN_KEY[4];
    extern int LEFT_KEY[4];
    extern int RIGHT_KEY[4];
    extern int FIRE_KEY[4][NB_WEAPONS];

    extern int EXIT;
}

#endif
