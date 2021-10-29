#include "Hitbox.hpp"

/* Implementation of the SAT algorithm */
bool Hitbox::intersects(Hitbox* obj1, Hitbox* obj2)
{
    vect_array shape1 = obj1->getPoints();
    vect_array shape2 = obj2->getPoints();

    for (sf::Vector2f axis : getAxes(shape1, shape2))
    {
        Projection projShape1 = project(shape1, axis);
        Projection projShape2 = project(shape2, axis);

        if (!overlap(projShape1, projShape2))
            return false;
    }
    return true;
}

Hitbox::~Hitbox()
{
}

bool Hitbox::hit(int damage)
{
    return true;
}

int Hitbox::getDamage() const
{
    return 1;
}

std::vector<sf::Vector2f> Hitbox::getPoints() const
{
    sf::Shape const* shape = getShape();
    std::vector<sf::Vector2f> points;
    for (unsigned i=0; i<shape->getPointCount(); ++i){
        double rotation = shape->getRotation();
        sf::Vector2f pos = shape->getPoint(i);
        sf::Vector2f new_pos = shape->getPosition();
        new_pos.x += pos.x * std::cos(rotation * M_PI / 180) - pos.y * std::sin(rotation * M_PI / 180);
        new_pos.y += pos.x * std::sin(rotation * M_PI / 180) + pos.y * std::cos(rotation * M_PI / 180);
        points.push_back(new_pos);
    }
    return points;
}

void Hitbox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (settings::HITBOX)
    {
        std::vector<sf::Vector2f> points = getPoints();
        for (unsigned i=0; i<points.size(); ++i) {
            sf::Vertex line[] = {sf::Vertex(points[i]), sf::Vertex(points[(i+1)%points.size()])};
            line[0].color = sf::Color::Red;
            line[1].color = sf::Color::Red;
            target.draw(line, 2, sf::Lines);
        }
    } else {
        states.transform *= getTransform();
        target.draw(*getShape(), states);
    }
}
