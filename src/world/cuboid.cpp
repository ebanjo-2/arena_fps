#include "cuboid.h"

#include <graphics/simple_geometry_generator.h>
#include <3D/file_loading/collada/collada_file.h>

using namespace undicht;

namespace fps {

    Cuboid::Cuboid() {

        ColladaFile f("res/cube.dae");
        f.loadModel(*this);

    }

    Cuboid::~Cuboid() {
        //dtor
    }

} // fps
