#ifndef HITBOX_POLYGON_H
#define HITBOX_POLYGON_H


#include <vector>
#include "math/plane.h"
#include "math/line.h"
#include "3D/math/orientation_3d.h"

#include <glm/glm/glm.hpp>


namespace undicht {


    class HitboxPolygon : public Orientation3D {

        public:

            std::vector<glm::vec3> m_vertices;
            Plane m_plane; // the plane on which all the vertices are

        public:

            /** the vertices all have to be on the same plane
            * and they have to be defined in clockwise order when viewed from outside the model */
            virtual void setVertices(const std::vector<glm::vec3>& vertices);

            /** @return false if the point is excluded from the model by this polygon*/
            virtual bool insideModel(const glm::vec3& point);

            /** @param dir_factor: the factor with which the direction vector of the line has to be multiplied
            * to get from the lines base point to the intersection whith the polygons plane */
            virtual bool insideModel(const Line& l, float& dir_factor);

            HitboxPolygon();
            HitboxPolygon(const std::vector<glm::vec3>& vertices);
            virtual ~HitboxPolygon();

    };


} // undicht

#endif // HITBOX_POLYGON_H
