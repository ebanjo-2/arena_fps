#include "simple_polygon_hitbox.h"


namespace undicht {

    SimplePolygonHitbox::SimplePolygonHitbox() {
        //ctor
    }

    SimplePolygonHitbox::~SimplePolygonHitbox() {
        //dtor
    }

    bool SimplePolygonHitbox::collision(const glm::vec3& point) {
        /** testing whether the point is inside the hitbox or not */

    }

    bool SimplePolygonHitbox::collision(const glm::vec3& line_start, const glm::vec3& line_end) {
        /** testing whether any part of the line is in the hitbox or not */


    }


    ///////////////////////////////////////// managing the polygons //////////////////////////////////////////

    int SimplePolygonHitbox::addPolygon(const HitboxPolygon& polygon) {

        m_polygons.push_back(polygon);
        m_polygons.back().setTransfRelTo(this);

        return m_polygons.size() - 1;
    }

    HitboxPolygon& SimplePolygonHitbox::getPolygon(int id) {

        return m_polygons.at(id);
    }


} // undicht
