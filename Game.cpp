#include "Game.h"

Game::Game() {
    bg = new TexRect("assets/winter_bg.png", -1, 1, 2, 2);
    fries = new TexRect("assets/fries.png", -0.2, 0.3, 0.1, 0.1);
    snowball = new TexRect("assets/snowball.png", -0.5, 0.2, 0.15, 0.15);
    pepe = new Pepe();
}

void Game::draw() {
    bg->draw();
    fries->draw();
    snowball->draw();
    pepe->draw();
}

void Game::key_up(unsigned char key) {
    pepe->key_up(key);
}

void Game::key_down(unsigned char key) {
    pepe->key_down(key);
}

void Game::idle() {
    pepe->idle();
}

Game::~Game() {
    delete bg;
    delete fries;
    delete snowball;
    delete pepe;
}