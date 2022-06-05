#ifndef HEADER_MENU
#define HEADER_MENU

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "MenuItem.hpp"


class Menu : public sf::Drawable
{
    public:
        Menu(std::string name, Menu* prevMenu);
        virtual ~Menu();

        void addItem(std::string name, Menu* nextMenu, GameMode mode=GameMode({}));
        void addItemSetting(std::string name, Menu* nextMenu, int* setting, std::vector<int> values={0,1});
        void addItemKeybind(std::string name, int* setting);

        Menu* press(sf::Keyboard::Key);
        void bind();

    private:
        sf::Font font;
        sf::Text title;
        int posY;
        Menu* prevMenu;

        bool binding;

        unsigned activeItem;
        std::vector<MenuItem*> items;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
