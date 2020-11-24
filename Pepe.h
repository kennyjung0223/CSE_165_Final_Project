#pragma once

#include "TexRect.h"

class Pepe: public TexRect {
    float speed;
    const float MAX_SPEED = 0.025;

public:
    Pepe();

    void moveUp();
    void moveLeft();
    void moveRight();
    void moveDown();

    float get_speed() const;
    float get_max_speed() const;
    void reset_speed();

    void increment_speed();

    void idle();

};