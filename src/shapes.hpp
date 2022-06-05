#ifndef HEADER_SHAPES
#define HEADER_SHAPES

#include <SFML/Graphics.hpp>
#include "Settings.hpp"
#include "utils.hpp"


sf::ConvexShape generateShipShape();
sf::ConvexShape generateAsteroidShape(int size);

sf::ConvexShape generateBulletShape();
sf::ConvexShape generateRocketShape();
sf::ConvexShape generateLaserShape(int length=-1);
sf::ConvexShape generateBombShape();

sf::ConvexShape generateHealthShape();
sf::ConvexShape generateShieldShape();
sf::ConvexShape generateSlowShape();
sf::ConvexShape generateStarShape();
sf::ConvexShape generateArrowShape();

#endif
