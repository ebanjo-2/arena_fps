#include "cuboid.h"

#include <graphics/simple_geometry_generator.h>

using namespace undicht;

namespace fps {

    Cuboid::Cuboid() {

        std::vector<float> cube_vertices;
        std::vector<int> cube_indices;
        std::vector<float> cube_indexed_vertices;

        SimpleGeometryGenerator mesh_generator;
        mesh_generator.genCube(cube_vertices);
        mesh_generator.buildIndices(cube_vertices, core::BufferLayout({core::UND_VEC3F}), cube_indexed_vertices, cube_indices);

        getMesh().setLayout(core::BufferLayout({core::UND_VEC3F}));
        getMesh().setData(cube_indexed_vertices);
        getMesh().setIndexData(cube_indices);

        mesh_generator.loadTexture(getTexture(), "res/tile_0.png");
    }

    Cuboid::~Cuboid() {
        //dtor
    }

} // fps
