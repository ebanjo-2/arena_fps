#ifndef CUBOID_HITBOX_H
#define CUBOID_HITBOX_H


#include <physics/hitbox.h>

namespace undicht {


    class CuboidHitbox : public Hitbox {
        /** the hitboxes position is its center, the scale the length of its edges*/
        public:

            virtual int getType();

            CuboidHitbox();
            virtual ~CuboidHitbox();

    };

} // undicht

#endif // CUBOID_HITBOX_H
