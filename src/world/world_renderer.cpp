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

        MasterRenderer3D::s_forward_renderer->drawModel(c);

    }

    void WorldRenderer::drawWorld(World& w) {

        MasterRenderer3D::s_forward_renderer->prepare();

        for(CuboidInstance& c : w.m_cuboids) {

            w.m_base_cuboid.setPosition(c.getPosition());
            w.m_base_cuboid.setScale(c.getScale());


            if(c.getTextureID() < w.m_textures.size()) {

                w.m_base_cuboid.m_child_models.at(0).setTexture(w.m_textures.at(c.getTextureID()));
            }

            drawCuboid(w.m_base_cuboid);
        }
    }



} // fps
