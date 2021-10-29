#ifndef HEADER_BULLET
#define HEADER_BULLET

#include <list>

#include <SFML/Graphics.hpp>
#include "Weapon.hpp"


class Bullet : public Weapon
{
    public:
        Bullet(SpaceShip* originShip, int x, int y, double angle, double speedX, double speedY);
        virtual ~Bullet();

        virtual int getType() const;

        virtual bool valid() const;
        virtual void update();

    private:
        double speedX, speedY, angle;
        sf::CircleShape bullet;

        virtual sf::Shape const* getShape() const;
        virtual std::vector<sf::Vector2f> getPoints() const;
};

#endif
