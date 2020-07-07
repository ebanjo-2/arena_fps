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

#include <phyiscs/physics.h>



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

        ImageFile image("res/tile_0.png");
        image.loadToTexture(first_map.m_textures.back());
        first_map.m_textures.back().setFilteringMethod(core::UND_LINEAR, core::UND_LINEAR);


        first_map.addCuboid(CuboidInstance(glm::vec3(0,-3,0), glm::vec3( 10,.1,10)));
        first_map.addCuboid(CuboidInstance(glm::vec3(1,-1,-2), glm::vec3(0.5,5,0.5)));
        first_map.addCuboid(CuboidInstance(glm::vec3(0,1,-4), glm::vec3(2,2,2)));


        player.addTranslation(glm::vec3(1,0,2));

        std::cout << Physics::cuboidCollision(first_map.m_cuboids.at(0).getPosition(), first_map.m_cuboids.at(0).getScale(),
                                              first_map.m_cuboids.at(1).getPosition(), first_map.m_cuboids.at(1).getScale()) << "\n";

        while(!window->shouldClose()) {

            MasterRenderer3D::newFrame();

            WorldRenderer::loadCamera(player);
            WorldRenderer::drawWorld(first_map);

            MasterRenderer3D::endFrame();

            window->update();
            player.update(first_map);

        }

    }

    Engine::terminate();

    return 0;
}
