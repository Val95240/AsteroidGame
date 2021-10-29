#ifndef HEADER_FLYING_OBJECT
#define HEADER_FLYING_OBJECT

#include <cmath>
#include <vector>
#include <algorithm>

#include <SFML/Graphics.hpp>
#include "Settings.hpp"
#include "utils.hpp"
#include "Hitbox.hpp"


class FlyingObject : public Hitbox
{
    public:
        FlyingObject(int life, int padding, sf::Color color=sf::Color::White);
        virtual ~FlyingObject();

        virtual Projection xRange() const;
        virtual Projection yRange() const;
        virtual sf::FloatRect getBounds() const;

        virtual bool hit(int damage);
        virtual void update();

    protected:
        double speedX, speedY;
        double angleSpeed;
        int padding;
        int totalLife;
        int life;
        sf::RectangleShape lifeOutline;
        sf::RectangleShape lifeBar;
        sf::ConvexShape shape;

        virtual sf::Shape const* getShape() const;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif
