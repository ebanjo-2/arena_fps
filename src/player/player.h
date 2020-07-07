#ifndef PLAYER_H
#define PLAYER_H


#include <3D/entities/perspective_camera_3d.h>
#include <window/key_input_watcher.h>
#include <window/mouse_input_watcher.h>

#include <world/world.h>


namespace fps {


    class Player : public undicht::PerspectiveCamera3D {
        public:

            float m_movement_speed = 0.001f;
            float m_mouse_speed = 100.0f;

            glm::vec3 m_hitbox_size = glm::vec3(0.5,1,0.5);
            glm::vec3 m_hitbox_offset = glm::vec3(0,-0.5,0);

            undicht::window::KeyInputWatcher m_key_input;
            undicht::window::MouseInputWatcher m_mouse_input;



            /** @param world: the world with which to check for collision */
            void update(World& world);

            Player();
            virtual ~Player();

    };

} // fps

#endif // PLAYER_H
