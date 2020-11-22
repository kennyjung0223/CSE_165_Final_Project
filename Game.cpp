#include <iostream>
#include "Game.h"

Game::Game() {
    bg = new TexRect("assets/winter_bg.png", -1, 1, 2, 2);
    objects.push_back(new Fries());
    objects.push_back(new Fries());
    // objects.push_back(new TexRect("assets/snowball.png", -0.5, 0.2, 0.15, 0.15));
    pepe = new Pepe();
}

void Game::draw() {
    bg->draw();
    pepe->draw();

    update();

    if (!objects.empty()) {
        std::vector<TexRect*>::iterator it = objects.begin();

        while (it != objects.end()) {
            (*it)->draw();
            (*it)->move();

            if (collided(*pepe, *(*it))) {
                pepe->increment_speed();
                objects.erase(it);
                std::cout << pepe->get_speed() << std::endl;
            }
            else {
                it++;
            }
        }
    }
}

void Game::key_up(unsigned char key) {
    if (key == 'w') {
        movingUp = false;
    }
    else if (key == 'a') {
        movingLeft = false;
    }
    else if (key == 'd') {
        movingRight = false;
    }
    else if (key == 's') {
        movingDown = false;
    }
}

void Game::key_down(unsigned char key) {
    if (key == 'w') {
        movingUp = true;
    }
    else if (key == 'a') {
        movingLeft = true;
    }
    else if (key == 'd') {
        movingRight = true;
    }
    else if (key == 's') {
        movingDown = true;
    }
    else if (key == ' ') {
        objects.pop_back();
    }
}

void Game::update() {
    if (movingUp) {
        pepe->moveUp();
    }
    if (movingLeft) {
        pepe->moveLeft();
    }
    if (movingRight) {
        pepe->moveRight();
    }
    if (movingDown) {
       pepe->moveDown();
    }
}

bool Game::collided(const TexRect& one, const TexRect& two) const {
    return one.getX() < two.getX() + two.getW() && one.getX() + one.getW() > two.getX() && one.getY() > two.getY() - two.getH() && one.getY() - one.getH() < two.getY();
}

void Game::idle() {
    pepe->idle();
}

Game::~Game() {
    delete bg;
    delete pepe;

    for (std::vector<TexRect*>::iterator it = objects.begin(); it != objects.end(); it++) {
        delete (*it);
    }
}