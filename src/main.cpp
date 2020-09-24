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


Model3D* cube_model = 0;
Model3D* sphere_model = 0;



void initGeometry() {

    SimpleGeometryGenerator g;

    std::vector<float> vertices;

    g.genCube(vertices);

    cube_model = new Model3D;
    cube_model->getMesh().setData(vertices);
    cube_model->getMesh().setLayout(BufferLayout({UND_VEC3F}));

    vertices.clear();

    g.genSphere(vertices);

    sphere_model = new Model3D;
    sphere_model->getMesh().setData(vertices);
    sphere_model->getMesh().setLayout(BufferLayout({UND_VEC3F}));

}

void termGeometry() {

    delete sphere_model;
    delete cube_model;
}


void draw(const glm::vec3& point) {

    sphere_model->setScale(glm::vec3(0.1, 0.1, 0.1));
    sphere_model->setPosition(point);

    MasterRenderer3D::s_forward_renderer->drawModel(*sphere_model);
}

void draw(const Ray& r) {

    cube_model->setScale(glm::vec3(0.1, 0.1, 1000.0));
    cube_model->setPosition(r.getPoint());

    // calculating the rotation (works only if the ray is not parallel to the x or y axis)
    // 1. rotation around y axis

    float angle_y = 0;

    if(r.getDir().z != 0) {
        angle_y = glm::degrees(glm::atan(r.getDir().x/r.getDir().z));
    } else {
        angle_y = 90;
    }

    std::cout << "angle around y: " << angle_y << "\n";

    glm::quat rot = glm::angleAxis(angle_y, glm::vec3(0,1,0));


    // adding pitch
    glm::vec3 pitch_axis = glm::cross(r.getDir(), glm::vec3(0,1,0));

    if(!glm::length(pitch_axis)) {
        pitch_axis = glm::vec3(1,0,0);
    } else {
        pitch_axis = glm::normalize(pitch_axis);
    }

    std::cout << pitch_axis << "\n";
    float pitch_angle = glm::degrees(glm::asin(r.getDir().y / glm::length(r.getDir())));

    std::cout << "pitch angle: " << pitch_angle << "\n";

    rot = glm::rotate(rot, pitch_angle, pitch_axis);

    cube_model->setRotation(rot);

    // changing the rays color to match its direction
    glm::vec3 color = glm::normalize(r.getDir());
    unsigned char rgba[4] = {color.x * 255, color.y * 255, color.z * 255, 1};

    cube_model->getTexture().setPixelFormat(BufferLayout({UND_UNSIGNED_CHAR, UND_UNSIGNED_CHAR, UND_UNSIGNED_CHAR, UND_UNSIGNED_CHAR}));
    cube_model->getTexture().setSize(1,1);
    cube_model->getTexture().setData((char*)rgba,4);


    MasterRenderer3D::s_forward_renderer->drawModel(*cube_model);
}

int main() {

    std::string file_path = core::getFilePath(UND_CODE_SRC_FILE, 1);

    std::cout << file_path << "\n";

    Engine::initialize(file_path + "engine_config.und");


    {

        initGeometry();

        window::Window* window = Engine::s_main_window;
        window->setTitle("Trying to build an arena fps using undicht 0.37");

        PolygonHitbox h1;
        PolygonHitbox h2;

        h1.addPolygon(HitboxPolygon({glm::vec3(0.5,0,0), glm::vec3(-0.5,0,0), glm::vec3(0,0,0.5)}));
        h2.addPolygon(HitboxPolygon({glm::vec3(0,0.5,0), glm::vec3(0,-0.6,0), glm::vec3(0,0,0.5)}));
        h2.setPosition(glm::vec3(0,0,0));
        h1.setScale(glm::vec3(3,3,3));

        bool collision = h1.collision(h2);

        std::cout << "collision: " << collision << "\n";

        LineHitbox line1;
        LineHitbox line2;

        line1.def(glm::vec3(0,0,0), glm::vec3(0.5,0.5,0.5));
        line2.def(glm::vec3(1,0,0), glm::vec3(1,-1,1));

        float f1, f2;
        //std::cout << line1.intersecOnPlane(line2, f1, f2) << " " << f1 << " " << f2 << "\n";

        Player player;

        World first_map;

        WorldFile map_file("res/first_map.arena");
        map_file.loadWorld(first_map);

        player.addTranslation(glm::vec3(-3,0,-3));

        Ray x_axis(glm::vec3(0,0,0), glm::vec3(1,0,0));
        Ray y_axis(glm::vec3(0,0,0), glm::vec3(0,1,0));
        Ray z_axis(glm::vec3(0,0,0), glm::vec3(0,0,1));

        Ray ray(glm::vec3(0,0,0), glm::vec3(0,1,1));


        double start_time;

        while(!window->shouldClose()) {

            start_time = core::Core::getTime();

            MasterRenderer3D::newFrame();

            /*draw(glm::vec3(0,2,0));
            draw(x_axis);
            draw(y_axis);
            draw(z_axis);

            draw(ray);*/

            MasterRenderer3D::s_sketch_renderer->drawSphere(glm::vec3(2,2,0), glm::vec3(0.8), 1);
            MasterRenderer3D::s_sketch_renderer->drawRay(x_axis, x_axis.getDir());
            MasterRenderer3D::s_sketch_renderer->drawRay(y_axis, y_axis.getDir());
            MasterRenderer3D::s_sketch_renderer->drawRay(z_axis, z_axis.getDir());





            WorldRenderer::loadCamera(player);
            WorldRenderer::drawWorld(first_map);

            MasterRenderer3D::endFrame();

            window->update();
            player.update(first_map);

            //std::cout << "fps: " << 1 / (core::Core::getTime() - start_time) << "\n";

        }

        termGeometry();
    }

    Engine::terminate();

    return 0;
}
