#include <iostream>
#include "Game.h"

Game::Game() {
    bg = new TexRect("assets/winter_bg.png", -1, 1, 2, 2);
    explosion = new Sprite("assets/explosion.png", 5, 5, -0.8, 0.8, 0.5, 0.5);
    fries.push_back(new Projectiles("assets/fries.png", -0.3, 1, 0.1, 0.1));
    fries.push_back(new Projectiles("assets/fries.png", 0.1, 1, 0.1, 0.1));
    fries.push_back(new Projectiles("assets/fries.png", 0.4, 1, 0.1, 0.1));
    snowballs.push_back(new Projectiles("assets/snowball.png", -0.6, 1, 0.15, 0.15));
    snowballs.push_back(new Projectiles("assets/snowball.png", -0.1, 1, 0.15, 0.15));
    snowballs.push_back(new Projectiles("assets/snowball.png", 0.3, 1, 0.15, 0.15));
    pepe = new Pepe();
}

void Game::draw() {
    bg->draw();
    pepe->draw();

    update();

    draw_snowballs();
    draw_fries();
}

void Game::draw_snowballs() {
    if (!snowballs.empty()) {
        std::vector<TexRect*>::iterator it = snowballs.begin();

        while (it != snowballs.end()) {
            (*it)->draw();
            (*it)->move();

            if (collided(*pepe, *(*it))) {
                explosion_visible = true;
                explosion->setX(pepe->getX());
                explosion->setY(pepe->getY());
                snowballs.erase(it);
            }
            else {
                it++;
            }
        }
    }
}

void Game::draw_fries() {
    if (!fries.empty()) {
        std::vector<TexRect*>::iterator it = fries.begin();

        while (it != fries.end()) {
            (*it)->draw();
            (*it)->move();

            if (collided(*pepe, *(*it))) {
                pepe->increment_speed();
                fries.erase(it);
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

Sprite* Game::get_explosion() const {
    return explosion;
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

    for (std::vector<TexRect*>::iterator it = snowballs.begin(); it != snowballs.end(); it++) {
        delete (*it);
    }

    for (std::vector<TexRect*>::iterator it = fries.begin(); it != fries.end(); it++) {
        delete (*it);
    }
}