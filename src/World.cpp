#include "World.hpp"

World::World() : exit(false), pause(false), pauseMenu("Pause", nullptr), nbShip(0), asteroidCooldown(0), upgradeCooldown(0) //250)
{
    pauseMenu.addItem("Resume", &pauseMenu, GameMode({{&pause, false}}));
    pauseMenu.addItem("Exit", &pauseMenu, GameMode({{&pause, false}, {&exit, true}}));
    font.loadFromFile(settings::FONT_FILE);

    std::set<int> teams;
    for (int i=0; i<settings::NB_PLAYERS; ++i) {
        teams.insert(settings::TEAMS[nbShip]);
        addShip();
    }

    nbTeam = teams.size();
    for (int i=0; i<nbTeam; ++i) {
        sf::Text textScore;
        textScore.setFont(font);
        textScore.setPosition(40 + i*settings::WIDTH/nbTeam, 10);
        textScore.setFillColor(settings::TEAM_COLORS[i]);
        textScores.push_back(textScore);
    }

    if (settings::AST_DENSITY > 0) {
        for (int i=0; i<(int) fRand(2*settings::AST_DENSITY, 4*settings::AST_DENSITY); i++)
            addAsteroid((int) fRand(1, 3));
    }

    if (settings::AUTH_WEAP[1]) {
        sf::ConvexShape rocketThumb = generateRocketShape();
        rocketThumb.scale(0.5, 0.5);
        rocketThumb.rotate(45);
        weaponThumbnails.push_back(rocketThumb);
    }

    if (settings::AUTH_WEAP[2]) {
        sf::ConvexShape laserThumb = generateLaserShape(30);
        laserThumb.scale(0.5, 0.5);
        laserThumb.rotate(45);
        weaponThumbnails.push_back(laserThumb);
    }

    if (settings::AUTH_WEAP[3]) {
        sf::ConvexShape bombThumb = generateBombShape();
        bombThumb.scale(0.5, 0.5);
        bombThumb.rotate(45);
        weaponThumbnails.push_back(bombThumb);
    }

    for (unsigned i=0; i<weaponThumbnails.size(); ++i)
        weaponThumbnails[i].setPosition(settings::WIDTH/6, settings::HEIGHT-10-20*(weaponThumbnails.size()-1-i));

}

World::~World()
{
    for (SpaceShip* ship : ships)
        delete ship;

    for (Asteroid* ast : asteroids)
        delete ast;
}

void World::addShip()
{
    int x, y;
    switch (settings::NB_PLAYERS)
    {
        case 1:
            x = settings::WIDTH/2;
            y = settings::HEIGHT/2;
            break;

        case 2:
            x = (nbShip+1)*settings::WIDTH/3;
            y = settings::HEIGHT/2;
            break;

        case 3:
            x = ((3-nbShip)%3 + 2)*settings::WIDTH/6;
            y = (nbShip/2+1)*settings::HEIGHT/3;
            break;

        case 4:
            x = (nbShip%2+1)*settings::WIDTH/3;
            y = (nbShip/2+1)*settings::HEIGHT/3;
            break;

        default:
            x = settings::WIDTH/2;
            y = settings::HEIGHT/2;
            break;
    }
    SpaceShip* newShip = new SpaceShip(nbShip, x, y);
    newShip->bind(settings::UP_KEY[nbShip], settings::DOWN_KEY[nbShip], \
            settings::LEFT_KEY[nbShip], settings::RIGHT_KEY[nbShip], \
            settings::FIRE_KEY[nbShip]);

    ships.push_back(newShip);
    ++nbShip;
}

void World::addAsteroid(int size)
{
    std::vector<Projection> border;
    for (Asteroid* ast : asteroids)
        border = removeOverlap(border, ast->getBounds());

    for (SpaceShip* ship : ships)
        border = removeOverlap(border, ship->getBounds());

    if (span(border) < 2*(settings::WIDTH+settings::HEIGHT)) {
        std::pair<int, int> xy = randomInProjection(border);
        asteroids.push_back(new Asteroid(this, xy.first, xy.second, size));
    }
}

void World::addAsteroid(Asteroid* newAsteroid)
{
    asteroids.push_back(newAsteroid);
}

void World::addUpgrade()
{
    int i = 0;
    double x, y = -1;
    while (y < 0 && i < 10)
    {
        x = fRand(20, settings::WIDTH-20);
        std::vector<Projection> projections;
        for (Asteroid* ast : asteroids) {
            Projection span = ast->xRange();
            if (span.first < x && x < span.second)
                projections = addProjection(projections, ast->yRange());
        }
        for (SpaceShip* ship : ships) {
            Projection span = ship->xRange();
            if (span.first < x && x < span.second)
                projections = addProjection(projections, ship->yRange());
        }
        if (span(projections) < settings::HEIGHT)
            y = randomLessProjections(projections);
        i++;
    }

    double proba[settings::NB_UPGRADES];
    std::copy(settings::PROBA_UPGRADES, settings::PROBA_UPGRADES+settings::NB_UPGRADES, proba);
    for (int i=0; i<3; ++i) {
        if (!settings::AUTH_WEAP[i+1])
            proba[i] = 0;
    }
    int type = tabRand(proba, settings::NB_UPGRADES);
    if (y > 0)
        inactiveUpgrades.push_back(new Upgrade(type, x, y));
}

void World::press(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Escape)
        pause = !pause;

    if (pause)
        pauseMenu.press(key);
}

bool World::update()
{
    if (pause)
        return false;

    for (SpaceShip* ship : ships)
        ship->update();

    for (Asteroid* ast : asteroids)
        ast->update();

    for (SpaceShip* ship : ships)
        ship->updateWeapons(ships, asteroids);

    for (SpaceShip* ship : ships) {
        for (std::list<Upgrade*>::iterator upg_it = inactiveUpgrades.begin(); upg_it != inactiveUpgrades.end();) {
            Upgrade* upg = *upg_it;
            if (Hitbox::intersects(ship, upg)) {
                upg->activate(ship);
                activeUpgrades.push_back(upg);
                upg_it = inactiveUpgrades.erase(upg_it);
            } else {
                ++upg_it;
            }
        }
    }

    for (std::list<Upgrade*>::iterator upg_it = activeUpgrades.begin(); upg_it != activeUpgrades.end();) {
        if((*upg_it)->update()) {
            delete *upg_it;
            upg_it = activeUpgrades.erase(upg_it);
        } else {
            ++upg_it;
        }
    }

    for (std::list<SpaceShip*>::iterator ship_it = ships.begin(); ship_it != ships.end(); ++ship_it) {
        for (std::list<Asteroid*>::iterator ast_it = asteroids.begin(); ast_it != asteroids.end(); ++ast_it) {
            SpaceShip* ship = *ship_it;
            Asteroid* ast = *ast_it;
            if (Hitbox::intersects(ship, ast)) {
                int astDamage = ast->getDamage();
                if (ast->hit(ship->getDamage())) {
                    delete ast;
                    ast_it = asteroids.erase(ast_it);
                    --ast_it;
                }

                if (ship->hit(astDamage)) {
                    delete ship;
                    ship_it = ships.erase(ship_it);
                    --ship_it;
                    break;
                }
            }
        }
    }

    for (SpaceShip* ship : ships) {
        if (ship->isBerserk()) {
            for (std::list<SpaceShip*>::iterator ship_it = ships.begin(); ship_it != ships.end(); ++ship_it) {
                if (*ship_it != ship && Hitbox::intersects(ship, *ship_it) && (*ship_it)->hit(ship->getDamage())) {
                    delete *ship_it;
                    ship_it = ships.erase(ship_it);
                    --ship_it;
                }
            }
        }
    }

    for (SpaceShip* ship : ships)
        ship->updateTarget(ships);

    if (settings::AST_DENSITY > 0)
    {
        if (asteroidCooldown > 0)
            --asteroidCooldown;

        if (asteroidCooldown == 0) {
            asteroidCooldown = fRand(90*(4-settings::AST_DENSITY), 270*(4-settings::AST_DENSITY));
            addAsteroid((int) fRand(1, 3));
        }
    }

    if (settings::UPG_DENSITY > 0)
    {
        if (upgradeCooldown > 0)
            --upgradeCooldown;

        if (upgradeCooldown == 0) {
            upgradeCooldown = fRand(100*(4-settings::UPG_DENSITY), 250*(4-settings::UPG_DENSITY));
            addUpgrade();
        }
    }

    if (ships.size() > 0)
    {
        for (int i=0; i<4; ++i)
            scores[i] = 0;

        for (SpaceShip* ship : ships)
            scores[ship->getTeam()] += ship->getScore();
    }

    for (int i=0; i<nbTeam; i++)
        textScores[i].setString(std::to_string(scores[i]));

    return ships.empty() || exit;
}

GamePhase* World::getNextPhase() const
{
    if (nbShip == 1)
        return new ScoreMenu(scores[0]);
    return new MainMenu();
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = NULL;

    if (pause)
        target.draw(pauseMenu, states);

    for (int i=0; i<nbTeam; ++i)
        target.draw(textScores[i], states);

    for (sf::ConvexShape thumb : weaponThumbnails)
        target.draw(thumb, states);

    for (SpaceShip* ship : ships)
        target.draw(*ship, states);

    for (Asteroid* ast : asteroids)
        target.draw(*ast, states);

    for (Upgrade* upg : inactiveUpgrades)
        target.draw(*upg, states);
}
