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
    pepe = new Pepe();

    gameover = false;
    score = 0;
    temp = 0;
    sb_quantity = 3;
    high_score = 0;
}

int Game::get_high_score(int score) {
    if (score > high_score) {
        high_score = score;
    }
    return high_score;
}

void Game::draw() {
    bg->draw();
    if (!gameover) {
        pepe->draw();

        update();

        draw_snowballs();
        draw_apples();

        if (temp % 1000 == 0) {
            generate_apples();
        }

        if (temp % 50 == 0) {
            generate_snowballs();

            if (temp == 1000) {
                temp = 0;
            }
        }

        renderText("Score: " + std::to_string(score), -0.95, -0.95, GLUT_BITMAP_HELVETICA_18, 0,0,0);
    }
    else {
        explode();

        renderText("Final Score: " + std::to_string(score), -0.17, -0.5, GLUT_BITMAP_HELVETICA_18, 0,0,0);
        renderText("High Score: " + std::to_string(get_high_score(score)), -0.17, -0.6, GLUT_BITMAP_HELVETICA_18, 0,0,0);
        renderText("Press r to restart", -0.2, -0.7, GLUT_BITMAP_HELVETICA_18, 0,0,0);
        renderText("Press esc to quit", -0.2, -0.8, GLUT_BITMAP_HELVETICA_18, 0,0,0);
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

void Game::draw_apples() {
    if (!apples.empty()) {
        std::vector<TexRect*>::iterator it = apples.begin();

        while (it != apples.end()) {
            (*it)->draw();
            (*it)->move();

            if (collided(*pepe, *(*it))) {
                score += 3;
                pepe->increment_speed();
                apples.erase(it);
            }
            else if ((*it)->getY() < -1) {
                apples.erase(it);
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
    else if (gameover && key == 'r') {
        reset();
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

void Game::generate_apples() {
    float arr[] = {-0.4, 0.2, 0.5};
    srand(time(0));

    for (int i = 0; i < A_QUANTITY; i++) {
        apples.push_back(new Projectiles("assets/apple.png", arr[i], 1, 0.125, 0.125, rand()));
    }
}

void Game::generate_snowballs() {
    float arr[] = {-0.6, -0.1, 0.3};

    srand(time(0));

    if (score != 0 && score % 100 == 0) {
        sb_quantity++;
    }

    for (int i = 0; i < sb_quantity; i++) {
        snowballs.push_back(new Projectiles("assets/snowball_c.png", arr[i], 1, 0.1, 0.1, rand()));
    }
}

void Game::explode() {
    if (explosion_visible) {
        explosion->draw();
    }
    if (explosion->isDone()) {
        explosion_visible = false;
    }
    explosion->advance();
}

bool Game::collided(const TexRect& one, const TexRect& two) const {
    return one.getX() < two.getX() + two.getW() && one.getX() + one.getW() > two.getX() && one.getY() > two.getY() - two.getH() && one.getY() - one.getH() < two.getY();
}

bool Game::is_gameover() const {
    return gameover;
}

void Game::idle() {
    pepe->idle();
}

void Game::reset() {
    gameover = false;
    pepe->setX(0);
    pepe->setY(0);
    pepe->reset_speed();
    snowballs.clear();
    apples.clear();
    score = 0;
    temp = 0;
    explosion_visible = false;
    explosion->reset();
}

Game::~Game() {
    delete bg;
    delete pepe;

    for (std::vector<TexRect*>::iterator it = snowballs.begin(); it != snowballs.end(); it++) {
        delete (*it);
    }

    for (std::vector<TexRect*>::iterator it = apples.begin(); it != apples.end(); it++) {
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