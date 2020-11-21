#include "Pepe.h"

Pepe::Pepe(): TexRect("assets/pepe.png", 0, 0, 0.4, 0.4) {
    speed = 0.01;
}

float Pepe::get_speed() const {
    return speed;
}

void Pepe::increment_speed() {
    speed += 0.0025;
}

void Pepe::moveUp() {
	y += speed;
}

void Pepe::moveLeft() {
	x -= speed;
}

void Pepe::moveRight() {
	x += speed;
}

void Pepe::moveDown() {
	y -= speed;
}

void Pepe::idle() {
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