#ifndef HEADER_WORLD
#define HEADER_WORLD

#include <list>
#include <set>
#include <vector>
#include <algorithm>

#include <SFML/Graphics.hpp>
#include "Settings.hpp"
#include "utils.hpp"
#include "shapes.hpp"
#include "GamePhase.hpp"
#include "MainMenu.hpp"
#include "Menu.hpp"
#include "ScoreMenu.hpp"
#include "SpaceShip.hpp"
#include "Asteroid.hpp"
#include "Upgrade.hpp"


class World : public GamePhase
{
    public:

        World();
        virtual ~World();
        void addShip();
        void addAsteroid(int size);
        void addAsteroid(Asteroid* newAsteroid);
        void addUpgrade();

        virtual void press(sf::Keyboard::Key);
        virtual bool update();
        virtual GamePhase* getNextPhase() const;

    private:
        int exit;
        int pause;
        Menu pauseMenu;

        int nbShip;
        int nbTeam;
        int scores[4] = {0};
        sf::Font font;
        std::vector<sf::Text> textScores;
        std::vector<sf::ConvexShape> weaponThumbnails;

        int asteroidCooldown;
        int upgradeCooldown;

        std::list<SpaceShip*> ships;
        std::list<Asteroid*> asteroids;
        std::list<Upgrade*> inactiveUpgrades;
        std::list<Upgrade*> activeUpgrades;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
