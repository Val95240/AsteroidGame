#ifndef HEADER_BOMB
#define HEADER_BOMB

#include <cmath>
#include <list>
#include <SFML/Graphics.hpp>

#include "Weapon.hpp"


class Bomb : public Weapon
{
    public:
        Bomb(SpaceShip* originShip, int x, int y);
        virtual ~Bomb();

        virtual int getType() const;

        virtual bool hit(int damage);

        virtual bool valid() const;
        virtual void update();

    private:
        int time;
        sf::CircleShape bomb;

        virtual sf::Shape const* getShape() const;
};

#endif
