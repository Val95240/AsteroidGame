#include <ctime>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "GamePhase.h"
#include "MainMenu.h"


int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(settings::WIDTH, settings::HEIGHT), "Asteroid");

    GamePhase* phase = new MainMenu();

    sf::Clock clock;
    while (window.isOpen() && !settings::EXIT)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
                phase->press(event.key.code);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (phase->update()) {
            GamePhase* newPhase = phase->getNextPhase();
            delete phase;
            phase = newPhase;
        }

        window.clear();
        window.draw(*phase);
        window.display();

        sf::sleep(sf::milliseconds(30) - clock.restart());
    }

    delete phase;

    return 0;
}
