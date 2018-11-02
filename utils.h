#ifndef HEADER_UTILS
#define HEADER_UTILS

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
#include <fstream>
#include <exception>

#include <SFML/Graphics.hpp>
#include "Settings.h"

using vect_array =  std::vector<sf::Vector2f>;
using Projection = std::pair<double, double>;


struct GameMode
{
    GameMode(std::vector<std::pair<int*, int>> settingValues) : settingValues(settingValues) { }

    std::vector<std::pair<int*, int>> settingValues;

    void apply() {
        for (unsigned i=0; i<settingValues.size(); ++i)
            *(settingValues[i].first) = settingValues[i].second;
    }
};

double fRand(double fMin, double fMax);
int tabRand(double* tab, int size);
void generateArray(int array[], int nbEdges, int min, int max, bool uniq);

vect_array getAxes(vect_array points1, vect_array points2);
Projection project(vect_array points, sf::Vector2f axis);
bool overlap(Projection project1, Projection project2);

double span(std::vector<Projection> projections);
std::vector<Projection> addProjection(std::vector<Projection> projections, Projection newProj);
std::vector<Projection> removeOverlap(std::vector<Projection>& border, sf::FloatRect const& bounds);
std::pair<int, int> randomInProjection(std::vector<Projection>& border);
double randomLessProjections(std::vector<Projection>& projections);

std::vector<std::pair<std::string, int>> readScores();
void writeScores(std::vector<std::pair<std::string, int>> scores);


#endif
