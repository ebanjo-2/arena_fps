#include <iostream>

// undicht includes
#include <core/core.h>
#include <engine/engine.h>
#include <3D/master_renderer_3d.h>
#include <3D/file_loading/collada/collada_file.h>

#include <3D/physics/collision_detection.h>
#include <3D/math/math_tools.h>

#include <core/types.h>
#include <core/string_tools.h>


// game includes
#include <player/player.h>

#include <world/world_file.h>
#include <world/cuboid.h>
#include <world/world_renderer.h>

#include <3D/physics/physics.h>

#include <3D/math/relations.h>
#include <graphics/simple_geometry_generator.h>
#include <glm/glm/gtc/matrix_transform.hpp>



using namespace undicht;
using namespace core;
using namespace fps;


int main() {

    std::string file_path = core::getFilePath(UND_CODE_SRC_FILE, 1);

    std::cout << file_path << "\n";

    Engine::initialize(file_path + "engine_config.und");


    {

        //initGeometry();

        window::Window* window = Engine::s_main_window;
        window->setTitle("Trying to build an arena fps using undicht 0.37");


        Player player;

        World first_map;

        WorldFile map_file("res/first_map.arena");
        map_file.loadWorld(first_map);

        player.addTranslation(glm::vec3(-3,0,-3));

        Plane plane1;
        plane1.def(glm::vec3(0,0,0), glm::vec3(0,1,0));

        Plane plane2;
        plane2.def(glm::vec3(0,0,0), glm::vec3(1,1,1));

        Ray inters;
        intersecPlanePlane(plane1, plane2, inters);

        std::cout << inters.getPoint();

        double start_time;

        while(!window->shouldClose()) {

            start_time = core::Core::getTime();

            MasterRenderer3D::newFrame();

            MasterRenderer3D::s_sketch_renderer->setDrawColor(glm::vec3(0,1,0))->drawTriangle(glm::vec3(0,0,0), glm::vec3(0,2,0), glm::vec3(0,0,2));
            MasterRenderer3D::s_sketch_renderer->drawPlane(plane1)->setDrawColor(glm::vec3(1,0,0))->drawPlane(plane2);
            MasterRenderer3D::s_sketch_renderer->setDrawColor(glm::vec3(0,0,1))->drawRay(inters, 0.2);

            WorldRenderer::loadCamera(player);
            WorldRenderer::drawWorld(first_map);

            MasterRenderer3D::endFrame();

            window->update();
            player.update(first_map);

            //std::cout << "fps: " << 1 / (core::Core::getTime() - start_time) << "\n";

        }

    }

    Engine::terminate();

    return 0;
}
