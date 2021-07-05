#include "Weapon.h"
#include "SpaceShip.h"

Weapon::Weapon(SpaceShip* originShip) : originShip(originShip)
{
}

Weapon::~Weapon()
{
}

void Weapon::updateTarget(std::list<SpaceShip*>& ships)
{
}

bool Weapon::updateHits(std::list<SpaceShip*>& ships)
{
    for (std::list<SpaceShip*>::iterator it=ships.begin(); it != ships.end(); ++it)
    {
        SpaceShip* ship = *it;
        if (ship != originShip && (settings::FRIENDLY_FIRE || ship->getTeam() != originShip->getTeam())) {

            if(ship->weaponCollision(this))
                return true;

            if (Hitbox::intersects(this, ship)) {
                int points;
                if (ship->hit(this->getDamage())) {
                    delete ship;
                    it = ships.erase(it);
                    --it;
                    points = 500;
                } else {
                    points = 100;
                }
                originShip->addScore((ship->getTeam() != originShip->getTeam() ? points : -points));

                if (hit(1))
                    return true;
            }
        }
    }
    return false;
}

bool Weapon::updateHits(std::list<Asteroid*>& asteroids)
{
    for (std::list<Asteroid*>::iterator it=asteroids.begin(); it != asteroids.end(); ++it)
    {
        Asteroid* ast = *it;
        if (Hitbox::intersects(this, ast)) {
            if (ast->hit(this->getDamage())) {
                delete ast;
                it = asteroids.erase(it);
                --it;
                originShip->addScore(100);
            } else {
                originShip->addScore(50);
            }

            if (hit(1))
                return true;
        }
    }
    return false;
}
