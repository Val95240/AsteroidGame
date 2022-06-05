#include "Bullet.hpp"

Bullet::Bullet(SpaceShip* originShip, int x, int y, double angle, double speedX, double speedY) :
    Weapon(originShip),
    speedX(speedX), speedY(speedY), angle(angle), bullet(3, 100)
{
    bullet.setOrigin(3, 3);
    bullet.move(x, y);
    bullet.rotate(angle);
}

Bullet::~Bullet()
{
}

int Bullet::getType() const
{
    return 0;
}

bool Bullet::valid() const
{
    sf::Vector2f pos = bullet.getPosition();
    return !(pos.x < 0 || settings::WIDTH < pos.x || pos.y < 0 || settings::HEIGHT < pos.y);
}

void Bullet::update()
{
    bullet.move(speedX, speedY);
}

sf::Shape const* Bullet::getShape() const
{
    return &bullet;
}

std::vector<sf::Vector2f> Bullet::getPoints() const
{
    sf::Vector2f pos = bullet.getPosition();
    std::vector<sf::Vector2f> points;
    points.push_back(sf::Vector2f(pos.x-3, pos.y-3));
    points.push_back(sf::Vector2f(pos.x+3, pos.y-3));
    points.push_back(sf::Vector2f(pos.x+3, pos.y+3));
    points.push_back(sf::Vector2f(pos.x-3, pos.y+3));
    return points;
}
