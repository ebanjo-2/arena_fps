#include "world_renderer.h"
#include <3D/master_renderer_3d.h>

using namespace undicht;


namespace fps {

    WorldRenderer::WorldRenderer() {
        //ctor
    }

    WorldRenderer::~WorldRenderer() {
        //dtor
    }

    void WorldRenderer::loadCamera(undicht::Camera3D& cam) {


        MasterRenderer3D::setSceneCamera(cam);
    }


    void WorldRenderer::drawCuboid(Cuboid& c) {

            MasterRenderer3D::s_forward_renderer->prepare();
            MasterRenderer3D::s_forward_renderer->drawModel(c);
    }


} // fps
