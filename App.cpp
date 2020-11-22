#include <iostream>
#include "App.h"

static App* singleton;

void explosion_timer(int id) {
    singleton->game->get_explosion()->advance();

    if (singleton->game->get_explosion()->isDone()) {
        singleton->game->explosion_visible = false;
    }
    glutTimerFunc(1200, explosion_timer, id);
}

App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
    game = new Game();
    singleton = this;
} 

void App::draw() const {
    game->draw();
    if (singleton->game->explosion_visible) {
        singleton->game->get_explosion()->draw();
        explosion_timer(1);
    }
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
