#ifndef HEADER_MAIN_MENU
#define HEADER_MAIN_MENU

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include "Settings.hpp"
#include "utils.hpp"
#include "GamePhase.hpp"
#include "World.hpp"
#include "Menu.hpp"


class MainMenu : public GamePhase
{
    public:
        MainMenu();
        virtual ~MainMenu();

        virtual void press(sf::Keyboard::Key key);
        virtual bool update();
        virtual GamePhase* getNextPhase() const;

    private:
        Menu* activeMenu;
        std::vector<Menu*> menus;
        Menu* newMenu(std::string name, Menu* prevMenu);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
