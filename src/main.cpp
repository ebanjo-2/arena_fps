#include <iostream>

// undicht includes
#include <core/core.h>
#include <engine/engine.h>
#include <3D/master_renderer_3d.h>
#include <graphics/file_loading/image_file.h>

#include <core/types.h>
#include <core/string_tools.h>


// game includes
#include <player/player.h>

#include <world/cuboid.h>
#include <world/world_renderer.h>

#include <phyiscs/physics.h>



using namespace undicht;
using namespace core;
using namespace fps;


int main() {

    std::string file_path = core::getFilePath(UND_CODE_SRC_FILE, 1);

    Engine::initialize(file_path + "engine_config.und");

    std::cout << file_path + "engine_config.und" << "\n";

    {

        window::Window* window = Engine::s_main_window;
        window->setTitle("Trying to build an arena fps using undicht 0.37");

        Player player;

        World first_map;

        first_map.m_textures.emplace_back(graphics::Texture());
        ImageFile image("res/tile_0.png");
        image.loadToTexture(first_map.m_textures.at(0));
        first_map.m_textures.back().setFilteringMethod(core::UND_NEAREST, core::UND_NEAREST);

        first_map.m_textures.emplace_back(graphics::Texture());
        image.open("res/tile_1.png");
        image.loadToTexture(first_map.m_textures.at(1));
        first_map.m_textures.back().setFilteringMethod(core::UND_NEAREST, core::UND_NEAREST);

        first_map.m_textures.emplace_back(graphics::Texture());
        image.open("res/wood_box.png");
        image.loadToTexture(first_map.m_textures.at(2));
        first_map.m_textures.back().setFilteringMethod(core::UND_NEAREST, core::UND_NEAREST);

        first_map.m_textures.emplace_back(graphics::Texture());
        image.open("res/bricks.png");
        image.loadToTexture(first_map.m_textures.at(3));
        first_map.m_textures.back().setFilteringMethod(core::UND_NEAREST, core::UND_NEAREST);


        first_map.addCuboid(CuboidInstance(glm::vec3(0,-3,0), glm::vec3( 15,.1,15), 1));
        first_map.addCuboid(CuboidInstance(glm::vec3(1,-2.5,-2), glm::vec3(0.5,5,0.5)));
        first_map.addCuboid(CuboidInstance(glm::vec3(2,-2,-4), glm::vec3(2,2,2),3));
        first_map.addCuboid(CuboidInstance(glm::vec3(0,-2.5,-4), glm::vec3(1,1,1), 2));
        first_map.addCuboid(CuboidInstance(glm::vec3(0.1,0,0.1), glm::vec3(3,0.1,3),2));
        first_map.addCuboid(CuboidInstance(glm::vec3(7.25,1.5,0), glm::vec3(0.5,3,3),3));


        player.addTranslation(glm::vec3(1,5,1));

        double start_time;


        while(!window->shouldClose()) {

            start_time = core::Core::getTime();

            MasterRenderer3D::newFrame();

            WorldRenderer::loadCamera(player);
            WorldRenderer::drawWorld(first_map);

            MasterRenderer3D::endFrame();

            window->update();
            player.update(first_map);

            std::cout << "fps: " << 1 / (core::Core::getTime() - start_time) << "\n";

        }

    }

    Engine::terminate();

    return 0;
}
