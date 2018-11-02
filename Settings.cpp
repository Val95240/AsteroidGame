#include "Settings.h"

namespace settings
{
    int HITBOX = false;

    int NB_PLAYERS = 1;
    int TEAMS[4] = {0, 1, 2, 3};
    int FRIENDLY_FIRE = false;
    int SHIP_LIFE = 5;

    int AST_DENSITY = 0;
    int AUTH_WEAP[NB_WEAPONS] = { true, true, true, true };
    int UPG_DENSITY = 3;
    double PROBA_UPGRADES[NB_UPGRADES] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    int UP_KEY[4] = {sf::Keyboard::Up, sf::Keyboard::W, sf::Keyboard::Unknown, sf::Keyboard::Unknown};
    int DOWN_KEY[4] = {sf::Keyboard::Down, sf::Keyboard::S, sf::Keyboard::Unknown, sf::Keyboard::Unknown};
    int LEFT_KEY[4] = {sf::Keyboard::Left, sf::Keyboard::A, sf::Keyboard::Unknown, sf::Keyboard::Unknown};
    int RIGHT_KEY[4] = {sf::Keyboard::Right, sf::Keyboard::D, sf::Keyboard::Unknown, sf::Keyboard::Unknown};
    int FIRE_KEY[4][NB_WEAPONS] = {{sf::Keyboard::F, sf::Keyboard::R, sf::Keyboard::T, sf::Keyboard::G},
                                   {sf::Keyboard::Space, sf::Keyboard::C, sf::Keyboard::V, sf::Keyboard::B},
                                   {sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown},
                                   {sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown, sf::Keyboard::Unknown}};

    int EXIT = false;
}
