#include "world.h"


namespace fps {


    World::World() {
        //ctor
    }

    World::~World() {
        //dtor
    }

    void World::addCuboid(const CuboidInstance& c) {

        m_cuboids.push_back(c);
    }


} // fps
