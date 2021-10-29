#ifndef HEADER_MENU_ITEM
#define HEADER_MENU_ITEM

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include "Settings.hpp"
#include "utils.hpp"


class Menu;

class MenuItem : public sf::Drawable
{
    public:
        MenuItem(std::string title, int posY, Menu* nextMenu, GameMode mode=GameMode({}));
        virtual ~MenuItem();

        virtual Menu* enter();
        virtual void change(sf::Keyboard::Key key);
        virtual void activate(bool active);
        virtual void bind(sf::Keyboard::Key key);
        virtual void apply();
        virtual void reset();

    protected:
        sf::Font font;
        sf::Text name;
        Menu* nextMenu;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        GameMode mode;
};


class MenuItemSetting : public MenuItem
{
    public:
        MenuItemSetting(std::string title, int posY, Menu* nextMenu, int* setting, std::vector<int> vals);
        virtual ~MenuItemSetting();

        virtual void change(sf::Keyboard::Key key);
        virtual void activate(bool active);
        virtual void apply();
        virtual void reset();

    private:
        int* setting;
        std::vector<int> values;
        std::vector<sf::Text> textValues;
        unsigned index;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


class MenuItemKeybinding : public MenuItem
{
    public:
        MenuItemKeybinding(std::string title, int posY, Menu* nextMenu, int* setting);
        virtual ~MenuItemKeybinding();

        virtual Menu* enter();
        void bind(sf::Keyboard::Key key);
        virtual void apply();
        virtual void reset();

    private:
        int* setting;
        sf::Keyboard::Key boundKey;
        sf::Text keyName;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
