#ifndef HEADER_HITBOX
#define HEADER_HITBOX

#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>
#include "utils.hpp"


class Hitbox : public sf::Drawable, public sf::Transformable
{
    public:
        static bool intersects(Hitbox* obj1, Hitbox* obj2);

        virtual ~Hitbox();
        virtual bool hit(int damage);
        virtual int getDamage() const;

    protected:
        virtual const sf::Shape* getShape() const = 0;
        virtual std::vector<sf::Vector2f> getPoints() const;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
