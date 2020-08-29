#include <iostream>

// undicht includes
#include <core/core.h>
#include <engine/engine.h>
#include <3D/master_renderer_3d.h>

#include <core/types.h>
#include <core/string_tools.h>


// game includes
#include <player/player.h>

#include <world/world_file.h>
#include <world/cuboid.h>
#include <world/world_renderer.h>

#include <3D/physics/physics.h>

#include <3D/math/relations.h>



using namespace undicht;
using namespace core;
using namespace fps;


int main() {

    std::string file_path = core::getFilePath(UND_CODE_SRC_FILE, 1);

    std::cout << file_path << "\n";

    Engine::initialize(file_path + "engine_config.und");


    {

        window::Window* window = Engine::s_main_window;
        window->setTitle("Trying to build an arena fps using undicht 0.37");

        Player player;

        World first_map;

        WorldFile map_file("res/first_map.arena");
        map_file.loadWorld(first_map);


        player.addTranslation(glm::vec3(1,5,1));

        double start_time;

        glm::vec3 point;
        Plane plane(glm::vec3(0,1,0), glm::vec3(0,1,0));
        Line line(glm::vec3(1,0,0), glm::vec3(1,1,0));

        std::cout << "intersection: " << intersecPlaneLine(plane, line, point) << "\n";
        std::cout << point.x << " " << point.y << " " << point.z << "\n";


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
