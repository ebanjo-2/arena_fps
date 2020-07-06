#include <iostream>

// undicht includes
#include <engine/engine.h>
#include <3D/master_renderer_3d.h>
#include <graphics/file_loading/image_file.h>

#include <core/types.h>


// game includes
#include <player/player.h>

#include <world/cuboid.h>
#include <world/world_renderer.h>



using namespace undicht;
using namespace fps;


int main() {


    Engine::initialize("D:/Programmieren/CB Workspace/arena_fps/engine_config.und");

    {

        window::Window* window = Engine::s_main_window;
        window->setTitle("Trying to build an arena fps using undicht 0.37");

        Player player;

        World first_map;
        first_map.m_textures.emplace_back(graphics::Texture());
        //first_map.m_textures.back().setFilteringMethod(core::UND_LINEAR, core::UND_LINEAR);

        ImageFile image("res/tile_0.png");
        image.loadToTexture(first_map.m_textures.back());

        first_map.addCuboid(CuboidInstance(glm::vec3(0,-3,0), glm::vec3( 10,.1,10)));
        first_map.addCuboid(CuboidInstance(glm::vec3(5,0,-2), glm::vec3(0.5,6,6)));
        first_map.addCuboid(CuboidInstance(glm::vec3(-5,-2,-4), glm::vec3(0.5,2,1)));


        player.addTranslation(glm::vec3(1,0,2));

        while(!window->shouldClose()) {

            MasterRenderer3D::newFrame();

            WorldRenderer::loadCamera(player);
            WorldRenderer::drawWorld(first_map);

            MasterRenderer3D::endFrame();

            window->update();

        }

    }

    Engine::terminate();

    return 0;
}
