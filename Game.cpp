#include <iostream>
#include <time.h>
#include "Game.h"

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

Game::Game() {
    bg = new TexRect("assets/winter_bg.png", -1, 1, 2, 2);
    explosion = new Sprite("assets/explosion.png", 5, 5, -0.8, 0.8, 0.5, 0.5);
    // fries.push_back(new Projectiles("assets/fries.png", -0.3, 1.2, 0.1, 0.1));
    // fries.push_back(new Projectiles("assets/fries.png", 0.1, 1.2, 0.1, 0.1));
    // fries.push_back(new Projectiles("assets/fries.png", 0.4, 1.2, 0.1, 0.1));
    pepe = new Pepe();

    gameover = false;
    score = 0;
    temp = 0;
}

void Game::draw() {
    bg->draw();
    if (!gameover) {
        pepe->draw();

        update();

        draw_snowballs();
        draw_fries();

        if (temp % 200 == 0) {
            generate_snowballs();

            if (temp == 1000) {
                temp = 0;
            }
        }

        renderText("Score: " + std::to_string(score), -0.95, -0.95, GLUT_BITMAP_HELVETICA_18, 0,0,0);
    }
    else {
        renderText("Final Score: " + std::to_string(score), -0.220, -0.5, GLUT_BITMAP_HELVETICA_18, 0,0,0);
    }
    temp++;
}

void Game::draw_snowballs() {
    if (!snowballs.empty()) {
        std::vector<TexRect*>::iterator it = snowballs.begin();

        while (it != snowballs.end()) {
            (*it)->draw();
            (*it)->move();

            if (collided(*pepe, *(*it))) {
                gameover = true;
                explosion_visible = true;
                explosion->setX(pepe->getX());
                explosion->setY(pepe->getY());
                snowballs.erase(it);
            }
            else if ((*it)->getY() < -1) {
                score++;
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

void Game::generate_snowballs() {
    float arr[] = {-0.6, -0.1, 0.3};

    srand(time(0));

    for (int i = 0; i < 3; i++) {
        snowballs.push_back(new Projectiles("assets/snowball.png", arr[i], 1, 0.15, 0.15, rand()));
    }
}

Sprite* Game::get_explosion() const {
    return explosion;
}

bool Game::collided(const TexRect& one, const TexRect& two) const {
    return one.getX() < two.getX() + two.getW() && one.getX() + one.getW() > two.getX() && one.getY() > two.getY() - two.getH() && one.getY() - one.getH() < two.getY();
}

bool Game::is_gameover() const {
    return gameover;
}

bool Game::is_explosion_visible() const {
    return explosion_visible == true;
}

void Game::set_explosion_off() {
    explosion_visible = false;
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

void Game::renderText(
    std::string text, 
    float x, 
    float y, 
    void* font = GLUT_BITMAP_HELVETICA_18, 
    float r = 1, 
    float g = 1, 
    float b = 1
){
    glColor3f(r, g, b);
    float offset = 0;
    for (int i = 0; i < text.length(); i++) {
        glRasterPos3f(x+offset, y, 1);
        glutBitmapCharacter(font, text[i]);
        int w = glutBitmapWidth(font, text[i]);
        offset += ((float)w / 640)*2;
    }
}