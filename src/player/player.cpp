#include "player.h"
#include <engine/engine.h>
#include <window/key_ids.h>
#include <3D/physics/physics.h>
#include <3D/file_loading/collada/collada_file.h>


using namespace undicht;
using namespace undicht::window;

namespace fps {


    Player::Player() {
        //ctor

        m_key_input.setWindow(Engine::s_main_window);
        m_mouse_input.setWindow(Engine::s_main_window);

        m_hitbox.setPosition(glm::vec3(0,-1,0));
        m_hitbox.setScale(glm::vec3(0.5,2,0.5));

        ColladaFile f("res/cube.dae");
        f.loadHitbox(m_hitbox);

        m_hitbox.setTransfRelTo(&m_center);



        //m_hitbox.setTransfRelTo(this);
    }

    Player::~Player() {
        //dtor
    }


    bool Player::checkCollision(World& world) {

        m_center.setPosition(getPosition()); // reference position to the hitbox

        for(CuboidInstance& c : world.m_cuboids) {

            if(Physics::collision(m_hitbox, c.m_hitbox)) {

                return true;
            }

        }

        return false;
    }



    void Player::update(World& world) {

        //std::cout << getViewDirection().x << " " << getViewDirection().y << " " << getViewDirection().z << "\n";

        m_mouse_input.updateCursorOffset();

        // points to reset to if the collision test is positive
        glm::vec3 old_pos = getPosition();
        glm::vec3 pos_after_user_input;

        // hiding / showing the cursor
        if(m_key_input.getKeyState(UND_KEY_E)) {

            Engine::s_main_window->setCursorVisible(true);

        } else {

            Engine::s_main_window->setCursorVisible(false);

            // moving
            if(m_key_input.getKeyState(UND_KEY_LSHIFT)) {

                m_movement_speed = 0.1;
            } else {
                m_movement_speed = 0.05f;
            }

            if(m_key_input.getKeyState(UND_KEY_S)) {

                addTranslation(-1.0f * glm::vec3(1,0,1) * getViewDirection() * m_movement_speed);
            }

            if(m_key_input.getKeyState(UND_KEY_W)) {

                addTranslation(glm::vec3(1,0,1) * getViewDirection() * m_movement_speed);
            }

            if(m_key_input.getKeyState(UND_KEY_A)) {

                addTranslation(-1.0f * glm::normalize(glm::vec3(1,0,1) * glm::cross(getViewDirection(), glm::vec3(0,1,0))) * m_movement_speed);
            }

            if(m_key_input.getKeyState(UND_KEY_D)) {

                addTranslation(glm::normalize(glm::vec3(1,0,1) * glm::cross(getViewDirection(), glm::vec3(0,1,0))) * m_movement_speed);
            }

            if(m_key_input.getKeyState(UND_KEY_SPACE)) {
                // jump
                if((m_jumping_state < m_max_jump) && (m_jumping_state >= 0)) {

                    addTranslation(glm::vec3(0, 0.2, 0));
                    m_jumping_state += 0.1;
                } // gravity will do the rest

            }

            if(m_jumping_state >= m_max_jump) {
                m_jumping_state = -1;
            }


            // changing view direction
            float offset_x, offset_y;
            m_mouse_input.getCursorOffset(offset_x, offset_y);

            // trying to avoid gimbal lock
            glm::vec3 view_dir = getViewDirection();
            if(((offset_y > 0) && (view_dir.y > 0.99)) || ((offset_y < 0) && (view_dir.y < -0.99))) {
                // no rotating any further
                offset_y = 0;
            }



            // adding pitch
            glm::vec3 pitch_axis = glm::normalize(glm::cross(getViewDirection(), glm::vec3(0,1,0)));
            glm::quat rotation = glm::angleAxis(offset_y * m_mouse_speed, pitch_axis) * getRotation();

            // adding yaw
            rotation = glm::angleAxis(offset_x * m_mouse_speed * -1.0f, glm::vec3(0,1,0)) * rotation;

            // saving the new rotation
            setRotation(rotation);


        }

    }

} // fps
