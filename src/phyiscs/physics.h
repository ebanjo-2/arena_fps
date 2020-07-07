#ifndef PHYSICS_H
#define PHYSICS_H


#include <glm/glm/glm.hpp>


namespace undicht {


    class Physics {

        public:

            static bool overlappingRanges(float range_1_start, float range_1_end, float range_2_start, float range_2_end);

        public:
            /** functions to test for the collision between objects
            * @param pos: the middle of the cuboids
            * @param size: length of the edges */

            /** tests if the cuboids volumes intersect at some point */
            static bool cuboidCollision(const glm::vec3& pos1, const glm::vec3& size1, const glm::vec3& pos2, const glm::vec3& size2);


            Physics();
            virtual ~Physics();

    };



} // undicht

#endif // PHYSICS_H
