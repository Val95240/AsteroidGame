#ifndef HEADER_SCOREMENU
#define HEADER_SCOREMENU

#include <cctype>

#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "utils.h"
#include "GamePhase.h"
#include "MainMenu.h"


class ScoreMenu : public GamePhase
{
    public:
        ScoreMenu(int score);

        virtual void press(sf::Keyboard::Key key);
        virtual bool update();
        virtual GamePhase* getNextPhase() const;

    private:
        sf::Font font;
        sf::Text title;
        sf::Text scoresName[6];
        sf::Text scoresValues[6];
        std::vector<std::pair<std::string, int>> scores;
        unsigned index;

        int score;
        bool nextPhase;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
