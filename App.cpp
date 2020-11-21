#include <iostream>
#include "App.h"

App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
    game = new Game();
} 

void App::draw() const {
    game->draw();
}

void App::keyUp(unsigned char key, float x, float y){
    game->key_up(key);
    redraw();
}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){
        exit(0);
    }
    game->key_down(key);
    redraw();
}

void App::idle() {
    game->idle();
    redraw();
}

App::~App(){   
    delete game;
    std::cout << "Exiting..." << std::endl;
}
