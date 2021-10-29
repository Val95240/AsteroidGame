#ifndef HEADER_WEAPON
#define HEADER_WEAPON

#include <list>

#include <SFML/Graphics.hpp>
#include "Settings.hpp"
#include "Hitbox.hpp"
#include "Asteroid.hpp"

class SpaceShip;


class Weapon : public Hitbox
{
    public:
        Weapon(SpaceShip* originShip);
        virtual ~Weapon();

        virtual int getType() const = 0;

        virtual bool valid() const = 0;
        virtual void updateTarget(std::list<SpaceShip*>& ships);
        virtual void update() = 0;
        virtual bool updateHits(std::list<SpaceShip*>& ships);
        virtual bool updateHits(std::list<Asteroid*>& asteroids);

    protected:
        SpaceShip* originShip;
};

#endif
