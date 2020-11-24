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
    fainted_pepe = new TexRect("assets/pepe_f.png", -0.2, 0, 0.4, 0.4);

    starting_points.push_back(-0.6);
    starting_points.push_back(0.1);
    starting_points.push_back(0.6);

    home = true;
    gameover = false;

    score = 0;
    temp = 0;
    sb_quantity = 3;
    high_score = 0;
    i = 0;
}

int Game::get_high_score(int score) {
    if (score > high_score) {
        high_score = score;
    }
    return high_score;
}

void Game::draw() {
    bg->draw();
    if (home) {
        pepe->draw();

        renderText("Welcome to 'Save Pepe'", -0.3, -0.5, GLUT_BITMAP_HELVETICA_18, 0,0,0);
        renderText("Move Pepe using WASD keys and dodge snowballs", -0.7, -0.6, GLUT_BITMAP_HELVETICA_18, 0,0,0);
        renderText("Occassionally, rainbow apples will fall which boosts Pepe's speed", -0.8, -0.7, GLUT_BITMAP_HELVETICA_18, 0,0,0);
        renderText("Snowball fallen to ground = 1 point, rainbow apple = 3 points", -0.75, -0.8, GLUT_BITMAP_HELVETICA_18, 0,0,0);
        renderText("Press p to play", -0.2, -0.9, GLUT_BITMAP_HELVETICA_18, 0,0,0);
    }
    else if (!gameover) {
        pepe->draw();

        update();

        draw_snowballs();
        draw_apples();

        if (temp % 1000 == 0) {
            generate_apples();
        }

        if (temp % 75 == 0) {
            generate_snowballs();

            if (temp == 1050) {
                temp = 0;
            }
        }

        std::string s = std::to_string(pepe->get_speed());

        if (pepe->get_speed() == pepe->get_max_speed()) {
            renderText("Speed is now maxed", 0.45, -0.95, GLUT_BITMAP_HELVETICA_18, 0,0,0);
        }

        renderText("Score: " + std::to_string(score), -0.95, -0.95, GLUT_BITMAP_HELVETICA_18, 0,0,0);
        temp++;
    }
    else {
        explode();

        fainted_pepe->draw();
        renderText("Final Score: " + std::to_string(score), -0.17, -0.5, GLUT_BITMAP_HELVETICA_18, 0,0,0);
        renderText("High Score: " + std::to_string(get_high_score(score)), -0.17, -0.6, GLUT_BITMAP_HELVETICA_18, 0,0,0);
        renderText("Press r to restart", -0.2, -0.7, GLUT_BITMAP_HELVETICA_18, 0,0,0);
        renderText("Press esc to quit", -0.2, -0.8, GLUT_BITMAP_HELVETICA_18, 0,0,0);
    }
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
            else if ((*it)->getY() < -1 || (*it)->getX() + (*it)->getW() > 1 || (*it)->getX() < -1) {
                score++;
                snowballs.erase(it);
                check_threshold();
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
            else if ((*it)->getY() < -1 || (*it)->getX() + (*it)->getW() > 1 || (*it)->getX() < -1) {
                apples.erase(it);
                check_threshold();
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
    else if (home && key == 'p') {
        home = false;
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

int Game::score_threshold(int num) {
    return ((num + 1) * (num + 2)) / 2;
}

void Game::check_threshold() {
    if (score >= (score_threshold(i) * 100)) {
        i++;
        add_snowball();
    }    
}

void Game::generate_snowballs() {
    srand(time(0));

    for (int i = 0; i < sb_quantity; i++) {
        snowballs.push_back(new Projectiles("assets/snowball.png", starting_points[i], 1, 0.1, 0.1, rand()));
    }
}

void Game::generate_apples() {
    float arr[] = {-0.4, 0, 0.4};
    srand(time(0));

    for (int i = 0; i < A_QUANTITY; i++) {
        apples.push_back(new Projectiles("assets/apple.png", arr[i], 1, 0.125, 0.125, rand()));
    }
}

void Game::add_snowball() {
    srand(time(0));

    index = ((rand() % 10) / 5.625) - 0.8;
    starting_points.push_back(index);
    sb_quantity++;    
}

void Game::reset_sp() {
    for (int i = 3; i < sb_quantity; i++) {
        starting_points.pop_back();
    }

    sb_quantity = 3;
}

void Game::reset() {
    gameover = false;
    pepe->setX(-0.1);
    pepe->setY(-0.1);
    pepe->reset_speed();
    reset_sp();
    snowballs.clear();
    apples.clear();
    score = 0;
    temp = 0;
    explosion_visible = false;
    explosion->reset();
}

void Game::explode() {
    if (explosion_visible) {
        explosion->draw();
    }

    explosion->advance();

    if (explosion->isDone()) {
        explosion_visible = false;
    }
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