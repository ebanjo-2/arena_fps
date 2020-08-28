#include "hitbox_polygon.h"


namespace undicht {

    HitboxPolygon::HitboxPolygon() {
        //ctor
    }

    HitboxPolygon::HitboxPolygon(const std::vector<glm::vec3>& vertices) {

        setVertices(vertices);
    }

    HitboxPolygon::~HitboxPolygon() {
        //dtor
    }


    void HitboxPolygon::setVertices(const std::vector<glm::vec3>& vertices) {
        /** the vertices all have to be on the same plane
        * and they have to be defined in clockwise order when viewed from outside the model */

        if(vertices.size() < 3) {

            return;
        }

        m_plane.def(vertices[0], vertices[1], vertices[2]);
        m_vertices = vertices;

    }

    bool HitboxPolygon::insideModel(const glm::vec3& point) {
        /** @return false if the point is excluded from the model by this polygon */

        if(glm::dot(m_plane.getNormal(), point - m_plane.getPoint()) >= 0) {

            return false;
        } else {

            return true;
        }

    }


    bool HitboxPolygon::insideModel(const Line& l, float& dir_factor) {
        /** @param dir_factor: the factor with which the direction vector of the line has to be multiplied
        * to get from the lines base point to the intersection whith the polygons plane */

        return intersecPlaneLine(m_plane, l, dir_factor);
    }


} // undicht
