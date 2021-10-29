#include "shapes.hpp"

sf::ConvexShape generateShipShape()
{
    sf::ConvexShape ship;
    ship.setPointCount(4);
    ship.setPoint(0, sf::Vector2f(0, 0));
    ship.setPoint(1, sf::Vector2f(-20, 10));
    ship.setPoint(2, sf::Vector2f(0, -40));
    ship.setPoint(3, sf::Vector2f(20, 10));
    ship.setOrigin(0, -10);
    return ship;
}

sf::ConvexShape generateAsteroidShape(int size)
{
    sf::ConvexShape ast;
    int nbEdges = (int) fRand(4+2*size, 6+2*size);
    ast.setPointCount(nbEdges);

    int angles[nbEdges] = {0};
    generateArray(angles+1, nbEdges, 1, 359, true);
    std::sort(angles, angles+nbEdges);

    int edges[nbEdges] = {0};
    generateArray(edges, nbEdges, 10+10*size, 20+20*size, false);

    for (int i=0; i<nbEdges; ++i) {
        double pointX = edges[i] * std::sin((double) angles[i] * M_PI / 180);
        double pointY = -1 *edges[i] * std::cos((double) angles[i] * M_PI / 180);
        ast.setPoint(i, sf::Vector2f(pointX, pointY));
    }
    return ast;
}

sf::ConvexShape generateBulletShape()
{
    sf::ConvexShape bullet;
    bullet.setPointCount(8);
    bullet.setPoint(0, sf::Vector2f(0, -4));
    bullet.setPoint(1, sf::Vector2f(3, -3));
    bullet.setPoint(2, sf::Vector2f(4, 0));
    bullet.setPoint(3, sf::Vector2f(3, 3));
    bullet.setPoint(4, sf::Vector2f(0, 4));
    bullet.setPoint(5, sf::Vector2f(-3, 3));
    bullet.setPoint(6, sf::Vector2f(-4, 0));
    bullet.setPoint(7, sf::Vector2f(-3, -3));
    return bullet;
}

sf::ConvexShape generateRocketShape()
{
    sf::ConvexShape rocket;
    rocket.setPointCount(11);
    rocket.setPoint(0, sf::Vector2f(-3, 9));
    rocket.setPoint(1, sf::Vector2f(-6, 14));
    rocket.setPoint(2, sf::Vector2f(-6, 3));
    rocket.setPoint(3, sf::Vector2f(-3, 1));
    rocket.setPoint(4, sf::Vector2f(-3, -11));
    rocket.setPoint(5, sf::Vector2f(0, -14));
    rocket.setPoint(6, sf::Vector2f(3, -11));
    rocket.setPoint(7, sf::Vector2f(3, 1));
    rocket.setPoint(8, sf::Vector2f(6, 3));
    rocket.setPoint(9, sf::Vector2f(6, 14));
    rocket.setPoint(10, sf::Vector2f(3, 9));
    return rocket;
}

sf::ConvexShape generateLaserShape(int length)
{
    sf::ConvexShape laser;
    int size = (length < 0 ? settings::WIDTH + settings::HEIGHT : length);

    laser.setPointCount(4);
    laser.setPoint(0, sf::Vector2f(-5, 0));
    laser.setPoint(1, sf::Vector2f(-5, -size));
    laser.setPoint(2, sf::Vector2f(5, -size));
    laser.setPoint(3, sf::Vector2f(5, 0));

    if (length > 0)
        laser.setOrigin(0, -length/2);
    return laser;
}

sf::ConvexShape generateBombShape()
{
    sf::ConvexShape bomb;
    bomb.setPointCount(19);
    bomb.setPoint(0, sf::Vector2f(8, -14));
    bomb.setPoint(1, sf::Vector2f(2, -8));
    bomb.setPoint(2, sf::Vector2f(6, -2));
    bomb.setPoint(3, sf::Vector2f(8, 2));
    bomb.setPoint(4, sf::Vector2f(10, 6));
    bomb.setPoint(5, sf::Vector2f(8, 8));
    bomb.setPoint(6, sf::Vector2f(6, 10));
    bomb.setPoint(7, sf::Vector2f(4, 12));
    bomb.setPoint(8, sf::Vector2f(2, 13));
    bomb.setPoint(9, sf::Vector2f(0, 14));
    bomb.setPoint(10, sf::Vector2f(-2, 13));
    bomb.setPoint(11, sf::Vector2f(-4, 12));
    bomb.setPoint(12, sf::Vector2f(-6, 10));
    bomb.setPoint(13, sf::Vector2f(-8, 8));
    bomb.setPoint(14, sf::Vector2f(-10, 6));
    bomb.setPoint(15, sf::Vector2f(-8, 2));
    bomb.setPoint(16, sf::Vector2f(-6, -2));
    bomb.setPoint(17, sf::Vector2f(-2, -8));
    bomb.setPoint(18, sf::Vector2f(-8, -14));
    return bomb;
}

sf::ConvexShape generateHealthShape()
{
    sf::ConvexShape health;
    health.setPointCount(12);
    health.setPoint(0, sf::Vector2f(4, -12));
    health.setPoint(1, sf::Vector2f(4, -4));
    health.setPoint(2, sf::Vector2f(12, -4));
    health.setPoint(3, sf::Vector2f(12, 4));
    health.setPoint(4, sf::Vector2f(4, 4));
    health.setPoint(5, sf::Vector2f(4, 12));
    health.setPoint(6, sf::Vector2f(-4, 12));
    health.setPoint(7, sf::Vector2f(-4, 4));
    health.setPoint(8, sf::Vector2f(-12, 4));
    health.setPoint(9, sf::Vector2f(-12, -4));
    health.setPoint(10, sf::Vector2f(-4, -4));
    health.setPoint(11, sf::Vector2f(-4, -12));
    return health;
}

sf::ConvexShape generateShieldShape()
{
    sf::ConvexShape shield;
    shield.setPointCount(7);
    shield.setPoint(0, sf::Vector2f(12, -12));
    shield.setPoint(1, sf::Vector2f(12, -4));
    shield.setPoint(2, sf::Vector2f(8, 5));
    shield.setPoint(3, sf::Vector2f(0, 12));
    shield.setPoint(4, sf::Vector2f(-8, 5));
    shield.setPoint(5, sf::Vector2f(-12, -4));
    shield.setPoint(6, sf::Vector2f(-12, -12));
    return shield;
}

sf::ConvexShape generateSlowShape()
{
    sf::ConvexShape slow;
    slow.setPointCount(7);
    slow.setPoint(0, sf::Vector2f(-12, 0));
    slow.setPoint(1, sf::Vector2f(-1, -12));
    slow.setPoint(2, sf::Vector2f(-1, -3));
    slow.setPoint(3, sf::Vector2f(10, -12));
    slow.setPoint(4, sf::Vector2f(10, 12));
    slow.setPoint(5, sf::Vector2f(-1, 3));
    slow.setPoint(6, sf::Vector2f(-1, 12));
    return slow;
}

sf::ConvexShape generateStarShape()
{
    sf::ConvexShape star;
    star.setPointCount(10);
    star.setPoint(0, sf::Vector2f(0, -14));
    star.setPoint(1, sf::Vector2f(3, -4));
    star.setPoint(2, sf::Vector2f(12, -4));
    star.setPoint(3, sf::Vector2f(6, 3));
    star.setPoint(4, sf::Vector2f(9, 12));
    star.setPoint(5, sf::Vector2f(0, 6));
    star.setPoint(6, sf::Vector2f(-9, 12));
    star.setPoint(7, sf::Vector2f(-6, 3));
    star.setPoint(8, sf::Vector2f(-12, -4));
    star.setPoint(9, sf::Vector2f(-3, -4));
    return star;
}

sf::ConvexShape generateArrowShape()
{
    sf::ConvexShape arrow;
    arrow.setPointCount(7);
    arrow.setPoint(0, sf::Vector2f(6, 0));
    arrow.setPoint(1, sf::Vector2f(0, 4));
    arrow.setPoint(2, sf::Vector2f(0, 2));
    arrow.setPoint(3, sf::Vector2f(-5, 2));
    arrow.setPoint(4, sf::Vector2f(-5, -2));
    arrow.setPoint(5, sf::Vector2f(0, -2));
    arrow.setPoint(6, sf::Vector2f(0, -4));
    return arrow;
}
