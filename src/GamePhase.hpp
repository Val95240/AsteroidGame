#ifndef HEADER_GAMEPHASE
#define HEADER_GAMEPHASE

#include <SFML/Graphics.hpp>
#include "Settings.hpp"


class GamePhase : public sf::Drawable, public sf::Transformable
{
    public:
        virtual ~GamePhase();

        virtual void press(sf::Keyboard::Key key) = 0;
        virtual bool update() = 0;
        virtual GamePhase* getNextPhase() const = 0;

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};


#endif
