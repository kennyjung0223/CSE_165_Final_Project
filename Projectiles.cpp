#include "Projectiles.h"
#include <iostream>

Projectiles::Projectiles(const char* filename, float x, float y, float w, float h, int rand): TexRect(filename, x, y, w, h) {
    x_speed = ((rand % 10) / 1125.0) - 0.004;
    y_speed = ((rand % 10) / 4500.0) - 0.004;

    if (filename == "assets/snowball.png") {
        y_speed -= 0.002;
    }
}

void Projectiles::move() {
    x += x_speed;
    y += y_speed;
}