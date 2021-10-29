#include "MenuItem.hpp"
#include "Menu.hpp"

MenuItem::MenuItem(std::string title, int posY, Menu* nextMenu, GameMode mode) : nextMenu(nextMenu), mode(mode)
{
    font.loadFromFile(settings::FONT_FILE);

    name.setFont(font);
    name.setString(title);
    sf::FloatRect hitbox = name.getLocalBounds();
    name.setOrigin(hitbox.width/2, hitbox.height/2);
    name.setPosition(settings::WIDTH/2, posY);
}

MenuItem::~MenuItem()
{
}

Menu* MenuItem::enter()
{
    mode.apply();
    return nextMenu;
}

void MenuItem::change(sf::Keyboard::Key key) {}
void MenuItem::bind(sf::Keyboard::Key key) {}
void MenuItem::apply() {}
void MenuItem::reset() {}


void MenuItem::activate(bool active)
{
    name.setFillColor((active ? sf::Color::Green : sf::Color::White));
}

void MenuItem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(name, states);
}


// #######################################################################################################################


MenuItemSetting::MenuItemSetting(std::string title, int posY, Menu* nextMenu, int* setting, std::vector<int> vals) :
    MenuItem(title, posY, nextMenu), setting(setting)
{
    name.setPosition(settings::WIDTH/3, posY);
    bool booleanValues = (vals.size() == 2 && vals[0] == 0 && vals[1] == 1);

    index = -1;

    for (unsigned i=0; i<vals.size(); ++i)
    {
        if (*setting == vals[i])
            index = i;

        sf::Text textValue;
        textValue.setFont(font);
        if (booleanValues)
            textValue.setString(vals[i] ? "yes" : "no");
        else
            textValue.setString(std::to_string(vals[i]));

        sf::FloatRect hitbox = textValue.getLocalBounds();
        textValue.setOrigin(hitbox.width/2, hitbox.height/2);

        if (title.empty())
            textValue.setPosition((i+1)*settings::WIDTH/(vals.size()+1), posY);
        else
            textValue.setPosition(settings::WIDTH/2 + (i+1)*settings::WIDTH/2/(vals.size()+1), posY);

        textValue.setFillColor((index == i) ? sf::Color::Green : sf::Color::Red);
        textValues.push_back(textValue);

        values.push_back(vals[i]);
    }
}

MenuItemSetting::~MenuItemSetting()
{
}

void MenuItemSetting::change(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Left && index > 0)
        --index;
    else if (key == sf::Keyboard::Right && index < values.size()-1)
        ++index;

    for (unsigned i=0; i<textValues.size(); ++i)
        textValues[i].setFillColor((index == i) ? sf::Color::Green : sf::Color::Red);
}

void MenuItemSetting::activate(bool active)
{
    MenuItem::activate(active);
}

void MenuItemSetting::apply()
{
    *setting = values[index];
}

void MenuItemSetting::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    MenuItem::draw(target, states);

    for (sf::Text textValue : textValues)
        target.draw(textValue, states);
}

void MenuItemSetting::reset()
{
    for (unsigned i=0; i<values.size(); ++i) {
        if (*setting == values[i])
            index = i;
    }
    for (unsigned i=0; i<values.size(); ++i)
        textValues[i].setFillColor((index == i) ? sf::Color::Green : sf::Color::Red);
}


// #######################################################################################################################


MenuItemKeybinding::MenuItemKeybinding(std::string title, int posY, Menu* nextMenu, int* setting) :
    MenuItem(title, posY, nextMenu), setting(setting)
{
    name.setPosition(settings::WIDTH/3, posY);

    boundKey = (sf::Keyboard::Key) *setting;
    keyName.setFont(font);
    keyName.setString(settings::NAME[*setting]);
    sf::FloatRect hitbox = keyName.getLocalBounds();
    keyName.setOrigin(hitbox.width/2, hitbox.height/2);
    keyName.setPosition(settings::WIDTH-80, posY);
}

MenuItemKeybinding::~MenuItemKeybinding()
{
}

Menu* MenuItemKeybinding::enter()
{
    keyName.setString("<Enter a key>");
    nextMenu->bind();
    return nextMenu;
}

void MenuItemKeybinding::bind(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Unknown)
        return;
    boundKey = key;
    keyName.setString(settings::NAME[boundKey]);
}

void MenuItemKeybinding::apply()
{
    *setting = boundKey;
}

void MenuItemKeybinding::reset()
{
    boundKey = (sf::Keyboard::Key) *setting;
    keyName.setString(settings::NAME[boundKey]);
}

void MenuItemKeybinding::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    MenuItem::draw(target, states);
    target.draw(keyName, states);
}
