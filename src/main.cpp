#include <iostream>

#include <engine/engine.h>

using namespace undicht;


int main() {


    Engine::initialize("undicht_0.37_engine/default_config.und");

    {

        window::Window* window = Engine::s_main_window;
        window->setTitle("Trying to build an arena fps using undicht 0.37");


        while(!window->shouldClose()) {

            window->update();

        }

    }

    Engine::terminate();

    return 0;
}
