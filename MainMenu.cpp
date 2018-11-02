#include "MainMenu.h"

MainMenu::MainMenu()
{
    Menu* mainMenu = newMenu("", nullptr);
        Menu* playMenu = newMenu("Play", mainMenu);
            Menu* twoPlayers = newMenu("Mode two players", playMenu);
            Menu* threePlayers = newMenu("Mode three players", playMenu);
            Menu* fourPlayers = newMenu("Mode four players", playMenu);

            Menu* optionsMenu = newMenu("Options", playMenu);

        Menu* settingsMenu = newMenu("Settings", mainMenu);
            Menu* bindMenu = newMenu("Bindings", settingsMenu);
            Menu* bindPlayerMenus[4];
            for (int i=0; i<4; ++i)
                bindPlayerMenus[i] = newMenu("Player " + std::to_string(i+1), bindMenu);
        Menu* exitMenu = newMenu("Exit", mainMenu);

    mainMenu->addItem("Play", playMenu);
    mainMenu->addItem("Settings", settingsMenu);
    mainMenu->addItem("Exit", exitMenu);

    playMenu->addItem("Mode Solo", optionsMenu, GameMode({{&settings::NB_PLAYERS, 1}}));
    playMenu->addItem("2 Players", twoPlayers, GameMode({{&settings::NB_PLAYERS, 2}}));
    playMenu->addItem("3 Players", threePlayers, GameMode({{&settings::NB_PLAYERS, 3}}));
    playMenu->addItem("4 Players", fourPlayers, GameMode({{&settings::NB_PLAYERS, 4}}));

    twoPlayers->addItem("1 VS 1", optionsMenu, GameMode({{&settings::TEAMS[1], 1}}));
    twoPlayers->addItem("2 VS Env", optionsMenu, GameMode({{&settings::TEAMS[1], 0}}));

    threePlayers->addItem("1 VS 1 VS 1", optionsMenu, GameMode({{&settings::TEAMS[1], 1}, {&settings::TEAMS[2], 2}}));
    threePlayers->addItem("2 VS 1", optionsMenu, GameMode({{&settings::TEAMS[1], 0}, {&settings::TEAMS[2], 1}}));
    threePlayers->addItem("3 VS Env", optionsMenu, GameMode({{&settings::TEAMS[1], 0}, {&settings::TEAMS[2], 0}}));

    fourPlayers->addItem("1 VS 1 VS 1 VS 1", optionsMenu, GameMode({{&settings::TEAMS[1], 1}, {&settings::TEAMS[2], 2},
                                                                    {&settings::TEAMS[3], 3}}));
    fourPlayers->addItem("2 VS 1 VS 1", optionsMenu, GameMode({{&settings::TEAMS[1], 0}, {&settings::TEAMS[2], 1},
                                                               {&settings::TEAMS[3], 2}}));
    fourPlayers->addItem("2 VS 2", optionsMenu, GameMode({{&settings::TEAMS[1], 0}, {&settings::TEAMS[2], 1}, 
                                                          {&settings::TEAMS[3], 1}}));
    fourPlayers->addItem("3 VS 1", optionsMenu, GameMode({{&settings::TEAMS[1], 0}, {&settings::TEAMS[2], 0},
                                                          {&settings::TEAMS[3], 1}}));
    fourPlayers->addItem("4 VS Env", optionsMenu, GameMode({{&settings::TEAMS[1], 0}, {&settings::TEAMS[2], 0},
                                                            {&settings::TEAMS[3], 0}}));

    optionsMenu->addItemSetting("Asteroid density", optionsMenu, &settings::AST_DENSITY, {0, 1, 2, 3});
    optionsMenu->addItemSetting("Upgrades density", optionsMenu, &settings::UPG_DENSITY, {0, 1, 2, 3});
    optionsMenu->addItemSetting("Bullet avail.", optionsMenu, &settings::AUTH_WEAP[0]);
    optionsMenu->addItemSetting("Rocket avail.", optionsMenu, &settings::AUTH_WEAP[1]);
    optionsMenu->addItemSetting("Laser avail.", optionsMenu, &settings::AUTH_WEAP[2]);
    optionsMenu->addItemSetting("Bomb avail.", optionsMenu, &settings::AUTH_WEAP[3]);
    optionsMenu->addItem("Play", nullptr);

    settingsMenu->addItem("Key bindings", bindMenu);
    settingsMenu->addItemSetting("Friendly fire", mainMenu, &settings::FRIENDLY_FIRE);
    settingsMenu->addItemSetting("Hitbox", mainMenu, &settings::HITBOX);
    settingsMenu->addItem("Save & Exit", mainMenu);
    
    for (int i=0; i<4; ++i)
    {
        bindMenu->addItem("Player " + std::to_string(i+1), bindPlayerMenus[i]);

        bindPlayerMenus[i]->addItemKeybind("Up key", &settings::UP_KEY[i]);
        bindPlayerMenus[i]->addItemKeybind("Down key", &settings::DOWN_KEY[i]);
        bindPlayerMenus[i]->addItemKeybind("Left key", &settings::LEFT_KEY[i]);
        bindPlayerMenus[i]->addItemKeybind("Right key", &settings::RIGHT_KEY[i]);
        bindPlayerMenus[i]->addItemKeybind("Bullet key", &settings::FIRE_KEY[i][0]);
        bindPlayerMenus[i]->addItem("Save & Exit", bindMenu);
    }
    bindMenu->addItem("Save & Exit", settingsMenu);

    exitMenu->addItemSetting("", mainMenu, &settings::EXIT);

    activeMenu = mainMenu;
}

MainMenu::~MainMenu()
{
    for (Menu* menu : menus)
        delete menu;
}

void MainMenu::press(sf::Keyboard::Key key)
{
    activeMenu = activeMenu->press(key);
}

bool MainMenu::update()
{
    return (activeMenu == nullptr);
}

GamePhase* MainMenu::getNextPhase() const
{
    return new World();
}

Menu* MainMenu::newMenu(std::string name, Menu* prevMenu)
{
    Menu* createdMenu = new Menu(name, prevMenu);
    menus.push_back(createdMenu);
    return createdMenu;
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (activeMenu)
        target.draw(*activeMenu, states);
}
