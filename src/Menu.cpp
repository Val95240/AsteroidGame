#include "Menu.hpp"

Menu::Menu(std::string name, Menu* prevMenu) : posY(3*settings::HEIGHT/10), prevMenu(prevMenu), binding(false), activeItem(0)
{
    font.loadFromFile(settings::FONT_FILE);

    title.setFont(font);
    title.setString(name);
    sf::FloatRect hitbox = title.getLocalBounds();
    title.setOrigin(hitbox.width/2, hitbox.height/2);
    title.setPosition(settings::WIDTH/2, 2*settings::HEIGHT/10);
}

Menu::~Menu()
{
    for (MenuItem* item : items)
        delete item;
}

void Menu::addItem(std::string name, Menu* nextMenu, GameMode mode)
{
    items.push_back(new MenuItem(name, posY, nextMenu, mode));
    posY += settings::HEIGHT/10;
}

void Menu::addItemSetting(std::string name, Menu* nextMenu, int* setting, std::vector<int> values)
{
    items.push_back(new MenuItemSetting(name, posY, nextMenu, setting, values));
    posY += settings::HEIGHT/10;
}

void Menu::addItemKeybind(std::string name, int* setting)
{
    items.push_back(new MenuItemKeybinding(name, posY, this, setting));
    posY += settings::HEIGHT/10;
}

Menu* Menu::press(sf::Keyboard::Key key)
{
    if (binding) {
        binding = false;
        items[activeItem]->bind(key);
        return this;
    }

    Menu* nextMenu = this;
    switch (key)
    {
        case sf::Keyboard::Up:
            if (items.size() != 0)
                activeItem = (items.size() + activeItem - 1) % items.size();
            break;

        case sf::Keyboard::Down:
            if (items.size() != 0)
                activeItem = (activeItem + 1) % items.size();
            break;

        case sf::Keyboard::Left:
        case sf::Keyboard::Right:
            items[activeItem]->change(key);
            break;

        case sf::Keyboard::Return:
            if (items.size() != 0) {
                nextMenu = items[activeItem]->enter();
                if (nextMenu != this) {
                    for (MenuItem* item : items)
                        item->apply();
                }
                break;
            }
            [[fallthrough]];

        case sf::Keyboard::Escape:
            if (prevMenu)
                nextMenu = prevMenu;
            break;

        default:
            break;
    }

    if (nextMenu != this) {
        activeItem = 0;
        for (MenuItem* item : items)
            item->reset();
    }
    return nextMenu;
}

void Menu::bind()
{
    binding = true;
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(title, states);
    for (unsigned i=0; i<items.size(); ++i) {
        items[i]->activate(i == activeItem);
        target.draw(*items[i], states);
    }
}
