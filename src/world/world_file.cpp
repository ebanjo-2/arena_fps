#include "world_file.h"

#include <graphics/file_loading/image_file.h>
#include <vector>
#include <core/string_tools.h>
#include <string>


using namespace undicht;
using namespace undicht::core;


namespace fps {

    WorldFile::WorldFile() {
        //ctor
    }

    WorldFile::WorldFile(const std::string& file_name) {

        open(file_name);
    }


    WorldFile::~WorldFile() {
        //dtor
    }


    void WorldFile::loadWorld(World& world) {

        std::string file_path = core::getFilePath(getFileName());

        // loading the textures used in the map
        ImageFile image_loader;
        std::vector<XmlElement*> images = getAllElements({"world", "textures", "image"});

        for(XmlElement* e : images) {
            world.m_textures.emplace_back(graphics::Texture());
            image_loader.open(file_path + e->getContent());
            image_loader.loadToTexture(world.m_textures.back());
            world.m_textures.back().setFilteringMethod(core::UND_NEAREST, core::UND_NEAREST);

        }

        // loading the geometry

        std::vector<XmlElement*> cuboids = getAllElements({"world", "geometry", "block"});

        for(XmlElement* c : cuboids) {

            std::vector<float> o; // orientation data
            extractFloatArray(o, c->getContent(), 6);

            int texture_id = 0;
            const XmlTagAttrib* texture_attr = c->getAttribute("texture");

            if(texture_attr) {

                texture_id = strtof(texture_attr->m_value.data(), 0);
            }

            if(o.size() >= 6) {

                world.addCuboid(CuboidInstance(glm::vec3(o[0],o[1],o[2]), glm::vec3( o[3],o[4],o[5]), texture_id));

            } else {

                std::cout << "failed to load cuboid, not enough data" << "\n";
            }
        }

    }


} // fps
