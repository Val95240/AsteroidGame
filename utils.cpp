#include "utils.h"

double fRand(double fMin, double fMax)
{
    double f = (double) rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int tabRand(double* tab, int size)
{
    double sum = std::accumulate(tab, tab+size, 0.0);
    double x = fRand(0, sum);
    int index = 0;
    while (index < size && tab[index] < x) {
        x -= tab[index];
        ++index;
    }
    return index;
}

void generateArray(int array[], int nbEdges, int min, int max, bool uniq)
{
    int value = 0;
    for (int i=0; i<nbEdges; ++i) {
        do {
            value = (int) fRand(min, max);
        } while (uniq && std::find(array, array+nbEdges, value) != array+nbEdges);
        array[i] = value;
    }
}


/* Return the normal axes to each edge of the two polygons
 * points1 and points2
 * */
vect_array getAxes(vect_array points1, vect_array points2)
{
    vect_array axes;

    for (unsigned i=0; i<points1.size(); ++i)
    {
        sf::Vector2f edge = points1[(i+1)%points1.size()] - points1[i];
        axes.push_back(sf::Vector2f(-edge.y, edge.x));
    }
    for (unsigned i=0; i<points2.size(); ++i)
    {
        sf::Vector2f edge = points2[(i+1)%points2.size()] - points2[i];
        axes.push_back(sf::Vector2f(-edge.y, edge.x));
    }

    return axes;
}

/* Compute the Projection of a shape onto an axis
 * Return the segment of this Projection [min, max]
 * */
Projection project(vect_array points, sf::Vector2f axis)
{
    Projection proj = {100000, -100000};
    for (sf::Vector2f edge : points)
    {
        double p = edge.x*axis.x + edge.y*axis.y;
        if (p < proj.first)
            proj.first = p;
        if (p > proj.second)
            proj.second = p;
    }
    return proj;
}

bool overlap(Projection project1, Projection project2)
{
    return !(project1.second < project2.first || project2.second < project1.first);
}


std::vector<Projection> addProjection(std::vector<Projection> projections, Projection newProj)
{
    std::vector<Projection> newProjections;
    for (unsigned i=0; i<projections.size(); i++)
    {
        Projection proj = projections[i];
        if (!(proj.second < newProj.first || newProj.second < proj.first)) {        // Intersection
            newProj.first = std::min(proj.first, newProj.first);
            newProj.second = std::max(proj.second, newProj.second);
        } else {
            newProjections.push_back(proj);
        }
    }
    newProjections.push_back(newProj);
    return newProjections;
}

std::vector<Projection> removeOverlap(std::vector<Projection>& border, sf::FloatRect const& bounds)
{
    if (bounds.top < 30)
        border = addProjection(border, Projection(bounds.left, bounds.left+bounds.width));

    if (bounds.left + bounds.width > settings::WIDTH - 30)
        border = addProjection(border, Projection(settings::WIDTH+bounds.top, settings::WIDTH+bounds.top+bounds.height));

    if (bounds.top + bounds.height > settings::HEIGHT + 30)
        border = addProjection(border, Projection(2*settings::WIDTH+settings::HEIGHT-bounds.left-bounds.width,
                                                  2*settings::WIDTH+settings::HEIGHT-bounds.left));
    if (bounds.left < 30)
        border = addProjection(border, Projection(2*(settings::WIDTH+settings::HEIGHT)-bounds.top-bounds.height,
                                                  2*(settings::WIDTH+settings::HEIGHT)-bounds.top));
    return border;
}

double span(std::vector<Projection> projections)
{
    double span = 0;
    for (Projection proj : projections)
        span += (proj.second - proj.first);
    return span;
}

std::pair<int, int> randomInProjection(std::vector<Projection>& border)
{
    double z = fRand(0, 2*(settings::WIDTH+settings::HEIGHT) - span(border));
    if (z < settings::WIDTH)
        return std::pair<int, int>(z, -40);

    if (z < settings::WIDTH + settings::HEIGHT)
        return std::pair<int, int>(settings::WIDTH+40, z-settings::WIDTH);

    if (z < 2*settings::WIDTH + settings::HEIGHT)
        return std::pair<int, int>(z-settings::WIDTH-settings::HEIGHT, settings::HEIGHT+40);

    return std::pair<int, int>(-40, z-2*settings::WIDTH-settings::HEIGHT);
}

double randomLessProjections(std::vector<Projection>& projections)
{
    double y = fRand(0, settings::HEIGHT - span(projections));
    std::sort(projections.begin(), projections.end());
    for (Projection proj : projections)
    {
        if (proj.first < y)
            y += (proj.second - proj.first);
        else
            break;
    }
    return 20 + (settings::HEIGHT-40) * y / settings::HEIGHT;
}


std::vector<std::pair<std::string, int>> readScores()
{
    std::ifstream file("scores", std::ios::in);
    std::vector<std::pair<std::string, int>> scores;

    if (file) {
        int line = 0;
        std::string name;
        int score;
        while (line < 6 && !file.eof())
        {
            file >> name >> score;
            scores.push_back(std::pair<std::string, int>((name == "???" ? "   " : name), score));
            ++line;
        }
        file.close();
    }

    while (scores.size() < 6)
        scores.push_back(std::pair<std::string, int>("   ", 0));
    return scores;
}

void writeScores(std::vector<std::pair<std::string, int>> scores)
{
    std::ofstream file("scores", std::ios::trunc);

    if (file)
    {
        for (std::pair<std::string, int> score : scores)
            file << ((score.first == "   ") ? "???" : score.first) << " " << score.second << std::endl;
        file.close();
    }
}
