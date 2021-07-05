#include "FlyingObject.h"

FlyingObject::FlyingObject(int life, int padding, sf::Color color) :
    speedX(0), speedY(0), angleSpeed(0),
    padding(padding), totalLife(life), life(life)
{
    lifeOutline.setSize(sf::Vector2f(20, 5));
    lifeOutline.setFillColor(sf::Color::Transparent);
    lifeOutline.setOutlineColor(color);
    lifeOutline.setOutlineThickness(1);
    lifeOutline.setOrigin(10, -30);

    lifeBar.setSize(sf::Vector2f(20, 5));
    lifeBar.setOrigin(10, -30);
}

FlyingObject::~FlyingObject()
{
}

Projection FlyingObject::xRange() const
{
    sf::FloatRect hitbox = shape.getGlobalBounds();
    return Projection(std::max(0.0f, hitbox.left - padding), \
                      std::min(hitbox.left + hitbox.width + padding, (float) settings::WIDTH));
}

Projection FlyingObject::yRange() const
{
    sf::FloatRect hitbox = shape.getGlobalBounds();
    return Projection(std::max(0.0f, hitbox.top - padding), \
                      std::min(hitbox.top + hitbox.height + padding, (float) settings::HEIGHT));
}

sf::FloatRect FlyingObject::getBounds() const
{
    return shape.getGlobalBounds();
}

bool FlyingObject::hit(int damage)
{
    life -= damage;
    lifeBar.setSize(sf::Vector2f(life*20/totalLife, 5));
    return life <= 0;
}

void FlyingObject::update()
{
    shape.move((int) speedX, (int) speedY);

    sf::Vector2f pos = shape.getPosition();
    if (pos.x < -padding)
        shape.move(settings::WIDTH+2*padding, 0);
    if (pos.x > settings::WIDTH + padding)
        shape.move(-settings::WIDTH-2*padding, 0);
    if (pos.y < -padding)
        shape.move(0, settings::HEIGHT+2*padding);
    if (pos.y > settings::HEIGHT + padding)
        shape.move(0, -settings::HEIGHT-2*padding);

    shape.rotate(angleSpeed);
}

sf::Shape const* FlyingObject::getShape() const
{
    return &shape;
}

void FlyingObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Hitbox::draw(target, states);

    if (totalLife > 1) {
        target.draw(lifeBar, states);
        target.draw(lifeOutline, states);
    }
}
