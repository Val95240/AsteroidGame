#ifndef HEADER_UPGRADES
#define HEADER_UPGRADES

#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "shapes.h"
#include "Hitbox.h"
#include "SpaceShip.h"


class Upgrade : public Hitbox
{
    public:
        Upgrade(int type, int x, int y);
        ~Upgrade();

        int getType() const;
        void activate(SpaceShip* boundShip);

        bool update();

    private:
        int type;
        sf::RectangleShape frame;
        std::vector<sf::ConvexShape> content;
        SpaceShip* ship;

        int time;

        virtual sf::Shape const* getShape() const;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
