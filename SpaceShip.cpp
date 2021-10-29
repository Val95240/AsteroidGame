#include "SpaceShip.hpp"

SpaceShip::SpaceShip(int id, int x, int y) : FlyingObject(settings::SHIP_LIFE, 40, settings::TEAM_COLORS[id]),
    team(settings::TEAMS[id]), score(0), shield(50, 100), shieldLife(0),
    freeRotation(false), accel(0.1),
    cooldown{0}, nbWeapon{0},
    nbActiveUpgrades{0}, berserk(false)
{
    // Ship creation
    shape = generateShipShape();
    shape.setOutlineThickness(2);
    shape.setOutlineColor(settings::TEAM_COLORS[settings::TEAMS[id]]);

    shield.setOrigin(50, 50);
    shield.setFillColor(sf::Color(60, 60, 250, 125));

    shape.move(x, y);
    lifeBar.move(x, y);
    lifeOutline.move(x, y);
    shield.move(x, y);

    // Free rotation
    if (freeRotation)
        angleAccel = 0.4;
    else
        angleAccel = 5;

    initializeAmmo(id);
}

SpaceShip::~SpaceShip()
{
    for (Weapon* weapon : weapons)
        delete weapon;
}

void SpaceShip::initializeAmmo(int id)
{
    font.loadFromFile(settings::FONT_FILE);

    int nbAuthWeap = 0;
    for (int i=settings::NB_WEAPONS-2; 0<=i; --i) {
        if (settings::AUTH_WEAP[i+1]) {
            weaponAmmoText[i].setFont(font);
            weaponAmmoText[i].setPosition((id+2)*settings::WIDTH/6, settings::HEIGHT-20-20*nbAuthWeap);
            weaponAmmoText[i].setCharacterSize(14);
            ++nbAuthWeap;
        }
    }

    // Bullets
    bulletSpeed = 8;
    weaponAmmo[0] = -1;
    cooldownLimits[0] = 10;
    weaponNbLimits[0] = 10;
    weaponRelativeSpeeds[0] = false;

    // Rockets
    weaponAmmo[1] = 0;
    cooldownLimits[1] = 30;
    weaponNbLimits[1] = 5;
    weaponRelativeSpeeds[1] = false;

    // Laser
    weaponAmmo[2] = 0;
    cooldownLimits[2] = 0;
    weaponNbLimits[2] = 2;
    weaponRelativeSpeeds[2] = false;

    // Bomb
    weaponAmmo[3] = 0;
    cooldownLimits[3] = 70;
    weaponNbLimits[3] = 1;
    weaponRelativeSpeeds[3] = false;
}

void SpaceShip::bind(int up, int down, int left, int right, int fire[settings::NB_WEAPONS])
{
    upKey = (key) up;
    downKey = (key) down;
    leftKey = (key) left;
    rightKey = (key) right;
    for (int i=0; i<settings::NB_WEAPONS; i++)
        fireKey[i] = (key) fire[i];
}

int SpaceShip::getTeam() const
{
    return team;
}

sf::Vector2f SpaceShip::getPosition() const
{
    return shape.getPosition();
}

bool SpaceShip::isBerserk() const
{
    return berserk;
}

void SpaceShip::addScore(int points)
{
    score += points;
}

int SpaceShip::getScore() const
{
    return score;
}

bool SpaceShip::hit(int damage)
{
    if (berserk)
        return false;

    if (damage < shieldLife) {
        shieldLife -= damage;
        damage = 0;
    } else {
        damage -= shieldLife;
        shieldLife = 0;
    }
    return FlyingObject::hit(damage);
}

void SpaceShip::update()
{
    if (sf::Keyboard::isKeyPressed(upKey))
        accelerate();
    if (sf::Keyboard::isKeyPressed(downKey))
        accelerate(true);

    if (sf::Keyboard::isKeyPressed(leftKey))
        rotate(false);
    if (sf::Keyboard::isKeyPressed(rightKey))
        rotate(true);

    for (int i=0; i<settings::NB_WEAPONS; i++) {
        if (settings::AUTH_WEAP[i] && sf::Keyboard::isKeyPressed(fireKey[i]))
            fire(i);
    }

    FlyingObject::update();

    if (!freeRotation)
        angleSpeed = 0;

    sf::Vector2f pos = shape.getPosition();
    lifeBar.setPosition(pos);
    lifeOutline.setPosition(pos);
    shield.setPosition(pos);

    for (int i=0; i < settings::NB_WEAPONS-1; ++i)
        weaponAmmoText[i].setString(std::to_string(weaponAmmo[i+1]));

    for (int i = 0; i < settings::NB_WEAPONS; ++i) {
        if (cooldown[i] > 0)
            --cooldown[i];
    }

    for (std::list<Weapon*>::iterator it = weapons.begin(); it != weapons.end();) {
        Weapon* weapon = *it;
        weapon->update();
        // If the bullet is out of the screen, remove it
        if (!weapon->valid()) {
            --nbWeapon[weapon->getType()];
            delete weapon;
            it = weapons.erase(it);
        } else {
            ++it;
        }
    }

    if (berserk)
        shape.setFillColor(settings::COLORS[(int) fRand(0, 8)]);
}

bool SpaceShip::weaponCollision(Weapon* attacker)
{
    for (std::list<Weapon*>::iterator weap_it = weapons.begin(); weap_it != weapons.end(); ++weap_it)
    {
        if (Hitbox::intersects(*weap_it, attacker)) {
            int damage = (*weap_it)->getDamage();

            if ((*weap_it)->hit(attacker->getDamage())) {
                --nbWeapon[(*weap_it)->getType()];
                delete (*weap_it);
                weap_it = weapons.erase(weap_it);
                --weap_it;
            }
            if (attacker->hit(damage))
                return true;
        }
    }
    return false;
}

void SpaceShip::updateWeapons(std::list<SpaceShip*>& ships, std::list<Asteroid*>& asteroids)
{
    for (std::list<Weapon*>::iterator weap_it = weapons.begin(); weap_it != weapons.end();)
    {
        // Ships-bullets collisions
        if ((*weap_it)->updateHits(ships)) {
            --nbWeapon[(*weap_it)->getType()];
            delete (*weap_it);
            weap_it = weapons.erase(weap_it);
        } else {
            ++weap_it;
        }
    }

    for (std::list<Weapon*>::iterator weap_it = weapons.begin(); weap_it != weapons.end();)
    {
        // Asteroid-bullets collisions
        if ((*weap_it)->updateHits(asteroids)) {
            --nbWeapon[(*weap_it)->getType()];
            delete (*weap_it);
            weap_it = weapons.erase(weap_it);
        } else {
            ++weap_it;
        }
    }
}

void SpaceShip::updateTarget(std::list<SpaceShip*>& ships)
{
    for (Weapon* weap : weapons)
        weap->updateTarget(ships);
}

void SpaceShip::accelerate(bool reverse)
{
    double angle = shape.getRotation();
    double sign = (reverse ? -1 : 1);
    speedX += sign * accel * std::sin(angle * M_PI / 180);
    speedY -= sign * accel * std::cos(angle * M_PI / 180);
}

void SpaceShip::rotate(bool clockwise)
{
    if (clockwise)
        angleSpeed += angleAccel;
    else
        angleSpeed -= angleAccel;
}

void SpaceShip::heal(int lp)
{
    life = std::min(life + 2, totalLife);
    lifeBar.setSize(sf::Vector2f(life*20/totalLife, 5));
}

void SpaceShip::addShield(int shieldLP)
{
    shieldLife += shieldLP;
}

void SpaceShip::fire(int type)
{
    if (!berserk && sf::Keyboard::isKeyPressed(fireKey[type]) && weaponAmmo[type] != 0 &&
            nbWeapon[type] < weaponNbLimits[type] && cooldown[type] == 0)
    {
        --weaponAmmo[type];
        ++nbWeapon[type];
        cooldown[type] = cooldownLimits[type];

        Weapon* newWeapon = 0;

        sf::Vector2f pos = shape.getPosition();
        double angle = shape.getRotation();

        // Weapon initial position
        double x = pos.x + 35 * std::sin(angle * M_PI / 180);
        double y = pos.y - 35 * std::cos(angle * M_PI / 180);

        // Weapon relative speed
        double relativeShipSpeedX = (weaponRelativeSpeeds[type] ? speedX : 0);
        double relativeShipSpeedY = (weaponRelativeSpeeds[type] ? speedY : 0);

        switch (type)
        {
            case 0:
            {
                double bulletSpeedX = relativeShipSpeedX + bulletSpeed * std::sin(angle * M_PI / 180);
                double bulletSpeedY = relativeShipSpeedY - bulletSpeed * std::cos(angle * M_PI / 180);

                newWeapon = new Bullet(this, x, y, angle, bulletSpeedX, bulletSpeedY);
                break;
            }

            case 1:
                newWeapon = new Rocket(this, x, y, angle, relativeShipSpeedX, relativeShipSpeedY);
                break;

            case 2:
                newWeapon = new Laser(this, x, y, angle);
                break;

            case 3:
                newWeapon = new Bomb(this, pos.x, pos.y);
                break;

            default:
                throw std::runtime_error("SpaceShip.cpp : fire : switch(type) : Weapon not implemented");
                break;
        }

        weapons.push_back(newWeapon);
    }
}

void SpaceShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    FlyingObject::draw(target, states);

    if (shieldLife > 0)
        target.draw(shield, states);

    for (int i=0; i<settings::NB_WEAPONS-1; ++i)
        target.draw(weaponAmmoText[i], states);

    for (Weapon* weapon : weapons) {
        target.draw(*weapon, states);
    }
}
