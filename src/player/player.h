#ifndef PLAYER_H
#define PLAYER_H


#include <3D/entities/perspective_camera_3d.h>

namespace fps {


    class Player : public undicht::PerspectiveCamera3D {
        public:


            Player();
            virtual ~Player();

    };

} // fps

#endif // PLAYER_H
