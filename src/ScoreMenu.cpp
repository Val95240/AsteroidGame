#include "ScoreMenu.hpp"

ScoreMenu::ScoreMenu(int score) : score(score), nextPhase(false)
{
    font.loadFromFile(settings::FONT_FILE);

    title.setFont(font);
    title.setString("GAME OVER");
    sf::FloatRect hitbox = title.getLocalBounds();
    title.setOrigin(hitbox.width/2, hitbox.height/2);
    title.setPosition(settings::WIDTH/2, 40);

    try {
        scores = readScores();
    } catch (std::exception const& e) {
        return;
    }

    index = 0;
    while (index < scores.size() && score <= scores[index].second)
        ++index;

    if (index < 6)
    {
        scoresName[index].setFont(font);
        scoresName[index].setString("___");
        scoresName[index].setPosition(settings::WIDTH/5, 100+40*index);

        scoresValues[index].setFont(font);
        scoresValues[index].setString(std::to_string(score));
        hitbox = scoresValues[index].getLocalBounds();
        scoresValues[index].setOrigin(hitbox.width, 0);
        scoresValues[index].setPosition(settings::WIDTH*4/5, 100+40*index);
    }

    for (unsigned i=0, j=0; i<6; ++i, ++j)
    {
        if (i == index)
            ++i;
        scoresName[i].setFont(font);
        scoresName[i].setFillColor(sf::Color::Green);
        scoresName[i].setString(scores[j].first);
        scoresName[i].setPosition(settings::WIDTH/5, 100+40*i);

        scoresValues[i].setFont(font);
        scoresValues[i].setFillColor(sf::Color::Green);
        scoresValues[i].setString(std::to_string(scores[j].second));
        hitbox = scoresValues[i].getLocalBounds();
        scoresValues[i].setOrigin(hitbox.width, 0);
        scoresValues[i].setPosition(settings::WIDTH*4/5, 100+40*i);
    }
}

void ScoreMenu::press(sf::Keyboard::Key key)
{
    switch (key)
    {
        case sf::Keyboard::A:
        case sf::Keyboard::B:
        case sf::Keyboard::C:
        case sf::Keyboard::D:
        case sf::Keyboard::E:
        case sf::Keyboard::F:
        case sf::Keyboard::G:
        case sf::Keyboard::H:
        case sf::Keyboard::I:
        case sf::Keyboard::J:
        case sf::Keyboard::K:
        case sf::Keyboard::L:
        case sf::Keyboard::M:
        case sf::Keyboard::N:
        case sf::Keyboard::O:
        case sf::Keyboard::P:
        case sf::Keyboard::Q:
        case sf::Keyboard::R:
        case sf::Keyboard::S:
        case sf::Keyboard::T:
        case sf::Keyboard::U:
        case sf::Keyboard::V:
        case sf::Keyboard::W:
        case sf::Keyboard::X:
        case sf::Keyboard::Y:
        case sf::Keyboard::Z:
        {
            std::string name = scoresName[index].getString();
            std::size_t first = name.find('_');
            if (first == std::string::npos)
                break;
            name[first] = std::toupper(settings::NAME[key][0]);
            scoresName[index].setString(name);
            break;
        }

        case sf::Keyboard::BackSpace:
        {
            std::string name = scoresName[index].getString();
            std::size_t first_ = name.find('_');
            if (first_ == 0)
                break;
            if (first_ == std::string::npos)
                first_ = 3;
            --first_;
            name[first_] = '_';
            scoresName[index].setString(name);
            break;
        }

        case sf::Keyboard::Return:
        {
            std::string name = scoresName[index].getString();
            std::size_t first_ = name.find('_');
            if (first_ != std::string::npos)
                break;
            scores.insert(scores.begin()+index, std::pair<std::string, int>(name, score));
            if (scores.size() > 6)
                scores.pop_back();
            writeScores(scores);
            nextPhase = true;
            [[fallthrough]];
        }

        case sf::Keyboard::Escape:
            nextPhase = true;
            break;

        default:
            break;
    }
}

bool ScoreMenu::update()
{
    return nextPhase;
}

GamePhase* ScoreMenu::getNextPhase() const
{
    return new MainMenu();
}

void ScoreMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(title);
    for (unsigned i=0; i<6; ++i)
    {
        target.draw(scoresName[i], states);
        target.draw(scoresValues[i], states);
    }
}
