#include "Asteroid.hpp"
#include "World.hpp"

Asteroid::Asteroid(World* world, int x, int y, int size) : FlyingObject(1, 10+20*size),
    world(world),  size(size)
{
    do {
        speedX = fRand(-2, 2);
        speedY = fRand(-2, 2);
    } while (speedX*speedX + speedY*speedY < 3);
    angleSpeed = fRand(-5, 5);

    shape = generateAsteroidShape(size);
    shape.move(x, y);
}

Asteroid::~Asteroid()
{
    if (size > 1) {
        sf::Vector2f pos = shape.getPosition();
        Asteroid* newAst = new Asteroid(world, pos.x, pos.y, size-1);
        newAst->speedX = -speedY;
        newAst->speedY = speedX;
        world->addAsteroid(newAst);

        newAst = new Asteroid(world, pos.x, pos.y, size-1);
        newAst->speedX = speedY;
        newAst->speedY = -speedX;
        world->addAsteroid(newAst);
    }
}

int Asteroid::getDamage() const
{
    return size;
}
