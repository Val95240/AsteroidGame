#include "Upgrade.hpp"

Upgrade::Upgrade(int type, int x, int y) : type(type)
{
    frame.setSize(sf::Vector2f(30, 30));
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineThickness(2);

    switch (type)
    {
        case 0:
            content.push_back(generateRocketShape());
            content.back().rotate(45);
            time = 0;
            break;

        case 1:
            content.push_back(generateLaserShape(30));
            content.back().rotate(45);
            time = 0;
            break;

        case 2:
            content.push_back(generateBombShape());
            content.back().rotate(45);
            time = 0;
            break;

        case 3:
            content.push_back(generateHealthShape());
            time = 0;
            break;

        case 4:
            content.push_back(generateShieldShape());
            time = 0;
            break;

        case 5:
            content.push_back(generateSlowShape());
            time = 800;
            break;

        case 6:
            content.push_back(generateShipShape());
            content.back().scale(0.4, 0.4);
            content.back().rotate(45);
            content.back().move(-5, 5);
            for (int i=1; i<4; ++i) {
                content.push_back(generateBulletShape());
                content.back().scale(0.5, 0.5);
                content.back().move(4*i, -4*i);
            }
            time = 800;
            break;

        case 7:
            content.push_back(generateShipShape());
            content.back().scale(0.4, 0.2);
            content.back().rotate(-90);
            content.back().move(-5, 0);
            content.push_back(generateShipShape());
            content.back().scale(0.4, 0.2);
            content.back().rotate(90);
            content.back().move(5, 0);
            time = 800;
            break;

        case 8:
            content.push_back(generateShipShape());
            content.back().scale(0.3, 0.3);
            content.back().move(0, 5);
            content.push_back(generateArrowShape());
            content.back().move(8, -3);
            content.push_back(generateArrowShape());
            content.back().move(-8, -3);
            content.back().rotate(180);
            time = 800;
            break;

        case 9:
            content.push_back(generateStarShape());
            time = 800;
            break;

        default:
            break;
    }
    frame.move(x-15, y-15);
    for (sf::ConvexShape& shape : content)
        shape.move(x, y);
}

Upgrade::~Upgrade()
{
    ship->nbActiveUpgrades[type]--;
    switch (type)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            break;

        case 5:
            ship->accel *= 4/3;
            ship->angleAccel *= 2;
            break;

        case 6:
            if (ship->nbActiveUpgrades[type] < 1) {
                ship->cooldownLimits[0] = 10;
                ship->weaponNbLimits[0] = 10;
                ship->cooldownLimits[1] = 10;
                ship->weaponNbLimits[1] = 10;
            }
            break;

        case 7:
        {
            sf::Keyboard::Key tmp = ship->leftKey;
            ship->leftKey = ship->rightKey;
            ship->rightKey = tmp;
            break;
        }

        case 8:
            if (ship->nbActiveUpgrades[type] < 1) {
                ship->freeRotation = false;
                ship->angleAccel = 5;
            }
            break;

        case 9:
            ship->berserk = false;
            ship->shape.setFillColor(sf::Color::White);
            break;

        default:
            break;
    }
}

int Upgrade::getType() const
{
    return type;
}

void Upgrade::activate(SpaceShip* boundShip)
{
    ship = boundShip;
    ship->nbActiveUpgrades[type]++;
    switch (type)
    {
        case 0:     // Missiles ammo (if not in Berserk mode)
            ship->weaponAmmo[1] += 5;
            break;

        case 1:     // Laser ammo (if not in Berserk mode)
            ship->weaponAmmo[2] += 75;
            break;

        case 2:     // Bombs (if not in Berserk mode)
            ship->weaponAmmo[3] += 1;
            break;

        case 3:     // Heal
            ship->heal(2);
            break;

        case 4:     // Shield
            ship->addShield(10);
            break;

        case 5:     // Slow malus
            ship->accel *= 0.75;
            ship->angleAccel *= 0.5;
            break;

        case 6:     // Fast shot
            ship->cooldownLimits[0] = 3;
            ship->weaponNbLimits[0] = 50;
            ship->cooldownLimits[1] = 15;
            ship->weaponNbLimits[1] = 3;
            break;

        case 7:     // Switch left-right keys
        {
            sf::Keyboard::Key tmp = ship->leftKey;
            ship->leftKey = ship->rightKey;
            ship->rightKey = tmp;
            break;
        }

        case 8:     // Activate free rotation
            ship->freeRotation = true;
            ship->angleAccel = 0.3;
            break;

        case 9:     // Berserk mode
            ship->berserk = true;
            break;

        default:
            break;
    }
}

bool Upgrade::update()
{
    --time;
    return (time <= 0);
}

sf::Shape const* Upgrade::getShape() const
{
    return &frame;
}

void Upgrade::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Hitbox::draw(target, states);
    for (sf::ConvexShape shape : content)
        target.draw(shape, states);
};
