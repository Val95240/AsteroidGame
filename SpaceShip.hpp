#ifndef HEADER_SPACESHIP
#define HEADER_SPACESHIP

#include <SFML/Graphics.hpp>
#include "Settings.hpp"
#include "utils.hpp"
#include "FlyingObject.hpp"
#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "Rocket.hpp"
#include "Laser.hpp"
#include "Bomb.hpp"

typedef sf::Keyboard::Key key;


class SpaceShip : public FlyingObject
{
    friend class Upgrade;

    public:
         SpaceShip(int id, int x, int y);
         virtual ~SpaceShip();
         void bind(int up, int down, int left, int right, int fire[settings::NB_WEAPONS]);

         int getTeam() const;
         sf::Vector2f getPosition() const;
         bool isBerserk() const;

         void addScore(int points);
         int getScore() const;

         virtual bool hit(int damage);
         virtual void update();
         bool weaponCollision(Weapon* attacker);
         void updateWeapons(std::list<SpaceShip*>& ships, std::list<Asteroid*>& asteroids);
         void updateTarget(std::list<SpaceShip*>& ships);

    private:
         int team;
         int score;

         key upKey;
         key downKey;
         key leftKey;
         key rightKey;
         key fireKey[settings::NB_WEAPONS];

         sf::CircleShape shield;
         int shieldLife;

         bool freeRotation;             // Whether the ship continues to rotate when Key is Up
         double accel;                  // The value added to speed each update with upKey or downKey pressed
         double angleAccel;             // The value added to angleSpeed each update with leftKey or rightKey pressed

         void accelerate(bool reverse=false);
         void rotate(bool clockwise);

         double bulletSpeed;
         int weaponAmmo[settings::NB_WEAPONS];
         int cooldownLimits[settings::NB_WEAPONS];
         int weaponNbLimits[settings::NB_WEAPONS];
         bool weaponRelativeSpeeds[settings::NB_WEAPONS];

         sf::Font font;
         sf::ConvexShape weaponAmmoShape[settings::NB_WEAPONS-1];
         sf::Text weaponAmmoText[settings::NB_WEAPONS-1];
         void initializeAmmo(int id);

         int cooldown[settings::NB_WEAPONS];
         int nbWeapon[settings::NB_WEAPONS];

         int nbActiveUpgrades[settings::NB_UPGRADES];
         bool berserk;
         void heal(int lp);
         void addShield(int shieldLP);

         std::list<Weapon*> weapons;
         void fire(int type);

         virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif
