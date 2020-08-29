#ifndef WORLDFILE_H
#define WORLDFILE_H

#include <engine/file_loading/xml/xml_file.h>
#include <world/world.h>


namespace fps {





    class WorldFile : public undicht::XmlFile {
            /** a class to load world files */

        public:

            void loadWorld(World& world);


            WorldFile();
            WorldFile(const std::string& file_name);
            virtual ~WorldFile();


    };



} // fps

#endif // WORLDFILE_H
