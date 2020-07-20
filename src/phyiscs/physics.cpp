#include "physics.h"
#include <iostream>

namespace undicht {


    Physics::Physics() {
        //ctor
    }

    Physics::~Physics() {
        //dtor
    }

    bool Physics::overlappingRanges(float range_1_start, float range_1_end, float range_2_start, float range_2_end) {

        // making sure the start of the range is before the end
        float s1 = glm::min(range_1_start, range_1_end);
        float e1 = glm::max(range_1_start, range_1_end);

        float s2 = glm::min(range_2_start, range_2_end);
        float e2 = glm::max(range_2_start, range_2_end);

        // cases in which the ranges do not overlap (is it really that easy ?)
        if((e1 < s2) || (e2 < s1)) {

            return false;
        }

        return true;
    }


    ////////////////////////////////// functions to test for the collision between mathematical objects ////////////////////////////////////////


    bool Physics::cuboidCollision(const glm::vec3& pos1, const glm::vec3& size1, const glm::vec3& pos2, const glm::vec3& size2) {
        /** tests if the cuboids volumes intersect at some point
        * @param pos: the middle of the cuboids
        * @param size: length of the edges */

        glm::vec3 half_size_1 = size1 / 2.0f;
        glm::vec3 half_size_2 = size2 / 2.0f;

        if(overlappingRanges(pos1.x - half_size_1.x, pos1.x + half_size_1.x, pos2.x - half_size_2.x, pos2.x + half_size_2.x)) {

            if(overlappingRanges(pos1.y - half_size_1.y, pos1.y + half_size_1.y, pos2.y - half_size_2.y, pos2.y + half_size_2.y)) {

                if(overlappingRanges(pos1.z - half_size_1.z, pos1.z + half_size_1.z, pos2.z - half_size_2.z, pos2.z + half_size_2.z)) {

                    return true;
                }
            }
        }

        return false;
    }


    ////////////////////////////////////functions to test for the collision between hitboxes ////////////////////////////////////////

    bool Physics::collision(Hitbox& h1, Hitbox& h2) {

        if((h1.getType() == UND_CUBOID_HITBOX) && (h1.getType() == UND_CUBOID_HITBOX)) {

            return cuboidCollision(h1.getWorldPosition(), h1.getWorldScale(), h2.getWorldPosition(), h2.getWorldScale());
        }

        // no known collision detection
        return false;
    }


} // undicht
