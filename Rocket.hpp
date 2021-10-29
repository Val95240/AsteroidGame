#ifndef HEADER_ROCKET
#define HEADER_ROCKET

#include <cmath>
#include <list>

#include <SFML/Graphics.hpp>
#include "shapes.hpp"
#include "Weapon.hpp"
#include "SpaceShip.hpp"


class Rocket : public Weapon
{
    public:
        Rocket(SpaceShip* originShip, int x, int y, double angle, double speedX, double speedY);
        virtual ~Rocket();

        virtual int getType() const;

        virtual bool valid() const;
        virtual void updateTarget(std::list<SpaceShip*>& ships);
        virtual void update();

    private:
        double accel;
        double speedX, speedY, angleSpeed;
        sf::ConvexShape rocket;

        virtual sf::Shape const* getShape() const;
};

#endif
