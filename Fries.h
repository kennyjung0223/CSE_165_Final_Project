#pragma once

#include "TexRect.h"

class Fries: public TexRect {
    float x_speed;
    float y_speed;

public:
    Fries();

    void move();
};