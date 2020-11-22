#pragma once

#include "TexRect.h"

class Projectiles: public TexRect {
    float x_speed;
    float y_speed;

public:
    Projectiles(const char*, float, float, float, float);

    void move();
};