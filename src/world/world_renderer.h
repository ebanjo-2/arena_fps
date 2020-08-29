#ifndef WORLD_RENDERER_H
#define WORLD_RENDERER_H

#include <world/cuboid.h>
#include <world/world.h>
#include <3D/entities/camera_3d.h>

namespace fps {


    class WorldRenderer{
        public:

            static void loadCamera(undicht::Camera3D& cam);
            static void drawCuboid(Cuboid& c);

            static void drawWorld(World& w);

            WorldRenderer();
            virtual ~WorldRenderer();

    };

} // fps

#endif // WORLD_RENDERER_H
