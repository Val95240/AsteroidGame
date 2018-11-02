#ifndef HEADER_ASTEROID
#define HEADER_ASTEROID

#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "shapes.h"
#include "utils.h"
#include "FlyingObject.h"

class World;


class Asteroid : public FlyingObject
{
    public:
        Asteroid(World* world, int x, int y, int size);
        virtual ~Asteroid();

        virtual int getDamage() const;

    private:
        World* world;
        int size;
};



#endif
