#ifndef WORLD_H
#define WORLD_H

#include "cuboid.h"
#include "cuboid_instance.h"

namespace fps {


    class World {
        public:

            Cuboid m_base_cuboid;

            std::vector<undicht::graphics::Texture> m_textures;

            std::vector<CuboidInstance> m_cuboids;


            void addCuboid(const CuboidInstance& c);

            World();
            virtual ~World();

    };


} // fps

#endif // WORLD_H
