#ifndef CUBOID_INSTANCE_H
#define CUBOID_INSTANCE_H

#include <glm/glm/glm.hpp>
#include <3D/math/orientation_3d.h>

namespace fps {

    class CuboidInstance : public undicht::Orientation3D {
        public:

            unsigned int m_texture_id = 0;

            void setTextureID(unsigned int id);
            int getTextureID() const;

            CuboidInstance();
            CuboidInstance(const glm::vec3& position, const glm::vec3& scale = glm::vec3(1,1,1), unsigned int texture = 0);
            virtual ~CuboidInstance();

    };

} // fps

#endif // CUBOID_INSTANCE_H