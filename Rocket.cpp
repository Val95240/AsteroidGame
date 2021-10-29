#include "Rocket.hpp"

Rocket::Rocket(SpaceShip* originShip, int x, int y, double angle, double speedX, double speedY) :
    Weapon(originShip),
    accel(0.2), speedX(speedX), speedY(speedY), angleSpeed(0)
{
    rocket = generateRocketShape();
    rocket.move(x, y);
    rocket.rotate(angle);
}

Rocket::~Rocket()
{
}

int Rocket::getType() const
{
    return 1;
}

bool Rocket::valid() const
{
    sf::Vector2f pos = rocket.getPosition();
    return !(pos.x < -10 || settings::WIDTH+10 < pos.x || pos.y < -10 || settings::HEIGHT+10 < pos.y);
}

void Rocket::updateTarget(std::list<SpaceShip*>& ships)
{
    if (ships.size() == 0)
        return;

    sf::Vector2f minDistVect;
    double minDistSq = settings::WIDTH*settings::WIDTH + settings::HEIGHT*settings::HEIGHT;
    SpaceShip* closestShip = 0;
    for (SpaceShip* ship : ships)
    {
        if (ship->getTeam() != originShip->getTeam())
        {
            sf::Vector2f distVect = ship->getPosition() - rocket.getPosition();
            double distanceSq = distVect.x*distVect.x + distVect.y*distVect.y;
            if (distanceSq < minDistSq) {
                minDistSq = distanceSq;
                minDistVect = distVect;
                closestShip = ship;
            }
        }
    }

    if (!closestShip || (minDistVect.x == 0 && minDistVect.y == 0))
        return;

    double angleRocket = rocket.getRotation();
    double angleToShip = 90 - std::atan2(-minDistVect.y, minDistVect.x) * 180 / M_PI;
    double deltaAngle = (angleToShip - angleRocket);
    if (deltaAngle < -180)
        deltaAngle += 360;
    deltaAngle = std::min(5.0, std::max(-5.0, deltaAngle));

    rocket.rotate(deltaAngle);
}

void Rocket::update()
{
    double angle = rocket.getRotation();
    speedX += accel * std::sin(angle * M_PI / 180);
    speedY -= accel * std::cos(angle * M_PI / 180);

    double norm = speedX*speedX + speedY*speedY;
    double clippedNorm = std::min(10.0, std::max(-10.0, norm));
    speedX *= clippedNorm / norm;
    speedY *= clippedNorm / norm;

    rocket.move(speedX, speedY);
}

sf::Shape const* Rocket::getShape() const
{
    return &rocket;
}
