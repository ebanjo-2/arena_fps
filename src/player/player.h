#ifndef PLAYER_H
#define PLAYER_H


#include <3D/entities/perspective_camera_3d.h>
#include <window/key_input_watcher.h>
#include <window/mouse_input_watcher.h>

#include <world/world.h>

#include <phyiscs/cuboid_hitbox.h>

using namespace undicht;

namespace fps {


    class Player : public undicht::PerspectiveCamera3D {
        public:

            float m_movement_speed = 0.001f;
            float m_mouse_speed = 100.0f;

            float m_jumping_state = 0;
            float m_max_jump = 1.3;

            glm::vec3 m_hitbox_size = glm::vec3(0.5,1,0.5);
            glm::vec3 m_hitbox_offset = glm::vec3(0,-0.5,0);

            Orientation3D m_center; // reference point to the hitbox, doesnt get rotated
            CuboidHitbox m_hitbox;

            undicht::window::KeyInputWatcher m_key_input;
            undicht::window::MouseInputWatcher m_mouse_input;

        public:

            bool checkCollision(World& world);


            /** @param world: the world with which to check for collision */
            void update(World& world);

            Player();
            virtual ~Player();

    };

} // fps

#endif // PLAYER_H
