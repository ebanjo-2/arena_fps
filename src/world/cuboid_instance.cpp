#include "cuboid_instance.h"

namespace fps {

    CuboidInstance::CuboidInstance() {
        //ctor

        m_hitbox.setTransfRelTo(this);
    }

    CuboidInstance::CuboidInstance(const glm::vec3& position, const glm::vec3& scale, unsigned int texture) {

        setTextureID(texture);
        setPosition(position);
        setScale(scale);

        m_hitbox.setTransfRelTo(this);
    }

    CuboidInstance::~CuboidInstance() {
        //dtor
    }

    void CuboidInstance::setTextureID(unsigned int id) {

        m_texture_id = id;
    }

    int CuboidInstance::getTextureID() const {

        return m_texture_id;
    }


} // fps
