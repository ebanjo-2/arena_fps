#ifndef CUBOID_H
#define CUBOID_H


#include <3D/entities/model_3d.h>


namespace fps {

    class Cuboid : public undicht::Model3D {
        /** a model with 6 sides, 8 corners, ... */
        public:

            Cuboid();
            virtual ~Cuboid();


    };


} // fps

#endif // CUBOID_H
