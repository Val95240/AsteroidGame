#ifndef HEADER_LASER
#define HEADER_LASER

#include <SFML/Graphics.hpp>
#include "shapes.h"
#include "Weapon.h"


class Laser : public Weapon
{
    public:
        Laser(SpaceShip* originShip, int x, int y, double angle);
        virtual ~Laser();

        virtual int getType() const;

        virtual bool hit(int damage);

        virtual bool valid() const;
        virtual void update();

    private:
        sf::ConvexShape laser;
        int turn;

        virtual sf::Shape const* getShape() const;
};

#endif
