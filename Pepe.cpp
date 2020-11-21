#include "Pepe.h"

Pepe::Pepe(): TexRect("assets/pepe.png", 0, 0, 0.4, 0.4) {
    dx = 0;
    dy = 0;
    speed = 0.01;
}

void Pepe::key_up(unsigned char key) {
    if (key == 'w') {
        dy -= speed;
    }
    else if (key == 'a') {
        dx += speed;
    }
    else if (key == 's') {
        dy += speed;
    }
    else if (key == 'd') {
        dx -= speed;
    }
}

void Pepe::key_down(unsigned char key) {
    if (key == 'w') {
        dy += speed;
    }
    else if (key == 'a') {
        dx -= speed;
    }
    else if (key == 's') {
        dy -= speed;
    }
    else if (key == 'd') {
        dx += speed;
    }
}

float Pepe::get_speed() const {
    return speed;
}

void Pepe::increment_speed() {
    speed += 0.01;
}

void Pepe::idle() {
    x += dx;
    y += dy;

    if (x < -1) {
        x = -1;
    }
    else if (x + w > 1) {
        x = 1 - w;
    }
    else if (y > 1) {
        y = 1;
    }
    else if (y - h < -1) {
        y = -1 + h;
    }
}