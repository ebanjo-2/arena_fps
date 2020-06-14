#include <iostream>

// undicht includes
#include <engine/engine.h>
#include <3D/master_renderer_3d.h>

// game includes
#include <player/player.h>

#include <world/cuboid.h>
#include <world/world_renderer.h>


using namespace undicht;
using namespace fps;


int main() {


    Engine::initialize("undicht_0.37_engine/default_config.und");

    {

        window::Window* window = Engine::s_main_window;
        window->setTitle("Trying to build an arena fps using undicht 0.37");

        Player player;
        Cuboid first_cube;

        player.addTranslation(glm::vec3(1,0,2));

        while(!window->shouldClose()) {

            MasterRenderer3D::newFrame();

            WorldRenderer::loadCamera(player);
            WorldRenderer::drawCuboid(first_cube);

            MasterRenderer3D::endFrame();

            window->update();

        }

    }

    Engine::terminate();

    return 0;
}
