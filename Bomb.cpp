#include "Bomb.hpp"

Bomb::Bomb(SpaceShip* originShip, int x, int y) :
    Weapon(originShip),
    time(1), bomb(1, 70)
{
    bomb.setOrigin(1, 1);
    bomb.setOutlineThickness(4);
    bomb.setFillColor(sf::Color::Transparent);
    bomb.move(x, y);
}

Bomb::~Bomb()
{
}

int Bomb::getType() const
{
    return 3;
}

bool Bomb::hit(int damage)
{
    return false;
}

bool Bomb::valid() const
{
    return (time < 150);
}

void Bomb::update()
{
    bomb.setRadius(++time*2);
    bomb.move(-2, -2);
}

sf::Shape const* Bomb::getShape() const
{
    return &bomb;
}
