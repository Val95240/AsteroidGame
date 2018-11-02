#include "Laser.h"

Laser::Laser(SpaceShip* originShip, int x, int y, double angle) :
    Weapon(originShip), turn(0)
{
    laser = generateLaserShape();
    laser.setPosition(x, y);
    laser.rotate(angle);
}

Laser::~Laser()
{
}

int Laser::getType() const
{
    return 2;
}

bool Laser::hit(int damage)
{
    return false;
}

bool Laser::valid() const
{
    return (turn < 2);
}

void Laser::update()
{
    ++turn;
}

sf::Shape const* Laser::getShape() const
{
    return &laser;
}
